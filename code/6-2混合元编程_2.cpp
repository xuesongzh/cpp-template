// MyProject2017.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>

#ifdef _DEBUG   //只在Debug（调试）模式下
#ifndef DEBUG_NEW
#define DEBUG_NEW new(_NORMAL_BLOCK,__FILE__,__LINE__) //重新定义new运算符
#define new DEBUG_NEW
#endif
#endif

//#pragma warning(disable:4996)
using namespace std;


namespace _nmsp1
{	
	//计算n的阶乘的泛化版本
	template <int n_v>
	struct Factorial
	{
		enum
		{
			value = n_v * Factorial<n_v - 1>::value
		};
	};

	//计算n的阶乘的特化版本，用于做递归调用的出口
	template <>
	struct Factorial<1>
	{
		enum
		{
			value = 1
		};
	};

	//-----------	
	template <typename T>
	struct AddPoint //类型元函数
	{
		using type = T * ;
	};

	//-----------
	template <typename T,int U> //T：元素类型，U：数组大小
	//auto DotProduct(T* array1, T *array2)
	inline auto DotProduct(T* array1, T *array2)
	{
		T dpresult = T{}; //零初始化
		for (int i = 0; i < U; ++i)
		{
			dpresult += array1[i] * array2[i];
		}
		return dpresult;
	}
}
namespace _nmsp2
{
	//泛化版本
	template <typename T,int U>//T：元素类型，U：数组大小
	struct DotProduct
	{
		static T result(const T* a, const T* b)
		{
			return (*a) * (*b) + DotProduct<T, U - 1>::result(a + 1, b + 1);
		}
	};

	//特化版本，用于做递归调用的出口
	template <typename T>
	struct DotProduct<T, 0>
	{
		static T result(const T* a, const T* b)
		{
			return T{};
		}
	};
}

namespace _nmsp3
{
	//泛化版本
	template <int x_v,int y_v>
	struct InstantiationObServe
	{
		//static const int value = (x_v > y_v) ? InstantiationObServe<x_v - 1, y_v>::value : InstantiationObServe<x_v, x_v>::value;

		using TmpType = typename std::conditional<(x_v > y_v), InstantiationObServe<x_v - 1, y_v>, 
												InstantiationObServe<x_v, x_v> >::type;

		//static const int value = TmpType::value;
		//enum {value = TmpType::value};
		static inline const int value = TmpType::value;
	};

	//特化版本
	template <int x_v>
	struct InstantiationObServe<x_v, x_v>
	{
		//static const int value = x_v; //int可以用auto代替，书写更方便
		//enum {value = x_v};
		static inline const int value = x_v;
	};
}

