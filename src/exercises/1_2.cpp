#include <iostream>
// Nhap 2 so tu ban phim, hay dung toan tu dieu kien de in ra so be hon
int main() {
    int a,b;
    std::cout<<"Input first number: "<<std::endl;
    std::cin>>a;
    std::cout<<"Input second number: "<<std::endl;
    std::cin>>b;
    int min = (a > b) ? b : a;
    int max = (a > b) ? a : b;
    std::cout<<"Min number is " << min <<std::endl;
    return 0;
}
