// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>
//#include <boost/type_index.hpp>

using namespace std;
//#pragma warning(disable : 4996) 

namespace _nmsp1
{	
	struct A {};
	union B
	{
		int num;
		char type;
	};

	/*template <class T, T _Val>
	struct integral_constant 
	{
		static constexpr T value = _Val;
		using value_type = T;
		using type = integral_constant;
		constexpr operator value_type() const noexcept 
		{
			return value;
		}
		constexpr value_type operator()() const noexcept 
		{
			return value;
		}
	};*/

}

int main()
{ 	
	//第八节 std::is_union、std::is_class、std::integral_constant
	//（1）std::is_union：类模板。用于判断某个类型是否是一个联合类型。
	//template <typename T>
	//struct is_union{.....};
	//template <class T>
	//inline constexpr bool is_union_v = is_union<T>::value;

	//（2）std::is_class：类模板。用于判断某个类型是否是一个类类型（联合不是类类型）。
	//template <typename T>
	//struct is_class{.....};
	//template <class T>
	//inline constexpr bool is_class_v = is_class<T>::value;

	//（3）std::integral_constant：C++11新标准引入的类模板。
	//integral_constant是一个用于包装目的的类。





	//cout << std::is_union<_nmsp1::A>::value << endl; //如果是联合,value就为true(1)，否则为false(0)
	//cout << std::is_union<_nmsp1::B>::value << endl;

	//cout << std::is_union_v<_nmsp1::A> << endl; //如果是联合,value就为true(1)，否则为false(0)
	//cout << std::is_union_v<_nmsp1::B> << endl;


	/*cout << std::is_class<_nmsp1::A>::value << endl;
	cout << std::is_class<_nmsp1::B>::value << endl;

	cout << std::is_class_v<_nmsp1::A> << endl;
	cout << std::is_class_v<_nmsp1::B> << endl;*/

	/*cout << std::integral_constant<int,15>::value << endl;
	cout << std::integral_constant<bool, true>::value << endl;*/
		
	//通过integral_constant的包装，把 !std::is_union<_nmsp1::B>::value 这个值（0）包装成了一个类型：std::integral_constant<bool, !std::is_union<_nmsp1::B>::value>
	//那么在很多需要用到类型的场合（比如函数返回类型中）就可以使用这个类型。
	//不要忘记，!std::is_union<_nmsp1::B>::value值在编译时就能确定。
	std::integral_constant<bool, !std::is_union<_nmsp1::B>::value> myobj1;
	cout << myobj1.value << endl;
	cout << !std::is_union<_nmsp1::B>::value << endl;


	std::integral_constant<bool, !std::is_union<_nmsp1::A>::value> myobj2;
	cout << myobj2.value << endl;




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
