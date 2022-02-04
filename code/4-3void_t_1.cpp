// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>
//#include <boost/type_index.hpp>

using namespace std;
//#pragma warning(disable : 4996) 

namespace _nmsp1
{	
	//// ALIAS TEMPLATE void_t
	//template <class... _Types>
	//using void_t = void;

	struct NoInnerType
	{
		int m_i;
	};

	struct HaveInnerType
	{
		using type = int; //类型别名
		void myfunc() {}
	};


	//泛化版本
	template <typename T,typename U = std::void_t<> >
	struct HasTypeMem : std::false_type  //struct 默认是public ,class默认是private继承
	{
	};
	//特化版本
	template <typename T>
	struct HasTypeMem<T, std::void_t<typename T::type> > : std::true_type //叫sizetype
	{
	};

	//带参数的宏定义,注意 反斜杠 表示下一行接着本行来，是本行的一部分
	#define _HAS_TYPE_MEM_(parMTpNm) \
	template <typename T,typename U = std::void_t<> > \
	struct HTM_##parMTpNm : std::false_type {}; \
	template <typename T> \
	struct HTM_##parMTpNm<T, std::void_t<typename T::parMTpNm> > : std::true_type{};

	_HAS_TYPE_MEM_(type);
	_HAS_TYPE_MEM_(sizetype);


	//_HAS_TYPE_MEM_(type);展开后
	/*template <typename T, typename U = std::void_t<> > 
		struct HTM_type : std::false_type{}; 
	template <typename T> 
	struct HTM_type<T, std::void_t<typename T::parMTpNm> > : std::true_type{};*/
	//_HAS_TYPE_MEM_(sizetype);展开后
	/*template <typename T, typename U = std::void_t<> >
	struct HTM_sizetype : std::false_type {};
	template <typename T>
	struct HTM_sizetype<T, std::void_t<typename T::parMTpNm> > : std::true_type {};*/


	//泛化版本
	template <typename T, typename U = std::void_t<> > 
	//template <typename T, typename U = int >
	//template <typename T, typename U = void >
	struct HasMember : std::false_type  //HasMember<HaveInnerType,void>
	{
	};
	//特化版本
	template <typename T>
	struct HasMember<T, std::void_t<decltype(T::m_i)> > : std::true_type  //HasMember<NoInnerType,void>
	{
	};

	//------------
	//泛化版本
	template <typename T, typename U = std::void_t<> >
	struct HasMemFunc : std::false_type 
	{
	};
	//特化版本
	template <typename T>
	struct HasMemFunc<T, std::void_t<decltype(std::declval<T>().myfunc())> > : std::true_type 
	{
	};
}

int main()
{ 	
	//第三节 std::void_t
	//（1）源码分析和常规范例
	  //功能：能够检测到应用SFINAE(替换失败并不是一个错误）特性时出现的非法类型。换句话说，给进来的类型必须是一个有效的类型，不能是一个非法类型。
	//（1.1）判断类中是否存在某个类型别名
	//（1.2）判断类中是否存在某个成员变量
	//（1.3）判断类中是否存在某个成员函数

	//（2）泛化版本和特化版本到底编译器如何选择
	 //编译器通过一种复杂的排序规则来决定使用类模板的泛化版本还是特化版本。
	 //一般来说，void这个干儿子跟任何其他类型比，都是最不受待见的那个。






	/*
	//std::void_t
	cout << _nmsp1::HasTypeMem<_nmsp1::NoInnerType>::value << endl;
	cout << _nmsp1::HasTypeMem<_nmsp1::HaveInnerType>::value << endl;*/

	/*
	cout <<  _nmsp1::HTM_type<_nmsp1::NoInnerType>::value << endl; 
	cout << _nmsp1::HTM_type<_nmsp1::HaveInnerType>::value << endl;

	cout << _nmsp1::HTM_sizetype<_nmsp1::NoInnerType>::value << endl;
	cout << _nmsp1::HTM_sizetype<_nmsp1::HaveInnerType>::value << endl;
	*/

	
	cout << _nmsp1::HasMember<_nmsp1::NoInnerType>::value << endl;
	cout << _nmsp1::HasMember<_nmsp1::HaveInnerType>::value << endl;
	

/*	cout << _nmsp1::HasMemFunc<_nmsp1::NoInnerType>::value << endl;
	cout << _nmsp1::HasMemFunc<_nmsp1::HaveInnerType>::value << endl;*/

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
