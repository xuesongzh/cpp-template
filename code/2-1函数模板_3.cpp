
#include <functional>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

#pragma warning(disable : 4996)

namespace _nmsp1 {
//普通函数
int mf(int tmp1, int tmp2) {
    return 1;
}
int mf2(int tmp1, int tmp2) {
    return 10;
}

typedef int (*FunType)(int, int);  //函数指针类型定义

template <typename T, typename F = FunType>
void testfunc(T i, T j, F funcpoint = mf) {
    cout << funcpoint(i, j) << endl;
}

template <typename T = int, typename U>
void testfunc2(U m) {
    T tmpvalue = m;
    cout << tmpvalue << endl;
}

}  // namespace _nmsp1

namespace _nmsp2 {
// template <typename T, typename U, int val = 100>
template <typename T, typename U, auto val = 100>  // C++17
auto Add(T tv1, U tv2) {
    return tv1 + tv2 + val;
}

template <double *p>
void mft() {
    cout << "mft()执行了" << endl;
}
double g_d = 1.3;  //全局量

/*
    （7.2）比较奇怪的语法
     a)不管类型还是非类型模板参数，如果代码中没有用到，则参数名可以省略。
     b)类型前面可以增加一个typename修饰以明确标识一个类型，一般跟模板有关的类型名前面是需要typename
*/

// template <typename T,int value>
// template <typename, int>
template <typename T, typename int value>
auto Add2() {
    return 100;
}
}  // namespace _nmsp2

int main() {
    //六：缺省参数
    _nmsp1::testfunc(15, 16);
    _nmsp1::testfunc(15, 16, _nmsp1::mf2);
    _nmsp1::testfunc2(12);

    /*
    七：非类型模板参数
    （7.1）基本概念
    前面的函数模板涉及到的 模板参数都是 “类型 模板参数”需要用typename(class)来修饰。
    模板参数还可以是 “非类型 模板参数（普通的参数）”
    c++17开始，支持非类型模板参数为auto类型。
    */
    cout << _nmsp2::Add<float, float>(22.3f, 11.8f) << endl;
    cout << _nmsp2::Add<float, float, 800>(22.3f, 11.8f) << endl;

    // 指定非类型模板参数的值时，一般给的都是常量。因为编译器在编译的时候就要能够确定非类型模板参数的值。
    // int k = 1000;
    // cout << _nmsp2::Add<float, float, k>(22.3f, 11.8f) << endl;

    /*
    并不是任何类型的参数都可以作为非类型模板参数。
    int类型可以，但double,float或者类类型string等等可能就不可以，不过double *这种指针类型可以。
    一般允许做非类型模板参数的类型如下：可能不断增加
        a)整型或者枚举型；
        b)指针类型；
        c)左值引用类型；
        d)auto或者decltype(auto);
        e)可能还有其他类型，请自行总结。
    */
    _nmsp2::mft<&_nmsp2::g_d>();

    cout << _nmsp2::Add2<int, 45>() << endl;
}
