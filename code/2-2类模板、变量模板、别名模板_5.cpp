
#include <iostream>

using namespace std;

namespace _nmsp1 {
template <typename T1>
class A {
 public:
    template <typename T2>
    A(T2 v1, T2 v2);  //构造函数模板，引入了自己的模板参数T2，与类A的模板参数T1没有关系

 public:
    A(double v1, double v2) {
        cout << "A::A(double,double)执行了!" << endl;
    }
    A(T1 v1, T1 v2) {
        cout << "A::A(T1,T1)执行了!" << endl;
    }

 public:
    //拷贝构造函数模板
    template <typename U>
    A(const A<U>& other) {
        cout << "A::A(const A<U>& other)拷贝构造函数模板执行了!" << endl;
    }

    //拷贝赋值运算符模板
    template <typename U>
    A<T1>& operator=(const A<U>& other) {
        cout << "operator=(const A<U>& other)拷贝赋值运算符模板执行了!" << endl;
        return *this;
    }

    template <typename T3, typename T4>  //普通成员函数模板
    void myft(T3 tmpt, T4 tmpt2) {
        cout << "myft()泛化版本" << endl;
        cout << tmpt << endl;
        cout << tmpt2 << endl;
    }

    template <typename T4>  //偏特化
    void myft(int tmpt, T4 tmpt2);

    template <>  //全特化
    void myft(int tmpt, float tmpt2);

 public:
    template <typename U>
    class OtherC {
     public:
        void myfOC();
        /*{
                cout << "myfOC执行了" << endl;
        }*/
    };

    T1 m_ic;
    static constexpr int m_stcvalue = 200;
};

//在类外实现类模板的构造函数模板
template <typename T1>
template <typename T2>
A<T1>::A(T2 v1, T2 v2) {
    cout << "A::A(T2,T2)执行了!" << endl;
}

//在类外实现类模板A的myft成员函数模板的偏特化版本
template <typename T1>
template <typename T4>
void A<T1>::myft(int tmpt, T4 tmpt2) {
    cout << "myft(int,T4)偏特化版本" << endl;
    cout << tmpt << endl;
    cout << tmpt2 << endl;
}

//在类外实现类模板A的myft成员函数模板的全特化版本
// template <typename T1>
// template <> //全特化
// void A<T1>::myft(int tmpt, float tmpt2)
//{
//	cout << "myft(int,float)全特化版本" << endl;
//	cout << tmpt << endl;
//	cout << tmpt2 << endl;
//}

//将myfOC实现在类外面
template <typename T1>
template <typename U>
void A<T1>::OtherC<U>::myfOC() {
    cout << "类模板A的myfOC执行了" << endl;
}

//类模板A的全特化版本
template <>
class A<float> {
 public:
    template <typename T3, typename T4>  //普通成员函数模板
    void myft(T3 tmpt, T4 tmpt2) {
        cout << "类A特化版本的myft()泛化版本" << endl;
        cout << tmpt << endl;
        cout << tmpt2 << endl;
    }
    // template <> //全特化
    // void myft(int tmpt, float tmpt2);

 public:
    template <typename U>
    class OtherC {
     public:
        void myfOC();
        /*{
                cout << "myfOC执行了" << endl;
        }*/
    };
};

// A<float>中有泛化版本的myft，因此不用在A<float>中声明如下的全特化版本。
template <>  //全特化
void A<float>::myft(int tmpt, float tmpt2) {
    cout << "类A特化版本的myft(int,float)全特化版本" << endl;
    cout << tmpt << endl;
    cout << tmpt2 << endl;
}

//将myfOC实现在类外面
template <typename U>
void A<float>::OtherC<U>::myfOC() {
    cout << "myfOC执行了" << endl;
}

}  // namespace _nmsp1

int main() {
    //六：成员函数模板
    //（6.3）特化
    //有些资料上说目前的C++标准不允许在类模板之外全特化一个未被特化的类模板（指的是类模板A）的成员函数。
    //整体感觉：类模板中的成员函数全特化可能还不算太完善，写代码时要注意测试。
    //在实际工作中，建议把这些特化版本写在类模板内部，然后类模板一般也要写在头文件。
    _nmsp1::A<float> a2(1, 2);
    a2.myft(3.1, 2);
    a2.myft(3, 2);
    a2.myft(3, 2.5f);

    _nmsp1::A<float> a3;
    a3.myft(3, 2.5f);
    a3.myft(3.1, 2);

    //七：类模板中的类模板（嵌套）
    _nmsp1::A<float>::OtherC<float> myobjc;
    myobjc.myfOC();

    _nmsp1::A<int>::OtherC<float> myobjc;
    myobjc.myfOC();

    return 0;
}