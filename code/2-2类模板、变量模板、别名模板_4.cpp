﻿
#include <iostream>

using namespace std;

namespace _nmsp1 {
template <typename T1>
class A {
 public:
    template <typename T2>
    A(T2 v1, T2 v2);  //构造函数模板，引入了自己的模板参数T2，与类A的模板参数T1没有关系

 public:
    A(double v1, double v2) {
        cout << "A::A(double,double)执行了!" << endl;
    }
    A(T1 v1, T1 v2) {
        cout << "A::A(T1,T1)执行了!" << endl;
    }

 public:
    //拷贝构造函数模板
    template <typename U>
    A(const A<U>& other) {
        cout << "A::A(const A<U>& other)拷贝构造函数模板执行了!" << endl;
    }

    //拷贝赋值运算符模板
    template <typename U>
    A<T1>& operator=(const A<U>& other) {
        cout << "operator=(const A<U>& other)拷贝赋值运算符模板执行了!" << endl;
        return *this;
    }

    //拷贝赋值运算符
    A<T1>& operator=(const A<T1>& other) {
        cout << "operator=(const A<T1>& other)拷贝赋值运算符执行了!" << endl;
        return *this;
    }

    //不支持虚成员函数模板
    /*template <typename T4>
    virtual void myvirfunc() {}*/
    virtual void myvirfunc2() {}

    //----------------------------------
    template <typename T3>
    void myft(T3 tmpt) {  //普通成员函数模板
        cout << tmpt << endl;
    }

    T1 m_ic;
    static constexpr int m_stcvalue = 200;
};

//在类外实现类模板的构造函数模板
template <typename T1>
template <typename T2>
A<T1>::A(T2 v1, T2 v2) {
    cout << "A::A(T2,T2)执行了!" << endl;
}

}  // namespace _nmsp1

int main() {
    //六：成员函数模板
    //（6.1）基本概念、构造函数模板
    // a)类模板中的成员函数，只有源程序代码中出现调用这些成员函数的代码时，这些成员函数才会出现在一个实例化了的类模板中。
    // b)类模板中的成员函数模板，只有源程序代码中出现调用这些成员函数模板的代码时，这些成员函数模板的具体实例才会出现在一个实例化了的类模板中。
    // c)目前编译器并不支持虚成员函数模板，因为虚函数表vtbl的大小是固定的。
    // 如果允许虚函数模板，则每次有人用新的参数类型调用该虚函数模板时，就必须给对应的虚函数表再增加一项，这意味着
    // 只有链接程序才能去构造虚函数表并在表中设置有关函数，因此成员函数模板绝不能是虚的。
    //类模板中可以有普通的虚成员函数（虚函数），这并没有什么问题。
    // 普通成员函数如果不被调用的情况下不会被实例化出来。但是，对于虚函数，不管是否调用，编译器都会把他实例化出来。
    // 因为编译器要创建虚函数表vtbl，该表中的每个具体表项都对应一个虚函数地址，所以编译器必然得把所有虚函数都实例化出来。
    _nmsp1::A<float> a(1, 2);           //实例化了A<float>这样一个类型，并用int类型来实例化构造函数
    a.myft(3);                          // 3
    _nmsp1::A<float> a2(1.1, 2.2);      // A<float>类型已经被上面的代码实例化过了，并用doule类型来实例化构造函数，因为1.1和2.2都是double类型
    _nmsp1::A<float> a3(11.1f, 12.2f);  //用float类型来实例化构造函数，因为11.1f和12.2f都是float类型

    //（6.2）拷贝构造函数模板与拷贝赋值运算符模板
    //拷贝构造函数模板不是拷贝构造函数，拷贝赋值运算符模板不是拷贝赋值运算符（构造函数模板也不是构造函数）
    //因为拷贝构造函数或者拷贝赋值运算符要求拷贝的对象类型完全相同，而拷贝构造函数模板和拷贝赋值运算符模板就没有这种要求。

    // a3,a4类型相同（A<float>），本该执行拷贝构造函数，但是因为类模板A中没有拷贝构造函数，
    // 所以编译器内部实际是执行了按值拷贝的一个动作，使a4.m_ic值变成了16.2了。
    //拷贝构造函数模板永远不可能成为拷贝构造函数。编译器不会用调用拷贝构造函数模板来代替调用拷贝构造函数。
    a3.m_ic = 16.2f;
    _nmsp1::A<float> a4(a3);  //不会执行拷贝构造函数模板中的代码

    //拷贝构造函数模板什么时候被调用？
    //类型不同（都是用类模板A实例化出来的，比如A<double>与A<float>）的两个对象，用一个拷贝构造另一个时。
    _nmsp1::A<int> a5(a3);  // a3是A<float>类型，a5是A<int>类型，两者类型不同

    //拷贝赋值运算符模板永远不可能成为拷贝赋值运算符
    a3 = a4;
    a3 = a5;

    return 0;
}
