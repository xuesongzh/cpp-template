
#include <iostream>

using namespace std;

namespace tpl {

//泛化版本
template <typename T, typename U = std::void_t<>>
struct HasMemFunc : std::false_type {
};

//特化版本
template <typename T>
struct HasMemFunc<T, std::void_t<decltype(std::declval<T>().myfunc_MTL())>> : std::true_type {
};

//----------------------------
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
    // C_First代表一个元素类型比如float，C_Others代表其余一堆元素类型 int, std::string
    template <typename C_First, typename... C_Others, typename = std::enable_if_t<!HasMemFunc<C_First>::value>>
    Tuple(C_First&& parf, C_Others&&... paro) : first(std::forward<C_First>(parf)),      // parf或者first代表第一个元素比如12.5f，
                                                others(std::forward<C_Others>(paro)...)  // others或者paro代表其余元素，比如 100, std::string("abc")
                                                                                         // others是Tuple<...>类型
    {
        cout << "Tuple构造函数模板执行了！" << endl;
    }

    //拷贝构造函数
    Tuple(const Tuple<First, Others...>& tmptpl) : first(tmptpl.first), others(tmptpl.others) {
        cout << "Tuple拷贝构造函数执行了！" << endl;
    }

    //拷贝构造函数模板
    template <typename C_First, typename... C_Others>
    Tuple(const Tuple<C_First, C_Others...>& tmptpl) : first(tmptpl.first), others(tmptpl.others) {
        cout << "Tuple拷贝构造函数模板执行了！" << endl;
    }

 public:
    void myfunc_MTL() {}  // HasMemFunc
};

//特化版本2：空元组不需要存储任何内容，支持tpl::Tuple<> mytuple;这种构造方式
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

//-------------------------------
//泛化版本
template <int index>
class TPLGetIdx {
 public:
    template <typename First, typename... Others>
    static auto myget(const Tuple<First, Others...>& tmptpl) {
        return TPLGetIdx<index - 1>::myget(tmptpl.others);
    }
};

//特化版本
template <>
class TPLGetIdx<0> {
 public:
    template <typename First, typename... Others>
    static auto myget(const Tuple<First, Others...>& tmptpl) {
        return tmptpl.first;
    }
};

//函数模板
template <int index, typename... Types>
auto TupleGet(const Tuple<Types...>& tmptpl) {
    return TPLGetIdx<index>::myget(tmptpl);
}
}  // namespace tpl

// 类型推导技术：函数模板可以通过实参中给进来的元素值推导出元素类型
template <typename... Types>
auto Make_Tuple(Types&&... Args)  //形参是万能引用（转发引用）
{
    return tpl::Tuple<std::decay_t<Types>...>(std::forward<Types>(Args)...);
}

int main() {
    //（2.2）拷贝构造函数及拷贝构造函数模板的实现--std::enable_if
    //拷贝构造函数模板永远不可能成为拷贝构造函数，
    // 当两个元素类型不同时，构造元素（对象）时，使用的是拷贝构造函数模板而不是拷贝构造函数。
    int i = 100;
    tpl::Tuple<float, int, std::string> mytuple(12.5f, i, std::string("abc"));
    tpl::Tuple<float, int, std::string> mytuple2(mytuple);
    cout << "--------" << endl;
    tpl::Tuple<double, int, std::string> mytuple2(mytuple);

    tpl::Tuple<float> tupleet1(12.5f);
    cout << "----------" << endl;
    tpl::Tuple<int, tpl::Tuple<float>> tmptuple1(15, tupleet1);

    //（2.3）实现获取tuple中元素的get接口
    cout << tpl::TupleGet<2>(mytuple) << endl;  // abc

    //（2.4）std::make_tuple的实现
    auto mytuple10 = std::make_tuple(12.5f, 100, std::string("abc"));  // 3个元素
    std::tuple<float, int, std::string> mytuple11 = std::make_tuple(12.5f, 100, std::string("abc"));

    auto mytuple12 = Make_Tuple(12.5f, 100, std::string("abc"));
    //（2.5）总结:无需过分强求完美的设计和实现。做到随时发现问题随时解决问题即可。

    tpl::Tuple<int, double> wtTpl1(100, 12.5);
    tpl::Tuple<tpl::Tuple<int, double>> stTpl2(wtTpl1);

    return 0;
}