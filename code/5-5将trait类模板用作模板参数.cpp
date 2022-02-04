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
	template <typename T>
	struct MinFixedTraits;

	template<>
	struct MinFixedTraits<int>
	{
		using sumT = int; //求最小值，结果类型与元素类型相同即可，为了名字统一，都用sumT这个名字
		static sumT initValue() { return INT_MAX; } //INT_MAX：整型最大值，任何一个数组元素都不会被这个值更大，因此可以顺利的找到数组元素中的最小值,参见MinPolicy::algorithm
	};


	//----------------------
	//求和策略类以实现求和算法。
	template <typename sumT, typename T>
	struct SumPolicy
	{
		//静态成员函数模板
		//template <typename sumT,typename T> //sumT是和值类型，T是数组元素类型
		static void algorithm(sumT& sum, const T& value) //策略类的核心算法
		{
			sum += value; //求和
		}
	};

	//----------------------
	//求最小值策略类
	template <typename minT, typename T>
	struct MinPolicy
	{
		//template <typename minT,typename T>
		static void algorithm(minT& min, const T& value)
		{
			if (min > value)
				min = value;
		}
	};


	//----------------------
	//funcsum函数模板
	//template <typename T, typename U = SumFixedTraits<T> >  //T = char ,U = SumFixedTraits<char>
	template <typename T, 
				typename U = SumFixedTraits<T> ,
				//typename V = SumPolicy
				template<class,class> class V = SumPolicy //这里class也可以写成typename
	>
	auto funcsum(const T* begin, const T* end)
	{
		//using sumT = typename SumFixedTraits<T>::sumT;
		//sumT sum = SumFixedTraits<T>::initValue();
		typename U::sumT sum = U::initValue();  //typename SumFixedTraits<char>::sumT sum = SumFixedTraits<char>::initValue();
												 //int sum = 0;

		for (;;)
		{
			//sum += (*begin);
			//V::algorithm(sum, *begin);
			V<U::sumT,T>::algorithm(sum, *begin); //捋一下：T是数组成员类型，U是固定萃取（fixed traits）类模板，
			                                      //从中可以提取出结算的结果类型（U::sumT)以及结果的初值，
			                                      //V是策略类模板，用于实现具体算法（求和，求最小值等）

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
	
	//第五节 策略（policy）技术中的算法策略
	//（1）常规范例：普通策略类
	//（2）常规范例：策略类模板
	//（3）萃取（trait）技术与策略（policy）技术的比较
	//两者之间的相同和不同之处：
	//a)两种技术都象一个中间件一样，夹在不同的功能代码之间，让代码之间的调用更加灵活。
	//b)萃取技术：给进去一个类型，萃取出另外一个类型或者另外一个值（注重于类型或者指定）。
	 //策略技术：给进去一个类型，萃取出一个算法或者是一个不同的功能实现（注重于动作或者行为）。
	   //因此，在书写策略类（类模板）的时候通常都需要包含成员函数以实现指定的行为。
	 //有时，萃取技术中也可能实现某些动作或者行为，所以从这个角度来讲，萃取技术与策略技术有时区分不是那么明显。
	//c)萃取技术一般通过一个类模板来实现，通常包含类模板的泛化版本和多个特化版本。策略技术用普通类或者类模板都可以实现。
	




	//char mychararray[] = "abc";
	//cout << (int)(_nmsp1::funcsum(&mychararray[0], &mychararray[2])) << endl;

	int myintarray1[] = { 10,15,20 };
	//cout << (int)(_nmsp1::funcsum<int, _nmsp1::SumFixedTraits<int>, _nmsp1::MinPolicy>(&myintarray1[0], &myintarray1[2])) << endl;
	cout << (int)(_nmsp1::funcsum<int, _nmsp1::MinFixedTraits<int>, _nmsp1::MinPolicy>(&myintarray1[0], &myintarray1[2])) << endl;


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



