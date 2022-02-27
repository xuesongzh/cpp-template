
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
        cout << "Tuple构造函数模板2执行了！" << endl;
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
    static auto myget(const Tuple<First, Others...>& tmptpl)  // auto用的好
    {
        return TPLGetIdx<index - 1>::myget(tmptpl.others);
    }
};

//特化版本
template <>
class TPLGetIdx<0> {
 public:
    template <typename First, typename... Others>
    static auto myget(const Tuple<First, Others...>& tmptpl)  // auto用的好
    {
        return tmptpl.first;
    }
};

//函数模板
template <int index, typename... Types>
auto TupleGet(const Tuple<Types...>& tmptpl) {
    return TPLGetIdx<index>::myget(tmptpl);
}

//泛化版本
template <typename TPLE>  // TPLE代表整个Tuple<...>类型
class pop_front_type;

//特化版本
template <typename FirstElem, typename... OtherElem>
class pop_front_type<Tuple<FirstElem, OtherElem...>> {
 public:
    using type = Tuple<OtherElem...>;
};

//---------------
/*
template <typename... ElemsTypes,typename NewType>
auto push_front(const Tuple<ElemsTypes...>& tmptuple, const NewType& tmpvalue)
{
        return Tuple<NewType, ElemsTypes...>(tmpvalue, tmptuple);
}*/
//向空Tuple的开头插入元素，用于结束递归
template <typename NewType>
auto push_front(const Tuple<>& tmptuple, const NewType& tmpvalue) {
    return Tuple<NewType>(tmpvalue);
}
//向非空Tuple的开头插入元素，利用递归
template <typename FirstType, typename... OtherType, typename NewType>
auto push_front(const Tuple<FirstType, OtherType...>& tmptuple, const NewType& tmpvalue) {
    return Tuple<NewType, FirstType, OtherType...>(tmpvalue, push_front(tmptuple.others, tmptuple.first));
}

//-----------------

//向空Tuple的结尾插入元素，用于结束递归
template <typename NewType>
auto push_back(const Tuple<>&, const NewType& tmpvalue) {
    return Tuple<NewType>(tmpvalue);
}
//向非空Tuple的结尾插入元素，利用递归
template <typename FirstType, typename... OtherType, typename NewType>
// auto：函数返回类型，实际相当于Tuple<FirstType,OtherType...,NewType>
auto push_back(const Tuple<FirstType, OtherType...>& tmptuple, const NewType& tmpvalue) {
    return Tuple<FirstType, OtherType..., NewType>(tmptuple.first, push_back(tmptuple.others, tmpvalue));
}

/*
template <typename... ElemsTypes, typename NewType>
auto push_back(const Tuple<ElemsTypes...>& tmptuple, const NewType& tmpvalue)
{
        return Tuple< ElemsTypes..., NewType>(tmptuple, tmpvalue);
}*/

//-------------------
template <typename... ElemsTypes>
auto pop_front(const Tuple<ElemsTypes...>& tmptuple) {
    return tmptuple.others;
}
//-------------------
//普通函数reverse
auto reverse(const Tuple<>&) {
    return Tuple<>();
}
//函数模板reverse
template <typename FirstType, typename... OtherType>
auto reverse(const Tuple<FirstType, OtherType...>& tmptuple) {
    return push_back(reverse(tmptuple.others), tmptuple.first);  //利用reverse递归可以逐步取得Tuple中每个元素，
                                                                 //而后用push_back把取得的元素放到Tuple末尾,即可达到颠倒的效果
}

}  // namespace tpl

//向integer_sequence开头插入元素：泛化版本
template <typename INTSEQ, unsigned int NewElem>
struct IntSeq_PushFront;

//向integer_sequence开头插入元素：特化版本
template <typename T, unsigned int... Elems, unsigned int NewElem>
struct IntSeq_PushFront<std::integer_sequence<T, Elems...>, NewElem> {
    using type = std::integer_sequence<T, NewElem, Elems...>;
};

//泛化版本
template <typename T, unsigned int N, unsigned int Count = 1>  //从1开始记数
struct Integer_Sequence_Reverse {
    using type = typename IntSeq_PushFront<typename Integer_Sequence_Reverse<T, N - 1>::type, N - Count>::type;
};

//特化版本
template <typename T, unsigned int N>
struct Integer_Sequence_Reverse<T, N, N> {
    using type = std::integer_sequence<T, N - 1>;
};

//定义别名模板
template <typename T, unsigned int N>
using Integer_Sequence_Reverse_T = typename Integer_Sequence_Reverse<T, N>::type;

//----------------------
template <typename... Elems, std::size_t... Index>
auto TPL_LastReverse(const tpl::Tuple<Elems...>& tmptuple, std::integer_sequence<std::size_t, Index...>) {
    return Make_Tuple(tpl::TupleGet<Index>(tmptuple)...);  // TupleGet被调用多次
}

template <typename... Elems>
auto TPL_MidReverse(const tpl::Tuple<Elems...>& tmptuple) {
    return TPL_LastReverse(tmptuple, Integer_Sequence_Reverse_T<unsigned int, sizeof...(Elems)>());  // std::integer_sequence<int,2,1,0>
}

int main() {
    //（3）操作接口（算法）
    // template<typename ...T>
    // class typelist {...};
    //（3.1）从tuple中移除第一个类型（pop_front_type）:对其中的元素 “类型” 进行操作。
    //（3.2）向tuple的开头和结尾插入一个元素（push_front、push_back）
    //（3.3）从tuple中移除第一个元素（pop_front）
    //（3.4）颠倒（反转）一个tuple中的元素的顺序（reverse）
    // std::integer_sequence类模板。Integer_Sequence_Reverse.

    tpl::Tuple<float, int, std::string> mytpobj1(12.5f, 100, "abc");
    tpl::pop_front_type<decltype(mytpobj1)>::type mytpobj2(100, "abc");
    cout << tpl::TupleGet<1>(mytpobj2) << endl;

    tpl::Tuple<> mytpobj3;
    auto mytpobj4 = tpl::push_front(mytpobj3, 12);
    tpl::Tuple<float, int, std::string> mytpobj5(12.5f, 100, "abc");
    auto mytpobj6 = tpl::push_front(mytpobj5, 12);
    auto mytpobj7 = tpl::push_back(mytpobj5, 12);
    auto mytpobj8 = tpl::pop_front(mytpobj5);

    cout << "--------------构造mytpobj9-----------" << endl;
    auto mytpobj9 = tpl::reverse(mytpobj5);
    cout << "---------------" << endl;

    //--------------------------
    Integer_Sequence_Reverse_T<int, 4> tmpobj4;
    cout << "tmpobj4的类型为：" << typeid(decltype(tmpobj4)).name() << endl;

    cout << "--------------构造mytpobj10-----------" << endl;
    auto mytpobj10 = TPL_MidReverse(mytpobj5);
    cout << "---------------" << endl;

    return 0;
}
