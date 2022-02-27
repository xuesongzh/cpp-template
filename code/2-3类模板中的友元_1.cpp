
#include <iostream>

using namespace std;

namespace _nmsp1 {

// template <typename U> class B; //类模板B的声明

template <typename T>
class A {
    // friend class B<long>; //不需要任何public,private等修饰符。
    template <typename>
    friend class B;

 private:
    int data;
};

template <typename U>
class B {
 public:
    void callBAF() {
        A<int> atmpobj;
        atmpobj.data = 5;
        cout << atmpobj.data << endl;
    }
};

}  // namespace _nmsp1

namespace _nmsp2 {
template <typename T>
class A2 {
    friend T;
    // friend class CF;

 private:
    int data;
};

class CF {
 public:
    void callCFAF() {
        A2<CF> aobj1;  //让CF类成为了A2<CF>类的友元类，可以直接访问aobj1这个A2<CF>类对象的data私有成员变量。
        aobj1.data = 12;
        cout << aobj1.data << endl;

        //如果传递给类模板A2的类型模板参数不是一个类类型，那么代码行friend T就会被忽略。
        A2<int> aobj2;  //因为CF类并不是A2<int>的友元类，自然不能在这里访问aobj2这个A2<int>类对象的data私有成员变量。
        aobj2.data = 15;
        cout << aobj2.data << endl;
    }
};

}  // namespace _nmsp2

int main() {
    // 2.3类模板中的友元
    //一：友元类：
    //让某个类B成为另外一个类A的友元类，这样的话，类B就可以在其成员函数中访问类A的所有成员
    //而不管这些成员在类A中是用什么（public,protected,private）来修饰的。
    //如果现在类A和类B都变成了类模板，那么能否让类模板B成为类模板A的友元类模板呢？
    // 1.1：让类模板的某个实例成为友元类
    // 1.2：让类模板成为友元类模板
    _nmsp1::B<long> bobj1;
    _nmsp1::B<int> bobj2;
    bobj2.callBAF();

    // 1.3：让类型模板参数成为友元类
    // C++11新标准中引入：如果传递进来的类型模板参数是一个类类型，则这个类类型可以成为当前类模板的友元类。
    _nmsp2::CF mycfobj;
    mycfobj.callCFAF();

    // _nmsp2::A2<_nmsp2::CF> aobj1;
    // aobj1.data = 12;

    return 0;
}
