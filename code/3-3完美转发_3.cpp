
#include <iostream>

using namespace std;
#pragma warning(disable : 4996)

namespace _nmsp1 {
class Human {
 public:
    //构造函数
    // Human(const string& tmpname) : m_sname(tmpname) {
    //     cout << "Human(const string &tmpname)执行" << endl;
    // }
    // // Human(string&& tmpname) :m_sname(tmpname)
    // Human(string&& tmpname) : m_sname(std::move(tmpname)) {  // move并不具备移动能力，把一个左值转换成一个右值。
    //     cout << "Human(string&& tmpname)执行" << endl;
    // }

    //构造函数模板
    template <typename T>
    Human(T&& tmpname) : m_sname(std::forward<T>(tmpname)) {
        cout << "Human(T&& tmpname)执行" << endl;
    }

    //拷贝构造函数
    Human(const Human& th) : m_sname(th.m_sname) {
        cout << "Human(const Human& th)拷贝构造函数执行" << endl;
    }

    //移动构造函数
    Human(Human&& th) : m_sname(std::move(th.m_sname)) {
        cout << "Human(Human&& th)移动构造函数执行" << endl;
    }

 private:
    string m_sname;
};
}  // namespace _nmsp1

namespace _nmsp2 {
void funcLast1(int v1, int& v2) {  //目标函数
    ++v2;
    cout << v1 + v2 << endl;
}

int funcLast2(int v1, int& v2) {  //目标函数
    ++v2;
    cout << v1 + v2 << endl;
    return v1 + v2;
}

//支持任意数量、类型参数的完美转发
template <typename F, typename... T>
void funcMiddle1(F f, T&&... t) {
    f(std::forward<T>(t)...);
}

template <typename F, typename... T>
// auto funcMiddle(F f, T&&... t)->decltype(  f(std::forward<T>(t)...)   )
decltype(auto) funcMiddle2(F f, T&&... t) {
    return f(std::forward<T>(t)...);
}

}  // namespace _nmsp2

namespace _nmsp3 {
//目标函数
void funcLast(char* p) {
    // if (p != NULL)
    if (p != nullptr) {
        strncpy(p, "abc", 3);
    }
}

//转发函数
template <typename F, typename... T>
void funcMiddle(F f, T&&... t) {
    f(std::forward<T>(t)...);
}

}  // namespace _nmsp3

int main() {
    //第三节 完美转发
    //（4）在构造函数模板中使用完美转发
    string sname = "ZhangSan";
    _nmsp1::Human myhuman1(sname);           //左值
    _nmsp1::Human myhuman2(string("LiSi"));  //临时对象，右值。"LiSi"是const char[5]类型，而string("LiSi")是string类型。

    _nmsp1::Human myhuman3(myhuman1);             //实际编译器去调用了构造函数模板，而不是调用了拷贝构造函数。 std::enable_if
    _nmsp1::Human myhuman4(std::move(myhuman1));  //调用了移动构造函数

    const _nmsp1::Human myhuman5(string("WangWu"));
    _nmsp1::Human myhuman6(myhuman5);  //调用了拷贝构造函数

    //（5）在可变参数模板中使用完美转发
    //（5.1）常规的在可变参模板使用完美转发
    int j = 70;
    _nmsp2::funcMiddle1(_nmsp2::funcLast1, 20, j);
    cout << "j = " << j << endl;  // 71

    //（5.2）将目标函数中的返回值通过转发函数返回给调用者函数
    //用到的技术：auto结合decltype构成返回类型后置语法。
    int k = _nmsp2::funcMiddle2(_nmsp2::funcLast2, 20, j);
    cout << "j = " << j << endl;
    cout << "k = " << k << endl;

    //（6）完美转发失败的情形
    //使用NULL或者0作为空指针进行参数传递时导致完美转发失败的情况。
    // C++11引入nullptr(空指针)

    char* p = new char[100];
    memset(p, 0, 100);
    _nmsp3::funcMiddle(_nmsp3::funcLast, NULL);  //报错
    _nmsp3::funcLast(NULL);
    _nmsp3::funcMiddle(_nmsp3::funcLast, nullptr);

    return 0;
}
