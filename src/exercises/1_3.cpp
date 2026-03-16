#include <iostream>

// doc tu ban phim 4 so thuc trong khoang [-3;3] tinh tong trung binh cua 4 so do, in ket qua len man hinh
int main() {
    double a,b,c,d;
    double sum = 0;
    int dem = 0;

    std::cout << "Nhap 4 gia tri trong khoang [-3;3]"<<std::endl;
    std::cin>>a>>b>>c>>d;
    if(a > -3 && a <= 3) {
        dem++;
        sum = sum + a;
    }
    if(b > -3 && b <= 3) {
        dem++;
        sum = sum + b;
    }
    if(c > -3 && c <= 3) {
        dem++;
        sum = sum + c;
    }
    if(d > -3 && d <= 3) {
        dem++;
        sum = sum + d;
    }
    std::cout << "Tong 4 so la: " <<sum<<std::endl;
    std::cout << "trung binh cong "<<dem<< " so la: "<< (float)sum/dem <<std::endl; 
    return 0;
}
