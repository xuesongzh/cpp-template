
#include <boost/type_index.hpp>
#include <iostream>

using namespace std;

template <typename T>
void myfunc(T tmprv) {
    cout << "---------------------begin------------------------" << endl;
    using boost::typeindex::type_id_with_cvr;
    cout << "T=" << type_id_with_cvr<T>().pretty_name() << endl;                    //显示T类型
    cout << "tmprv=" << type_id_with_cvr<decltype(tmprv)>().pretty_name() << endl;  //显示tmprv类型
    cout << "----------------------end-------------------------" << endl;
}

namespace _nmsp1 {
//泛化版本
template <typename T>
struct RemoveReference {
    using type = T;
};

//特化版本
template <typename T>
struct RemoveReference<T&> {
    using type = T;
};
template <typename T>
struct RemoveReference<T&&> {
    using type = T;
};

//别名模板
template <typename T>
using RemoveReference_t = typename RemoveReference<T>::type;

//泛化版本
template <typename T>
struct RemoveConst {
    using type = T;
};

//特化版本
template <typename T>
struct RemoveConst<const T> {
    using type = T;
};
//根据需要增加其他特化版本....

template <typename T>
using RemoveConst_t = typename RemoveConst<T>::type;

//---------------------------------------
void testFunc() {}

//----------------------------------------
template <typename T>
struct RemoveCR : RemoveConst<typename RemoveReference<T>::type> {  //把const和引用修饰符去掉
};
template <typename T>
using RemoveCR_t = typename RemoveCR<T>::type;
//简写
template <typename T>
using RemoveCR_t = RemoveConst_t<typename RemoveReference_t<T>>;

//----------------------------------------
//泛化版本
template <typename T>
struct Decay : RemoveCR<T> {
};

//特化版本，处理数组，该特化版本没有继承任何父类
//有边界数组转换成指针
template <typename T, std::size_t size>
struct Decay<T[size]> {
    using type = T*;
};

//无边界数组转换成指针
template <typename T>
struct Decay<T[]> {
    using type = T*;
};

//函数名变成了函数指针
template <typename T, typename... Args>
struct Decay<T(Args...)> {  //返回类型是T，参数Args....
    using type = T (*)(Args...);
};

template <typename T>
using Decay_t = typename Decay<T>::type;

//----------------------
void testFunc2() {
    cout << "testFunc2()执行了" << endl;
}

}  // namespace _nmsp1

void gfunc() {
    cout << "rfunc执行了!" << endl;
}

extern int g_array[];  // int []
int main() {
    //（5）const修饰符的移除RemoveConst类模板，与C++标准库里std::remove_const比较类似
    _nmsp1::RemoveConst_t<const int> nca = 15;  // nca是int类型
    nca = 18;                                   //可以给nca重新赋值

    //（6）退化（decay）技术
    //对于const int类型来说，int类型就是一种退化的表现。
    // const修饰符和&、&&修饰符被丢弃，数组类型变成指针类型，函数名变成了函数指针等，都是类型上的退化表现。
    const int a = 16;
    const int& b = a;
    const int&& c = 18;
    int array[5] = {1, 2, 3, 4, 5};
    myfunc(a);      // int
    myfunc(b);      // int
    myfunc(c);      // int
    myfunc(array);  // int*
    myfunc(_nmsp1::testFunc);

    // c++标准库：std::decay，该类模板的作用就是把类型退化掉（把类型中的修饰符丢弃掉）
    std::decay<const int&>::type nb = 26;
    cout << "nb的类型为：" << typeid(decltype(nb)).name() << endl;  // nb类型为int

    //无边界数组，某个.cpp源文件中定义一个全局数组   int g_array[10]，类型int[10];
    // extern int g_array[];  //外部变量说明
    _nmsp1::RemoveCR_t<const int&&> rcrobj = 16;  // rcrobj为int类型。

    int arr[2] = {1, 2};
    _nmsp1::Decay<decltype(arr)>::type myarray;
    cout << "myarray类型为：" << typeid(decltype(myarray)).name() << endl;  // int*

    _nmsp1::Decay<decltype(g_array)>::type myarray2;
    cout << "myarray2类型为：" << typeid(decltype(myarray2)).name() << endl;  // int*

    // a)函数类型：由函数返回值和函数参数决定，testFunc2代表的函数类型void()
    // b)可以利用函数指针指向某种函数类型，若要指向testFunc2，那么函数指针的类型就应该void(*)()
    void (*p)() = _nmsp1::testFunc2;  //定义了一个函数指针，指向testFunc2函数
    p();                              //调用p指向的函数，调用的是testFunc2函数

    // c)如果不为“函数名退化成函数指针”写一个Decay的特化版本，给进去的是函数类型，返回的依旧是函数类型。
    //表面看起来此代码行定义了一个函数类型的变量rfunc，实际理解成函数声明更好，类似于void rfunc();
    _nmsp1::Decay<decltype(_nmsp1::testFunc2)>::type gfunc;
    cout << "gfunc类型为：" << typeid(decltype(gfunc)).name() << endl;  //函数
    gfunc();                                                            //调用rfunc函数

    //增加函数名退化成函数指针的特化版本
    // _nmsp1::Decay<decltype(_nmsp1::testFunc2)>::type rfunc;
    _nmsp1::Decay_t<decltype(_nmsp1::testFunc2)> rfunc;
    cout << "rfunc类型为：" << typeid(decltype(rfunc)).name() << endl;  //函数指针
    rfunc = _nmsp1::testFunc2;                                          //给函数指针赋值
    rfunc();                                                            //相当于调用了testFunc2函数

    return 0;
}