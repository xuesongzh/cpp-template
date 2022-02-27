
#include <iostream>

using namespace std;

namespace _nmsp1 {
void myptfunct() {
}

//可变参函数模板
template <typename... T>   //...代表参数包
void myvtfunct(T... args)  // T称为“可变参类型”，T中包含的是0到多个不同的类型（一包类型）
                           // args称为一包/一堆 参数（函数模板的形参：0个到多个），每个参数的类型可以各不相同。
{
    cout << "-----------begin-----------" << endl;
    cout << sizeof...(args) << endl;  //收到的参数数量，sizeof...固定语法，C++11中引入，用于表示 收到的模板参数个数或者类型数量。
                                      // sizeof...针对的只能是这种...的可变参，后面圆括号中可以是函数模板的形参args，也可以是类型模板参数T.
    cout << sizeof...(T) << endl;     //收到的类型数量
    cout << "-----------end-----------" << endl;
}

// 再实现一个同名的递归终止函数(这是个真正的函数)，位置放在参数包展开函数的前面
// void myvtfunct() {  //这是个普通函数，而不是函数模板
//     cout << "参数包展开时执行了递归终止函数myvtfunct()" << endl;
// }

// 先实现参数包展开函数
template <typename T, typename... U>
void myvtfunct(T firstarg, U... otherargs) {
    cout << "收到的参数值：" << firstarg << endl;
    // myvtfunct(otherargs...); //递归调用，注意塞进来的是一包形参，这里的...不能省略

    // C++17中增加了一个语句，叫做“编译期间if语句（constexpr if)”。
    // if constexpr()....   //constexpr代表“常量”的意思，或者代表“编译时求值”的意思。
    if constexpr (sizeof...(otherargs) > 0) {  // constexpr必须有否则无法成功编译，圆括号中是常量表达式。
        myvtfunct(otherargs...);               // 不需要递归终止函数
    }

    //深入认识if constexpr
    // a)不满足条件的分支，也同样会被编译器编译(被编译器进行语法检查）。
    // if constexpr (sizeof...(otherargs) > 100) {  //不管if constexpr条件是否成立，{}中的代码行都会被编译
    //     testfunc();
    // }

    // b)if constexpr所指定的条件必须是常量：理解成普通if语句，只是判断条件从执行期间挪到了编译期间
    //总结：if constexpr的存在，完善了模板与泛型编程中的程序执行路径选择问题。
    /*
        int i = 8;
        if constexpr (i > 8){

        }
    */
}
}  // namespace _nmsp1

namespace _nmsp2 {
template <typename... T>
void myfunc(T... arg) {
    cout << "myfunc(T... arg)执行了!" << endl;
}

template <typename... T>
void myfunc(T *...arg) {
    cout << "myfunc(T*... arg)执行了!" << endl;
}

void myfunc(int arg) {
    cout << "myfunc(int arg)执行了!" << endl;
}

}  // namespace _nmsp2

int main() {
    //四：可变参模板
    //英文：Variadic Templates ，C++11
    //允许模板定义中包含 0到多个（任意个）模板参数。

    //（1）可变参函数模板
    //（1.1）基本含义
    //可变参函数模板中，传递进来的一包实参怎样展开：一般都采用递归函数的方式展开参数包。
    //要求在可变参函数模板代码中，有一个参数包展开函数和一个同名的递归终止函数。
    _nmsp1::myvtfunct();
    _nmsp1::myvtfunct(10, 20);
    _nmsp1::myvtfunct(10, 25.8, "abc", 68);
    _nmsp1::myvtfunct<double, double>(10, 25.8, "abc", 68, 73);  //指定部分类型，让编译器去推断另一部分类型，是允许的。

    _nmsp1::myvtfunct(10, "abc", 12.7);

    //（1.2）重载
    //一般来说，调用普通函数和调用函数模板都合适的时候，编译器优先选择普通函数。
    //把握不准时，可以多做测试。
    _nmsp2::myfunc(NULL);
    _nmsp2::myfunc(nullptr);  // nullptr是空指针
    _nmsp2::myfunc((int *)nullptr);

    return 0;
}
