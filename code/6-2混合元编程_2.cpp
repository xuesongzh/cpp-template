
#include <iostream>

using namespace std;

namespace _nmsp3 {
//泛化版本
template <int x_v, int y_v>
struct InstantiationObServe {
    // static const int value = (x_v > y_v) ? InstantiationObServe<x_v - 1, y_v>::value : InstantiationObServe<x_v, x_v>::value;

    using TmpType = typename std::conditional<(x_v > y_v), InstantiationObServe<x_v - 1, y_v>,
                                              InstantiationObServe<x_v, x_v> >::type;

    // static const int value = TmpType::value;
    // enum {value = TmpType::value};
    static inline const int value = TmpType::value;
};

//特化版本
template <int x_v>
struct InstantiationObServe<x_v, x_v> {
    // static const int value = x_v; //int可以用auto代替，书写更方便
    // enum {value = x_v};
    static inline const int value = x_v;
};
}  // namespace _nmsp3

namespace _nmsp4 {
struct TST {
    // static const int mystatic = 1; //int相关类型char,unsigned,int,short等
    // static inline double mystatic2 = 12.6;
    static constexpr double mystatic2 = 12.6;
};
}  // namespace _nmsp4

int main() {
    //第二节 混合元编程
    //（2.4）类模板实例化进一步观察
    //元编程时小心使用 条件运算符，因为不管条件是否成立，所涉及到的类都可能被实例化出来。
    // std::conditional比条件运算符（?:）更有优势的地方。
    //元编程 “计算完整性”概念，包含几点：
    // a)状态变量：指的是InstantiationObServe类模板中的模板参数。
    // b)迭代构造（循环构造）：通过在InstantiationObServe模板中融入递归编程技术。
    // c)执行路径的选择：使用条件运算符（或者std::conditional)以及InstantiationObServe类模板的特化（达到递归结束的效果），
    //当然也可以调用其他元函数。
    // d)整数对象（整数运算）：静态成员变量value（或者枚举类型value），其他功能就等价于变量（常量）的功能。

    //元编程中不能使用变量（编译期间能接受的只有静态常量），传统意义上的分支和循环在元编程中只能通过条件运算符、特化、递归等手段来实现。
    //所以这种编程风格常常也被称为 函数式编程。

    //（2.5）inline静态成员变量（C++17中引入）
    // c++11 constexpr，c++17开始，constexpr自带inline属性
    // static inline const double mystatic2 = 12.6;
    // static constexpr double mystatic2 = 12.6;

    cout << _nmsp3::InstantiationObServe<6, 4>::value << endl;

    return 0;
}
