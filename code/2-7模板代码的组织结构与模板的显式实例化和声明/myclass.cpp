
#include "myclass.h"

#include <iostream>

using namespace std;

//类实现
void MyClass::func() {
    std::cout << "MYClass::func成员函数执行了!" << endl;
}

template <typename T>
void MYClass<T>::func() {
    std::cout << "MYClass::func成员函数执行了!" << endl;
}