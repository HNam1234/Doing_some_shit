// https://cppdeveloper.com/c-nang-cao/data-alignment-trong-c-c/
//  bình thường tao nhìn memory , tao nghĩ nó là sự sắp xếp liên tiếp của các byte!
//  ví dụ1 : Data (bytes)              1    2    3    4
//          Address                  0x00 0x01 0x02 0x03
//  Nhưng cpu méo nhìn như vậy, nó nhìn data theo từng block ví dụ cpu nhìn 1 block là 4 bytes (4 bytes ở trong trường hợp giả sử này, thực tế cpu có thể đọc các loại 1 bytes, 2,8,16bytes...)
//  ví dụ2 : Data (bytes)              1    2    3    4
//          Address                  0x00 0x04 0x08 0x012

// basicaly, ví cpu nhìn 1 block là 4 byte đọc 4 bytes trong ví dụ 1, nhưng đọc từ địa chỉ 0x01, vậy nó phải đọc 2 lần, đọc
// 1 block đầu từ 0x00, lấy data từ 0x01,0x02, 0x03, đọc block thứ 2, lấy data ở 0x04. và sau đó ghép chúng lại để đọc 4 bytes.
// quá trình này quá ngu lz nên anh zai lập trình đã quyết định thêm cơ chế padding để cpu luôn đọc từ đầu 1 block! hay gọi là
// alligned address! chứ méo phải từ địa chỉ lửng lơ như ví dụ trên! Việc này là do trình biên dịch nếu thấy mày tạo 1 struct
// ko đủ bytes để tạo thành 1 số nguyên lần block, nó tự thêm vào đuôi để fit với n lần block luôn.

/***
 * Câu hỏi: tại sao lệnh đọc 2 byte ở địa chỉ lẻ lại gây ra hardfault : ví dụ  tại sao struct test{char a; short b;} phải nhét 1 padding vào giữa
 * // ví dụ2 : Data (bytes)              a    padding     b     b
 *             Address                  0x00   0x01      0x02  0x03
 *
 * Câu trả lời:
 * Trên con NXP1176 (kiến trúc 32-bit), đường truyền dữ liệu từ RAM vào CPU có độ rộng đúng 32 sợi dây điện (tương đương 4 byte). Người ta chia nó làm 4 làn cố định:

Làn 0: Đọc/Ghi byte ở địa chỉ 0x00, 0x04, 0x08...

Làn 1: Đọc/Ghi byte ở địa chỉ 0x01, 0x05, 0x09...

Làn 2: Đọc/Ghi byte ở địa chỉ 0x02, 0x06, 0x0A...

Làn 3: Đọc/Ghi byte ở địa chỉ 0x03, 0x07, 0x0B...

2. Sự "Hợp rơ" của lệnh đọc chẵn (Aligned Access)
Khi ông dùng con trỏ short* trỏ vào địa chỉ 0x00 (hoặc 0x02) và yêu cầu đọc 2 byte, CPU gọi lệnh LDRH (Load Halfword).

Ở địa chỉ 0x00: Phần cứng mở cổng cho Làn 0 và Làn 1 chạy thẳng vào thanh ghi (Register) của CPU.

Ở địa chỉ 0x02: Phần cứng mở cổng cho Làn 2 và Làn 3 chạy thẳng vào thanh ghi.
👉 Các cổng logic (Multiplexer - MUX) bên trong CPU đã được hàn cứng (hardwired) để làm việc này trong đúng 1 chu kỳ đồng hồ. Cực kỳ mượt!

3. Tại sao địa chỉ lẻ (0x01) lại làm phần cứng "phát điên"?
Bây giờ, ông ép CPU đọc lệnh LDRH từ địa chỉ 0x01.
Tức là ông đang yêu cầu nó lấy 1 byte từ Làn 1 và 1 byte từ Làn 2.

Vấn đề vật lý nảy sinh:
Bên trong CPU, tập lệnh LDRH không có sẵn mạng lưới dây điện (MUX) để "vắt ngang" lấy dữ liệu từ Làn 1 và Làn 2 cùng lúc rồi ghép lại cho khớp vào thanh ghi một cách tức thời.
Để làm được việc đó, chip sẽ phải thiết kế thêm rất nhiều cổng logic phức tạp. ARM (bọn thiết kế lõi chip) đã tính toán và thấy rằng: Nếu hỗ trợ đọc vắt ngang cho mọi lệnh,
 con chip sẽ tốn thêm hàng triệu transistor, tốn điện hơn, tỏa nhiệt nhiều hơn, và làm chậm tốc độ tổng thể của toàn hệ thống.

Như vậy kết luận rằng thằng Compiler cũng chỉ làm để vừa lòng thằng khó tính hardware, tránh đội chi phí k cần thiết
*/
#include <iostream>

