// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>
//#include <boost/type_index.hpp>
#include <functional>


using namespace std;
//#pragma warning(disable : 4996) 

namespace _nmsp1
{	
	void myfunc(int tmpvalue) //普通函数
	{
		std::cout << "myfunc执行了：tmpvalue = " << tmpvalue << endl;
	}

	void callObjFunc(std::function<void(int)> cobj)
	{
		cobj(120);
	}

	//------------------------------------
	//引入一个CFObjHandler类模板，作为可调用对象处理器。
	//可调用对象处理器
	template <typename T,typename ...Args>
	class CFObjHandler
	{
	public:
		virtual T invoke(Args... args) const {}; //虚函数，后续要创建子类
	};



	//----------------------------------------CallFuncObj的类模板，实现std::function的功能。
	//泛化版本(只进行了声明，是因为有特化版本必须得有泛化版本)
	template <typename T>
	class CallFuncObj;

	//特化版本
	template <typename T,typename... Args>
	class CallFuncObj<T(Args...)>
	{
	public:
		//构造函数模板
		template <typename U>
		CallFuncObj(U&& acobj) //可以接收各种可调用对象（函数对象，lambda表达式等)
		{

		}

	public:
		//重载()，实现该类对象的可调用
		T operator()(Args... args) const
		{
			return handler->invoke(std::forward<Args>(args)...); //使用了std::forward实现参数的完美转发，保持原始实参的佐治或者右值性。
		}

	private:
		CFObjHandler<T, Args...>* handler; //可调用对象处理器
	};

	void callObjFunc2(CallFuncObj<void(int)> cobj)
	{		
		cobj(120); //会调用CallFuncObj类模板的operator()成员函数
	}


}

int main()
{ 	
	//第五节 std::function的实现
	//（1）讲述标准库中的std::function
	//std::function：是可调用对象包装器，是C++11新标准引入的类模板。
	//函数名（函数指针）、具有operator()成员函数的类对象、lambda表达式等等，都属于可调用对象。
	//通过范例，感受到了std::function的强大能力——接收各种可调用对象并进行实际的调用。

	//（2）实现类似std::function的功能


	/*
	_nmsp1::callObjFunc(_nmsp1::myfunc);

	_nmsp1::callObjFunc([](int tmpvalue) {
		std::cout << "lambda表达式执行了，tmpvalue = " << tmpvalue << endl;
	});
	*/

	_nmsp1::callObjFunc2(_nmsp1::myfunc);

	_nmsp1::callObjFunc2([](int tmpvalue) {
		std::cout << "lambda表达式执行了，tmpvalue = " << tmpvalue << endl;
		});
	

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
