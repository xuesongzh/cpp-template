
#include <iostream>

using namespace std;

void mf(const int& j) {}
void mf2(int&& k) {}
void mf3(int m) {}

template <typename T>
void myfunc(T&& tmprv) {
    //这里借助boost手段以得到准确的类型信息
    using boost::typeindex::type_id_with_cvr;
    cout << "T=" << type_id_with_cvr<T>().pretty_name() << endl;                          //显示T类型
    cout << "tmprv的类型=" << type_id_with_cvr<decltype(tmprv)>().pretty_name() << endl;  //显示tmprv类型
}

template <typename T>
class TmpClass {
 public:
    // TmpClass(T&& tmpvalue)
    template <typename T2>
    TmpClass(T2&& tmpvalue) {
        cout << "TmpClass::TmpClass()执行了" << endl;
    }
};

void lastfunc(int&& tmprv) {}

template <typename T>
void midfunc(T&& tmprv)  //转发----tmprv的类型 int &&，T 的类型是int
//虽然tmprv的类型是右值引用类型int&&，但是tmprv本身是个左值，因为tmprv可以放在赋值语句的左侧，所以是个左值。
{
    // lastfunc(tmprv);
    lastfunc(std::forward<T>(tmprv));
}

int main() {
    //第四节 元组(tuple)实现
    //（1）重要基础知识回顾
    //（1.1）左值、右值、左值引用、右值引用
    //左值引用只能绑定到左值上。但是const引用可以绑定左值，也可以绑定右值。
    //右值引用只能绑定到右值上。
    //（1.2）std::move究竟干了什么
    // std::move：类型转换函数，把一个左值转换成一个右值，如果原来是右值，使用std::move后没有啥效果。
    const int& j = 10;
    mf(10);
    int i = 10;
    int&& a = std::move(i);
    mf2(10);

    mf3(10);
    mf3(i);

    //（1.3）std::forward究竟干了什么
    // std::forward也是一个类型转换函数（函数模板）
    // std::forward是根据后面尖括号<>中的类型决定整个std::forward要转换成什么类型
    // 尖括号中是左值引用类型，则std::forward转换成左值，否则转换成右值。
    // std::forward有两个明显的作用：a)提高程序运行效率；b)用于完美转发
    //（1.4）万能引用（转发引用）
    //（1.5）完美转发
    //一个变量，从左值右值这个角度来讲必然是个左值，因为它能放在赋值运算符左侧。
    //一个变量，从类型这个角度，可能是左值引用类型，也可能是右值引用类型，也可能根本就不是个引用类型
    // 试比较int &i;int &&j; int k;

    int&& m = std::forward<int&&>(i);  //把i用数字10替换，效果一样
    // int&& n = std::forward<int&>(i); //左值
    int&& p = std::forward<int>(i);

    std::string str1 = "abc";
    std::string str2 = str1;
    // 因为使用了forward，导致std::forward<std::string&&>(str1)变成了右值引用类型
    std::string str3 = std::forward<std::string&&>(str1);  //此时，构造str3时会调用std::string的移动构造函数

    int k = 10;
    myfunc(k);
    myfunc(10);

    TmpClass<int> tcobj1(10);
    TmpClass<int> tcobj2(k);

    midfunc(10);  //右-左-右

    return 0;
}