struct Car
{
    int speed;
    char brand[20];
    double price;
    const int wheel = 4;
};

struct Bike
{
    int speed;
    char brand[20];
    double price;
};

struct Garage
{
    Car redCar;
    Bike blueBike;
};

struct B
{
    char a;
    double b;
    char c;
};


struct Dog
{
    char name[20];
    double weight;
    int Bark();
};
int Dog::Bark()
{
    std::cout << "GAU GAU" << std::endl;
    return 1;
};

int main()
{
    Car myCar;
    Bike myBike;
    Garage myGarage;
    std::cout << "Struct Car size is : " << sizeof(myCar) << std::endl;
    // Ok tao đang đoán và tính tổng struct của Car tại sao là 36 trong khi in ra là 40. tao luôn được dạy là struct size phải chia hết
    // cho phần tử lớn nhất (ở đây là double - 8) nhưng tại sao ?
    // Ok theo tao investigate thì cpu chỉ đọc double theo các địa chỉ chia hết cho nó, ở đây là 0,8,16,... chứ k phải 1,2,3,10,...
    // Cái thứ 2 là, để tránh trường hợp Car myCar[2] thì allignment luôn chuẩn để đọc được double.
    // Ok vậy thể có vẻ dễ rồi, tao sẽ tính lần lượt các struct bike và garage nhé:
    // Bike là : 32, Garage là :32 + 40 = 72 , padding lên để chia hết cho 40 là 80.
    std::cout << "Struct Bike size is : " << sizeof(myBike) << std::endl;
    std::cout << "Struct Garage size is : " << sizeof(myGarage) << std::endl;
    // Hmm Intersting! thế nào mà Garage lại có size là 72 ???? có thể là phần tử lớn nhất chỉ tính primitive type thôi?
    // Ở đây là 8?! yes, tao đoán chắc là như vậy vì cpu đâu có đọc theo từng struct custom đâu!- Yes, Its true!

    // Ok tao cần mày tính size của struct B = 1 + 8 + 1 = 10, chia hết cho 8 = 16 đúng k ?
    // Sai nhé! Struct B được tính như sau :
    /**
     *  offset 0      : a
        offset 1..7   : padding
        offset 8..15  : b
        offset 16     : c
        offset 17..23 : trailing padding
     */
    // Luôn nhớ struct off set bắt đầu từ 0.
    // Vậy tổng là 24 nhé . Nguyên nhân bởi vì cpu k thể đọc được double có địa chỉ ko chia hết cho 8. nên phải thêm padding! vậy việc sắp xếp class
    // tưởng chừng như vô nghĩa nhưng thực sự tối ưu khá nhiều đó!
    std::cout << "Struct B size is : " << sizeof(B) << std::endl;
    // Tao có thể tạo 1 hàm trong struct k ?
    Dog myDog;
    myDog.Bark();
    // Ok i can! nhuwng bây giờ sizeof struct này là bao nhiêu ? - Tao đoán void Bark là 1 function pointer. nó thường có giá trị là 8.
    // Vậy size of Dog sẽ là 20 + 4 padding + 8 + 8 = 40.
    std::cout << "Struct Dog size is : " << sizeof(myDog) << std::endl;
    // Hmm size của dog là 32. vậy thì void size sẽ là 0 ở trong struct! vậy nếu return int thì sao ? -  Vẫn là 32 ! tại sao ?
    // Có vẻ như là hàm bark không nằm trong từng object Dog mà nằm ở vùng ext/code segment nên k chiếm bộ nhớ.
    return 0;
}