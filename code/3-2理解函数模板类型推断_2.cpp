
#include <boost/type_index.hpp>
#include <initializer_list>
#include <iostream>

using namespace std;

//函数模板
// template <typename T,unsigned L1> //L1就是数组长度
// void myfunc(T (&tmprv)[L1] )
template <typename T>
// void myfunc1(T&& tmprv)
void myfunc2(T tmprv)
// void myfunc3(T& tmprv)
// void myfunc4(std::initializer_list<T>  tmprv)
{
    cout << "--------------------------------begin----------------" << endl;
    using boost::typeindex::type_id_with_cvr;
    cout << "T=" << type_id_with_cvr<T>().pretty_name() << endl;                    //显示T的类型
    cout << "tmprv=" << type_id_with_cvr<decltype(tmprv)>().pretty_name() << endl;  //显示tmprv的类型
    cout << "--------------------------------end------------------" << endl;

    // tmprv = nullptr;
    //*tmprv = 'Y'; //编译报错：error C3892: “tmprv”: 不能给常量赋值

    // tmprv = 12;
    // int& tmpvaluec = tmprv;
    // tmpvaluec = 1200;

    // cout << L1 << endl;
}

template <typename T>
// void tf1(const T& tmprv) //这里把auto替换成T,xy就相当于这里的tmprv
void tf2(T&& tmprv) {
    cout << "--------------------------------begin----------------" << endl;
    using boost::typeindex::type_id_with_cvr;
    cout << "T=" << type_id_with_cvr<T>().pretty_name() << endl;                    //显示T的类型
    cout << "tmprv=" << type_id_with_cvr<decltype(tmprv)>().pretty_name() << endl;  //显示tmprv的类型
    cout << "--------------------------------end------------------" << endl;
}

void testFunc() {}

int main() {
    //（2.2）万能引用类型
    int i = 18;        // i的类型是int
    const int j = i;   // j的类型是const int
    const int& k = i;  // k的类型是const int &
    myfunc1(i);        // T = int & ，tmprv = int &
    myfunc1(j);        // T = int const & ,tmprv = int const &
    myfunc1(k);        // T = int const & ,tmprv = int const &
    myfunc1(100);      // T = int ,tmprv = int &&

    //（2.3）传值方式
    // a)若实参是引用类型，则引用部分会被忽略，T不会被推导为引用类型。除非手工指定为引用类型(不建议这样写代码)。
    // b)若实参是const类型，则const部分会被忽略，T不会推导为const类型（毕竟产生的是新副本）
    myfunc2(i);  // T = int  ，tmprv = int
    myfunc2(j);  // T = int  ，tmprv = int
    myfunc2(k);  // T = int  ，tmprv = int

    // 如果传递的是const char *或者const char[],这个const会被保留。
    char mystr[] = "I Love China";
    const char* const p = mystr;  //第一个const表示p指向的目标中的内容不能通过p改变
                                  //第二个const表示p指向一个内容后，p不可以再指向其他内容（p不可以指向不同目标）。
    myfunc2(p);                   // T = char const * ，tmprv=char const * ，传递给myfunc后，第二个const没有了，第一个const是保留的。
                                  //这表示进入到myfunc函数模板内部后，tmprv指向的内容不能通过tmprv改变，但是tmprv可以指向其他内存地址。

    //（2.4）传值方式的引申——std::ref与std::cref
    //当函数模板定义中使用传值方式时，可以通过std::ref和std::cref来以引用方式传递参数，提高效率
    int m = 180;
    myfunc2(std::ref(m));  // std::ref和std::cref像对象包装器，编译器通过创建一个 class std::reference_wrapper<T>类型的对象
                           // T=class std::reference_wrapper<int> ,tmprv=class std::reference_wrapper<int>
    cout << "m=" << m << endl;

    //（2.5）数组做实参
    const char mystr[] = "I Love China!";
    myfunc2(mystr);  // T=char const *  , tmprv=char const *

    myfunc3(mystr);  // T=char const [14],tmprv=char const (&)[14]--(&)代表数组的一个引用。

    //（2.6）函数名做实参
    myfunc2(testFunc);  // T=void (__cdecl*)(void),tmprv=void (__cdecl*)(void)
    myfunc3(testFunc);  // T=void __cdecl(void),tmprv=void (__cdecl&)(void)——tmprv是一个函数引用类型：void(&)(void)

    //（2.7）初始化列表做实参
    myfunc4({1, 2, 3});  // T=int,tmprv=class std::initializer_list<int>

    //总结：
    // a)推断中，引用类型实参的引用类型等于不存在。
    // b)万能引用，实参为左值或者右值，推断的结果不同。
    // c)按值传递的实参，传递给形参时const属性不起作用，但传递进去指针则另当别论。
    // d)数组或者函数类型在类型推断中会被看做是指针，除非函数模板的形参是个引用。
    // e)初始化列表不能直接推断成initializer_list类型，必须在函数模板的形参中明确指出使用initializer_list类型。

    //（3）auto类型常规推断:用于变量的自动类型推断。
    //声明变量的时候根据变量初始化的类型自动为此变量选择匹配的类型，不需要程序员显式的指定类型。
    // auto的特点如下：
    // a)auto的自动类型推断发生在编译期间。
    // b)auto定义变量必须立即初始化，这样编译器才能推断出他的实际类型。
    // 编译的时候才能确定auto类型以及整个变量的类型，然后在编译期间就可以用真正的类型替换掉auto这个类型占位符了。
    // c)auto的使用比较灵活，可以和指针、引用、const等限定符结合使用。
    // auto推断出来后会代表一个具体类型，auto相当于函数模板类型推断中的参数T。
    //（3.1）传值方式（非指针，非引用）
    //总结传值方式对auto类型：会抛弃引用，const等限定符。
    auto x = 27;         // x = int, auto =int
    const auto x2 = x;   // x2 = const int,auto =int
    const auto& xy = x;  // xy = const int &，auto = int
    auto xy2 = xy;       // xy2 = int,auto =int
    tf1(x);              // T=int，tmprv=int const &

    //（3.2）指针或者引用类型
    //总结传指针或者引用方式针对auto类型：不会抛弃const限定符，但是会抛弃引用。
    auto& xy3 = xy;          // xy3 = const int &,auto = const int。针对auto类型：引用会被丢弃，const属性会被保留。
    auto y = new auto(100);  // y = int *，auto = int *，auto可以用于new。
    const auto* xp = &x;     // xp = cont int *,auto = int
    auto* xp2 = &x;          // xp2 = int *,auto = int
    auto xp3 = &x;           // xp3 = int *，auto = int * ，xp3不声明为指针，也能推导出指针类型。

    //（3.3）万能引用类型
    //与讲解函数模板类型推断时万能引用的情形完全相同。
    auto&& wnyy0 = 222;  //万能引用，222是右值，auto = int,wnyy0 = int &&
    auto&& wnyy1 = x;    //万能引用，x是左值，auto  = int &，wnyy1 = int &
    auto&& wnyy2 = x2;   // auto = int const &，wnyy2 = int const &
    tf2(x2);

    return 0;
}
