#include <iostream>
#include <cstdint>
#include <sys/types.h>

int main() {
    std::cout<<"Hello, World!"<<std::endl;
    int a = 5;
    int *b = &a;
    int *c = b + 1;
    std::cout<<"Hello b which leave in "<<b<<" and have value is "<<a<<"and have size of "<<sizeof(b)<<std::endl;
    std::cout<<"Hello b+1 which leave in "<<c<<" and have value is "<<*c<<"and have size of "<<sizeof(c)<<std::endl;
    std::cout<<"So all the pointer a the same and have the size of 8 in 64-bit cpu? let me create some void pointer?"<<std::endl;
    void *void_ptr = b;
    std::cout<<"So basicly, void ptr is "<<*(double*)void_ptr<<std::endl;
    //Interesting! so i cant not directly use the void_ptr except cast it first! 
    //i cant not dereference the ptr: *void_ptr. but what is the diffirence
    //if i cast it to int, char, double ?
    std::cout<<"The value dereference of &a is "<<(int *)&a<<std::endl;
    //this is i assume a kind of casting ! its tell the cpu read this memory in int* 
    //also you can tell cpu read the void_ptr what ever you want! 
    //but why people do that? like what is the benefit of create a pointer that
    //dont know what kind is it? i mean, maybe the dev expect that it will be use 
    //in many form? i still dont know the idea here! ok, maybe some function that actually use void
    //for example : void StreamBuffers(void* buffer) ? like this ? maybe some kind of interface ?

    std::cout<<"We can read binary of a with value is "<<(int)*(uint8_t*)&a << "the following steps."<<std::endl;
    bool big_endian = true;
    int edian_check = 1;
    uint8_t* edian_address = (uint8_t*)&edian_check;
    uint8_t* a_byte_address = (uint8_t*)&a;

    for(int i=0; i < sizeof(int); i++) {
        std::cout<<(int)*(a_byte_address + i)<<" ";
    }
    if((int)*(edian_address) > 0) {
        big_endian = false;
    }
    std::cout<<"This is " << (big_endian ? "Big endian" : "Little endian");

    //ok trong đại dương các switch điện tử đó, có cực nhiều các swtich được nối
    //liền nhau 010101.... và chúng ta có thể chia các kiểu 01010... đó ra thành
    //các block 4 bit hay 8 bit? việc gán data cũng chỉ là việc set switch về trạng
    //thái 0 hay 1!  và rằng cpu sẽ quy định mỗi địa chỉ chiêm bao nhiêu vùng nhớ?
    //ví dụ kiến trúc cpu 64 bit thường là mỗi địa chir 1 vùng nhớ 8bit! ? và rằng
    //ta cast sang unit_8* chỉ có ý nghĩa ở cpu 64 bit (có thể 1 số k phải 8 bit nhưng
    // hầu hết). ta cast như vậy để có thể lấy đuọc chinh xác các số 010101... , 
    // điều này giúp cpu đọc lại hay dereference đúng giá trị binary! hay raw-data! . 
    return 0;
}
