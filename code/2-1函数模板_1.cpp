﻿
#include <iostream>

using namespace std;

namespace _nmsp1 {
/*
int Sub(int tv1, int tv2) {
        return tv1 - tv2;
}

float Sub(float tv1, float tv2) {
        return tv1 - tv2;
}
*/

// template <typename T>  //T:称为 类型模板参数，代表的是一个类型。
template <class T>  // class 可以取代typename，但是这里的class并没有“类”
T Sub(T tv1, T tv2) {
    return tv1 - tv2;
}

// template <typename T,typename U,typename V>
// template < typename V,typename T, typename U>
// V Add(T tv1, U tv2)

template <typename T, typename U>
// auto Add(T tv1, U tv2) //auto用于表达推导返回值类型的含义。
auto Add(T tv1, U tv2) -> decltype(tv1 + tv2) {
    //返回类型后置语法，这里的auto只是返回类型后置语法的组成部分，并没有类型推导的含义
    return tv1 + tv2;
}

template <typename T>
T mydouble(T tmpvalue) {
    return tmpvalue * 2;
}

double mydouble(double tmpvalue) {
    return tmpvalue * 2;
}
}  // namespace _nmsp1

int main() {
    /*
        一：基本范例
        a)模板的定义是以template关键字开头。
        b)类型模板参数T前面用typename来修饰，所以遇到typename就该知道其后面跟的是一个类型。
        typename可以被class取代，但此处的class并没有“类”
        c)类型模板参数T（代表是一个类型）以及前面的修饰符typename/class都用<>括起来
        d)T这个名字可以换成任意其他标识符，对程序没有影响。用T只是一种编程习惯。

        二：实例化
        实例化：编译时，用具体的“类型”代替“类型模板参数”的过程就叫做实例化（有人也叫代码生成器）。
        .obj文件在编译完成后就会产生
        .obj文件的格式一般会被认为是一种COFF——通用对象文件格式（Common Object File Format）。
        int  Sub<int>(int,int)
        double Sub<double>(double,double)

        实例化之后的函数名分别叫做Sub<int>和Sub<double>
        通过函数模板实例化之后的函数名包含三部分：
        a)模板名；b)后面跟着一对<>；c)<>中间是一个具体类型。

        在编译阶段，编译器就会查看函数模板的 函数体 部分，来确定能否针对该类型string进行Sub函数模板的实例化。
        在编译阶段，编译器需要能够找到函数模板的函数体部分。

        三：模板参数的推断
        （3.1）常规的参数推断
        通过<>可以只指定一部分模板参数的类型，另外一部分模板参数的类型可以通过调用时给的实参来推断。
        auto代替函数模板返回类型
        decltype,可以与auto结合使用来构成返回类型后置语法。
        这种后置语法其实也就是使用auto和decltype结合来完成返回值类型的推导。
        （3.2）各种推断的比较以及空模板参数列表的推断
        a)自动推断
        b)指定类型模板参数，优先级比自动推断高
        c)指定空模板参数列表<>：作用就是 请调用mydouble函数模板而不是调用普通的mydouble函数。
    */

    int subv = _nmsp1::Sub(3, 5);
    int subv = _nmsp1::Sub(double(3), 5.9);  //强制类型转换可以
    double subv = _nmsp1::Sub<double>(3, 5.9);
    cout << "subv=" << subv << endl;

    double subv2 = _nmsp1::Sub(4.7, 2.1);
    cout << "subv2=" << subv2 << endl;

    string a("abc"), b("def");
    string addresult = _nmsp1::Sub(a, b);
    /*
        cout << _nmsp1::Add(15, 17.8) << endl;
        cout << _nmsp1::Add<..., ..., double>(15, 17.8) << endl;
        cout << _nmsp1::Add<int, double, double>(15, 17.8) << endl;
        cout << _nmsp1::Add<double>(15, 17.8) << endl;
     */
    cout << _nmsp1::Add(15, 17.8) << endl;

    cout << _nmsp1::mydouble(15) << endl;  //可以推断出T类型是int
    int result2 = _nmsp1::mydouble<int>(16.9);
    cout << result2 << endl;  // 32

    auto result3 = _nmsp1::mydouble<>(16.9);  //此种场合下，空的<>没有用处，但语法上允许
    cout << result3 << endl;                  // 33.8

    auto result4 = _nmsp1::mydouble(16.9);    //调用的是普通函数，编译器会优先调用普通函数
    auto result3 = _nmsp1::mydouble<>(16.9);  //<>作用就是告诉编译器，调用mydouble函数模板
}
