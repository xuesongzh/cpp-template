
#include <iostream>
//#include <map>
//#include <vector>
//#include <list>
//#include <functional>

using namespace std;
//
//#pragma warning(disable : 4996)

namespace _nmsp1 {
// TC的泛化版本
// template <typename T,typename U>
template <typename T = int, typename U = int>
struct TC {
    TC() {
        cout << "TC泛化版本的构造函数" << endl;
    }
    void functest1() {
        cout << "functest1泛化版本" << endl;
    }
};

// TC的特化版本
// template <typename T = char> //类模板偏特化版本中的类型模板参数不可以有缺省值
template <typename T>
struct TC<T, int> {
};

}  // namespace _nmsp1

namespace _nmsp2 {
template <typename T, typename U = T *>
struct TC {
};
}  // namespace _nmsp2

namespace _nmsp3 {

//声明1，指定了V和W
template <typename T, typename U, typename V = int, typename W = char>
struct TC;

//声明2，指定U
template <typename T, typename U = char, typename V, typename W>
struct TC;

//定义泛化版本的TC
template <typename T, typename U, typename V, typename W>
struct TC {
    //...
};

typedef TC<int, float> IF_TC;
using IF_TCU = TC<int, float>;

}  // namespace _nmsp3

namespace _nmsp4 {
// template <typename T , typename U ,size_t arrsize=8>
template <typename T, typename U, auto arrsize = 8>
struct TC {
    T m_arr[arrsize];  //这个arrsize是在编译器期间，编译器就会传递进来arrsize的大小来确定数组m_arr的大小。
    void functest2();
};

// template <typename T, typename U, size_t arrsize>
template <typename T, typename U, auto arrsize>
void TC<T, U, arrsize>::functest2() {
    cout << "functest2泛化版本" << endl;
}

}  // namespace _nmsp4

namespace _nmsp5 {
template <const char *p>
struct TC2 {
    TC2() {
        printf("TC2::TC2执行了,p= %s\n", p);
    }
};
// const char* g_s = "hello"; //全局指针
const char g_s[] = "hello";
}  // namespace _nmsp5

int main() {
    //三：缺省参数
    //（3.1）常规缺省参数
    //类型模板参数缺省值的规矩：如果某个模板参数有缺省值，那么从这个有缺省值的模板参数开始，后面的所有模板参数都得有缺省值。
    _nmsp1::TC<> mytc5;        //使用了缺省模板参数，所以<>中啥也不用提供
    _nmsp1::TC<double> mytc6;  //<>中第一个类型不使用缺省参数，第二个类型使用缺省参数

    //（3.2）后面的模板参数依赖前面的模板参数
    _nmsp2::TC<double> mytc5;
    _nmsp2::TC<double, int> mytc6;

    //（3.3）在模板声明中指定缺省参数
    _nmsp3::TC<int> mytc;  //第二、三、四个模板参数采用缺省值，所以<>里只提供了一个类型模板实参

    //四：类型别名
    //考虑到类型名比较长，所以一般都用typedef或者using给这些类型名起一个额外的别名来简化书写。
    _nmsp3::IF_TC mytc10;   // IF_TC等价于TC<int, float> ,所以整个代码行等价于：_nmsp3::TC<int, float> mytc10;
    _nmsp3::IF_TCU mytc11;  // IF_TCU等价于TC<int, float>

    //五：非类型模板参数
    //数值是常量，类型一般也限制在整型、指针类型等等
    _nmsp4::TC<double, double> mytc30;  //缺省的第三个模板参数是8
    for (size_t i = 0; i < 8; ++i) {
        mytc30.m_arr[i] = static_cast<double>(i);
    }
    cout << mytc30.m_arr[7] << endl;  // 7

    _nmsp4::TC<double, double, 18> mytc31;
    mytc31.m_arr[10] = 16.8;
    cout << mytc31.m_arr[10] << endl;  // 16.8

    //(1)全局指针不能作为函数参数
    //(2)字符串常量也无法作为模板参数
    //为什么不允许浮点类型数字作为非类型模板参数,因为其保存的不是一个精确数字。
    // TC3<2.1111111>和TC3<2.11111109>
    _nmsp5::TC2<_nmsp5::g_s> mytc40;
    _nmsp5::TC2<"hello"> mytc41;

    return 0;
}
