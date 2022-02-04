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
	//泛化版本
	template<typename T1, typename T2>
	struct IsSameType
	{
		static const bool value = false;
	};

	//特化版本
	template<typename T1>
	struct IsSameType<T1, T1>
	{
		static const bool value = true;
	};
	//----------------------------------------
	class A {};
	class B
	{
	public:
		B(int tmpval) {};
	};


	/*
	template <typename T>
	class IsDefConstructible
	{
	private:
		template <typename = decltype(T())>
		static std::true_type test(void*); //学习std::declval时看到过只声明，不实现的范例。

		template <typename = int>
		static std::false_type test(...); //...是C语言中的省略号形参，代表可以接受0到多个实参。
		                                   //带省略号形参的test具有最低优先级
	public:
		static constexpr bool value = IsSameType< decltype(test(nullptr)), std::true_type>::value;
	};*/

	template <typename T>
	class IsDefConstructibleHelper
	{
	private:
		template <typename = decltype(T())>
		static std::true_type test(void*);

		template <typename = int> //这行代码其实可以不要
		static std::false_type test(...); 
										  
	public:
		using type = decltype(test(nullptr));
	};
	template <typename T>
	class IsDefConstructible :public IsDefConstructibleHelper<T>::type
	{
	};
}
namespace _nmsp2
{
	class A {};
	class B :public A
	{

	};

	template <typename FROM,typename TO>
	struct IsConvertibleHelper
	{
	private:
		static void testfunc(TO);

		template<typename = decltype(testfunc(std::declval<FROM>()))>
		static std::true_type test(void*);
				
		static std::false_type test(...);
	public:
		using type = decltype(test(nullptr));
	};

	template <typename FROM,typename TO>
	struct IsConvertible : IsConvertibleHelper<FROM, TO>::type //struct默认的继承方式是public
	{

	};

	//变量模板
	template <typename FROM, typename TO>
	constexpr bool IsConvertible_v = IsConvertible<FROM, TO>::value;
}



int main()
{ 	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口
	
	 //第三节 使用了SFINAE特性的信息萃取
	 //SFINAE：替换失败并不是 一个错误
	//（1）用成员函数重载实现is_default_constructible
	//c++标准库：std::is_default_constructible类模板：判断一个类的对象是否能够被默认构造。

	//（2）用成员函数重载实现is_convertible
	//std::is_convertible类模板：能力是判断能否从某个类型隐式的转换到另一个类型。



	//_nmsp1::A aobj;
	////_nmsp1::B bobj;
	//_nmsp1::B bobj(1);


	/*cout << std::is_default_constructible<int>::value << endl;
	cout << std::is_default_constructible<double>::value << endl;
	cout << std::is_default_constructible<_nmsp1::A>::value << endl;
	cout << std::is_default_constructible<_nmsp1::B>::value << endl;*/
	
	/*
	cout << _nmsp1::IsDefConstructible<int>::value << endl;
	cout << _nmsp1::IsDefConstructible<double>::value << endl;
	cout << _nmsp1::IsDefConstructible<_nmsp1::A>::value << endl;
	cout << _nmsp1::IsDefConstructible<_nmsp1::B>::value << endl;
	*/

	/*cout << std::is_convertible<float, int>::value << endl;
	cout << std::is_convertible<int , float>::value << endl;
	cout << std::is_convertible<_nmsp2::A, _nmsp2::B>::value << endl;
	cout << std::is_convertible<_nmsp2::B, _nmsp2::A>::value << endl;*/

	/*cout << _nmsp2::IsConvertible<float, int>::value << endl;
	cout << _nmsp2::IsConvertible<int, float>::value << endl;
	cout << _nmsp2::IsConvertible<_nmsp2::A, _nmsp2::B>::value << endl;
	cout << _nmsp2::IsConvertible<_nmsp2::B, _nmsp2::A>::value << endl;*/

	cout << _nmsp2::IsConvertible_v<float, int> << endl;
	cout << _nmsp2::IsConvertible_v<int, float> << endl;
	cout << _nmsp2::IsConvertible_v<_nmsp2::A, _nmsp2::B> << endl;
	cout << _nmsp2::IsConvertible_v<_nmsp2::B, _nmsp2::A> << endl;

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
	template<typename T1, typename T2>
	struct IsSameType
	{
		static const bool value = false;
	};

	//特化版本
	template<typename T1>
	struct IsSameType<T1,T1>
	{
		static const bool value = true;
	};

*/