
#include <boost/type_index.hpp>
#include <iostream>
#include <vector>

using namespace std;

//函数模板
template <typename T>
// void myfunc1(T& tmprv)
// void myfunc2(const T& tmprv)
void myfunc3(T* tmprv) {
    cout << "--------------------------------begin----------------" << endl;
    using boost::typeindex::type_id_with_cvr;
    cout << "T=" << type_id_with_cvr<T>().pretty_name() << endl;                    //显示T的类型
    cout << "tmprv=" << type_id_with_cvr<decltype(tmprv)>().pretty_name() << endl;  //显示tmprv的类型
    cout << "--------------------------------end------------------" << endl;

    // tmprv = 15;
}

int main() {
    //第二节 理解函数模板类型推断、查看类型推断结果、auto类型推断
    //（1）如何查看类型推断结果
    //当前要解决的问题：如何查看类型推断结果——指编译器给我们进行类型推断的结果
    //最终目的：希望大家通过“查看编译器类型推断结果”的手段来学习并掌握C++类型推断的规则。
    //如何查看编译器帮助我们进行类型推断的结果。依赖Boost库——如何利用这个库把编译器推断出来的类型信息打印出来。

    //（2）理解函数模板类型推断
    // myfunc中T的类型不仅仅取决于实参，还取决于tmprv的类型（const T&）有关。
    // 函数模板的形参（tmprv）是如下类型时编译器推断出的 类型模板参数的类型（T），以及最终的函数形参类型（tmprv）
    //（2.1）引用或指针类型
    //(1)若实参是引用类型，那么引用部分会被忽略，T不会被推导为引用类型，这个需要记一下。
    //(2)当向引用类型的形参tmprv传入const类型实参时了，那么形参tmprv会成为const引用（原来是个引用）。
    //这里可以看到，实参的const属性会成为类型模板参数T类型推导的组成部分，所以不用担心在myfunc中能够修改原来const属性的实参。
    int i = 18;        // i的类型是int
    const int j = i;   // j的类型是const int
    const int& k = i;  // k的类型是const int &
    myfunc1(i);        // T=int，tmprv = int &
    myfunc1(j);        // T=int const  tmprv=int const &
    myfunc1(k);        // T=int const  tmprv=int const &

    // T中的const没有了，因为函数模板的形参tmprv里出现const。但只要实参带const，形参tmprv中终究还是会带着const。
    myfunc2(i);  // T=int   tmprv=int const &
    myfunc2(j);  // T=int   tmprv=int const &
    myfunc2(k);  // T=int   tmprv=int const &

    //通过上面的范例，小节一下编码技巧：
    // a)形参中引用有两个作用：1是可以通过对形参的修改来修改实参 2是传递引用比传值效率高
    //所以，函数模板中的形参建议优先考虑“T &tmprv”这样的形态，
    //这样的形参就不怕实参中的引用被忽略掉而导致开发者想通过对形参的修改达到修改实参的本意无法达成。
    // b)如何既想享受形参为引用带来的效率上的提高，又不希望通过形参来修改实参，则函数模板中的形参建议考虑“const T &tmprv”这样的形态。

    //(3)如果tmprv是个指针或者引用
    // tmprv中如果没有const，则实参中的const会被带到类型T中去。如果tmprv中有const，则T类型中不会带const。

    int i = 18;
    const int* pi = &i;
    myfunc3(&i);  // T = int   tmprv = int *
    myfunc3(pi);  // T = int const    tmprv = int const *

    return 0;
}