namespace _nmsp4
{
	struct TST
	{
		//static const int mystatic = 1; //int相关类型char,unsigned,int,short等
		//static inline double mystatic2 = 12.6;
		static constexpr double mystatic2 = 12.6;
	};
}
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口

	//第二节 混合元编程
	//(a)程序员写出一段元编程代码
	//(b)编译器根据这段代码编译（生成）出来一段新代码，实现程序真正功能的是这段生成的新代码。
	//(c)编译器会对这段新代码进行编译，产生出最终的可执行程序。
	//混合元编程可以看成是运行期C++代码的生成器。

	//（1）常规的计算点积范例
	//a)数组a有三个元素，a[0],a[1],a[2]，值分别是1，2,3
	//b)数组b有三个元素，b[0],b[1],b[2]，值分别是4，5,6
	//c)a和b的点积是一个数值，结果为：a[0]*b[0] + a[1]*b[1]  + a[2]*b[2]  =1*4 + 2*5 + 3*6 = 32

	//(2)混合元编程计算点积
	//（2.1）范例演示
	//dpresult += array1[0] * array2[0];
	//dpresult += array1[1] * array2[1];
	//dpresult += array1[2] * array2[2];
	//DotProduct<int,3>被实例化，DotProduct<int,2>被实例化，DotProduct<int,1>被实例化，DotProduct<int, 0>被实例化
	//DotProduct<int, 3>::result(a, b) = 
	//(*a) * (*b) + DotProduct<int, 2>::result(a + 1, b + 1) =
	//(*a) * (*b) + (*(a+1)) * (*(b+1)) + DotProduct<int, 1>::result(a + 2, b + 2) =
	//(*a) * (*b) + (*(a+1)) * (*(b+1)) + (*(a+2)) * (*(b+2)) +0
	//0=DotProduct<int, 0>::result(a + 3, b + 3)返回的值

	//（2.2）C++编译的两个阶段
	//把整个编译过程分成两个阶段：前期阶段   后期阶段
	//a)前期阶段：此阶段的C++编译器实际充当解释器的角色，直接针对程序员开发的C++源码（元编程代码）进行解释执行，这一阶段的工作成果
	  //就是产生了一系列的C++代码（所以元编程才被看做 运行期 C++代码生成器）。
	//b)后期阶段：此阶段的C++编译器恢复了大家比较熟悉的C++编译器本应该具备的功能——针对前期阶段产生的结果代码进行编译、链接，最终生成可执行程序。

	//（2.3）范例演示的扩展——代码的智能化产生与膨胀
	//int result = (*a) * (*b) + (*(a + 1)) * (*(b + 1)) + (*(a + 2)) * (*(b + 2)) + .........+ (*(a + 11)) * (*(b + 11)) 
	//vs 2019编译器在 针对元编程产生一系列C++代码 方面已经具备了相当的智能性——通过一些函数调用避免产生过分冗长的C++代码。
	//_nmsp2::DotProduct<int, 12>::result(a, b)产生了代码膨胀（最终生成的可执行程序尺寸会变大），这点，适当给已关注。

	//（2.4）类模板实例化进一步观察
	//元编程时小心使用 条件运算符，因为不管条件是否成立，所涉及到的类都可能被实例化出来。
	//std::conditional比条件运算符（?:）更有优势的地方。
	//元编程 “计算完整性”概念，包含几点：
	//a)状态变量：指的是InstantiationObServe类模板中的模板参数。
	//b)迭代构造（循环构造）：通过在InstantiationObServe模板中融入递归编程技术。
	//c)执行路径的选择：使用条件运算符（或者std::conditional)以及InstantiationObServe类模板的特化（达到递归结束的效果），
	               //当然也可以调用其他元函数。
	//d)整数对象（整数运算）：静态成员变量value（或者枚举类型孩子value），其他功能就等价于变量（常量）的功能。

	//元编程中不能使用变量（编译期间能接受的只有静态常量），传统意义上的分支和循环在元编程中只能通过条件运算符、特化、递归等手段来实现。
	  //所以这种编程风格常常也被称为 函数式编程。

	//（2.5）inline静态成员变量（C++17中引入）
	//c++11 constexpr，c++17开始，constexpr自带inline属性
	//static inline const double mystatic2 = 12.6;
	//static constexpr double mystatic2 = 12.6;












	/*cout << _nmsp1::Factorial<5>::value << endl;
	_nmsp1::AddPoint<const char>::type s = "I Love China!";*/

	/*int a[] = { 1,2,3 };
	int b[] = { 4,5,6 };
	int result = _nmsp1::DotProduct<int, 3>(a, b);
	cout << result << endl;*/

	//int a[] = { 1,2,3 };
	//int b[] = { 4,5,6 };
	//int result = _nmsp2::DotProduct<int, 3>::result(a, b); //编译器经过编译后产生了 (*a) * (*b) + (*(a+1)) * (*(b+1)) + (*(a+2)) * (*(b+2)) 
	//                                      //int result =  (*a) * (*b) + (*(a+1)) * (*(b+1)) + (*(a+2)) * (*(b+2)) ;
	//cout << result << endl;
	
	/*
	int a[] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
	int b[] = { 4,5,6,7,8,9,1,2,3,10,11,12 };
	int result = _nmsp2::DotProduct<int, 12>::result(a, b); //编译器经过编译后产生了 (*a) * (*b) + (*(a+1)) * (*(b+1)) + (*(a+2)) * (*(b+2)) 
										  //int result =  (*a) * (*b) + (*(a+1)) * (*(b+1)) + (*(a+2)) * (*(b+2)) ;
	cout << result << endl;

	int result2 = _nmsp2::DotProduct<int, 12>::result(a, b);
	*/

	//DotProduct<int, 0>、DotProduct<int, 1>、DotProduct<int, 2>。。。。DotProduct<int, 12>
	//DotProduct<int,4>::result ,DotProduct<int,7>::result ,DotProduct<int,10>::result 

	cout << _nmsp3::InstantiationObServe<6, 4>::value << endl;

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

/*
	//计算n的阶乘的泛化版本
	template <int n_v>
	struct Factorial
	{
		enum
		{
			value = n_v * Factorial<n_v - 1>::value
		};
	};

	//计算n的阶乘的特化版本，用于做递归调用的出口
	template <>
	struct Factorial<1>
	{
		enum
		{
			value = 1
		};
	};

	//-----------
	template <typename T>
	struct AddPoint //类型元函数
	{
		using type = T * ;
	};

*/
