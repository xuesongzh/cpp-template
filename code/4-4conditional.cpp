
#include <iostream>

using namespace std;

namespace _nmsp1 {
/*template <bool b, class T, class U> //泛化版本
struct conditional
{
        using type = T; //type类型别名
};

template <class T, class U>
struct conditional<false, T, U>
{
        using type = U;
};*/

}

int main() {
    //第四节 std::conditional
    // C++11引入的类模板，表示的是一种编译期的分支逻辑
    //如果b值为true，那么type这个类型别名所代表的类型就是conditional类模板的第二个模板参数T，
    //否则就是conditional类模板第三个模板参数U。所以这个类模板看起来表达的是一种if-then-else逻辑。
    //能力：根据给进来的布尔值不同，做到了让一个变量可能会有多种不同的类型的效果——范例中变量可能是int类型，也可能是double类型。
    std::conditional<true, int, double>::type tmp1;
    std::conditional<false, int, double>::type tmp2;

    cout << "tmp1的类型为：" << typeid(decltype(tmp1)).name() << endl;  // int
    cout << "tmp2的类型为：" << typeid(decltype(tmp2)).name() << endl;  // double

    //需求：定义一个名字叫做tsvar的变量，根据某个常量（取名为j）值的不同，tsvar变量的类型也不同:
    // a)j如果大于100，那么tsvar的类型是double类型，
    // b)j如果在80-100之间，那么tsvar的类型是float类型，
    // c)j如果在40-80之间，那么tsvar的类型是int类型，
    // d)j如果不超过40，那么tsvar的类型是char类型。
    // std::conditional通常适合实现真或者假两种分支，如果要支持多分支，那么可以看到，写出来的代码非常难看。
    /*
        int i = 35;
        if (i > 100) {
            cout << "i > 100" << endl;
        } else {
            if (i > 80) {
                cout << "i > 80并且 <=100" << endl;
            } else {
                if (i > 40) {
                    cout << "i > 40并且 <= 80" << endl;
                } else {
                    cout << "i <= 40" << endl;
                }
            }
        }
     */
    constexpr int j = 135;  //假设给进去35

    std::conditional<
        (j > 100), double,  //值>100，tsvar是double*
        std::conditional<
            (j > 80), float,  //值在80-100之间，那么tsvar是float类型。
            std::conditional<
                (j > 40), int,  //值在40-80之间，那么tsvar是int类型。
                char            //值不超过40，tsvar是char类型
                >::type>::type>::type tsvar;

    cout << "tsvar的类型为:" << typeid(decltype(tsvar)).name() << endl;

    return 0;
}
