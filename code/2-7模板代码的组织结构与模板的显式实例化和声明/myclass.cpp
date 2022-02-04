
#include <iostream>
#include "myclass.h"

using namespace std;

////类实现
//void MYClass::func()
//{
//	std::cout << "MYClass::func成员函数执行了!" << endl;
//}


template <typename T>
void MYClass<T>::func()
{
	std::cout << "MYClass::func成员函数执行了!" << endl;
}