
#include <iostream>

using namespace std;

namespace _nmsp1 {
//计算数组中元素的和值的函数模板
template <typename T>
T funcsum1(const T* begin, const T* end) {
    T sum{};  //零初始化，如果数值型变量被初始化为0，指针型变量被初始化为nullptr，bool类型变量被初始化为false。
    for (;;) {
        sum += (*begin);
        if (begin == end)
            break;
        ++begin;
    }
    return sum;
}

template <typename U, typename T>
U funcsum2(const T* begin, const T* end) {
    U sum{};
    for (;;) {
        sum += (*begin);
        if (begin == end)
            break;
        ++begin;
    }
    return sum;
}

}  // namespace _nmsp1

namespace _nmsp2 {

// fixed traits类模板的泛化版本
template <typename T>
struct SumFixedTraits;  //不需要实现代码，因为不需要用该版本进行实例化。

//各个fixed traits类模板的特化版本
//(1)给进来char类型时，返回的是int类型
template <>
struct SumFixedTraits<char> {  // char表示给进来的是char类型
    using sumT = int;          //类型别名sumT代表int类型（返回类型）
};

//(2)给进来int类型时，返回的是int64_t类型
template <>
struct SumFixedTraits<int> {  // int表示给进来的是int类型
    using sumT = int64_t;     //类型别名sumT代表int64_t类型（返回类型）
};

//(3)....其他给进来的是某个类型，返回的是另外一个类型，可以任意扩展出多个SumFixedTraits类模板的特化版本。

//-----------------------
template <typename T>
auto funcsum(const T* begin, const T* end) {
    using sumT = typename SumFixedTraits<T>::sumT;  //给进来一个类型（T），返回一个类型（sumT），这是fixed traits的运用。
    sumT sum{};
    for (;;) {
        sum += (*begin);
        if (begin == end)
            break;
        ++begin;
    }
    return sum;
}

}  // namespace _nmsp2

int main() {
    //第一节 萃取技术及fixed traits（固定萃取）演示
    // trait(萃取)技术用于对模板中的各种模板参数进行管理。
    // type traits：类型萃取
    //学习目的：
    //(a)了解标准库中许多trait技术的实现方法。
    //(b)灵活运用并组合这些实现方法，写出功能更强大，更优雅和实用的代码。
    // fixed traits（固定萃取）：主要用于  给进来一种类型，萃取出（得到）另外一种类型。

    //（1）一个常规范例
    // SumFixedTraits固定萃取类模板的作用：通过类型，得到另外一个类型。

    int myintarray1[] = {10, 15, 20};
    int myintarray2[] = {1000000000, 1500000000, 2000000000};  // 10亿，15亿，20亿
    char mychararray[] = "abc";                                // 97,98,99

    cout << _nmsp1::funcsum1(&myintarray1[0], &myintarray1[2]) << endl;         // int funcsum<int>(const int*,const int*);
    cout << _nmsp1::funcsum1(&myintarray2[0], &myintarray2[2]) << endl;         // 溢出
    cout << (int)(_nmsp1::funcsum1(&mychararray[0], &mychararray[2])) << endl;  // char funcsum<char>(const char*,const char*);

    cout << _nmsp1::funcsum2<int64_t>(&myintarray1[0], &myintarray1[2]) << endl;
    cout << _nmsp1::funcsum2<int64_t>(&myintarray2[0], &myintarray2[2]) << endl;
    cout << (int)(_nmsp1::funcsum2<int>(&mychararray[0], &mychararray[2])) << endl;

    cout << _nmsp2::funcsum(&myintarray1[0], &myintarray1[2]) << endl;  // int funcsum<int>(const int*,const int*);
    cout << _nmsp2::funcsum(&myintarray2[0], &myintarray2[2]) << endl;
    cout << (int)(_nmsp2::funcsum(&mychararray[0], &mychararray[2])) << endl;  // char funcsum<char>(const char*,const char*);

    return 0;
}
