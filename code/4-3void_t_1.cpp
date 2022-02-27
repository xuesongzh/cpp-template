
#include <iostream>
//#include <boost/type_index.hpp>

using namespace std;
//#pragma warning(disable : 4996)

namespace _nmsp1 {
//// ALIAS TEMPLATE void_t
// template <class... _Types>
// using void_t = void;

struct NoInnerType {
    int m_i;
};

struct HaveInnerType {
    using type = int;  //类型别名
    void myfunc() {}
};

//泛化版本
template <typename T, typename U = std::void_t<> >
struct HasTypeMem : std::false_type {  // struct 默认是public ,class默认是private继承
};

//特化版本
template <typename T>
struct HasTypeMem<T, std::void_t<typename T::type> > : std::true_type {  //只支持type
};

//带参数的宏定义，注意 反斜杠 表示下一行接着本行来，是本行的一部分
#define _HAS_TYPE_MEM_(parMTpNm)                       \
    template <typename T, typename U = std::void_t<> > \
    struct HTM_##parMTpNm : std::false_type {};        \
    template <typename T>                              \
    struct HTM_##parMTpNm<T, std::void_t<typename T::parMTpNm> > : std::true_type {};

_HAS_TYPE_MEM_(type);
_HAS_TYPE_MEM_(sizetype);

//_HAS_TYPE_MEM_(type);展开后
/*template <typename T, typename U = std::void_t<> >
        struct HTM_type : std::false_type{};
template <typename T>
struct HTM_type<T, std::void_t<typename T::type> > : std::true_type{};*/
//_HAS_TYPE_MEM_(sizetype);展开后
/*template <typename T, typename U = std::void_t<> >
struct HTM_sizetype : std::false_type {};
template <typename T>
struct HTM_sizetype<T, std::void_t<typename T::sizetype> > : std::true_type {};*/

//------------
//泛化版本
template <typename T, typename U = std::void_t<> >
// template <typename T, typename U = int >
// template <typename T, typename U = void >
struct HasMember : std::false_type {  // HasMember<HaveInnerType,void>
};

//特化版本
template <typename T>
struct HasMember<T, std::void_t<decltype(T::m_i)> > : std::true_type {  // HasMember<NoInnerType,void>
};

//------------
//泛化版本
template <typename T, typename U = std::void_t<> >
struct HasMemFunc : std::false_type {
};

//特化版本
template <typename T>
struct HasMemFunc<T, std::void_t<decltype(std::declval<T>().myfunc())> > : std::true_type {
};

}  // namespace _nmsp1

int main() {
    //第三节 std::void_t
    //（1）源码分析和常规范例
    //功能：能够检测到应用SFINAE(替换失败并不是一个错误）特性时出现的非法类型。
    // 换句话说，给进来的类型必须是一个有效的类型，不能是一个非法类型。
    //（1.1）判断类中是否存在某个类型别名
    cout << _nmsp1::HasTypeMem<_nmsp1::NoInnerType>::value << endl;    // 0 泛化
    cout << _nmsp1::HasTypeMem<_nmsp1::HaveInnerType>::value << endl;  // 1 特化

    cout << _nmsp1::HTM_type<_nmsp1::NoInnerType>::value << endl;    // 0
    cout << _nmsp1::HTM_type<_nmsp1::HaveInnerType>::value << endl;  // 1

    cout << _nmsp1::HTM_sizetype<_nmsp1::NoInnerType>::value << endl;    // 0
    cout << _nmsp1::HTM_sizetype<_nmsp1::HaveInnerType>::value << endl;  // 0

    //（1.2）判断类中是否存在某个成员变量
    cout << _nmsp1::HasMember<_nmsp1::NoInnerType>::value << endl;    // 1 特化
    cout << _nmsp1::HasMember<_nmsp1::HaveInnerType>::value << endl;  // 0 泛化

    //（1.3）判断类中是否存在某个成员函数
    cout << _nmsp1::HasMemFunc<_nmsp1::NoInnerType>::value << endl;    // 0 泛化
    cout << _nmsp1::HasMemFunc<_nmsp1::HaveInnerType>::value << endl;  // 1 特化

    //（2）泛化版本和特化版本到底编译器如何选择
    //编译器通过一种复杂的排序规则来决定使用类模板的泛化版本还是特化版本。
    //一般来说，void跟任何其他类型比，都是最后选择的。

    return 0;
}
