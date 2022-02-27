
#include <iostream>

using namespace std;

namespace _nmsp1 {
/*template <class T, T... Ints>
struct integer_sequence
{
        using value_type = T;

        static constexpr size_t size() noexcept
        {
                return sizeof...(Ints);
        }
};*/

//-----------------------------------
//向integer_sequence末尾插入元素：
//泛化版本
template <typename INTSEQ, unsigned int NewElem>  // INTSEQ代表整个的std::integer_sequence< ......>类型
struct IntSeq_PushBack;                           //因为不使用泛化版本，所以泛化版本可以只声明不定义。

//向std::integer_sequence末尾插入元素：特化版本
template <typename T, unsigned int... Elems, unsigned int NewElem>  //泛化版本一般要求可变参放在最后，特化版本一般无此要求
struct IntSeq_PushBack<std::integer_sequence<T, Elems...>, NewElem> {
    using type = std::integer_sequence<T, Elems..., NewElem>;
};

//-----------------------------------
//泛化版本
template <typename T, unsigned int N>
struct Integer_Sequence {  //实现std::make_integer_sequence功能
    //依次遍历出4,3,2,1，应该往末尾插入元素，所以还应该引入IntSeq_PushBack操作。
    using type = typename IntSeq_PushBack<typename Integer_Sequence<T, N - 1>::type, N - 1>::type;  //这里理解成函数调用，把type理解成所调用的函数名
};

//特化版本
template <typename T>
struct Integer_Sequence<T, 1> {                //这里是1，意味着递归到1就可以了
    using type = std::integer_sequence<T, 0>;  //这是0，注意。
};

//---------
//定义别名模板
template <typename T, unsigned int N>
using Integer_Sequence_T = typename Integer_Sequence<T, N>::type;

}  // namespace _nmsp1

int main() {
    //第七节 std::integer_sequence:C++14中引入的一个类模板。
    //产生整型数字序列，0,1,2,3,4,5
    // T：int,unsigned int,char,short。
    // Ints：非类型模板参数包，一堆数字，这堆数字类型相同，都是T类型。

    // std::make_integer_sequence，别名模板，就可以理解成是一个 std::integer_sequence，伪代码：
    // template<class T, T N>
    // using make_integer_sequence=std::integer_sequence<T,0,1,2,3,....N-1序列>;

    // std::make_index_sequence，别名模板，与make_integer_sequence非常类似，伪代码：
    // template<std::size_t N>
    // using make_index_sequence=std::integer_sequence<std::size_t,0,1,2,3,....N-1序列>;//	std::size_t = unsigned int;
    std::make_integer_sequence<int, 5> tmpobj;
    cout << "tmpobj的类型为：" << typeid(decltype(tmpobj)).name() << endl;

    std::make_index_sequence<4> tmpobj2;
    cout << "tmpobj2的类型为：" << typeid(decltype(tmpobj2)).name() << endl;

    //（1）正向排列数字生成一个类型——Integer_Sequence
    //研究如何通过类型make_integer_sequence<int,5>得到类型 std::integer_sequence<int,0,1,2,3,4>

    //(i)Integer_Sequence_T<int, 4> tmpobj3;   //等价于
    //(i)Integer_Sequence<int, 4>::type tmpobj3;   //把type看成函数调用
    //(i)    using type = typename IntSeq_PushBack<  typename Integer_Sequence< int,3 >::type,3 >::type;
    //(i)        //展开上行后面这个 Integer_Sequence< int,3 >::type 如下:
    //(i)        using type = typename IntSeq_PushBack<  typename Integer_Sequence< int,2 >::type,2 >::type;
    //(i)            //展开上行后面这个 Integer_Sequence< int,2 >::type 如下:
    //(i)            using type = typename IntSeq_PushBack<  typename Integer_Sequence< int,1 >::type,1 >::type;
    //(i)                //展开上行后面这个 Integer_Sequence< int,1 >::type ，调用的是特化版本
    //(i)                using type = std::integer_sequence<int, 0>;  //递归结束，开始往回返
    //(i)            //递归往回返的时候注意IntSeq_PushBack是向std::integer_sequence末尾插入内容
    //(i)            using type = std::integer_sequence<int, 0,1>
    //(i)        using type = std::integer_sequence<int, 0,1,2>
    //(i)    using type = std::integer_sequence<int, 0,1,2,3>
    //(i)//最终结果
    //(i) std::integer_sequence<int, 0,1,2,3>

    _nmsp1::Integer_Sequence_T<int, 4> tmpobj3;
    cout << "tmpobj3的类型为：" << typeid(decltype(tmpobj3)).name() << endl;

    return 0;
}
