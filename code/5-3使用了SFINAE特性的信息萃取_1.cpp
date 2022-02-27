
#include <iostream>

using namespace std;

namespace _nmsp1 {
//泛化版本
template <typename T1, typename T2>
struct IsSameType {
    static const bool value = false;
};

//特化版本
template <typename T1>
struct IsSameType<T1, T1> {
    static const bool value = true;
};
//----------------------------------------
class A {};
class B {
 public:
    B(int tmpval){};
};

/*
template <typename T>
class IsDefConstructible
{
private:
        template <typename = decltype(T())>
        static std::true_type test(void*); //学习std::declval时看到过只声明，不实现的范例。

        template <typename = int>
        static std::false_type test(...); //...是C语言中的省略号形参，代表可以接受0到多个实参。
                                           //带省略号形参的test具有最低优先级
public:
        static constexpr bool value = IsSameType< decltype(test(nullptr)), std::true_type>::value;
};*/

template <typename T>
class IsDefConstructibleHelper {
 private:
    template <typename = decltype(T())>
    static std::true_type test(void*);

    template <typename = int>  //这行代码其实可以不要
    static std::false_type test(...);

 public:
    using type = decltype(test(nullptr));
};

template <typename T>
class IsDefConstructible : public IsDefConstructibleHelper<T>::type {
};

}  // namespace _nmsp1

namespace _nmsp2 {
class A {};
class B : public A {
};

template <typename FROM, typename TO>
struct IsConvertibleHelper {
 private:
    static void testfunc(TO);

    template <typename = decltype(testfunc(std::declval<FROM>()))>
    static std::true_type test(void*);

    static std::false_type test(...);

 public:
    using type = decltype(test(nullptr));
};

template <typename FROM, typename TO>
struct IsConvertible : IsConvertibleHelper<FROM, TO>::type {  // struct默认的继承方式是public
};

//变量模板
template <typename FROM, typename TO>
constexpr bool IsConvertible_v = IsConvertible<FROM, TO>::value;

}  // namespace _nmsp2

int main() {
    //第三节 使用了SFINAE特性的信息萃取
    // SFINAE：替换失败并不是 一个错误
    //（1）用成员函数重载实现is_default_constructible
    // std::is_default_constructible类模板：判断一个类的对象是否能够被默认构造。
    cout << std::is_default_constructible<int>::value << endl;        // 1
    cout << std::is_default_constructible<double>::value << endl;     // 1
    cout << std::is_default_constructible<_nmsp1::A>::value << endl;  // 1
    cout << std::is_default_constructible<_nmsp1::B>::value << endl;  // 0

    cout << _nmsp1::IsDefConstructible<int>::value << endl;
    cout << _nmsp1::IsDefConstructible<double>::value << endl;
    cout << _nmsp1::IsDefConstructible<_nmsp1::A>::value << endl;
    cout << _nmsp1::IsDefConstructible<_nmsp1::B>::value << endl;

    //（2）用成员函数重载实现is_convertible
    // std::is_convertible类模板：判断能否从某个类型隐式的转换到另一个类型。
    cout << std::is_convertible<float, int>::value << endl;            // 1
    cout << std::is_convertible<int, float>::value << endl;            // 1
    cout << std::is_convertible<_nmsp2::A, _nmsp2::B>::value << endl;  // 0
    cout << std::is_convertible<_nmsp2::B, _nmsp2::A>::value << endl;  // 1

    cout << _nmsp2::IsConvertible<float, int>::value << endl;
    cout << _nmsp2::IsConvertible<int, float>::value << endl;
    cout << _nmsp2::IsConvertible<_nmsp2::A, _nmsp2::B>::value << endl;
    cout << _nmsp2::IsConvertible<_nmsp2::B, _nmsp2::A>::value << endl;

    cout << _nmsp2::IsConvertible_v<float, int> << endl;
    cout << _nmsp2::IsConvertible_v<int, float> << endl;
    cout << _nmsp2::IsConvertible_v<_nmsp2::A, _nmsp2::B> << endl;
    cout << _nmsp2::IsConvertible_v<_nmsp2::B, _nmsp2::A> << endl;

    return 0;
}