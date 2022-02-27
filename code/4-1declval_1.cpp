
#include <boost/type_index.hpp>
#include <iostream>

using namespace std;

namespace _nmsp1 {
class A {
 public:
    A(int i) {
        printf("A::A()函数执行了,this=%p\n", this);
    }

    double myfunc() {
        printf("A::myfunc()函数执行了,this=%p\n", this);
        return 12.1;
    }

 private:
    ~A() {}
};

template <typename T>
// T mydeclval() noexcept;
T& mydeclval() noexcept;
}  // namespace _nmsp1

int main() {
    //第四章	标准库的典型内容
    //介绍C++标准库中典型且常用的函数模板、类模板、别名模板等功能组件以及他们的实现细节。
    //不要求学完后能运用自如，只要求在课程辅助下，遇到实际代码时能够顺利阅读就达到了学习效果。
    //第一节 std::declval
    //（1）基本概念和常规范例
    // std::declval--c++11新标准中出现的函数模板，没有函数体（只有声明，没有实现），无法被调用
    //一般用于与decltype，sizeof等关键字配合来进行类型推导、占用内存空间计算等。
    // add_rvalue_reference：是C++标准库中的类模板，给进来一个类型，能够返回该类型的右值引用类型。
    // a)给进来一个int类型,返回的就是int &&
    // b)给进来一个int &类型，返回的还是int &类型。这里用到了引用折叠。
    // c)给进来一个int &&类型，返回的还是int &&类型。这里依旧用到了引用折叠知识。
    // std::declval的功能：返回某个类型T的右值引用，不管该类型是否有默认构造函数或者该类型是否可以创建对象。
    //返回某个类型T的右值引用 这个动作是在编译时完成的，所以很多人把std::declval也称为编译时工具。
    // std::declval的作用：
    // a)从类型转换的角度来讲，将任意一个类型转换成右值引用类型。
    // b)从假想创建出某类型对象的角度来说，配合decltype，令在decltype表达式中，不必经过该类型的构造函数就能使用该类型的成员函数。
    //注意，std::declval不能被调用，也不能创建任何对象。
    // 但std::declval能在不创建对象的情况下，达到创建了一个该类型对象的效果或者说程序员可以假定创建出了一个该类型对象。

    //利用boost输出类型名比typeid(...).name()用法输出类型名更准确
    using boost::typeindex::type_id_with_cvr;
    using YT = decltype(std::declval<_nmsp1::A>());                 //这里注意不要把std::declval<_nmsp1::A>后面的圆括号对丢掉，否则代码含义就发生变化了。想象函数调用时即便没有参数也要把圆括号带着。
    cout << "YT=" << type_id_with_cvr<YT>().pretty_name() << endl;  // class _nmsp1::A &&

    _nmsp1::A myaobj(1);  //必须为构造函数提供参数
    // double
    cout << "myaobj.myfunc()的返回类型=" << type_id_with_cvr<decltype(myaobj.myfunc())>().pretty_name() << endl;
    // double
    cout << "A::myfunc()的返回类型=" << type_id_with_cvr<decltype(std::declval<_nmsp1::A>().myfunc())>().pretty_name() << endl;

    //看起来是一个函数声明的语法 ，该函数返回的类型是A&&，可以看成是返回了一个A&&类型的对象，这种对象就可以看成是类A对象。
    _nmsp1::A&& ayinobj();
    //	ayinobj(); //看起来是调用ayinobj这个函数，链接报错
    //	ayinobj().myfunc();
    decltype(ayinobj().myfunc()) mydblvar;  //定义了一个double类型的变量mydblvar;

    //（2）std::declval为什么返回右值引用类型
    //（2.1）返回类型本身是不好的
    //因为返回类型本身，导致为了遵循语义限制，编译器内部创建了临时的A类对象。
    //为了绕开语义限制，在设计mydeclval函数模板时，就不要返回类型T了，可以返回T&，也可以返回T&&，
    //这样从遵循语义限制方面来说，就不会创建临时的A类对象了。这就是返回T&或者T&&的好处。

    cout << "mydeclval<A>()的返回类型=" << type_id_with_cvr<decltype(_nmsp1::mydeclval<_nmsp1::A>())>().pretty_name() << endl;
    cout << "mydeclval<A>().myfunc()的返回类型=" << type_id_with_cvr<decltype(_nmsp1::mydeclval<_nmsp1::A>().myfunc())>().pretty_name() << endl;  //语义限制

    cout << "sizeof(mydeclval<_nmsp1::A>())=" << sizeof(_nmsp1::mydeclval<_nmsp1::A>()) << endl;

    return 0;
}