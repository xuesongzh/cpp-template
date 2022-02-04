﻿// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>

using namespace std;
#pragma warning(disable : 4996) 

namespace _nmsp1
{
	template<typename T>
	void myfunc(T tmpvalue)
	{
		cout << "myfunc(T tmpvalue)执行了" << endl;
	}

	template<typename T>
	void myfunc(T* tmpvalue)
	{
		cout << "myfunc(T* tmpvalue)执行了" << endl;
	}

	void myfunc(int tmpvalue)
	{
		cout << "myfunc(int tmpvalue)执行了" << endl;
	}

}
namespace _nmsp2
{
	//泛化版本
	template <typename T,typename U>  //T = const char *；U = int
	void tfunc(T& tmprv, U& tmprv2)   //tmprv = const char * &,tmprv2 = int &
	{
		cout << "tfunc泛化版本" << endl;
		cout << tmprv << endl;
		cout << tmprv2 << endl;
	}

	//全特化版本
	template <> //全特化<>里面为空
	void tfunc<int ,double>(int& tmprv, double& tmprv2)//<int, double>可以省略，因为根据实参可以完全推导出T和U的类型。
	//void tfunc(int& tmprv, double& tmprv2)  
	{
		cout << "---------------begin------------" << endl;
		cout << "tfunc<int,double>特化版本" << endl;
		cout << tmprv << endl;
		cout << tmprv2 << endl;
		cout << "---------------end------------" << endl;
	}

	//重载函数
	void tfunc(int& tmprv, double& tmprv2)
	{
		cout << "---------------begin------------" << endl;
		cout << "tfunc普通函数" << endl;		
		cout << "---------------end------------" << endl;
	}

	////从模板参数数量上的偏特化
	//template <typename U> 
	//void tfunc<double, U>(double& tmprv, U& tmprv2)
	//{
	//	//.......
	//}
	template <typename U>
	void tfunc(double& tmprv, U& tmprv2)
	{
		cout << "---------------begin------------" << endl;
		cout << "类似于tfunc<double, U>偏特化的tfunc重载版本" << endl;
		cout << tmprv << endl;
		cout << tmprv2 << endl;
		cout << "---------------end------------" << endl;
	}


	template <typename T, typename U>
	void tfunc(const T& tmprv, U& tmprv2)
	{
		cout << "tfunc(const T& tmprv, U& tmprv2)重载版本" << endl;
	}
}

int main()
{
	//第一节 函数模板
	//4：重载
	//函数（函数模板）名字相同，但是参数数量或者参数类型上不同。
	//函数模板和函数也可以同时存在,此时可以把函数看成是一种重载,当普通函数和函数模板都比较合适的时候，编译器会优先选择普通函数来执行。
	 //如果选择最合适（最特殊）的函数模板/函数，编译器内部有比较复杂的排序规则，规则也在不断更新。

	//5：特化
	//泛化（泛化版本）：大众化的，常规的。常规情况下，写的函数模板都是泛化的函数模板。
	//特化（特化版本）：往往代表着从泛化版本中抽出来的一组子集。
	//（5.1）全特化：就是把tfunc这个泛化版本中的所有模板参数都用具体的类型来代替构成的一个特殊的版本（全特化版本）；
	 //全特化实际上等价于实例化一个函数模板，并不等价于一个函数重载。
	//void tfunc<int ,double>(int& tmprv, double& tmprv2){......}  //全特化的样子
	//void tfunc(int& tmprv, double& tmprv2) { ...... }  //重载函数的样子
	//编译器考虑的顺序：优先选择普通函数，然后才会考虑函数模板的特化版本，最后才会考虑函数模板的泛化版本。
	//（5.2）偏特化（局部特化）
	//从两方面来说：一个是模板参数数量上的偏特化，一个是模板参数范围上的偏特化。
	//a)模板参数数量上的偏特化：比如针对tfunc函数模板，第一个模板参数类型为double，第二个模板参数不特化；
	  //实际上，从模板参数数量上来讲，函数模板不能偏特化。否则会导致编译错误。
	//b)模板参数范围上的偏特化：
	 //范围上：int->const int，类型变小；   T->T*，T->T&，T->T&&。针对T类型，从类型范围上都变小了。
	   //实际上，对于函数模板来讲，也不存在模板参数范围上的偏特化。因为这种所谓模板参数范围上的偏特化，实际上是函数模板的重载。
	//c）通过重载实现模板参数数量上的偏特化
	
	//后续讲解类模板时，对于类模板，还是存在模板参数范围上的偏特化以及数量上的偏特化，后续会详细讲解。
	   	  	
	/*_nmsp1::myfunc(12);
	char* p = nullptr;
	_nmsp1::myfunc(p);
	_nmsp1::myfunc(12.1);*/

	/*
	const char* p = "I Love China!";
	int i = 12;
	_nmsp2::tfunc(p, i);

	int k = 12;
	double db = 15.8;
	_nmsp2::tfunc(k, db);

	const int k2 = 12;
	_nmsp2::tfunc(k2, db);*/

	const char* p = "I Love China!";
	int i = 12;
	_nmsp2::tfunc(p, i);

	double j = 18.5;
	_nmsp2::tfunc(j, i);



}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
