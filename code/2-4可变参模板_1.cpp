// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>


//#include <boost/type_index.hpp>
using namespace std;
//#pragma warning(disable : 4996) 

namespace _nmsp1
{
	void myptfunct()
	{
	}

	//可变参函数模板
	//template <typename... T>  //...代表参数包
	//void myvtfunct(T... args) //T：一包类型，args：一包形参   ,T称为“可变参类型”,T中包含的是0到多个不同的类型（一包类型）
	//	                           //args称为一包/一堆 参数（函数模板的形参：0个到多个），每个参数的类型可以各不相同。
	//{
	//	cout << "-----------begin-----------" << endl;
	//	cout << sizeof...(args) << endl;   //收到的参数数量，sizeof...固定语法，C++11中引入，用于表示 收到的模板参数个数或者类型数量。
	//	                                       //sizeof...针对的只能是这种...的可变参，后面圆括号中可以是函数模板的形参args，也可以是类型模板参数T.
	//	cout << sizeof...(T) << endl;      //收到的类型数量
	//	cout << "-----------end-----------" << endl;
	//}
	//再实现一个同名的递归终止函数(这是个真正的函数)，位置放在  参数包展开函数 的前面
	//void myvtfunct() //这是个普通函数，而不是函数模板
	//{
	//	cout << "参数包展开时执行了递归终止函数myvtfunct()" << endl;
	//}

	//先实现参数包展开函数
	template <typename T,typename...U>
	void myvtfunct(T firstarg, U...otherargs)  //(10, "abc", 12.7);
	{
		cout << "收到的参数值：" << firstarg << endl;
		//myvtfunct(otherargs...); //递归调用，注意塞进来的是一包形参，这里的...不能省略
		if constexpr (sizeof...(otherargs) > 0) //constexpr必须有否则无法成功编译，圆括号中是常量表达式。
		{
			myvtfunct(otherargs...); //递归调用，注意塞进来的是一包形参，这里的...不能省略
		}
		else
		{
			//不需要做什么，其实整个else都可以不要。
		}


	/*	if constexpr (sizeof...(otherargs) > 100) //不管if constexpr条件是否成立，{}中的代码行都会被编译
		{
			testfunc();
		}*/
//#define _MYDEF_
//#ifdef  _MYDEF_
//		testfunc();
//#endif

		/*int i = 8;
		if constexpr (i > 8)
		{

		}*/

	}
}
namespace _nmsp2
{
	template<typename... T>
	void myfunc(T... arg)
	{
		cout << "myfunc(T... arg)执行了!" << endl;
	}

	template<typename... T>
	void myfunc(T*... arg)
	{
		cout << "myfunc(T*... arg)执行了!" << endl;
	}

	void myfunc(int arg)
	{
		cout << "myfunc(int arg)执行了!" << endl;
	}

}


int main()
{
	//四：可变参模板
	//英文：Variadic Templates ，C++11
	//允许模板定义中包含 0 ，到多个（任意个）模板参数。
	//C++17
	//（1）可变参函数模板
	//（1.1）基本含义
	  //可变参函数模板中，传递进来的一包实参怎样展开：一般都采用递归函数的方式展开参数包。
	     //要展开，要求，在可变参函数模板代码中，有一个  参数包展开函数，  以及 一个 同名的递归终止函数。
	       //a)myvtfunct(10, "abc", 12.7);    b)myvtfunct( "abc", 12.7); c)myvtfunct(12.7); d)myvtfunct();

	//C++17中增加了一个语句，叫做“编译期间if语句（constexpr if)”。
	//if constexpr()....   //constexpr，代表“常量”的意思，或者代表“编译时求值”的意思。
	//myvtfunct<int,char const *,double>(int,char const *,double)	
	//myvtfunct<char const*, double>(char const*, double)
	//myvtfunct<double>(double)
	//深入认识if constexpr
	//a)不满足条件的分支，也同样会被编译器编译(被编译器进行语法检查）。
	//b)if constexpr所指定的条件必须是常量：理解成普通if语句，只是判断条件从执行期间挪到了编译期间
	//总结：if constexpr的存在，完善了模板与泛型编程中的程序执行路径选择问题。

	//（1.2）重载
	//一般来说，调用普通函数和调用函数模板都合适的时候，编译器优先选择普通函数。
	 //把握不准时，可以多做测试。







	//_nmsp1::myvtfunct();
	//_nmsp1::myvtfunct(10,20);
	//_nmsp1::myvtfunct(10, 25.8,"abc",68);
	//_nmsp1::myvtfunct<double,double>(10, 25.8, "abc", 68,73); //指定部分类型，让编译器去推断另一部分类型，是允许的。

	//_nmsp1::myvtfunct(10, "abc", 12.7);


	_nmsp2::myfunc(NULL);
	_nmsp2::myfunc(nullptr); //nullptr是空指针
	_nmsp2::myfunc((int *)nullptr);





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
