
#include <iostream>

using namespace std;

namespace _nmsp1 {
//计算n的阶乘的泛化版本
template <int n_v>
struct Factorial {
    enum {
        value = n_v * Factorial<n_v - 1>::value
    };
};

//计算n的阶乘的特化版本，用于做递归调用的出口
template <>
struct Factorial<1> {
    enum {
        value = 1
    };
};

//--------------------
template <typename T>
struct AddPoint {  //类型元函数
    using type = T*;
};

//--------------------
template <typename T, int U>  // T：元素类型，U：数组大小
// auto DotProduct(T* array1, T *array2)
inline auto DotProduct(T* array1, T* array2) {
    T dpresult = T{};  //零初始化
    for (int i = 0; i < U; ++i) {
        dpresult += array1[i] * array2[i];
    }
    return dpresult;
}
}  // namespace _nmsp1

namespace _nmsp2 {
//泛化版本
template <typename T, int U>  // T：元素类型，U：数组大小
struct DotProduct {
    static T result(const T* a, const T* b) {
        return (*a) * (*b) + DotProduct<T, U - 1>::result(a + 1, b + 1);
    }
};

//特化版本，用于做递归调用的出口
template <typename T>
struct DotProduct<T, 0> {
    static T result(const T* a, const T* b) {
        return T{};
    }
};

}  // namespace _nmsp2

int main() {
    // cout << _nmsp1::Factorial<5>::value << endl;
    // _nmsp1::AddPoint<const char>::type s = "I Love China!";

    //第二节 混合元编程
    //(a)程序员写出一段元编程代码
    //(b)编译器根据这段代码编译（生成）出来一段新代码，实现程序真正功能的是这段生成的新代码。
    //(c)编译器会对这段新代码进行编译，产生出最终的可执行程序。
    //混合元编程可以看成是运行期C++代码的生成器。

    //（1）常规的计算点积范例
    // a)数组a有三个元素，a[0],a[1],a[2]，值分别是1，2,3
    // b)数组b有三个元素，b[0],b[1],b[2]，值分别是4，5,6
    // c)a和b的点积是一个数值，结果为：a[0]*b[0] + a[1]*b[1]  + a[2]*b[2]  =1*4 + 2*5 + 3*6 = 32
    int a[] = {1, 2, 3};
    int b[] = {4, 5, 6};
    int result = _nmsp1::DotProduct<int, 3>(a, b);
    cout << result << endl;

    //(2)混合元编程计算点积
    //（2.1）范例演示
    // dpresult += array1[0] * array2[0];
    // dpresult += array1[1] * array2[1];
    // dpresult += array1[2] * array2[2];
    // DotProduct<int,3>被实例化，DotProduct<int,2>被实例化，DotProduct<int,1>被实例化，DotProduct<int, 0>被实例化
    // DotProduct<int, 3>::result(a, b) =
    //(*a) * (*b) + DotProduct<int, 2>::result(a + 1, b + 1) =
    //(*a) * (*b) + (*(a+1)) * (*(b+1)) + DotProduct<int, 1>::result(a + 2, b + 2) =
    //(*a) * (*b) + (*(a+1)) * (*(b+1)) + (*(a+2)) * (*(b+2)) +0
    // 0=DotProduct<int, 0>::result(a + 3, b + 3)返回的值
    //编译器经过编译后产生了int result =  (*a) * (*b) + (*(a+1)) * (*(b+1)) + (*(a+2)) * (*(b+2))
    int result = _nmsp2::DotProduct<int, 3>::result(a, b);
    cout << result << endl;

    //（2.2）C++编译的两个阶段
    //把整个编译过程分成两个阶段：前期阶段   后期阶段
    // a)前期阶段：此阶段的C++编译器实际充当解释器的角色，直接针对程序员开发的C++源码（元编程代码）进行解释执行，
    // 这一阶段的工作成果就是产生了一系列的C++代码（所以元编程才被看做 运行期 C++代码生成器）。
    // b)后期阶段：针对前期阶段产生的结果代码进行编译、链接，最终生成可执行程序。

    //（2.3）范例演示的扩展——代码的智能化产生与膨胀
    // int result = (*a) * (*b) + (*(a + 1)) * (*(b + 1))  + ......... + (*(a + 11)) * (*(b + 11))
    // vs 2019编译器在 针对元编程产生一系列C++代码 方面已经具备了相当的智能性——通过一些函数调用避免产生过分冗长的C++代码。
    //_nmsp2::DotProduct<int, 12>::result(a, b)产生了代码膨胀（最终生成的可执行程序尺寸会变大）

    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int b[] = {4, 5, 6, 7, 8, 9, 1, 2, 3, 10, 11, 12};
    int result = _nmsp2::DotProduct<int, 12>::result(a, b);
    cout << result << endl;

    int result2 = _nmsp2::DotProduct<int, 12>::result(a, b);

    // DotProduct<int, 0>、DotProduct<int, 1>、DotProduct<int, 2>。。。。DotProduct<int, 12>
    // DotProduct<int,4>::result ,DotProduct<int,7>::result ,DotProduct<int,10>::result

    return 0;
}
