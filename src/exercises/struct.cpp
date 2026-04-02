//https://cppdeveloper.com/c-nang-cao/data-alignment-trong-c-c/
// bình thường tao nhìn memory , tao nghĩ nó là sự sắp xếp liên tiếp của các byte! 
// ví dụ1 : Data (bytes)              1    2    3    4
//         Address                  0x00 0x01 0x02 0x03
// Nhưng cpu méo nhìn như vậy, nó nhìn data theo từng block ví dụ cpu nhìn 1 block là 4 bytes
// ví dụ2 : Data (bytes)              1    2    3    4
//         Address                  0x00 0x04 0x08 0x012

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
Để làm được việc đó, chip sẽ phải thiết kế thêm rất nhiều cổng logic phức tạp. ARM (bọn thiết kế lõi chip) đã tính toán và thấy rằng: Nếu hỗ trợ đọc vắt ngang cho mọi lệnh, con chip sẽ tốn thêm hàng triệu transistor, tốn điện hơn, tỏa nhiệt nhiều hơn, và làm chậm tốc độ tổng thể của toàn hệ thống.

Như vậy kết luận rằng thằng Compiler cũng chỉ làm để vừa lòng thằng khó tính hardware, tránh đội chi phí k cần thiết
*/
#include <iostream>

int main() {
    std::cout<< "Hello, World!" << std::endl;
    return 0;
}