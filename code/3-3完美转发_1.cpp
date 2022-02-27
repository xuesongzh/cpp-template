
#include <iostream>

using namespace std;

namespace _nmsp1 {
// void funcLast1(int v1, int v2)
void funcLast2(int v1, int& v2) {
    ++v2;  //改变v2的值，让其自增1
    cout << v1 + v2 << endl;
}

void funcLast3(int&& v1, int& v2) {
    cout << v1 << endl;
    cout << v2 << endl;
}

//函数模板（跳板函数）：把收到的参数以及这些参数相对应的类型不变的转发给其他函数（完美转发）
template <typename F, typename T1, typename T2>
// void funcMiddle1(F f, T1 t1, T2 t2) //f:函数指针类型void(*)(int,int)
void funcMiddle2(F f, T1&& t1, T2&& t2) {
    f(t1, t2);
}

}  // namespace _nmsp1

int main() {
    //第三节 完美转发
    //（1）完美转发的概念和步骤演绎
    // a)直接调用：  funcLast();
    // b)转发： 通过funcMiddle()间接调用funcLast。funcMiddle相当于一个跳板函数。
    // 如果有参数，那么参数也需要通过funcMiddle中转传递给funcLast
    int i = 50;
    _nmsp1::funcLast1(41, i);  // 92

    int j = 70;
    _nmsp1::funcMiddle1(_nmsp1::funcLast1, 20, j);  // 91

    int i = 50;
    _nmsp1::funcLast2(41, i);  // 92，i=51

    int j = 70;
    _nmsp1::funcMiddle1(_nmsp1::funcLast2, 20, j);  // 91，j = 70
    //当前情况下j被funcMiddle推断成了int而不是int&
    // void funcMiddle(void(*f)(int,int &),int t1,int t2){...}

    // c)完美转发：const，左值，右值。实参的属性完全不丢失，原原本本的通过funcMiddle转发给funcLast，这种转发就是完美转发。
    //万能引用：实参的所有信息都会传递到万能引用当中去从而让编译器推导出来函数模板最终的形参类型 (引用折叠)。
    //完美转发：就是让程序员可以书写接受任意实参的函数模板（funcMiddle），并将其转发到目标函数（funcLast2)
    // 目标函数会接收到与转发函数（funcMiddle）所接收的完全相同（保持参数的左值、右值特性）的参数。
    //要实现完美转发，就要用到std::forward了。
    int j = 70;
    _nmsp1::funcMiddle2(_nmsp1::funcLast2, 20, j);  // 91，j = 71
    // T1=int, t1 = int &&，T2 = int & , t2 = int &

    int j = 70;
    _nmsp1::funcLast3(20, j);  // 20,70
    _nmsp1::funcMiddle2(_nmsp1::funcLast3, 20, j);
    // 20->t1(int &&)，但是t1本身是左值。报错

    return 0;
}
