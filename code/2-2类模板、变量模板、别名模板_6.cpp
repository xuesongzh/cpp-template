
#include <iostream>
#include <map>

using namespace std;

namespace _nmsp1 {
// g_myvar的泛化版本
template <typename T>
T g_myvar{};  //写成T g_myvar =0;也不会出现语法错误，但该写法一般只适合数值类型
              //{}是一种对变量的初始化方式，叫做零初始化。int = 0，指针=nullptr,bool = false
//全特化
template <>
char g_myvar<double>{};

//偏特化
template <typename T>
T g_myvar<T*>{120};  //要求T*必须依赖于T
                     // T g_myvar<double*>{120};

}  // namespace _nmsp1

namespace _nmsp2 {
// g_myvar的泛化版本
template <typename T = int>
T g_myvar;

}  // namespace _nmsp2

namespace _nmsp3 {
template <typename T, int value>
T g_myvar[value];

}

namespace _nmsp4 {
template <typename T>
struct B {
    const static T value = {160};  // const也可以写成constexpr,{}也可以不加
};

template <typename T>
int g_myvar4 = B<T>::value;  //注意g_myvar4是个变量模板

}  // namespace _nmsp4

namespace _nmsp5 {
template <typename T>
class D {
 public:
    template <typename W>
    static W m_tpi;  //静态成员变量模板声明
};

template <typename T>
template <typename W>
W D<T>::m_tpi = 5;

}  // namespace _nmsp5

namespace _nmsp6 {
//别名模板
template <typename T>
using str_map_t = std::map<std::string, T>;

template <typename T1>
class E {
    //成员别名模板
    template <typename T2>
    using str_map_t = std::map<std::string, T2>;

 public:
    str_map_t<int> map1;
};
}  // namespace _nmsp6

int main() {
    //八：变量模板与成员变量模板
    //变量模板:Variable Templates。C++14新标准中引入的(一般放在.h头文件中）
    //从感觉上，变量模板与函数模板有些类似，看起来像一个没有参数，但是有返回值的函数模板。
    //三种零初始化方式（T表示一个类型）
    // a)T(); //比如int temp1 = int();
    // b)T t = {}; //比如 int temp2 = {};
    // c)T {}; //比如int temp3 = int{};
    _nmsp1::g_myvar<float> = 15.6f;
    _nmsp1::g_myvar<int> = 13;
    cout << _nmsp1::g_myvar<float> << endl;
    cout << _nmsp1::g_myvar<int> << endl;

    //（8.1）变量模板的特化
    // a)变量模板的全特化
    //变量模板特化的时候，并不需要正在特化的类型（double）与这个变量模板的类型（char)保持一致。
    _nmsp1::g_myvar<double> = '2';  //这个使用的就是刚刚特化版本的g_myvar变量模板
    cout << _nmsp1::g_myvar<double> << endl;
    printf("%d\n", _nmsp1::g_myvar<double>);  // asiic码

    // b)变量模板的偏特化
    cout << _nmsp1::g_myvar<int*> << endl;
    cout << _nmsp1::g_myvar<int> << endl;

    //（8.2）默认模板参数
    _nmsp2::g_myvar<int> = 13;
    _nmsp2::g_myvar<> = 26;                //尖括号不能省略,_nmsp2::g_myvar<>等价于_nmsp2::g_myvar<int>
    cout << _nmsp2::g_myvar<int> << endl;  // 26
    cout << _nmsp2::g_myvar<> << endl;     // 26

    //（8.3）非类型模板参数
    for (int i = 0; i < 15; ++i) {
        // g_myvar<int,15>写法一出现就表示定义了g_myvar<int,15>[15]这个大小为15个元素的int类型数组。
        _nmsp3::g_myvar<int, 15>[i] = i;
        cout << _nmsp3::g_myvar<int, 15>[i] << endl;
    }

    //（8.4）变量模板的另一种形式
    cout << _nmsp4::g_myvar4<int> << endl;  // 160,g_myvar4<int>相当于B<int>::value
    _nmsp4::g_myvar4<int> = 152;
    cout << _nmsp4::g_myvar4<int> << endl;  // 152
    cout << _nmsp4::B<int>::value << endl;  // 160

    //（8.5）成员变量模板
    cout << _nmsp5::D<float>::m_tpi<int> << endl;
    _nmsp5::D<float>::m_tpi<int> = 150;
    cout << _nmsp5::D<float>::m_tpi<int> << endl;

    //九：别名模板与成员别名模板
    //别名模板 = "Alias Templates"，C++11新标准中引入的，引入的目的不但能简化书写，而且可以达到一些通过其他手段难以达到的效果。
    _nmsp6::str_map_t<int> map1;
    map1.insert({"first", 1});
    map1.insert({"second", 2});

    _nmsp6::E<float> obja;
    obja.map1.insert({"first", 1});
    obja.map1.insert({"second", 8});

    return 0;
}