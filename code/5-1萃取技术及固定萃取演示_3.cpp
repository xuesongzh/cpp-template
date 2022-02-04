// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>
//#include <boost/type_index.hpp>
#include <vector>
#include <list>

using namespace std;
//#pragma warning(disable : 4996) 

namespace _nmsp1
{	
	//template <class T>
	//struct vector
	//{
	//	.....
	//	using value_type = T:
	//};
	
	/*
	//泛化版本
	template <typename T>
	struct GetEleType;

	//特化版本
	template <typename T>
	struct GetEleType<std::vector<T>>
	{
		using type = T;
	};
	template <typename T>
	struct GetEleType<std::list<T>>
	{
		using type = T;
	};

	template <typename T,std::size_t Size> //这个特化版本增加了一个模板参数
	struct GetEleType<T[Size]> //萃取出数组元素个数
	{
		using type = T;
		static const std::size_t size = Size;
	};
	*/
	//泛化版本，用泛化版本实现对容器类型的支持
	template <typename T>
	struct GetEleType
	{
		using type = typename T::value_type; //针对容器
	};
	//针对数组的特化版本（内容不变）
	template <typename T, std::size_t Size> //这个特化版本增加了一个模板参数
	struct GetEleType<T[Size]> //萃取出数组元素个数
	{
		using type = T;
		static const std::size_t size = Size;
	};

	//别名模板：
	template <typename T>
	using EleType = typename GetEleType<T>::type;


	//---------------
	//函数模板
	template <typename T>
	void PrintEleType(const T& container)
	{
		//cout << "容器(数组)的元素类型为：" << typeid(GetEleType<T>::type).name() << endl;
		cout << "容器(数组)的元素类型为：" << typeid(EleType<T>).name() << endl;
	}
}

int main()
{ 	
	//第一节 萃取技术及fixed traits（固定萃取）演示
	//（3）通过容器（数组）类型萃取元素类型范例
	//（3.1）用GetEleType类模板进行常规实现
	//（3.2）引入函数模板PrintEleType
	//（3.2）GetEleType类模板的改进


	/*
	cout << "vector<double>的元素类型为：" << typeid(_nmsp1::GetEleType< vector<double> >::type).name() << endl;
	cout << "list<int>的元素类型为：" << typeid(_nmsp1::GetEleType< list<int> >::type).name() << endl;
	cout << "float[45]的元素类型为：" << typeid(_nmsp1::GetEleType< float[45] >::type).name() << endl;
	cout << "float[45]的数组元素数量为：" << _nmsp1::GetEleType< float[45] >::size << endl;
	*/

	
	vector<double> mydblvec;
	_nmsp1::PrintEleType(mydblvec);

	list<int> myintlist;
	_nmsp1::PrintEleType(myintlist);

	float myfloatarr[45];
	_nmsp1::PrintEleType(myfloatarr);

	//vector<int

	//cout << "vector<double>的元素类型为：" << typeid(vector<double>::value_type).name() << endl;

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
