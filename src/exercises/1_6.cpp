#include <iostream>
#include <cstdint>
#include <vector>

// Doc tu ban phim 3 so thuc, hay xem 3 so do co tao thanh 3 canh cua tam giac, 3 canh cua tam giac deu, tam giac can hay tam giac vuong?
int main() {
    float a,b,c;
    std::cout<<"Nhap 3 so thuc: "<<std::endl;
    std::cin>>a>>b>>c;
    if(a <= 0 || b <= 0 || c <= 0) 
    {
        std::cout<<"Invalid params"<<std::endl;
        return 0;
    }
    if(a+b<=c || a+c<=b || b+c<=a)
    {
        std::cout<<"Ko the tao thanh 1 tam giac"<<std::endl;
        return 0;
    }
    std::cout<<"3 so thuc tao thanh tam giac";
    if(a*a + b*b == c*c || a*a + c*c == b*b || b*b + c*c == a*a)
    {
        std::cout<<" vuong";
    }
    if (a == b && b == c && c == a)
    {
        std::cout<<" deu";
    }
    else if(a == b || b == c || c == a)
    {
        std::cout<<" can";
    }
    return 0;
}
