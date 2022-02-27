
#include <boost/type_index.hpp>
#include <iostream>

using namespace std;
//#pragma warning(disable : 4996)

namespace _nmsp1 {
template <bool var>
struct BoolConstant {
    using type = BoolConstant;  //写成using type = BoolConstant<val>;也行
    static constexpr bool value = var;
};
using TrueType = BoolConstant<true>;
using FalseType = BoolConstant<false>;

template <typename T, bool val>
struct AClass {
    AClass() {
        cout << "AClass::AClass()执行了" << endl;
        /*
                if (val)
                // if constexpr (val){
                    T tmpa = 15;
                } else {
                    T tmpa = "abc";  // int tmpa = "abc";    ---if constexpr：编译期间if语句。
                }
         */
        AClassEx(BoolConstant<val>());  //创建一个临时对象
    }

    void AClassEx(TrueType abc) {
        T tmpa = 15;
    }

    void AClassEx(FalseType) {
        T tmpa = "abc";
    }
};
}  // namespace _nmsp1

int main() {
    //第二节 std::true_type和std::false_type
    //是两个类型（类模板）
    // using true_type = integral_constant<bool,true>;
    // using false_type = integral_constant<bool,false>;
    //注意区分true_type，false_type与true,false的区别。
    // true_type，false_type：代表类型（类类型）
    // true,false：代表值
    // bool代表true也可以代表false。而true_type类型代表的就是true，false_type类型代表的就是false.

    // a)TrueType和FalseType代表一个类类型，TrueType（std::true_type）代表一种true(真)的含义，而False_Type(std::false_type)代表一种false（假）的含义。
    // b)一般是当作基类被继承。当作为基类被继承时，派生类也就具备了真或假的这种意味。
    // is，比如is_pointer、is_union、is_function等类模板，都是继承自类似BoolConstant<true>或者BoolConstant<false>这样的基类来实现的。
    // c)可以当作一种返回类型被使用，比如：
    //_nmsp1::FalseType myfunc1(); //返回“假”这种含义
    //_nmsp1::TrueType myfunc2(); //返回“真”这种含义

    _nmsp1::AClass<int, true> tmpobj1;
    _nmsp1::AClass<string, false> tmpobj2;

    return 0;
}
