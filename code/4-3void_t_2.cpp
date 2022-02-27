
#include <iostream>
//#include <boost/type_index.hpp>
#include <vector>

using namespace std;
//#pragma warning(disable : 4996)

namespace _nmsp1 {
class ACPABL {
};

class BCPABL {
 public:
    BCPABL& operator=(const BCPABL& tmpobj) {  //拷贝赋值运算符
        //...
        return *this;
    }
};

class CCPABL {
 public:
    CCPABL& operator=(const CCPABL& tmpobj) = delete;  //拷贝赋值运算符标记为delete
};

// IsCopyAssignable类模板
//泛化版本
template <typename T, typename U = std::void_t<>>
struct IsCopyAssignable : std::false_type {
};

//特化版本
template <typename T>
struct IsCopyAssignable<T, std::void_t<decltype(std::declval<T&>() = std::declval<const T&>())>> : std::true_type {
    // a = b====> a.operator=(b);
    // decltype(   std::declval<T&>())  = class T&
    // decltype(   std::declval<T&>() = std::declval<const T&>()   )   = class T&
};

}  // namespace _nmsp1

namespace _nmsp2 {
//----------------------
//泛化版本
template <typename T, typename U, typename V = std::void_t<>>  // T,U,V可以省略template<typename , typename  , typename  = std::void_t<>>
struct IfCanAdd : std::false_type {
};

//特化版本
template <typename T, typename U>
struct IfCanAdd<T, U, std::void_t<decltype(std::declval<T>() + std::declval<U>())>> : std::true_type {
};

//----------------------

//考虑设计 一个类模板VecAddResult
/*
template<typename T, typename U>
struct VecAddResult {
        //using type = decltype( T() + U()); //把结果类型的推导交给了编译器来做
        using type = decltype(std::declval<T>() + std::declval<U>());
};
*/

//泛化版本的VecAddResult
template <typename T, typename U, bool ifcando = IfCanAdd<T, U>::value>
struct VecAddResult {
    using type = decltype(std::declval<T>() + std::declval<U>());
};

//特化版本
template <typename T, typename U>
struct VecAddResult<T, U, false> {
};

//----------------------
template <typename T, typename U>
using VecAddResult_t = typename VecAddResult<T, U>::type;

//----------------------
template <typename T, typename U>  // T,U表示容器中的元素类型
// std::vector<T> operator+(std::vector<T> const& vec1, std::vector<U> const& vec2) {}; //两个容器相加，重载的+运算符
// std::vector<typename VecAddResult<T, U>::type> operator+(std::vector<T> const& vec1, std::vector<U> const& vec2)
std::vector<VecAddResult_t<T, U>> operator+(std::vector<T> const& vec1, std::vector<U> const& vec2) {
    // std::vector<typename VecAddResult<T, U>::type > tmpvec;
    std::vector<VecAddResult_t<T, U>> tmpvec;
    return tmpvec;
};

struct elemC {
    elemC(int tmpvalue);                   //带一个参数的构造函数
    elemC operator+(const elemC& tmppar);  //重载加法运算符以支持加法操作。
};

}  // namespace _nmsp2

int main() {
    //第三节 std::void_t
    //（3）借助void_t和declval实现is_copy_assignable
    // C++标准库里的类模板 is_copy_assignable用来判断一个类对象是否能够进行拷贝赋值。
    _nmsp1::ACPABL aobj1;
    _nmsp1::ACPABL aobj2;
    aobj2 = aobj1;  //拷贝赋值

    _nmsp1::BCPABL bobj1;
    _nmsp1::BCPABL bobj2;
    bobj2 = bobj1;  //拷贝赋值

    _nmsp1::CCPABL cobj1;
    _nmsp1::CCPABL cobj2;
    // cobj2 = cobj1;  //不能拷贝赋值

    cout << "int:" << std::is_copy_assignable<int>::value << endl;                // 1
    cout << "ACPABL:" << std::is_copy_assignable<_nmsp1::ACPABL>::value << endl;  // 1
    cout << "BCPABL:" << std::is_copy_assignable<_nmsp1::BCPABL>::value << endl;  // 1
    cout << "CCPABL:" << std::is_copy_assignable<_nmsp1::CCPABL>::value << endl;  // 0

    cout << "int:" << _nmsp1::IsCopyAssignable<int>::value << endl;
    cout << "ACPABL:" << _nmsp1::IsCopyAssignable<_nmsp1::ACPABL>::value << endl;
    cout << "BCPABL:" << _nmsp1::IsCopyAssignable<_nmsp1::BCPABL>::value << endl;
    cout << "CCPABL:" << _nmsp1::IsCopyAssignable<_nmsp1::CCPABL>::value << endl;

    //（4）综合范例
    //两个vector容器，元素数量相同（10元素），但是这两个容器中的元素类型不同（比如第一个容器里边是int类型的元素，第二个容器里面是double类型的元素）
    //希望重载一下+运算符，做一下这两个容器的加法运算，加法运算的意思就是第一个容器的第一个元素与第二个容器的第一个元素相加
    //假如容器中的元素类型不是基本类型，而是一个类类型elemC类型。
    // decltype(elemC() + elemC())
    //代码改进：希望通过SFINAE特性检测一下两个类型的对象之间到底能不能相加。准备引入一个叫做IfCanAdd类模板，用来判断两个类型能否相加。
    // VecAddResult和IfCanAdd这两个类模板之间有一种SFINAE-friendly（SFINAE友好）关系。
    //编写模板时的原则：如果选择要实例化某个模板（operator+，VecAddResult)，则实例化时不应该失败（编译错误）。

    int i = int();  //定义了一个int类型的变量，而且这种定义方式会把i的初值设置为0
    i = 5;
    double j = double();  //定义了一个double类型的变量，而且这种定义方式会把j的初值设置为0.0
    j = 13.6;

    std::vector<int> veca;
    std::vector<double> vecb;
    // veca + vecb;
    _nmsp2::operator+(veca, vecb);

    std::vector<_nmsp2::elemC> veca;
    std::vector<_nmsp2::elemC> vecb;
    veca + vecb;

    return 0;
}
