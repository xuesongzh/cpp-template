// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>



//#include <boost/type_index.hpp>
using namespace std;
//#pragma warning(disable : 4996) 


namespace _nmsp1
{
	//SumFixedTraits类模板
	template <typename T>
	struct SumFixedTraits;

	template<>
	struct SumFixedTraits<char>
	{
		using sumT = int;
		static sumT initValue() { return 0; }
	};

	template<>
	struct SumFixedTraits<int>
	{
		using sumT = __int64;
		static sumT initValue() { return 0; }
	};
	
	template<>
	struct SumFixedTraits<double>
	{
		using sumT = double;
		static sumT initValue() { return 0.0; }
	};
	//----------------------
	//funcsum函数模板
	template <typename T,typename U = SumFixedTraits<T> >  //T = char ,U = SumFixedTraits<char>
	auto funcsum(const T* begin, const T* end)
	{
		//using sumT = typename SumFixedTraits<T>::sumT;
		//sumT sum = SumFixedTraits<T>::initValue();
		typename U::sumT sum = U::initValue();  //typename SumFixedTraits<char>::sumT sum = SumFixedTraits<char>::initValue(); 
		                                         //int sum = 0;

		for (;;)
		{
			sum += (*begin);
			if (begin == end)
				break;
			++begin;
		}//end for
		return sum;
	}



}

int main()
{ 	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口
	
	//第四节 将trait类模板用作模板参数
	//SumFixedTraits类模板，funcsum函数模板。

	char mychararray[] = "abc";
	//cout << (int)(_nmsp1::funcsum(&mychararray[0], &mychararray[2])) << endl;
	cout << (int)(_nmsp1::funcsum<char, _nmsp1::SumFixedTraits<int> >(&mychararray[0], &mychararray[2])) << endl;


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



