
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

namespace tplt2 {
class NullTypelist {};  //空Typelist就用这个class表达
template <typename T, typename U = NullTypelist>
class Typelist {  //类模板名首字母大写以示与前面typelist的区别
 public:
    using Head = T;  // Typelist中第一个元素（列表头）
    using Tail = U;  // Typelist中的其余元素（用到嵌套列表）
};

// 1：取得Typelist中的第一个元素（front)
template <typename TPLT>
class front {
 public:
    using type = typename TPLT::Head;
};

// 2:取得Typelist容器中的元素数量（size)
//泛化版本
template <typename TPLT>
class size;

//特化版本1
template <>
class size<NullTypelist> {
 public:
    static inline size_t value = 0;
};

//特化版本2
template <typename T, typename U>
class size<Typelist<T, U>> {
 public:
    static inline size_t value = size<U>::value + 1;  //递归
};

// 3:从Typelist中移除第一个元素（pop_front)
template <typename TPLT>
class pop_front {
 public:
    using type = typename TPLT::Tail;
};

// 4:向Typelist的开头插入一个元素（push_front）
template <typename TPLT, typename NewElem>
class push_front {
 public:
    using type = Typelist<NewElem, TPLT>;
};

// 5:判断Typelist是否为空（is_empty)
//泛化版本
template <typename TPLT>
class is_empty {
 public:
    static inline const bool value = false;
};
//特化版本
template <>
class is_empty<NullTypelist> {
 public:
    static inline const bool value = true;
};

// 6:根据索引号查找Typelist的某个元素（find）
////泛化版本
// template <typename TPLT,unsigned int index_v>
// class find :public find<typename pop_front<TPLT>::type, index_v - 1>
//{
// };

////特化版本
// template <typename TPLT>
// class find<TPLT, 0> :public front<TPLT> //0，作为递归 出口了
//{
// };

//泛化版本
template <class TPLT, unsigned int index_v>
class find;

//特化版本1
template <class Head, class Tail>
class find<Typelist<Head, Tail>, 0> {
 public:
    using type = Head;
};

//特化版本2
template <class Head, class Tail, unsigned int index_v>
class find<Typelist<Head, Tail>, index_v> {
 public:
    using type = typename find<Tail, index_v - 1>::type;
};

// 7:根据索引号查找Typelist的某个元素（find_nostrict）
//泛化版本
template <class TPLT, unsigned int index_v, typename DefaultType = NullTypelist>
class find_nostrict {
 public:
    using type = DefaultType;
};
//特化版本1
template <class Head, class Tail, typename DefaultType>
class find_nostrict<Typelist<Head, Tail>, 0, DefaultType> {
 public:
    using type = Head;
};

//特化版本2
template <class Head, class Tail, unsigned int index_v, typename DefaultType>
class find_nostrict<Typelist<Head, Tail>, index_v, DefaultType> {
 public:
    using type = typename find_nostrict<Tail, index_v - 1, DefaultType>::type;
};

//范例，采用typelist老式设计， 展示typelist的一个基本应用
template <typename Args>
class TestTPClass {
 public:
    //不要使用find,否则可能导致编译出错的境况
    using Arg1 = typename find_nostrict<Args, 0>::type;
    using Arg2 = typename find_nostrict<Args, 1>::type;
    using Arg3 = typename find_nostrict<Args, 2>::type;
    //可以根据需要加入更多Arg开头的类型

    void myfunc(Arg1 val1, Arg2 val2) {
        std::cout << "myfunc执行了，参数之和为：" << val1 + val2 << endl;
    }
};
}  // namespace tplt2

#define MAC_TYPELIST1(T1) tplt2::Typelist<T1, tplt2::NullTypelist>
#define MAC_TYPELIST2(T1, T2) tplt2::Typelist<T1, MAC_TYPELIST1(T2)>
#define MAC_TYPELIST3(T1, T2, T3) tplt2::Typelist<T1, MAC_TYPELIST2(T2, T3)>
#define MAC_TYPELIST4(T1, T2, T3, T4) tplt2::Typelist<T1, MAC_TYPELIST3(T2, T3, T4)>
//根据此法可以定义出许多个参数的Typelist......
// using TPL_NM3 = MAC_TYPELIST3(int, double, char);

int main() {
    //（3）typelist的老式设计 与 typelist的思考
    //（3.1）typelist的老式设计   《Modern C++ Design》——列表头+嵌套列表——实现代码Loki库。
    // NullTypelist：空的typelist
    // Typelist<int,NullTypelist>：有一个元素的typelist
    //以往：using TPL_NM3 = tplt::typelist<int, double, char>;
    //现在：using TPL_NM3 = tplt2::Typelist<int,tplt2::Typelist<double,tplt2::Typelist<char,tplt2::NullTypelist>>>;

    //（3.2）typelist的思考:std::function
    //比较适合于一次传输很多个类型的场合

    cout << typeid(tplt2::front<MAC_TYPELIST1(int)>::type).name() << endl;
    cout << typeid(tplt2::front<MAC_TYPELIST3(char, float, double)>::type).name() << endl;

    cout << tplt2::size<tplt2::NullTypelist>::value << endl;
    cout << tplt2::size<MAC_TYPELIST1(int)>::value << endl;
    cout << tplt2::size<MAC_TYPELIST3(int, double, char)>::value << endl;

    cout << typeid(tplt2::pop_front<MAC_TYPELIST1(int)>::type).name() << endl;
    cout << typeid(tplt2::pop_front<MAC_TYPELIST3(char, float, double)>::type).name() << endl;

    cout << typeid(tplt2::push_front<MAC_TYPELIST1(int), bool>::type).name() << endl;
    cout << typeid(tplt2::push_front<MAC_TYPELIST2(char, double), int>::type).name() << endl;

    cout << tplt2::is_empty<MAC_TYPELIST1(int)>::value << endl;
    cout << tplt2::is_empty<MAC_TYPELIST3(char, float, double)>::value << endl;
    cout << tplt2::is_empty<tplt2::NullTypelist>::value << endl;

    cout << typeid(tplt2::find<MAC_TYPELIST1(int), 0>::type).name() << endl;
    cout << typeid(tplt2::find<MAC_TYPELIST3(char, float, double), 2>::type).name() << endl;
    // cout << typeid(tplt2::find<MAC_TYPELIST3(char, float, double), 5>::type).name() << endl;

    cout << typeid(tplt2::find_nostrict<MAC_TYPELIST4(int, double, char, float), 2>::type).name() << endl;
    cout << typeid(tplt2::find_nostrict<MAC_TYPELIST4(int, double, char, float), 100>::type).name() << endl;

    tplt2::TestTPClass<MAC_TYPELIST2(int, int)> myodtpobj;
    myodtpobj.myfunc(18, 19);

    return 0;
}
