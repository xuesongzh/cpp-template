
#include <iostream>

using namespace std;

namespace _nmsp1 {
struct A {};
union B {
    int num;
    char type;
};

/*
template <class T, T _Val>
struct integral_constant
{
        static constexpr T value = _Val;
        using value_type = T;
        using type = integral_constant;
        constexpr operator value_type() const noexcept
        {
                return value;
        }
        constexpr value_type operator()() const noexcept
        {
                return value;
        }
};
*/

}  // namespace _nmsp1

int main() {
    //第八节 std::is_union、std::is_class、std::integral_constant
    //（1）std::is_union：类模板。用于判断某个类型是否是一个联合类型。
    // template <typename T>
    // struct is_union{.....};
    cout << std::is_union<_nmsp1::A>::value << endl;  // 0
    cout << std::is_union<_nmsp1::B>::value << endl;  // 1

    // template <class T>
    // inline constexpr bool is_union_v = is_union<T>::value;
    cout << std::is_union_v<_nmsp1::A> << endl;
    cout << std::is_union_v<_nmsp1::B> << endl;

    //（2）std::is_class：类模板。用于判断某个类型是否是一个类类型（联合不是类类型）。
    // template <typename T>
    // struct is_class{.....};
    cout << std::is_class<_nmsp1::A>::value << endl;  // 1
    cout << std::is_class<_nmsp1::B>::value << endl;  // 0

    // template <class T>
    // inline constexpr bool is_class_v = is_class<T>::value;
    cout << std::is_class_v<_nmsp1::A> << endl;
    cout << std::is_class_v<_nmsp1::B> << endl;

    //（3）std::integral_constant：C++11新标准引入的类模板。是一个用于包装目的的类。

    cout << std::integral_constant<int, 15>::value << endl;
    cout << std::integral_constant<bool, true>::value << endl;

    //通过integral_constant的包装，把 !std::is_union<_nmsp1::B>::value 这个值（0）包装成了一个类型：
    // std::integral_constant<bool, !std::is_union<_nmsp1::B>::value>
    //那么在很多需要用到类型的场合（比如函数返回类型中）就可以使用这个类型。
    //不要忘记，!std::is_union<_nmsp1::B>::value值在编译时就能确定。
    std::integral_constant<bool, !std::is_union<_nmsp1::B>::value> myobj1;
    cout << myobj1.value << endl;

    std::integral_constant<bool, !std::is_union<_nmsp1::A>::value> myobj2;
    cout << myobj2.value << endl;

    return 0;
}
