
#include <iostream>
//#include <map>
//#include <vector>
//#include <list>
//#include <functional>

using namespace std;
//
//#pragma warning(disable : 4996)

namespace _nmsp1 {
//泛化：大众化，常规
template <typename T, typename U>
struct TC {
    TC() {
        cout << "TC泛化版本构造函数" << endl;
    }
    void functest1() {
        cout << "functest1泛化版本" << endl;
    }

    static int m_stc;  //声明一个静态成员变量
};

// template <>
void TC<double, int>::functest1() {  // functest1成员函数的全特化版本
    cout << "普通成员函数TC<double,int>::functest1的全特化" << endl;
}

template <typename T, typename U>
int TC<T, U>::m_stc = 50;  //定义静态成员变量

// template <>
int TC<double, int>::m_stc = 100;

//特别值得一提的是：如果进行了普通成员函数的全特化，或者是静态成员变量的全特化
// 那么，就无法用这些全特化时指定的类型来对整个类模板进行全特化了。
// template <>
// struct TC<double, int> {
// };

//-------------------
template <>  //全特化：所有类型模板参数都用具体类型代表，所以<>里就空了
struct TC<int, int> {
    TC() {
        cout << "TC<int,int>特化版本构造函数" << endl;
    }
    void functest1();
    void functest2();
};

// template <>
void TC<int, int>::functest1() {
    cout << "functest1特化版本" << endl;
}
void TC<int, int>::functest2() {
    cout << "functest2特化版本" << endl;
}

//-------------------------
template <typename U>
struct TC<float, U> {
    TC() {
        cout << "TC<float,U>偏特化版本构造函数" << endl;
    }
    void functest1();
};

template <typename U>
void TC<float, U>::functest1() {
    cout << "TC<float,U>::functest1偏特化版本" << endl;
}

//-------------------------
template <typename T, typename U>
struct TC<const T, U *> {
    TC() {
        cout << "TC<const T,U*>偏特化版本构造函数" << endl;
    }
    void functest1();
};
template <typename T, typename U>
void TC<const T, U *>::functest1() {
    cout << "TC<const T,U*>::functest1偏特化版本" << endl;
}

}  // namespace _nmsp1

int main() {
    //二：类模板的各种特化
    //一般来讲，所写的类模板都是泛化的类模板
    //特化的类模板是通过泛化的类模板来生成的，所以：得先要有泛化版本，才能有特化版本。
    //所谓特化版本，就是特殊对待的版本
    _nmsp1::TC<int, float> mytc;
    mytc.functest1();

    //（2.1）类模板的全特化
    //全特化：就是把TC这个泛化版本中的所有模板参数都用具体的类型来代替构成一个特殊的版本（全特化版本）。
    //在理解上：泛化版本的类模板与全特化版本的类模板，只是名字相同（都叫TC）
    //在其他方面，可以把实例化后的他们理解成是两个完全不同的类。
    _nmsp1::TC<int, int> mytc2;
    mytc2.functest1();
    mytc2.functest2();

    //（2.2）普通成员函数的全特化
    _nmsp1::TC<double, int> mytc3;
    mytc3.functest1();

    //（2.3）静态成员变量的全特化
    cout << "mytc3.m_stc = " << mytc3.m_stc << endl;

    //（2.4）类模板的偏特化（局部特化）
    //（2.4.1）模板参数数量上的偏特化
    _nmsp1::TC<float, int> mytc4;
    mytc4.functest1();

    //（2.4.2）模板参数范围上的偏特化
    // int ->const int.   T->T*  ,  T->T&    ,T->T&&
    _nmsp1::TC<const float, int *> mytc5;
    mytc5.functest1();

    return 0;
}
