
#include <iostream>
#include "ca.h"

using namespace std;

template class  A<float>; //这叫“实例化定义”。一般只有一个.cpp文件里这样写，编译器为其生成代码。
template void myfunc(int& v1, int& v2); //函数模板实例化定义，编译器会为其生成实例化代码

void mfunc()
{
	A<float> a(1, 2);
	a.myft(3); //3
}