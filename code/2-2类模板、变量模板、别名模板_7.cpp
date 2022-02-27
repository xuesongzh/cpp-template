
#include <iostream>
#include <list>
#include <vector>

using namespace std;

namespace _nmsp1 {
// T：类型模板参数，代表容器中元素类型。
// Container：代表的不是一个类型模板参数，而是一个类模板（类名）
// 叫做 模板 模板参数，表示这个模板参数本身又是一个模板
template <
    typename T,
    // typename Container = std::vector
    // template <class> class Container = std::vector //这就是一个模板模板参数，写法比较固定，这里的名字叫Container，叫U也可以。
    template <typename W> typename Container = std::vector  //也要理解这种写法，W可以省略
    >
class myclass {
 public:
    Container<T> myc;

 public:
    void func();
    myclass() {  //构造函数
        for (int i = 0; i < 10; ++i) {
            myc.push_back(i);  //这几行代码是否正确取决于实例化该类模板时所提供的模板参数类型。
        }
    }
};

template <
    typename T,
    template <typename W> typename Container>
void myclass<T, Container>::func() {
    cout << "good!" << endl;
}

//-------------------
template <
    //.....
    template <typename W, W* point> typename Container>
class myclass2 {
    // W* m_p;  //错误，不可以在这里使用W（W叫做：模板模板参数Container的模板参数）
};

// Container如果myclass类模板中不使用，也可以省略，从而出现了typename后面直接接=的写法。
template <
    //......
    template <typename W> typename = std::vector>
class myclass3 {
};
}  // namespace _nmsp1

namespace _nmsp2 {
template <typename T, typename U>
union myuni {
    T carnum;     //轿车编号，4个字节。
    U cartype;    //轿车的类型，比如微型车，小型车，中，中大。1个字节。
    U cname[60];  //轿车名，60个字节
};
}  // namespace _nmsp2

int main() {
    //十：模板模板参数
    //英文名：Template Template Parameters。就是：让模板参数本身成为模板。
    // a)int：类型，简单类型/内部类型
    // b)vector,list：是C++标准库中的容器，类模板（类名），vector<int>或者list<double>就属于模板被实例化了的参数，称呼为类型（类类型）。
    //创建myclass的类模板，成员变量myc，是个容器
    //复习一下：a）类型模板参数，b)非类型模板参数，c)模板模板参数。
    _nmsp1::myclass<int, vector> myvectorobj;  // int是容器中的元素类型，vector是容器类型。
    _nmsp1::myclass<double, list> mylistobj;   // double是容器中的元素类型，list是容器类型
    mylistobj.func();

    //十一：共用体模板（联合模板）
    // union
    //可以把联合理解成一种类类型（不要理解成类）。联合也支持模板化。
    //共用体模板的英文名：Union Templates
    _nmsp2::myuni<int, char> myu;
    myu.carnum = 156;
    cout << myu.carnum << endl;

    return 0;
}
