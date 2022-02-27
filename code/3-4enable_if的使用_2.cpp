
#include <iostream>
#include <vector>

using namespace std;

namespace _nmsp1 {
template <typename T>
struct MEB {
    using type = T;
};

}  // namespace _nmsp1

namespace _nmsp2 {
template <typename T>
// typename std::enable_if<(sizeof(T) > 2)>::type funceb() // void funceb(){}
// std::enable_if_t<(sizeof(T) > 2)> funceb()
std::enable_if_t<(sizeof(T) > 2), T> funceb() {  // int funceb(){}
    T myt = {};
    return myt;
}

// template <bool _Test, class _Ty = void>
// using enable_if_t = typename std::enable_if<_Test, _Ty>::type; //别名模板

}  // namespace _nmsp2

namespace _nmsp3 {
//给类型模板定义一个别名(别名模板)
template <typename T>
using StrProcType = std::enable_if_t<std::is_convertible<T, std::string>::value>;

class Human {
 public:
    //构造函数模板
    // template<typename T>
    template <
        typename T,
        // typename  = std::enable_if_t<std::is_convertible<T, std::string>::value>
        //如果T能够成功转换成std::string类型，那么等价于typename  = void
        typename = StrProcType<T> >
    Human(T&& tmpname) : m_sname(std::forward<T>(tmpname)) {
        cout << "Human(T&& tmpname)执行" << endl;
    }

    //拷贝构造函数
    Human(const Human& th) : m_sname(th.m_sname) {
        cout << "Human(const Human& th)拷贝构造函数执行" << endl;
    }

    //移动构造函数
    Human(Human&& th) : m_sname(std::move(th.m_sname)) {
        cout << "Human(Human&& th)移动构造函数执行" << endl;
    }

 private:
    string m_sname;
};

}  // namespace _nmsp3

int main() {
    //第四节 std::enable_if的使用
    //（3）enable_if
    // 1. 基础认识:C++11新标准中引入的类模板（结构模板）。使用体现了C++编译器的SFINAE特性。
    //定位为一个helper模板（助手模板），用于辅助其他模板的设计，表现一种：编译器的分支逻辑（编译期就可以确定走哪条分支）。
    //偏特化完全可以理解成一种条件分支语句。
    //// STRUCT TEMPLATE enable_if
    // template <bool _Test, class _Ty = void>   //泛化版本
    // struct enable_if {}; // no member "type" when !_Test

    // template <class _Ty> //偏特化版本:怎么理解：只有这个偏特化版本存在，才存在一个名字叫做type的类型别名（类型）
    // struct enable_if<true, _Ty> { // type is _Ty for _Test
    //	using type = _Ty;
    // };
    _nmsp1::MEB<int>::type abc = 15;                    //_nmsp1::MEB<int>::type 就代表int类型
    std::enable_if<(3 > 2)>::type* mypoint1 = nullptr;  // void *mypoint1 = nullptr
    std::enable_if<(3 < 2)>::type* mypoint1 = nullptr;  // 泛化版本，没有type

    // 2. 范例：enable_if用于函数模板中：典型应用是作为函数模板的返回类型。
    _nmsp2::funceb<int>();
    _nmsp2::funceb<char>();

    // 3. 范例：enable_if用于类模板中
    //针对构造函数模板，如果给进来的参数是一个string类型的参数，就让这个构造函数模板生效。否则就让这个构造函数模板被忽略即可。
    // 也就是说，如果使用enable_if于构造函数模板中，enable_if的条件只需要设置成“形参类型==string类型”即可。
    // std::is_convertible，两个模板参数分别是From和To：用于判断能否从某个类型隐式的转换到另外一个类型。返回一个bool值——true或者false。

    cout << "string=>float:" << std::is_convertible<string, float>::value << endl;  // 0
    cout << "float=>int:" << std::is_convertible<float, int>::value << endl;        // 1

    string sname = "ZhangSan";
    _nmsp3::Human myhuman1(sname);
    _nmsp3::Human myhuman3(myhuman1);  //实际编译器去调用了构造函数模板，而不是调用了拷贝构造函数。

    return 0;
}
