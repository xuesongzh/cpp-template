// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>



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

	//----------------------------------
	class A {};
	class B : public A
	{
	};
	//----------------------------------
	template <typename T>
	class IsClass
	{
	private:
		template <typename U>
		static std::integral_constant<bool, !std::is_union<U>::value> test(int U::*); //形参：代表成员变量指针，去掉了指针名
		                    //如果T(U)不是一个联合那么返回类型就变成了 std::integral_constant<bool, true>,
		                     //否则，返回类型就变成了 std::integral_constant<bool, false>.

		template <typename>
		static std::integral_constant<bool, false> test(...);

	public:
		static constexpr bool value = IsSameType <
			decltype(test<T>(nullptr)),
			std::integral_constant<bool,true>		
		>::value;
	};
	
	//------------------------------
	template <typename Base, typename Derived> //<父，子>
	class IsBaseOf
	{
	private:
		template <typename T>
		static std::true_type test(T*);

		template <typename>
		static std::false_type test(void *);

		template <typename B,typename D> //<父，子>
		static auto test_middle()->decltype(test<B>(static_cast<D*>(nullptr))); //调用test()

	public:
		static constexpr bool value = IsSameType<

			std::integral_constant<
					bool, 
					std::is_class_v<Base> && 
					std::is_class_v<Derived> && 
					decltype(test_middle<Base,Derived>())::value //std::true_type::value
			>
			,
			std::integral_constant<bool,true>

		>::value;
	};

	//--------------------------
	class PAR {};//父类
	class SON :public PAR {}; //PAR的子类
	class OTHER {}; //其他类
	void f(PAR*) {}
	void f(void*) {}



}
namespace _nmsp2
{
	class A{};
	class B
	{
	public:
		B(int tmpval) {}; //构造函数
	};


	//泛化版本
	template <typename T,typename U = std::void_t<>>
	class IsDefConstructible :public std::false_type //IsDefConstructible<B,void>
	{

	};
	//特化版本
	template <typename T>
	class IsDefConstructible<T, std::void_t<decltype(T()) >   > :public std::true_type //IsDefConstructible<A,void>
	{

	};
}

int main()
{ 	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口
	
	//第三节 使用了SFINAE特性的信息萃取
	//（3）用成员函数重载实现is_class
	//std::is_class：是否是一个类类型（不是联合类型）的类模板。

	//（4）用成员函数重载实现is_base_of
	//std::is_base_of:判断某个类是否是另一个类父类的类模板
	//template <typename Base,typename Derived>
	//struct is_base_of{....}
	//c++17
	//template <typename Base,typename Derived>
	//inline constexpr bool is_base_of_v = is_base_of<Base,Derived>::value;

	//（5）用类模板特化实现is_default_constructible
	//std::void_t别名模板：能够检测到应用SFINAE特性时出现的非法类型。
	//template<typename ...Args>
	//using void_t = void;
	//IsDefConstructible与IsCopyAssignable范例类似。





	/*
	cout << _nmsp1::IsClass<_nmsp1::A>::value << endl;
	cout << _nmsp1::IsClass<_nmsp1::B>::value << endl;
	cout << _nmsp1::IsClass<int>::value << endl;
	*/

	//int _nmsp1::A::*mp = nullptr;

	/*cout << std::is_base_of<_nmsp1::A,_nmsp1::A>::value << endl;
	cout << std::is_base_of<_nmsp1::B, _nmsp1::A>::value << endl;
	cout << std::is_base_of<_nmsp1::A, _nmsp1::B>::value << endl;*/

	/*cout << std::is_base_of_v<_nmsp1::A, _nmsp1::A> << endl;
	cout << std::is_base_of_v<_nmsp1::B, _nmsp1::A> << endl;
	cout << std::is_base_of_v<_nmsp1::A, _nmsp1::B> << endl;*/

	/*

	cout << _nmsp1::IsBaseOf<_nmsp1::A, _nmsp1::A>::value << endl;
	cout << _nmsp1::IsBaseOf<_nmsp1::B, _nmsp1::A>::value << endl;
	cout << _nmsp1::IsBaseOf<_nmsp1::A, _nmsp1::B>::value << endl;


	_nmsp1::f(static_cast<_nmsp1::PAR*>(nullptr)); //没问题
	_nmsp1::f(static_cast<_nmsp1::SON*>(nullptr)); //没问题，因为SON是PAR的子类
	_nmsp1::f(static_cast<_nmsp1::OTHER*>(nullptr)); //编译报错

	 */

	cout << _nmsp2::IsDefConstructible< _nmsp2::A>::value << endl;
	cout << _nmsp2::IsDefConstructible< _nmsp2::B>::value << endl;

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
class A {};
class B : public A
{
};

//-------------
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