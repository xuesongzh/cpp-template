// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>
//#include <boost/type_index.hpp>
#include <vector>

using namespace std;
//#pragma warning(disable : 4996) 

namespace _nmsp1
{	
	class ACPABL
	{
	};

	class BCPABL
	{
	public:
		BCPABL& operator=(const BCPABL& tmpobj) //拷贝赋值运算符
		{
			//...
			return *this;
		}
	};
	class CCPABL
	{
	public:
		CCPABL& operator=(const CCPABL& tmpobj) = delete;//拷贝赋值运算符标记为delete
	};

	//IsCopyAssignable类模板
	//泛化版本
	template <typename T, typename U = std::void_t<>>
	struct IsCopyAssignable : std::false_type
	{
	};
	//特化版本
	template <typename T>
	struct IsCopyAssignable<T, std::void_t< decltype(   std::declval<T&>() = std::declval<const T&>()   )  > > :std::true_type //a = b====> a.operator=(b);
		                         //decltype(   std::declval<T&>())  = class T&
		                          //decltype(   std::declval<T&>() = std::declval<const T&>()   )   = class T&
	{

	};

}
namespace _nmsp2
{
	//----------------------
	//泛化版本
	template<typename T, typename U , typename V = std::void_t<>> //T,U,V可以省略template<typename , typename  , typename  = std::void_t<>>
	struct IfCanAdd : std::false_type
	{
	};
	//特化版本
	template<typename T, typename U>
	struct IfCanAdd<T,U,  std::void_t<  decltype (  std::declval<T>()  + std::declval<U>() )   >   > : std::true_type
	{
	};
	//----------------------

	/*
	//考虑设计 一个类模板VecAddResult。
	template<typename T, typename U>
	struct VecAddResult
	{
		//using type = decltype( T() + U()); //把结果类型的推导交给了编译器来做
		using type = decltype(std::declval<T>()  + std::declval<U>());
	};
	*/

	//泛化版本的VecAddResult
	template<typename T, typename U, bool ifcando = IfCanAdd<T,U>::value >
	struct VecAddResult
	{
		using type = decltype(std::declval<T>() + std::declval<U>());
	};

	//特化版本
	template<typename T, typename U>
	struct VecAddResult<T, U, false>
	{
	};

	//----------------------
	template<typename T, typename U>
	using VecAddResult_t = typename   VecAddResult<T, U>::type;


	//----------------------
	template<typename T,typename U> //T,U表示容器中的元素类型
	//std::vector<T> operator+(std::vector<T> const& vec1, std::vector<U> const& vec2) {}; //两个容器相加，重载的+运算符。
	//std::vector< typename   VecAddResult<T,U>::type  > operator+(std::vector<T> const& vec1, std::vector<U> const& vec2)
	std::vector<   VecAddResult_t<T, U>  > operator+(std::vector<T> const& vec1, std::vector<U> const& vec2)
	{
		//随便写几句代码
		//std::vector <  typename   VecAddResult<T, U>::type > tmpvec;
		std::vector <  VecAddResult_t<T, U> > tmpvec;
		return tmpvec;
	};

	struct elemC
	{
		elemC(int tmpvalue); //带一个参数的构造函数
		elemC operator+(const elemC& tmppar); //重载加法运算符以支持加法操作。
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
	
	//（3）借助void_t和declval实现is_copy_assignable
	//C++标准库里的类模板 is_copy_assignable，用来判断一个类对象是否能够进行拷贝赋值。

	//（4）综合范例
	//两个vector容器，元素数量相同（10元素），但是这两个容器中的元素类型不同（比如第一个容器里边是int类型的元素，第二个容器里面是double类型的元素）
	//希望重载一下+运算符，做一下这两个容器的加法运算，加法运算的意思就是第一个容器的第一个元素与第二个容器的第一个元素相加。。。。
	//假如容器中的元素类型不是基本类型，而是一个类类型elemC类型。
	//decltype(elemC() + elemC())
	//代码改进：希望通过SFINAE特性检测一下两个类型的对象之间到底能不能相加。准备引入一个叫做IfCanAdd类模板，用来判断两个类型能否相加。
	//VecAddResult和IfCanAdd这两个类模板之间有一种SFINAE-friendly（SFINAE友好）关系。
	//编写模板时的原则：如果选择要实例化某个模板（operator+，VecAddResult)，则实例化时不应该失败（编译错误）。



	/*
	_nmsp1::ACPABL aobj1;
	_nmsp1::ACPABL aobj2;
	aobj2 = aobj1; //拷贝赋值


	_nmsp1::BCPABL bobj1;
	_nmsp1::BCPABL bobj2;
	bobj2 = bobj1; //拷贝赋值

	_nmsp1::CCPABL cobj1;
	_nmsp1::CCPABL cobj2;
	cobj2 = cobj1; //拷贝赋值*/

	/*cout << "int:" << std::is_copy_assignable<int>::value << endl;
	cout << "ACPABL:" << std::is_copy_assignable<_nmsp1::ACPABL>::value << endl;
	cout << "BCPABL:" << std::is_copy_assignable<_nmsp1::BCPABL>::value << endl;
	cout << "CCPABL:" << std::is_copy_assignable<_nmsp1::CCPABL>::value << endl;*/

	/*cout << "int:" << _nmsp1::IsCopyAssignable<int>::value << endl;
	cout << "ACPABL:" << _nmsp1::IsCopyAssignable<_nmsp1::ACPABL>::value << endl;
	cout << "BCPABL:" << _nmsp1::IsCopyAssignable<_nmsp1::BCPABL>::value << endl;
	cout << "CCPABL:" << _nmsp1::IsCopyAssignable<_nmsp1::CCPABL>::value << endl;*/

	//int i = int(); //定义了一个int类型的变量，而且这种定义方式会把i的初值设置为0；
	//i = 5;
	//double j = double(); //定义了一个double类型的变量，而且这种定义方式会把j的初值设置为0.0；
	//j = 13.6;

	/*
	std::vector< int > veca;
	std::vector< double > vecb;
	//veca + vecb;
	_nmsp2::operator+(veca, vecb);
	*/

	std::vector< _nmsp2::elemC > veca;
	std::vector< _nmsp2::elemC > vecb;
	veca + vecb;

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
