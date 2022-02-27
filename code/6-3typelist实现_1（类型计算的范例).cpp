
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

namespace tplt {
//所有的typelist设计代码都放入这里
template <typename... T>  // T代表typelist中装的一包类型（typelist中装的一系列元素）
class typelist {
};

//-----------------------
//取得typelist中的第一个元素（front）
//泛化版本只需要声明，存在的目的就是要引出特化版本
template <typename TPLT>  // TPLT代表整个typelist<...>类型
class front;

//特化版本，先写front后面尖括号中的内容（这个内容必须遵从泛化版本中template中的内容来书写）
//再根据尖括号中用到的内容来填补template中的内容
template <typename FirstElem, typename... OtherElem>
class front<typelist<FirstElem, OtherElem...>> {
 public:
    using type = FirstElem;
};

//------------------------
//取得typelist容器中元素的数量（size）
//泛化版本
template <typename TPLT>
class size;

//特化版本
template <typename... Args>
class size<typelist<Args...>> {
 public:
    static inline size_t value = sizeof...(Args);
};

//------------------------
//从typelist中移除第一个元素（pop_front）
//泛化版本
template <typename TPLT>
class pop_front;

//特化版本
template <typename FirstElem, typename... OtherElem>
class pop_front<typelist<FirstElem, OtherElem...>> {
 public:
    using type = typelist<OtherElem...>;
};

//------------------------
//向typelist的开头插入一个元素（push_front）
//向开头插入元素，泛化版本
template <typename TPLT, typename NewElem>  // TPLT代表整个typelist<...>类型，NewElem代表要插入的元素
class push_front;

//向开头插入元素，特化版本
template <typename... Elem, typename NewElem>
class push_front<typelist<Elem...>, NewElem> {
 public:
    using type = typelist<NewElem, Elem...>;
};

//-----------------------
//向末尾插入元素，泛化版本(push_back)
template <typename TPLT, typename NewElem>  // TPLT代表整个typelist<...>类型，NewElem代表要插入的元素
class push_back;

//向末尾插入元素，特化版本
template <typename... Elem, typename NewElem>
class push_back<typelist<Elem...>, NewElem> {
 public:
    using type = typelist<Elem..., NewElem>;
};

//--------------------------
//替换typelist的开头元素（replace_front）
//泛化版本
template <typename TPLT, typename NewElem>
class replace_front;

//特化版本
template <typename FirstElem, typename... OtherElem, typename NewElem>
class replace_front<typelist<FirstElem, OtherElem...>, NewElem> {
 public:
    using type = typelist<NewElem, OtherElem...>;
};

//--------------------------
//判断typelist是否为空（is_empty）
//泛化版本
template <typename TPLT>
class is_empty {
 public:
    static inline const bool value = false;
};

//特化版本
template <>
class is_empty<typelist<>> {
 public:
    static inline const bool value = true;
};
}  // namespace tplt

using TPL_NM1 = tplt::typelist<int, double, float, char, bool>;
using TPL_NM2 = tplt::typelist<>;  //没有元素的typelist容器

int main() {
    //第三节 typelist实现（类型计算的范例)
    //《Modern C++ Design》 ---《C++设计新思维》---Loki实现了typelist（列表头+嵌套列表技术来实现，因为2003年C++不支持可变参模板）
    // typelist：用来操作一大堆类型的C++容器，就像C++标准库中的list容器（能够对各种数值提供各种基本操作），但typelist是针对类型进行操作。
    // typelist简单的说就是一个类型容器，能够对类型提供一系列的操作（把类型当成数据来操作）。
    //从实现上，typelist是一个类模板，中文名字叫：类型列表。该类模板用来表示一个列表，在该列表中存放着一堆类型。
    //（1）设计和基本操作接口（算法）
    //（1.1）取得typelist中的第一个元素（front）
    //（1.2）取得typelist容器中元素的数量（size）
    //（1.3）从typelist中移除第一个元素（pop_front）
    //（1.4）向typelist的开头和结尾插入一个元素（push_front、push_back）
    //（1.5）替换typelist的开头元素（replace_front）
    //（1.6）判断typelist是否为空（is_empty）

    tplt::typelist<>;
    tplt::typelist<int>;
    tplt::typelist<int, double, float, char, bool>;

    cout << typeid(tplt::front<TPL_NM1>::type).name() << endl;  // int
    cout << typeid(tplt::front<TPL_NM2>::type).name() << endl;  //报错

    cout << tplt::size<TPL_NM1>::value << endl;  // 5
    cout << tplt::size<TPL_NM2>::value << endl;  // 0

    cout << typeid(tplt::pop_front<TPL_NM1>::type).name() << endl;  // tplt::typelist<double, float, char, bool>
    cout << typeid(tplt::pop_front<TPL_NM2>::type).name() << endl;  //报错

    cout << typeid(tplt::push_front<TPL_NM1, bool>::type).name() << endl;
    cout << typeid(tplt::push_front<TPL_NM2, bool>::type).name() << endl;

    cout << typeid(tplt::push_back<TPL_NM1, bool>::type).name() << endl;
    cout << typeid(tplt::push_back<TPL_NM2, bool>::type).name() << endl;

    using TmpType = tplt::push_front<tplt::pop_front<TPL_NM1>::type, int64_t>::type;  // int64_t == long long
    cout << typeid(TmpType).name() << endl;

    cout << typeid(tplt::replace_front<TPL_NM1, int64_t>::type).name() << endl;

    cout << tplt::is_empty<TPL_NM1>::value << endl;
    cout << tplt::is_empty<TPL_NM2>::value << endl;

    return 0;
}
