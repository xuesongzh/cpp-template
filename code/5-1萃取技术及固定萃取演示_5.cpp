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

template<typename T>
void myfunc(T tmprv)
{
	cout << "---------------------begin------------------------" << endl;
	using boost::typeindex::type_id_with_cvr;
	cout << "T=" << type_id_with_cvr<T>().pretty_name() << endl;               //显示T类型
	cout << "tmprv=" << type_id_with_cvr<decltype(tmprv)>().pretty_name() << endl; //显示tmprv类型
	cout << "----------------------end-------------------------" << endl;
}

namespace _nmsp1
{	
	//泛化版本
	template<typename T>
	struct RemoveReference
	{
		using type = T;
	};

	//特化版本
	template<typename T>
	struct RemoveReference<T&>
	{
		using type = T;
	};
	template<typename T>
	struct RemoveReference<T&&>
	{
		using type = T;
	};
	template <typename T>
	using RemoveReference_t = typename RemoveReference<T>::type;
	//-------------------------------------

	//泛化版本
	template <typename T>
	struct RemoveConst
	{
		using type = T;
	};
	//特化版本
	template <typename T>
	struct RemoveConst<const T>
	{
		using type = T;
	};
	//根据需要增加其他特化版本....

	template <typename T>
	using RemoveConst_t = typename RemoveConst<T>::type;

	//------------
	void testFunc() {}

	//----------------------------------------
	template <typename T>
	struct RemoveCR :RemoveConst<typename RemoveReference<T>::type> //把const和引用修饰符去掉
	{

	};
	template <typename T>
	using RemoveCR_t = typename RemoveCR<T>::type;
	/*template <typename T>
	using RemoveCR_t = RemoveConst_t<typename RemoveReference_t<T>>;*/

	//----------------------------------------
	//泛化版本
	template<typename T>
	struct Decay :RemoveCR<T>
	{
	};
	//特化版本，处理数组,该特化版本没有继承任何父类
	//有边界数组转换成指针
	template<typename T,std::size_t size>
	struct Decay<T[size]>
	{
		using type = T*;
	};

	//无边界数组转换成指针
	template<typename T>
	struct Decay<T[]>
	{
		using type = T*;
	};
	//函数名变成了函数指针等
	template <typename T,typename... Args>
	struct Decay<T(Args...)> //返回类型是T，参数Args....
	{
		using type = T(*)(Args...);
	};
	template <typename T>
	using Decay_t = typename Decay<T>::type;


	//----------------------
	void testFunc2()
	{
		cout << "testFunc2()执行了" << endl;
	}

}

//void rfunc()
//{
//	cout << "rfunc执行了!" << endl;
//}

extern int g_array[]; //int []
int main()
{ 	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口
	

	//第一节 萃取技术及fixed traits（固定萃取）演示
	//（5）const修饰符的移除RemoveConst类模板，与C++标准库里std::remove_const比较类似。
	//（6）退化（decay）技术
	//退化：对于const int类型来说，int类型就是一种退化的表现。
	//const修饰符和&、&&修饰符被丢弃，数组类型变成指针类型，函数名变成了函数指针等，都是类型上的退化表现。
	//c++标准库：std::decay，该类模板的作用就是把类型退化掉（把类型中的修饰符丢弃掉）。
	//无边界数组，某个.cpp源文件中定义一个全局数组   int g_array[10]; int[10];
	//extern int g_array[];  //外部变量说明
	//基本概念：
	//a)函数类型：由函数返回值和函数参数决定，testFunc2代表的函数类型void()
	//b)可以利用函数指针指向某种函数类型,若要指向testFunc2，那么函数指针的类型就应该void(*)()
	//c)如果不为“函数名退化成函数指针”写一个Decay的特化版本，观察一些测试代码：给进去的是函数类型，返回的依旧是函数类型。





	/*
	_nmsp1::RemoveConst_t<const int> nca = 15; //nca是int类型
	nca = 18; //可以给nca重新赋值
	*/
	/*
	const int a = 16;
	const int& b = a;
	const int&& c = 18;
	int array[5] = { 1,2,3,4,5 };
	myfunc(a);
	myfunc(b);
	myfunc(c);
	myfunc(array);
	myfunc(_nmsp1::testFunc);*/

	/*
	std::decay<const int&>::type nb = 26;
	cout << "nb的类型为：" << typeid(decltype(nb)).name() << endl;  //nb类型为int类型。*/

	//_nmsp1::RemoveCR_t<const int&&> rcrobj = 16; //rcrobj为int类型。
	/*
	int arr[2] = { 1,2 };
	_nmsp1::Decay<decltype(arr)>::type myarray;
	cout << "myarray类型为：" << typeid(decltype(myarray)).name() << endl;
	*/

	/*
	_nmsp1::Decay<decltype(g_array)>::type myarray2;
	cout << "myarray2类型为：" << typeid(decltype(myarray2)).name() << endl;
	*/

	/*
	void (*p) () = _nmsp1::testFunc2; //定义了一个函数指针，指向testFunc2函数
	p(); //调用p指向的函数，调用的是testFunc2函数。
	*/

	//_nmsp1::Decay<decltype(_nmsp1::testFunc2)>::type rfunc; //表面看起来此代码行定义了一个函数类型的变量rfunc，实际理解成函数声明更好
	//                                                          //类似于这种代码行的感觉：    void rfunc();

	//cout << "rfunc类型为：" << typeid(decltype(rfunc)).name() << endl;
	//rfunc(); //调用rfunc函数




	//_nmsp1::Decay<decltype(_nmsp1::testFunc2)>::type rfunc;
	_nmsp1::Decay_t<decltype(_nmsp1::testFunc2)> rfunc;
	cout << "rfunc类型为：" << typeid(decltype(rfunc)).name() << endl;
	rfunc = _nmsp1::testFunc2; //给函数指针赋值
	rfunc(); //相当于调用了testFunc2函数

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
//泛化版本
template<typename T>
struct RemoveReference
{
	using type = T;
};

//特化版本
template<typename T>
struct RemoveReference<T&>
{
	using type = T;
};
template<typename T>
struct RemoveReference<T&&>
{
	using type = T;
};

*/