#include <iostream>
#include <cstdint>
#include <vector>

// Viet chuong trinh giai bat phuong trinh bac nhat mot an ax + b > 0 voi a#0
int main() {
    double a,b;
    std::cout<<"Nhap cac he so a va b"<<std::endl;
    std::cin>>a>>b;
    if(a == 0){
        std::cout<<"Invalid a. a cant be zero"<<std::endl;
        return 0;
    }
    std::cout<<"Nghiem cua phuong trinh la"<<-a/b<<std::endl;
    return 0;  
}
