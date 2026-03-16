#include <iostream>
#include <cstdint>
#include <vector>

// Viet chuong trinh cho so nguyen a = 23, dich trai 1 bit roi 2 bit, sau do dich phai 1 bit roi 2 bit.
int main() {
    int a = 23;
    std::cout << "so nguyen a co gia tri la " << a << std::endl;
    a = a << 1;
    std::cout << "tien hanh dich trai 1 bit: " << a << std::endl;
    a= a << 2;
    std::cout << "tien hanh dich trai 2 bit: " << a << std::endl;
    a = a >> 1;
    std::cout << "tien hanh dich phai 1 bit: " << a << std::endl;
    a= a >> 2;
    std::cout << "tien hanh dich phai 2 bit: " << a << std::endl;
    return 0;
}
