
#include <iostream>

using namespace std;

namespace tpl {
//泛化版本
template <typename... Types>
class Tuple;

//特化版本1
template <typename First, typename... Others>
class Tuple<First, Others...> {
 public:
    First first;
    Tuple<Others...> others;

 public:
    //构造函数，支持tpl::Tuple<int,float> mytuple;这种构造方式
    Tuple() {
    }

    //构造函数模板，支持tpl::Tuple<float, int, std::string> mytuple(12.5f, 100, std::string("abc"));这种构造方式
    // C_First代表一个元素类型比如float，C_Others代表其余一堆元素类型 int, std::string，
    template <typename C_First, typename... C_Others>
    Tuple(C_First&& parf, C_Others&&... paro) : first(std::forward<C_First>(parf)),      // parf或者first代表第一个元素比如12.5f，
                                                others(std::forward<C_Others>(paro)...)  // others或者paro代表其余元素，比如 100, std::string("abc")
                                                                                         // others是Tuple<...>类型
    {
        cout << "Tuple构造函数模板2执行了！" << endl;
    }
};

//特化版本2：空元组，不需要存储任何内容，支持tpl::Tuple<> mytuple;这种构造方式
template <>
class Tuple<> {
 public:
    //构造函数
    Tuple() {
        m_sign = 0;  //随便给个值，方便调试时观察而已
        cout << "Tuple特化版本2的构造函数执行了！" << endl;
    }
    //拷贝构造函数
    Tuple(const Tuple<>&) {
        m_sign = 100;  //随便给个值，方便调试时观察而已
        cout << "Tuple特化版本2的拷贝构造函数执行了！" << endl;
    }
    int m_sign;  //引入的目的其实仅仅是为了设置断点调试时方便观察和确认
};

}  // namespace tpl

int main() {
    //第四节 元组（tuple）实现
    //（2）元组基本概念、基础代码的设计和实现
    // Boost-tuple（元组）：tuple是一个里面能够装各种不同类型元素的数组/容器。
    tuple<float, int, std::string> mytuple(12.5f, 100, std::string("abc"));  //一个tuple（元组）：一堆各种类型数据的组合
    cout << get<0>(mytuple) << endl;                                         // 12.5,get是一个函数模板

    //（2.1）泛化、特化、构造函数的实现
    //可变参类模板的模板参数包的展开方式有两种：a)通过递归继承方式展开，b)通过递归组合方式展开（要讲的）
    //递归组合方式缺点：占用的内存可能相对多一点（一般就是一个字节），因为会涉及到一个“空白基类优化（EBCO）”的话题。
    // tpl::Tuple<float, int, std::string> 拆分成float和tpl::Tuple< int, std::string>
    // tpl::Tuple< int, std::string>拆分成int 和tpl::Tuple<std::string>
    // tpl::Tuple<std::string>拆分成std::string和tpl::Tuple<>
    int i = 100;
    tpl::Tuple<float, int, std::string> mytuple(12.5f, i, std::string("abc"));

    return 0;
}