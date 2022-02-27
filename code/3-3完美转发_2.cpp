
#include <iostream>

using namespace std;

namespace _nmsp1 {
// void funcLast1(int v1, int v2)
void funcLast2(int v1, int& v2) {
    ++v2;  //改变v2的值，让其自增1
    cout << v1 + v2 << endl;
}

void funcLast3(int&& v1, int& v2) {
    cout << v1 << endl;
    cout << v2 << endl;
}

//函数模板（跳板函数）：把收到的参数以及这些参数相对应的类型不变的转发给其他函数（完美转发）
template <typename F, typename T1, typename T2>
// void funcMiddle_Temp1(F f, T1 t1, T2 t2) //f:函数指针类型void(*)(int,int)，而funcLast是函数类型void(int,int)
void funcMiddle2(F f, T1&& t1, T2&& t2) {
    // f(t1, t2);
    f(
        std::forward<T1>(t1),  // T1 = int
        std::forward<T2>(t2)   // T2 = int &
    );
}

}  // namespace _nmsp1

namespace _nmsp2 {
void printInfo(int& t) {
    cout << "printInfo()参数类型为左值引用" << endl;
}

void printInfo(int&& t) {
    cout << "printInfo()参数类型为右值引用" << endl;
}

void printInfo(const int& t) {
    cout << "printInfo()参数类型为const 左值引用" << endl;
}

template <typename T>
void TestF(T&& t) {
    printInfo(std::forward<T>(t));
}

}  // namespace _nmsp2

namespace _nmsp3 {
int getData() {
    return 3;
}

void funcLast(int v1) {
    cout << "v1=" << v1 << endl;
}

void funcMiddle() {
    auto&& result = getData();  // getData返回的是右值，所以auto = int ,result = int &&（右值引用）
    //....对result做各种运算。
    funcLast(std::forward<decltype(result)>(result));
}

}  // namespace _nmsp3

int main() {
    //第三节 完美转发
    //（2）std::forward ：C++11中专门为转发而存在的函数。这个函数要么返回一个左值，要么返回一个右值。
    //万能引用类型才是forward能够发挥作用的重要条件。forward能够转化回原来该实参的左值或者右值性。
    //(a)实参原来是个左值j，到了形参中还是左值t2。forward之后还是个左值。
    //(b)实参原来是个右值20，到了形参中变成了左值t1。forward之后还是个右值。
    // forward这个函数有强制把左值转换成右值的能力。所以forward这个函数只对原来是个右值这种情况有用。
    // forward的能力：保持原始实参的左值性或者右值性，解决了参数转发的问题。
    int j = 70;
    _nmsp1::funcLast3(20, j);  // 20,70
    _nmsp1::funcMiddle2(_nmsp1::funcLast3, 20, j);

    _nmsp2::TestF(1);  // printInfo()参数类型为右值引用
    int i = 5;
    _nmsp2::TestF(i);             // printInfo()参数类型为左值引用
    _nmsp2::TestF(std::move(i));  // printInfo()参数类型为右值引用     ----std::move能够将左值转换成右值。
    const int j = 8;
    _nmsp2::TestF(j);        // printInfo()参数类型为const 左值引用   ------j是个const左值
    _nmsp2::TestF(int(12));  // printInfo()参数类型为右值引用 ----int(12)是个临时对象，是个右值。
    int&& tempvalue = 16;
    _nmsp2::TestF(tempvalue);  // printInfo()参数类型为左值引用

    //（3）普通参数的完美转发:auto &&
    _nmsp3::funcLast(_nmsp3::getData());

    _nmsp3::funcMiddle();

    return 0;
}
