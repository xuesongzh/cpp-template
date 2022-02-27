
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
T& mydeclval1() noexcept;
// T&& mydeclval2() noexcept;

class ALR {
 public:
    void onAnyValue() {
        cout << "ALR::onAnyValue()函数执行了！" << endl;
    }

    void onLvalue() & {  //只能被类ALR的左值对象调用
        cout << "ALR::onLvalue()函数执行了！" << endl;
    }

    void onRvalue() && {  //只能被类ALR的右值对象调用
        cout << "ALR::onRvalue()函数执行了！" << endl;
    }
};

}  // namespace _nmsp1

namespace _nmsp2 {
int myfunc(int a, int b) {
    //函数类型一般是由函数的返回值和参数类型决定，与函数名没有关系，所以myfunc代表的函数类型是: int(int,int);
    return a + b;
}

template <typename T_F, typename... U_Args>
decltype(std::declval<T_F>()(std::declval<U_Args>()...)) TestFnRtnImpl(T_F func, U_Args... args) {
    // std::declval<>中的U_Args写成U_Args&&或者U_Args&
    // 根据函数类型以及函数参数类型，推导函数返回值类型。
    // decltype(T_F(U_Args...)) TestFnRtnImpl(T_F func, U_Args... args)
    // 报错：decltype不是这么用的，decltype后面元口号中出现的一般都是变量、对象、表达式、函数名、函数指针名等等。
    auto rtnvalue = func(args...);
    return rtnvalue;
}

template <typename T_F, typename... U_Args>
auto TestFnRtnImpl2(T_F func, U_Args... args) -> decltype(func(args...)) {
    // decltype(func(args...))：int类型，也就是myfunc的返回类型。
    // decltype(func)：int(*)(int,int)类型，函数指针类型
    auto rtnvalue = func(args...);
    return rtnvalue;
}

}  // namespace _nmsp2

int main() {
    //第四章	标准库的典型内容
    //（2.2）返回左值引用还是返回右值引用
    // decltype(mydeclval1<A>)())的返回类型 = class _nmsp1::A &
    // decltype(mydeclval1<A&>)())的返回类型 = class _nmsp1::A &
    // decltype(mydeclval1<A&&>)())的返回类型 = class _nmsp1::A &

    // decltype(mydeclval2<A>)())的返回类型 = class _nmsp1::A &&
    // decltype(mydeclval2<A&>)())的返回类型 = class _nmsp1::A &
    // decltype(mydeclval2<A&&>)())的返回类型 = class _nmsp1::A &&
    using boost::typeindex::type_id_with_cvr;
    cout << "decltype(mydeclval<A>)())的返回类型=" << type_id_with_cvr<decltype(_nmsp1::mydeclval1<_nmsp1::A>())>().pretty_name() << endl;
    cout << "decltype(mydeclval<A&>)())的返回类型=" << type_id_with_cvr<decltype(_nmsp1::mydeclval1<_nmsp1::A&>())>().pretty_name() << endl;
    cout << "decltype(mydeclval<A&&>)())的返回类型=" << type_id_with_cvr<decltype(_nmsp1::mydeclval1<_nmsp1::A&&>())>().pretty_name() << endl;

    //（2.3）调用引用限定符修饰的成员函数范例
    _nmsp1::ALR alr;  //左值对象alr
    alr.onLvalue();
    // alr.onRvalue(); //编译错误，因为onRvalue只能被类A的右值对象调用
    _nmsp1::ALR().onRvalue();  //临时对象是右值对象
    //_nmsp1::ALR().onLvalue();  //编译错误，因为onLvalue只能被类A的左值对象调用

    decltype(_nmsp1::mydeclval1<_nmsp1::ALR>().onAnyValue());
    decltype(_nmsp1::mydeclval1<_nmsp1::ALR&>().onLvalue());
    // decltype(_nmsp1::mydeclval1<_nmsp1::ALR&&>().onRvalue()); //返回的 类型是class ALR &，代表返回的是左值对象，左值对象调用onRvalue是错误的
    // decltype(_nmsp1::mydeclval1<_nmsp1::ALR&>().onRvalue());//返回的 类型是class ALR &，代表返回的是左值对象，左值对象调用onRvalue是错误的
    decltype(_nmsp1::mydeclval1<_nmsp1::ALR&&>().onLvalue());

    decltype(_nmsp1::mydeclval2<_nmsp1::ALR>().onAnyValue());
    decltype(_nmsp1::mydeclval2<_nmsp1::ALR&>().onLvalue());
    decltype(_nmsp1::mydeclval2<_nmsp1::ALR&&>().onRvalue());
    // decltype(_nmsp1::mydeclval2<_nmsp1::ALR&>().onRvalue());//返回的类型是class ALR &，代表返回的是左值对象，左值对象调用onRvalue是错误的
    // decltype(_nmsp1::mydeclval2<_nmsp1::ALR&&>().onLvalue()); //返回的类型是class ALR &&，代表返回的是右值对象，右值对象调用onLvalue是错误的

    //（3）推导函数返回值范例
    // T_F：是int (*)(int,int)类型，也就是函数指针类型
    // decltype(std::declval<T_F>()(std::declval<U_Args>()...))：是int类型，也就是myfunc函数的返回类型
    // a)decltype(std::declval<T_F>())：是 int (* && )(int,int),函数指针的右值引用类型，其实就简单理解成函数指针类型
    // b)decltype(std::declval<U_Args>()...)这种写法：推导出来的是两个int &&

    auto result = _nmsp2::TestFnRtnImpl(_nmsp2::myfunc, 5, 8);  // T_F被推断出 int(*)(int,int)
    // auto result = _nmsp2::TestFnRtnImpl<int(int, int)>(_nmsp2::myfunc, 5, 8);  // T_F被推断出 int(*)(int,int)
    cout << result << endl;

    int (*fp_var)(int x, int y);                           //函数指针类型fp_var = int(*)(int,int)
    int (*&&yy_fp_var)(int x, int y) = std::move(fp_var);  //函数指针的右值引用yy_fp_var = int(* &&)(int,int),现在yy_fp_var就可以代表fp_var
    fp_var = _nmsp2::myfunc;
    cout << fp_var(1, 2) << endl;     // 3
    cout << yy_fp_var(1, 2) << endl;  // 3

    auto result2 = _nmsp2::TestFnRtnImpl2(_nmsp2::myfunc, 13, 15);
    cout << result2 << endl;

    return 0;
}
