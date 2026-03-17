#include <iostream>
#include <cstdint>
#include <vector>

// Viet chuong trinh thuc hien tinh thue thu nhap ca nhan theo cac gia tri sau:
// Thu nhap <10m, ko can dong thue, thu nhap tu 11-16m, dong thue 0.005 cua thu nhap, 
// thu nhap tu 16-35 thi dong thue 0.01, thu nhap 35-40m thi dong thue 0.03, con lai la 0.045
int main() {
    double income,tax;
    std::cout<<"Input your income(milion dong)"<<std::endl;
    std::cin>>income;
    if(income <= 0)
    {
        std::cout<<"Invalid income"<<std::endl;
        return 0;
    }
    if(income > 0 && income <= 10)
    {
        tax = 0;
    }
    else if (income > 10 && income <= 16) 
    {
        tax = income * 0.005 * 1000000;
    }
    else if (income > 16 && income <= 35) 
    {
        tax = income * 0.01 * 1000000;
    }
    else if (income > 35 && income <= 40) 
    {
        tax = income * 0.03 * 1000000;
    }
    else if (income > 40) 
    {
        tax = income * 0.045 * 1000000;
    }
    std::cout<<"With income is "<<income<<" milion dong, you have to pay amount of tax is "<<tax<<" dong"<<std::endl;
    return 0;
}
