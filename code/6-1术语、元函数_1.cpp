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
	//元函数(数值元函数)
	constexpr int myfunc(int abc)
	 //int myfunc(int abc)
	{
		return abc * 2;
	}

}
namespace _nmsp2
{
	/*template <int x_v ,int y_v>
	struct Calc
	{
		enum
		{
			addvalue = x_v + y_v,
			subvalue = x_v - y_v
		};
	};*/

	template <int x_v, int y_v>
	struct Calc
	{
		static const int addvalue = x_v + y_v; //const可以用constexpr代替
	};

	void testfunc(const int &tmpvalue)
	{
		return;
	}
}
namespace _nmsp3
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

}
namespace _nmsp4
{
	constexpr int Factorial(int n_v)
	{
		return n_v <= 1 ? 1 : (n_v * Factorial(n_v - 1));
	}
}
namespace _nmsp5
{
	constexpr int Factorial(int n_v)
	{
		int result = 1;
		for (int i = 1; i <= n_v; ++i)
		{
			result *= i;
		}
		return result;
	}
}
namespace _nmsp6
{
	/*
	//变量模板（其实result代表的是常量），看起来也像函数调用，也是元函数的一种形式
	//泛化版本
	template<int Arg>
	constexpr int result = Arg * result<Arg - 1>;

	//特化版本
	template <>
	constexpr int result<0> = 1;
	*/

	//泛化版本
	template<int Arg>
	constexpr int result()
	{
		return Arg * result<Arg - 1>();
	}

	//特化版本
	template<>
	constexpr int result<0>()
	{
		return 1;
	}

	//----------------------------	
	//泛化版本
	template<int ...FTArgs>
	constexpr int resultsum = 0;

	//特化版本
	template <int First, int ... Others>
	constexpr int resultsum<First, Others...> = First + resultsum<Others...>;


	//--------------
	template <int ... FTArgs>
	constexpr int resultsum2()
	{
		return (... + FTArgs); //或者写成return (0 + ... + FTArgs);
	}


}
namespace _nmsp7
{
	//template <typename T>
	//struct AddPoint //类型元函数
	//{
	//	using type = T * ;
	//};

	template <typename T>
	using AddPoint = T * ; //元函数
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口

	//第六章  元编程
	//元编程：将各种计算从运行期提前至编译器进行以达到提供程序运行时性能提升的目的，是一种增加程序编译时间从而提升程序运行效率的一种编程技术。
	//元编程：会涉及到很多与循环有关的代码，很多操作针对的是类型、常量，此种循环的实现往往会采用递归手段。
	//范例：typelist（类型列表）、tuple（元组）。
	//Boost库有一个叫做MPL（Meta-Programming Library)库，用于辅助模板元编程。
	//《C++模板元编程》书籍，对MPL有比较详细的介绍。
	//GitHub有一个MPL11元编程库：使用了C++11新标准语法对Boost中的MPL进行了改写。

	//第一节 术语、元函数
	//（1）术语
	//元编程：Meta Programming，也叫模板元编程（tmplate meataprogramming)，可以理解为一种编程手法，用来实现一些比较特殊的功能。
	 //一般和 “递归”这个词有比较密切的联系。多数都会在元编程中使用到递归编程技术。
	//元编程随着C++新标准的推出，也在不断发展，能力越来越强大。
	//模板编程主要两个方面：a)泛型编程（generic programming）； b)元编程(meat programming)
	 //a)泛型编程：“通用”，程序员不需要关心具体类型
	 //b)元编程：突出一种程序设计技巧达到常规编程难以达到的效果。前面章节：std::remove_all_extents类模板的实现。
	   //这种技巧注重模板在实例化过程中的一些推导过程，而这些推导过程恰恰是解决问题和体现程序设计技巧的过程。
	   //此外，元编程手法还可以让某些计算在程序的编译期间完成,提高了程序运行的性能。
	    //1994年C++标准委员会会议上，Erwin Unruh，演示了一段利用编译器错误信息计算素数的代码。。。。
	//老师建议，将元编程直接理解为泛型编程。元编程只是在编程方式上比传统的泛型编程更特殊一点。

	//（2）元函数
	//元函数：能在程序编译期间被调用和执行的函数（编译期间就能得到结果）。元编程的核心也正是这些元函数。
	//总结：所谓元编程就是用这些元函数进行编程，甚至可以说，书写和使用这些元函数的过程本身就是在进行元编程。
	//C++11 引入 constexpr关键字用于在编译的时候求值。
	//constexpr 自带inline属性，该属性是在C++17中引入的。

	//（2.1）数值元函数
	//a)编译期间能够被调用的类模板
	//范例：在编译期间计算5的阶乘：1*2*3*4*5 = 120
	//b)constexpr修饰的函数
	//c)constexpr修饰的变量模板
	//（2.2）类型元函数
	//4.6：std::remove_all_extents类模板。remove_all_extents类模板所实现的元编程就是靠递归模板实例化来驱动的。
	//象AddPoint这种包含了using来定义类型别名的类模板，就可以称为类型元函数（fixed trait类模板）；

	//元函数总结：宽泛的概念，只要用于元编程之中，在编译期间能够被调用，都可以视为元函数，不必局限在数值元函数和类型元函数分类上。












	////编译期间调用myfunc
	//constexpr int var = 11 * _nmsp1::myfunc(12);
	//static_assert(var == 264, "std error"); //静态断言,编译期间断言

	/*
	//运行期间调用myfunc
	int var2 = 12;
	int var3 = _nmsp1::myfunc(var2);
	*/

	/*
	const int var3 = _nmsp2::Calc<12, 15>::addvalue;
	static_assert(var3 == 27, "sth error");
	cout << var3 << endl;
	cout << _nmsp2::Calc<12, 15>::subvalue << endl;
	*/
	//_nmsp2::testfunc(_nmsp2::Calc<12, 15>::addvalue);

	/*
	cout << _nmsp3::Factorial<5>::value << endl; // _nmsp3::Factorial<5>::value理解成函数调用
	static_assert(_nmsp3::Factorial<5>::value == 120, "sth error");
	int tempvalue = _nmsp3::Factorial<5>::value;
	*/

	/*
	cout << _nmsp4::Factorial(5) << endl;
	static_assert(_nmsp4::Factorial(5) == 120, "sth error");
	int tempvalue = _nmsp4::Factorial(5);
	*/
	//int tempvalue = _nmsp5::Factorial(5);
	//cout << _nmsp6::result<5> << endl;
	//cout << _nmsp6::result<5>() << endl;
	//cout << _nmsp6::resultsum<1, 10, 100> << endl;
	//cout << _nmsp6::resultsum2<1, 10, 100>() << endl;

	//_nmsp7::AddPoint<const char>::type s = "I Love China!"; //_nmsp7::AddPoint<const char>::type 等价于const char *
	//printf("s的类型是：%s\n", typeid(decltype(s)).name());

	_nmsp7::AddPoint<const char> s = "I Love China!";
	printf("s的类型是：%s\n", typeid(decltype(s)).name());

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
