// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>
#include <vector>

using namespace std;
//#pragma warning(disable : 4996) 

namespace _nmsp1
{	
	template <typename T>
	void myfunc(const T& t)
	{
		cout << "myfunc函数模板执行了" << endl;
	}

	//void myfunc(int tmpvalue)
	//void myfunc(unsigned int tmpvalue)
	void myfunc(unsigned short tmpvalue)
	{
		cout << "myfunc函数执行了" << endl;
	}
}
namespace _nmsp2
{
	template <typename T>
	typename T::size_type mydouble(const T& t)  //typename int::size_type mydouble(const int& t) ;
	{
		return t[0] * 2;
	}
	
	int mydouble(int i)
	{
		return i * 2;
	}
}

int main()
{ 
	//第四节 std::enable_if的使用
	//要逐步的领略 泛型编程 与以往 面向对象编程 的不同之处了
	//（1）一个简单范例:对于重载的函数或者函数模板的选择上，编译器内部有一个自己的规则，
	         //并不是简单粗暴的对函数就优先选择，对函数模板就靠后选择。

	//（2）替换失败并不是一个错误（SFINAE）:每个学习这门课程的人必须听懂，而且必须理解好。
	//SFINAE:Substitution Failure Is Not An Error，翻译成中文是“替换失败并不是一个错误”
	//SFINAE看成是C++语言的一种特性或者说一种模板设计中要遵循的重要原则，非常重要，务必理解好。
	 //SFINAE特性是针对“函数模板重载”而言。
	//针对于函数模板而言，当用一个具体类型替换函数模板的参数时，可能会产生意想不到的问题 ：
	          //比如产生一些毫无意义甚至是看起来语法上有错误的代码，对于这些代码，编译器并不一定报错，有可能是忽略——
	               //编译器认为这个函数模板不匹配针对本次的函数调用，就当这个函数模板不存在一样。
	                //转而去选择其他更匹配的函数或者函数模板，这就是所谓的“替换失败并不是 一个错误”说法的由来。
	//SFINAE特性：我（编译器）虽然看不出你（实例化了的模板）的对错（错误一般指无效的类型，无效的表达式等），但是我能决定是否选择你，
	      //当我觉得不合适的时候，我虽然不说你错，但是我忽略你（而不会选择你）；






	//_nmsp1::myfunc(15); //15编译器一般会认为是一个int类型的有符号数(int)
	//_nmsp1::myfunc(15U); //15U = unsigned int

	//_nmsp2::mydouble(15);

	vector<int> myvec;
	myvec.push_back(15);
	cout << _nmsp2::mydouble(myvec) << endl;

	//vector<int>::size_type
	
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
