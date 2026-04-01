// https://www.reddit.com/r/cs2a/comments/1h4h2nc/whats_the_difference_between_heap_and_stack_in_c/
///https://freedium-mirror.cfd/https://medium.com/@sofiasondh/what-is-the-difference-between-new-and-malloc-160c0f38f45f
// https://www.laptrinhdientu.com/2023/11/cpp-dangling-pointer.html

#include <iostream>
#include <cstdlib>
class Car{
    public:
        int max_speed;
        std::string brand;
    public:
        void Run() {
            std::cout<<"Car " << brand <<" VROOM VROOM!! at " << max_speed << std::endl;
        }
};

double averageTwoNumber(int a, int b) {
    //average will create in stack here and automaticaly free when out of this scope
    double average = (double)(a+b)/2;
    return average;
}
int main() {
    std::cout<<"Hello World!"<<std::endl;
    int a = 5;
    //this create in stack of main
    double average = averageTwoNumber(a,10);
    std::cout<<"Average of "<<a<<" and "<<10<<" is : " << average <<std::endl;

    //now we create some variable in heap:
    int* c = new int;
    Car* myCar = new Car;
    // is this basicaly we create a memory of int ? what if we just read that mem without init it ?
    std::cout<<"Memory of heap memory of int(primitive) that not init yet is : "<<*c<<std::endl;
    std::cout<<"Memory of heap memory of class Car that not init yet is : "<<(int)((Car*)myCar)->max_speed<<std::endl;
    //so baicaly we have to init it with() the value is 0?
    int* d = new int();
    Car* herCar = new Car();
    std::cout<<"Memory of heap memory of int(primitive) that init with defalut () : "<<*d<<std::endl;
    std::cout<<"Memory of heap memory of class Car that init with default value which is call constructor : "<<(int)(Car*)herCar->max_speed<<std::endl;
    //Hmm intersting! so primitive is init with 0 when using () but not a custom class so basicaly class just call the constructor??
    //Lets just create a constructor for car and it actually call the constructor!
    //so basicly use new with type ex: int, Car, its just create a memory. but add int(), Car(), it create or call
    //the init value of contructor or 0 with primitive
    delete c;
    c = nullptr;
    delete myCar;
    // What about malloc ? why use new over malloc ? lets take a look and create a memory using malloc
    int *arr = (int*)malloc(sizeof(int)*10);
    for(int i = 0; i < 10; i++) {
        arr[i] = 0;
        std::cout<<"The arr["<<i<<"] is : "<<arr[i]<<" "<<std::endl;
    }
    //so basicly this equal to int* arr = new int[10]; ? what is the different ?
    //Lets try some dangling pointer!
    std::cout<<"My car speed which is dangling pointer is "<<myCar->max_speed<<std::endl;
    std::cout<<"Her car speed which is not dangling pointer is "<<herCar->max_speed<<std::endl;
    //expect crash here
    std::cout<<"Pointer value after delete and assign to nullptr is : "<<*c<<std::endl;
    /// Some question test knowledge
    /***
     * ❓ Câu 1
        int* p = new int(10);
        int* q = p;

        delete q;
        std::cout << *p << std::endl;

        👉 Hỏi:

        p là gì sau delete?
        bug gì?
        câu 1 : p là dangling pointer, bug cố truy cập vào 1 dangling pointer để lấy giá trị p , sẽ in ra giá trị rác undefined.
        ❓ Câu 2
        int* p = new int(10);
        delete p;

        if (p) {
            std::cout << "valid\n";
        }

        👉 Hỏi:

        if (p) có đáng tin không?
        vì sao?
        câu 2 : if (p) không hề đáng tin vì ko thể đoán đưuọc gái trị của 1 con trỏ giá trị bao nhiêu khi đã trỏ đến 1 vùng nhớ đã được giải phóng. 
        ❓ Câu 3
        int* p = new int(10);
        int* q = p;

        delete p;
        q = nullptr;

        👉 Hỏi:

        có bug không?
        vùng nhớ đã được xử lý đúng chưa?
        câu 3 : ko có bug nhưng nên gán nốt p thành nullptr vì hiện tại nó đang có giá trị undefined
        ❓ Câu 4
        int* p = new int(10);
        int* q = new int(20);

        p = q;

        👉 Hỏi:

        bug gì?
        vùng nhớ nào bị ảnh hưởng?
        câu 4 : bug: mem leak, vùng nhớ int 10 sẽ k có con trỏ nào quản lý nó
        
        ❓ Câu 5
        int* p = new int(10);
        int* q = p;

        delete p;
        delete q;

        👉 Hỏi:

        bug gì?
        vì sao nguy hiểm?
        câu 5 : bug free 1 vùng nhớ 2 lần! nguy hiểm ở chỗ nào thì k biết nhưng  chắc chắn nguy hiểm
     ***/
}