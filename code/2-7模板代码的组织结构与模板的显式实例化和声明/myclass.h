#ifndef __MYCLASS_H__
#define __MYCLASS_H__

#include <iostream>

// 类定义
class MyClass {
 public:
    void func();
};

//类模板的定义
template <typename T>
class MYClass {
 public:
    void func();
};

//类模板的实现
template <typename T>
void MYClass<T>::func() {
    std::cout << "MYClass::func成员函数执行了!" << std::endl;
}

//特化版本的MYClass可以放在这里
template <>
class MYClass<int> {
 public:
    void func();
};

// template <> //不要加这行
void MYClass<int>::func() {
    std::cout << "MYClass<int>::func成员函数执行了!" << std::endl;
}

#endif
