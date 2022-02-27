
#include <iostream>

using namespace std;

namespace _nmsp2 {
//-----------------------------------
//向integer_sequence开头插入元素：
//泛化版本
template <typename INTSEQ, unsigned int NewElem>  // INTSEQ代表整个的std::integer_sequence< ......>类型
struct IntSeq_PushFront;                          //因为不使用泛化版本，所以泛化版本可以只声明不定义。

//向std::integer_sequence开头插入元素：特化版本
template <typename T, unsigned int... Elems, unsigned int NewElem>  //泛化版本一般要求可变参放在最后，特化版本一般无此要求
struct IntSeq_PushFront<std::integer_sequence<T, Elems...>, NewElem> {
    using type = std::integer_sequence<T, NewElem, Elems...>;
};

//-----------------------------------
//泛化版本
template <typename T, unsigned int N, unsigned Count = 1>  //从1开始计数
struct Integer_Sequence_Reverse {
    using type = typename IntSeq_PushFront<typename Integer_Sequence_Reverse<T, N - 1>::type, N - Count>::type;
};

//特化版本
template <typename T, unsigned int N>
struct Integer_Sequence_Reverse<T, N, N> {
    using type = std::integer_sequence<T, N - 1>;
};

//---------
//定义别名模板
template <typename T, unsigned int N>
using Integer_Sequence_Reverse_T = typename Integer_Sequence_Reverse<T, N>::type;

}  // namespace _nmsp2

namespace _nmsp3 {
//泛化版本
template <std::size_t Num, std::size_t RepeatTime, typename INTSEQ = std::integer_sequence<std::size_t>>  // INTSEQ代表整个的std::integer_sequence< ......>类型
class Repeat_Integer;

//特化版本1：
template <std::size_t Num, std::size_t RepeatTime, std::size_t... index>
class Repeat_Integer<Num, RepeatTime, std::integer_sequence<std::size_t, index...>> : public Repeat_Integer<Num, RepeatTime - 1, std::integer_sequence<std::size_t, index..., Num>> {
};

//特化版本2（用于结束递归）
template <std::size_t Num, std::size_t... index>
class Repeat_Integer<Num, 0, std::integer_sequence<std::size_t, index...>> {
 public:
    using type = std::integer_sequence<std::size_t, index...>;
};

//定义别名模板
template <std::size_t Num, std::size_t RepeatTime>
using Repeat_Integer_T = typename Repeat_Integer<Num, RepeatTime>::type;

}  // namespace _nmsp3

int main() {
    //第七节 std::integer_sequence:C++14中引入的一个类模板。
    //（2）逆向排列数字生成一个类型Integer_Sequence_Reverse
    //(i)Integer_Sequence_Reverse_T<int, 4> tmpobj4;   //等价于
    //(i)Integer_Sequence_Reverse<int, 4>::type tmpobj4; //把type看成函数调用
    //(i)    using type = IntSeq_PushFront<Integer_Sequence_Reverse< int,3>::type, 3 >::type;
    //(i)        //展开上行后面这个Integer_Sequence_Reverse< int,3>::type如下
    //(i)        using type = IntSeq_PushFront<Integer_Sequence_Reverse< int,2>::type, 2 >::type;
    //(i)            //展开上行后面这个Integer_Sequence_Reverse< int,2>::type如下
    //(i)            using type = IntSeq_PushFront<Integer_Sequence_Reverse< int,1>::type, 1 >::type;
    //(i)                //展开上行后面这个Integer_Sequence_Reverse< int,1>::type，调用的是特化版本
    //(i)                using type = std::integer_sequence<int, 0>; //递归结束往回返
    //(i)            using type = std::integer_sequence<int, 1,0>
    //(i)        using type = std::integer_sequence<int, 2,1,0>
    //(i)    using type = std::integer_sequence<int,3,2,1,0>
    //(i)//最终结果
    //(i)std::integer_sequence<int,3,2,1,0>
    _nmsp2::Integer_Sequence_Reverse_T<int, 4> tmpobj4;
    cout << "tmpobj4的类型为：" << typeid(decltype(tmpobj4)).name() << endl;

    //（3）将一个数字重复多次生成一个类型Repeat_Integer
    //前面是通过递归调用的方式实现。现在这里通过递归继承的方式实现。
    // （a）因为Repeat_Integer<1, 4>::type tmpobj5; 代码行的存在，导致系统会根据Repeat_Integer特化版本1实例化出如下类：
    // Repeat_Integer<1, 4, std::integer_sequence<std::size_t>>
    // （b）要想实例化出Repeat_Integer<1, 4, std::integer_sequence<std::size_t>>
    // 根据继承关系，编译器必须要实例化出他的父类，其实也就是
    // Repeat_Integer<1, 3, std::integer_sequence<std::size_t, 1>>
    // 上面这个写法注意：std::integer_sequence模板参数的末尾，已经多出个1了，而且此时的index代表的不是0个参数，而是1个参数了。
    // ......
    // （c）在递归结束时，即 使用Repeat_Integer的特化版本2来实例化Repeat_Integer时，使用了using来定义类型别名type，
    //  此时type就相当于类型std::integer_sequence<std::size_t, 1, 1, 1, 1>，因为是一种类继承关系，
    //  所以父类中定义的type在子类中即可使用，因此Repeat_Integer<1, 4>::type这种写法毫无问题。

    _nmsp3::Repeat_Integer<1, 4>::type tmpobj5;
    // struct std::integer_sequence<unsigned int,1,1,1,1>
    cout << "tmpobj5的类型为：" << typeid(decltype(tmpobj5)).name() << endl;

    _nmsp3::Repeat_Integer<1, 4, std::integer_sequence<std::size_t, 12, 18, 19>>::type tmpobj6;
    // struct std::integer_sequence<unsigned int,12,18,19,1,1,1,1>
    cout << "tmpobj6的类型为：" << typeid(decltype(tmpobj6)).name() << endl;

    return 0;
}