
#include <iostream>

using namespace std;

namespace _nmsp1 {
//函数模板func的声明
// template <typename U, typename V> 	void func(U val1, V val2);

// Men类模板
template <typename Z>
class Men {
    //因为func2在类模板Men中，所以调用func2时，如果func2中的代码特别简单，则func2会被当成内联函数来处理。
    //如果func2中的代码比较复杂，比如出现了for循环，那么func2很可能就不会被当做内联函数来处理。
    friend void func2(Men<Z>& tmpmen) {
        // for(int i= 0; i<1 ; ++i)
        tmpmen.funcmen();
    }

    // friend void func<int, int>(int, int);  //<int,int>是两个模板实参
    ////friend void func<>(int, int);
    ////friend void func<int>(int, int);

    ////friend void func<float,int>(float, int);
    // friend void func<>(float, int);

    ////friend void func<int, float>(int, float);
    // friend void func<>(int, float);

    //让函数模板func成为类模板Men的友元函数模板
    template <typename U, typename V>
    friend void func(U val1, V val2);

 private:
    void funcmen() const {
        cout << "Men::funcmen被调用了" << endl;
    }
};

template <typename U, typename V>
void func(U val1, V val2) {
    /*cout << "val1 = " << val1 << endl;
    cout << "val2 = " << val2 << endl;*/
    // Men mymen;
    Men<int> mymen;
    mymen.funcmen();
}

// func全特化版本
//编译器会把全特化的func函数模板看待成一个实例化过的函数模板。
//看待成了void func<int,double>(int val1, double val2)
template <>
void func(int val1, double val2) {
    Men<int> mymen;
    mymen.funcmen();
}

}  // namespace _nmsp1

int main() {
    //三：类模板中的友元
    //(2)友元函数：函数模板可以被声明为友元函数
    //（2.1）让函数模板的某个实例成为友元函数
    //调用func的方法很多
    _nmsp1::func(2, 3);                 //会实例化出 void func<int,int>(int,int){......}
    _nmsp1::func<float>(4.6f, 5);       //第一个模板参数指定，第二个模板参数编译器自己推断
    _nmsp1::func<int, float>(4, 5.8f);  //完全手工指定模板参数

    //（2.2）友元模板
    //将func函数模板（泛化版本）声明为Men类模板的友元模板之后，那么func函数模板的特化版本也会被看成是Men类模板的友元。

    //（2.3）在类模板中定义友元函数
    //这种友元函数是能够被调用的，而且也只有在代码中调用了函数的时候，编译器才会实例化出这个函数。
    //之所以这样定义友元函数，一般都是因为在该友元函数中会 用到这个类模板。
    //这种友元函数的调用与调用普通函数函数差不多，大家就把他当成普通函数来看待即可。

    // func2其实是个全局函数。

    // func2在Men类模板被实例化时并不会被一并实例化出来，只有调用了func2的时候，才会被实例化出来。
    // func2(mymen2); 可以被实例化出  void func2(class Men<double>&);
    _nmsp1::Men<double> mymen2;
    func2(mymen2);  //直接调用Men类模板中定义的友元函数func2

    // func2(mymen3); 可以被实例化出  void func2(class Men<int>&);
    _nmsp1::Men<int> mymen3;
    func2(mymen3);

    return 0;
}
