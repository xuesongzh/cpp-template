
#include <iostream>

using namespace std;
#pragma warning(disable : 4996)

namespace _nmsp1 {
template <typename... Args>
class myclasst {
 public:
    myclasst() {
        cout << "myclasst::myclasst()执行了，可变参个数=" << sizeof...(Args) << endl;
    }
};

template <typename... Args>
// class myclasst1 :public myclasst<Args...>

// class myclasst2 :public myclasst<Args>...
// class myclasst2 :public myclasst<double>,pubic myclasst<float>,pubic myclasst<int>

// class myclasst3 :public myclasst<Args,char>...
class myclasst4 : public myclasst<Args, Args...>... {
 public:
    myclasst4() {
        cout << "myclasst4::myclasst4()执行了，可变参个数=" << sizeof...(Args) << endl;
    }
};

}  // namespace _nmsp1

int main() {
    //第五节 类模板中可变参的逐步展开
    //（1）myclasst<Args...>继承
    //实例化后，myclasst<Args...> 代表的是一个类：myclasst<double,float,int>

    //（2）myclasst<Args>...继承
    //实例化后，myclasst<Args>... 代表的是三个类，分别是myclasst<double>、myclasst<float>、myclasst<int>

    //（3）myclasst<Args,char>...继承
    //实例化后，myclasst<Args,char>... 代表的是三个类，分别是myclasst<double,char>、myclasst<float,char>、myclasst<int,char>

    //（4）myclasst<Args,Args...>...继承
    //实例化后，myclasst<Args, Args...>... 代表的是三个类，分别是
    // myclasst<double, double, float, int>、myclasst<float, double, float, int>、myclasst<int, double, float, int>

    _nmsp1::myclasst4<double, float, int> tmpobj;

    return 0;
}
