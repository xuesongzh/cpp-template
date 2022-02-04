// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>
//#include <boost/type_index.hpp>

using namespace std;
//#pragma warning(disable : 4996) 

namespace _nmsp1
{	
	//计算数组中元素的和值的函数模板
	//template <typename T>
	//T funcsum(const T* begin, const T* end)
	//{
	//	T sum{}; //零初始化，如果数值型变量被初始化为0，指针型变量被初始化为nullptr，bool类型变量被初始化为false。
	//	for (;;)
	//	{
	//		sum += (*begin);
	//		if (begin == end)
	//			break;
	//		++begin;
	//	}
	//	return sum;
	//}

	template <typename U,typename T>
	U funcsum(const T* begin, const T* end)
	{
		U sum{}; //零初始化，如果数值型变量被初始化为0，指针型变量被初始化为nullptr，bool类型变量被初始化为false。
		for (;;)
		{
			sum += (*begin);
			if (begin == end)
				break;
			++begin;
		}
		return sum;
	}



}
namespace _nmsp2
{
	//fixed traits类模板的泛化版本
	template<typename T>
	struct SumFixedTraits; //不需要实现代码，因为不需要用该版本进行实例化。

	//各个fixed traits类模板的特化版本
	//(1)给进来char类型时，返回的是int类型
	template <>
	struct SumFixedTraits<char> //char表示给进来的是char类型
	{
		using sumT = int; //类型别名sumT代表int类型（返回类型）
	};
	//(2)给进来int类型时，返回的是__int64(long long/int64_t)类型
	template <>
	struct SumFixedTraits<int> //int表示给进来的是int类型
	{
		using sumT = __int64; //类型别名sumT代表__int64类型（返回类型）
	};
	//(3)....其他给进来的是某个类型，返回的是另外一个类型，可以任意扩展出多个SumFixedTraits类模板的特化版本。

	//-----------------------
	template <typename T>
	auto funcsum(const T* begin, const T* end)
	{
		using sumT = typename SumFixedTraits<T>::sumT; //给进来一个类型（T），返回一个类型（sumT），这是fixed traits的运用。
		sumT  sum{}; //零初始化，如果数值型变量被初始化为0，指针型变量被初始化为nullptr，bool类型变量被初始化为false。
		for (;;)
		{
			sum += (*begin);
			if (begin == end)
				break;
			++begin;
		}
		return sum;
	}

}

int main()
{ 	
	//第一节 萃取技术及fixed traits（固定萃取）演示
	//trait(萃取)技术用于对模板中的各种模板参数进行管理。
	//type traits：类型萃取
	//学习目的：
	//(a)了解标准库中许多trait技术的实现方法。
	//(b)灵活运用并组合这些实现方法，写出功能跟强大，更优雅和实用的代码。
	//fixed traits（固定萃取）：主要用于  给进来一种类型，萃取出（得到）另外一种类型。

	//（1）一个常规范例
	//SumFixedTraits固定萃取类模板的作用：通过类型，得到另外一个类型。

	//int myintarray1[] = { 10,15,20 };
	//int myintarray2[] = { 1000000000,1500000000,2000000000 }; //10亿，15亿，20亿
	//char mychararray[] = "abc";//97,98,99

	//cout << _nmsp1::funcsum(&myintarray1[0], &myintarray1[2]) << endl;  //int funcsum<int>(const int*,const int*);
	//cout << _nmsp1::funcsum(&myintarray2[0], &myintarray2[2]) << endl;
	//cout << (int)(_nmsp1::funcsum(&mychararray[0], &mychararray[2])) << endl; //char funcsum<char>(const char*,const char*);


	//int myintarray1[] = { 10,15,20 };
	//int myintarray2[] = { 1000000000,1500000000,2000000000 }; //10亿，15亿，20亿
	//char mychararray[] = "abc";//97,98,99
	//
	//						   //int64_t,long long 
	//cout << _nmsp1::funcsum<__int64>(&myintarray1[0], &myintarray1[2]) << endl;  //int funcsum<int>(const int*,const int*);
	//cout << _nmsp1::funcsum<__int64>(&myintarray2[0], &myintarray2[2]) << endl;
	//cout << (int)(_nmsp1::funcsum<int>(&mychararray[0], &mychararray[2])) << endl; //char funcsum<char>(const char*,const char*);

	int myintarray1[] = { 10,15,20 };
	int myintarray2[] = { 1000000000,1500000000,2000000000 }; //10亿，15亿，20亿
	char mychararray[] = "abc";//97,98,99

	cout << _nmsp2::funcsum(&myintarray1[0], &myintarray1[2]) << endl;  //int funcsum<int>(const int*,const int*);
	cout << _nmsp2::funcsum(&myintarray2[0], &myintarray2[2]) << endl;
	cout << (int)(_nmsp2::funcsum(&mychararray[0], &mychararray[2])) << endl; //char funcsum<char>(const char*,const char*);

	return 0;
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
