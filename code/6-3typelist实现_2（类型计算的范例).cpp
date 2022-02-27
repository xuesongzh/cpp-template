
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

namespace _nmsp1 {
}

namespace tplt {
//所有的typelist设计代码都放入这里
template <typename... T>  // T代表typelist中装的一包类型（typelist中装的一系列元素）
class typelist {
};

//-----------------------
//取得typelist中的第一个元素（front）
//泛化版本，用不到，所以只需要声明，存在的目的就是要引出特化版本
template <typename TPLT>  // TPLT代表整个typelist<...>类型
class front;

//特化版本，写特化版本时，先书写front后面尖括号中的内容（这个内容必须遵从泛化版本中template中的内容来书写）,
//回头再根据尖括号中用到的内容来填补template中的内容
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

//---------------------(push_back)
//向末尾插入元素，泛化版本
template <typename TPLT, typename NewElem>  // TPLT代表整个typelist<...>类型，NewElem代表要插入的元素
class push_back;

//向末尾插入元素，特化版本
template <typename... Elem, typename NewElem>
class push_back<typelist<Elem...>, NewElem> {
 public:
    using type = typelist<Elem..., NewElem>;
};

//-----------------
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

//--------------------
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

//------------------------------------
//泛化版本
template <typename TPLT, unsigned int index_v>
class find : public find<typename pop_front<TPLT>::type, index_v - 1> {
};

//特化版本
template <typename TPLT>
class find<TPLT, 0> : public front<TPLT> {  // 0，作为递归的出口了
};

//------------------------------------
//泛化版本
template <typename TPLT>
class get_maxsize_type {
 private:
    //当前get_maxsize_type中typelist（模板参数）的第一个元素
    using tl_first_elem = typename front<TPLT>::type;  //获取type中第一个元素（是一个类型），比如获取到int

    using tl_remain = typename pop_front<TPLT>::type;

    //递归下去的get_maxsize_type中typelist(模板参数）的第一个元素
    using tl_first_elem_rec = typename get_maxsize_type<tl_remain>::type;

 public:
    using type = typename std::conditional<
        sizeof(tl_first_elem) >= sizeof(tl_first_elem_rec),
        tl_first_elem,
        tl_first_elem_rec>::type;
};

//特化版本
template <>
class get_maxsize_type<typelist<>> {
 public:
    using type = char;
};

//------------------------------------
//泛化版本
template <typename TPLT, bool = is_empty<TPLT>::value>
class reverse;

//特化版本1，当typelist中还有元素时
template <typename TPLT>
class reverse<TPLT, false> {
 private:
    using tl_first_elem = typename front<TPLT>::type;  //获取type中第一个元素（是一个类型），比如获取到int

    using tl_remain = typename pop_front<TPLT>::type;

    using tl_result_rec = typename reverse<tl_remain>::type;

 public:
    using type = typename push_back<tl_result_rec, tl_first_elem>::type;
};

//特化版本2，当typelist中没有元素时
template <typename TPLT>
class reverse<TPLT, true> {
 public:
    using type = typename TPLT;  //其实此时TPLT就是typelist<>
};

}  // namespace tplt

using TPL_NM1 = tplt::typelist<int, double, float, char, bool>;
using TPL_NM2 = tplt::typelist<>;  //没有元素的typelist容器

int main() {
    //（2）扩展操作接口（算法）
    //（2.1）根据下标查找typelist的某个元素（find）
    // tplt::find<TPL_NM1, 2>::type：函数调用，调用的是find的泛化版本，把TPL_NM1替换一下
    //===========>tplt::find<  tplt::typelist<int, double, float, char, bool> , 2> 会被实例化出来。
    // 父类是 tplt::find<  tplt::typelist<double, float, char, bool> , 1>
    // 父类是 tplt::find<  tplt::typelist<float, char, bool> , 0>，正好是find的特化版本
    // 父类是 tplt::front<  tplt::typelist<float, char, bool>>
    // 因为front(find的父类）的特化版本中定义了type，因此main中tplt::find<TPL_NM1, 2>::type的结果
    // 其实也就是tplt::front<tplt::typelist<float, char, bool>>::type
    cout << typeid(tplt::find<TPL_NM1, 2>::type).name() << endl;   // float
    cout << typeid(tplt::find<TPL_NM1, 20>::type).name() << endl;  //超出边界，编译时就会报错

    //（2.2）遍历typelist找到sizeof值最大的元素（get_maxsize_type）
    //元编程计算完整：
    // a)迭代构造（循环构造）：也就是在get_maxsize_type模板中融入递归编程技术
    // b)状态变量：指的是类模板get_maxsize_type中的模板参数，因为这里类模板的模板参数是typelist，
    //           所以每次递归，typelist中的元素数量肯定要少一个，最终才能符合递归结束条件。
    // c)执行路径的选择：使用std::conditional以及get_maxsize_type类模板的特化达到结束递归的效果，
    //                这个特化版本的特点是模板参数typelist中的元素为0个。
    // d)运算对象：类模板中的type成员里面记录的就是当前sizeof值最大的类型。
    cout << typeid(tplt::get_maxsize_type<TPL_NM1>::type).name() << endl;  // double

    //（2.3）颠倒（反转）一个typelist中的元素的顺序（reverse）
    //高级代码书写技巧：写出模糊代码->整理调用关系->反推确定代码。
    cout << typeid(tplt::reverse<tplt::typelist<int, double, float>>::type).name() << endl;

    return 0;
}
