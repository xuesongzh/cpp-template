// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>


#ifdef _DEBUG   //只在Debug（调试）模式下
#ifndef DEBUG_NEW
#define DEBUG_NEW new(_NORMAL_BLOCK,__FILE__,__LINE__) //重新定义new运算符
#define new DEBUG_NEW
#endif
#endif

//#include <boost/type_index.hpp>
using namespace std;
//#pragma warning(disable : 4996) 

namespace _nmsp1
{
	
}

namespace tpl
{
	//泛化版本
	template <typename ...Types>
	class TuplE;

	//特化版本1
	template <typename First,typename ...Others>
	class TuplE<First, Others...>
	{
	public:
		First  first;
		TuplE<Others...> others;

	public:
		//构造函数1，支持tpl::TuplE<int,float> mytuple;这种构造方式 
		TuplE()
		{
		}

		//构造函数模板2，支持tpl::TuplE<float, int, std::string> mytuple(12.5f, 100, std::string("abc"));这种构造方式 
		template<typename C_First,typename ... C_Others>  //C_First代表一个元素类型比如float，C_Others代表其余一堆元素类型 int, std::string，
		TuplE(C_First&& parf, C_Others&& ... paro) :first(std::forward<C_First>(parf)),  //parf或者first代表第一个元素比如12.5f，
			others(std::forward<C_Others>(paro)...) //others或者paro代表其余元素，比如 100, std::string("abc")
													//others是TuplE<...>类型
		{
			//cout << "TuplE构造函数模板2执行了，first = " << first << endl; //为了避免报错，牵扯开发者精力，不要输出first值，因为有些first值不嫩共用cout正常输出
			cout << "TuplE构造函数模板2执行了！" << endl;
		}			                                       
	};

	//特化版本2：空元组不需要存储任何内容，支持tpl::TuplE<> mytuple;这种构造方式
	template<>
	class TuplE<>
	{
	public:
		//构造函数
		TuplE()
		{
			m_sign = 0; //随便给个值，方便调试时观察而已
			cout << "TuplE特化版本2的构造函数执行了！" << endl;
		}
		//拷贝构造函数
		TuplE(const TuplE<>&)
		{
			m_sign = 100;//随便给个值，方便调试时观察而已
			cout << "TuplE特化版本2的拷贝构造函数执行了！" << endl;
		}
		int m_sign; //引入的目的其实仅仅是为了设置断点调试时方便观察和确认
	};

}
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口
	
	//第四节 元组（tuple）实现
	//（2）元组基本概念、基础代码的设计和实现
	//Boost-tuple（元组）：tuple是一个里面能够装各种不同类型元素的数组/容器。
	//（2.1）泛化、特化、构造函数的实现
	//可变参类模板的模板参数包的展开方式有两种：a)通过递归继承方式展开，b)通过递归组合方式展开（要讲的）
	//递归组合方式缺点：占用的内存可能相对多一点（一般就是一个字节），因为会涉及到一个“空白基类优化（EBCO）”的话题。
	//tpl::TuplE<float, int, std::string> 拆分成float和tpl::TuplE< int, std::string>
	//tpl::TuplE< int, std::string>拆分成int 和tpl::TuplE<std::string>
	//tpl::TuplE<std::string>拆分成std::string和tpl::TuplE<>





	//tuple<float, int, std::string> mytuple(12.5f, 100, std::string("abc")); //一个tuple（元组）：一堆各种类型数据的组合
	//cout << get<0>(mytuple) << endl; //12.5,get是一个函数模板。

	int i = 100;
	tpl::TuplE<float, int, std::string> mytuple(12.5f, i, std::string("abc"));
	

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

