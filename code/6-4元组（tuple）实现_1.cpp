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

#include <boost/type_index.hpp>
using namespace std;
//#pragma warning(disable : 4996) 

namespace _nmsp1
{
	
}
//void mf(int& j) {}
void mf(const int& j) {}
void mf2(int&& k) {}
void mf3(int m) {}
//void myfunc(int &&tmprv){}
//void myfunc(int& tmprv) {}
template <typename T>
void myfunc(T&& tmprv) //tmprv就是万能引用类型
{
	//这里借助boost手段以得到准确的类型信息
	using boost::typeindex::type_id_with_cvr;
	cout << "T=" << type_id_with_cvr<T>().pretty_name() << endl;               //显示T类型
	cout << "tmprv的类型=" << type_id_with_cvr<decltype(tmprv)>().pretty_name() << endl; //显示tmprv类型
}

template <typename T>
class TmpClass
{
public:
	//TmpClass(T&& tmpvalue)
	template <typename T2>	
	TmpClass(T2&& tmpvalue)  //T2&&是万能引用类型
	{
		cout << "TmpClass::TmpClass()执行了" << endl;
	}
};

void lastfunc(int&& tmprv) {}

template <typename T>
void midfunc(T&& tmprv) //转发----tmprv的类型 int &&，T 的类型是int
                        //虽然tmprv的类型是右值引用类型int&&,但是tmprv本身是个左值，因为tmprv可以放在赋值语句的左侧，所以是个左值。
{
	//lastfunc(tmprv);
	lastfunc(std::forward<T>(tmprv));
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口
		
	//第四节 元组(tuple)实现
	//（1）重要基础知识回顾
	//（1.1）左值、右值、左值引用、右值引用
	//口诀：左值引用只能绑定到左值上。但是，编译器会且只会为const引用开绿灯，可以让其绑定左值，也可以让其绑定右值。
	//口诀：右值引用只能绑定到右值上。
	//（1.2）std::move究竟干了什么
	//std::move：类型转换函数，把一个左值转换成一个右值，如果原来是右值，使用std::move后没有啥效果。
	//（1.3）std::forward究竟干了什么
	//std::forward也是一个类型转换函数（函数模板）
	//std::forward是根据后面尖括号<>中的类型决定整个std::forward要转换成什么类型——尖括号中是左值引用类型，
	       //则std::forward转换成左值，否则转换成右值。
	//std::forward有两个明显的作用：a)提高程序运行效率；b)用于完美转发
	//（1.4）万能引用（转发引用）
	//（1.5）完美转发
	//一个变量，从左值右值这个角度来讲必然是个左值，因为它能放在赋值运算符左侧。
	//一个变量，从类型这个角度，可能是左值引用类型，也可能是右值引用各类型，也可能根本就不是个引用类型，试比较int &i;int &&j; int k;




	//int i = 10;
	////int& j = 10; // i;
	//int& j = i;
	//mf(i);
	////mf(10);
	/*const int& j = 10;
	mf(10);
	//int&& k = 10;
	int&& k = std::move(i);// std::move(i)的结果是一个右值引用类型
	k = 200;
	cout << i << endl;
	mf2(10);
	int m; //m这个类型通吃
	mf3(10);
	mf3(i);*/

	/*
	int&& m = std::forward<int&&>(i);  //把i用数字10替换，效果一样
	//int&& n = std::forward<int&>(i);   //把i用数字10替换，效果一样
	int&& p = std::forward<int>(i);    //把i用数字10替换，效果一样

	std::string str1 = "abc";
	std::string str2 = str1;
	std::string str3 = std::forward<std::string&&>(str1); // 因为使用了forward，导致std::forward<std::string&&>(str1)变成了右值引用类型
	                                                       //此时，构造str3时会调用std::string的移动构造函数。
	 */

	/*
	int k = 10;
	myfunc(k);
	myfunc(10);
	
	TmpClass<int> tcobj1(10);
	TmpClass<int> tcobj2(k);*/

	//lastfunc(10);
	midfunc(10);

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











