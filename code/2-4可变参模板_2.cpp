
#include <iostream>

using namespace std;

namespace _nmsp1 {
template <typename... T>
auto add_val(T... args) {
    // return (... + args); //圆括号不能省略，否则出现编译错误，一元左折
    return (args + ...);  //一元右折
}

template <typename... T>
auto sub_val_left(T... args) {
    return (... - args);  //一元左折
}

template <typename... T>
auto sub_val_right(T... args) {
    return (args - ...);  //一元右折
}

template <typename... T>
auto sub_val_left_b(T... args) {
    return (220 - ... - args);  //二元左折，220就是init
}

template <typename... T>
void print_val_left_b(T... args) {
    (cout << ... << args);  //二元左折，但init是cout，运算符代表的是 <<
}

template <typename... T>
auto sub_val_right_b(T... args) {
    return (args - ... - 220);  //二元右折
}
}  // namespace _nmsp1

namespace _nmsp2 {
template <typename... T>
auto print_result(T const&... args) {
    (cout << ... << args) << " 结束" << endl;
    return (... + args);  //计算一下参数和值
}

template <typename... T>
void print_calc(T const&... args) {
    cout << print_result(2 * args...) << endl;  //“2 * args...“就是可变参表达式
    // print_result(2 * args...) 等价于 print_result(2 * 10, 2*20, 2*30, 2*40)

    // print_result(2 * args); //不行
    // print_result(args... * 2);  //不行
    // print_result(args * 2...); //不行
    // print_result(args * 2 ...); //可以
    // print_result((args * 2) ...); //可以
    print_result(args + args...);  //可以，等价于print_result(10+10,20+20,30+30,40+40);
}

}  // namespace _nmsp2

int main() {
    //四：可变参模板
    //（2）折叠表达式:Fold Expressions，C++17
    //目的：计算某个值（表达式的结果当然是一个值）
    //该值的特殊性在于：它与所有可变参有关，而不是与单独某个可变参有关。需要所有可变参都参与计算，才能求出该值。
    //折叠表达式有四种格式：一元左折、一元右折，二元左折、二元右折
    //注意，每种格式的折叠表达式都需要用圆括号括住。
    //左折：就是参数从左侧开始计算  右折：参数从右侧开始计算

    //（2.1）一元左折（unary left fold）
    //格式： (... 运算符 一包参数)
    //计算方式：((( 参数1  运算符  参数2） 运算符  参数3）....运算符 参数N）
    cout << _nmsp1::add_val(10, 20, 30) << endl;

    //（2.2）一元右折（unary right fold）
    //格式： (一包参数 运算符 ...)
    //计算方式：( 参数1  运算符  ( ... (参数N-1  运算符  参数N)))
    cout << _nmsp1::sub_val_left(10, 20, 30, 40) << endl;   //-80：((10-20)-30)-40
    cout << _nmsp1::sub_val_right(10, 20, 30, 40) << endl;  //-20：10-(20-(30-40))

    //（2.3）二元左折（binary left fold）
    //格式：(init 运算符 ... 运算符 一包参数)
    //计算方式：(((init 运算符 参数1) 运算符 参数2) ... 运算符 参数N)
    // init表示 一个初始的东西，它可能是一个值，也可能是个其他东西。
    cout << _nmsp1::sub_val_left_b(10, 20, 30, 40) << endl;  // 120：(((220-10)-20)-30)-40
    _nmsp1::print_val_left_b(10, "abc", 30, "def");          // 10abc30def

    //（2.4）二元右折（binary right fold）
    //格式：(一包参数 运算符 ... 运算符 init)
    //计算方式：（参数1 运算符 （...（参数N 运算符 init )))
    cout << _nmsp1::sub_val_right_b(10, 20, 30, 40) << endl;  // 200：10-(20-（30-（40-220)))

    //（3）可变参表达式
    cout << _nmsp2::print_result(10, 20, 30, 40) << endl;
    _nmsp2::print_calc(10, 20, 30, 40);

    return 0;
}
