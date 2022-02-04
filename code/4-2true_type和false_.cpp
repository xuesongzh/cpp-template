// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>
#include <boost/type_index.hpp>

using namespace std;
//#pragma warning(disable : 4996) 

namespace _nmsp1
{
	template <bool var>
	struct BoolConstant
	{
		using type = BoolConstant; //写成using type = BoolConstant<val>;也行
		static constexpr bool value = var;
	};
	using TrueType = BoolConstant<true>;
	using FalseType = BoolConstant<false>;


	template <typename T,bool val>
	struct AClass
	{
		AClass() //构造函数
		{
			cout << "AClass::AClass()执行了" << endl;

			/*
			if (val)
			//if constexpr (val)
			{
				T tmpa = 15;
			}
			else
			{
				T tmpa = "abc"; //int tmpa = "abc";    ---if constexpr：编译期间if语句。
			}
			*/
			AClassEx(BoolConstant<val>()); //创建一个临时对象
		}
		void AClassEx(TrueType abc)
		{
			T tmpa = 15;		
		}
		void AClassEx(FalseType)
		{
			T tmpa = "abc";
		}
	};
}

int main()
{ 
	//第二节 std::true_type和std::false_type
	//是两个类型（类模板）。
	//using true_type = integral_constant<bool,true>;
	//using false_type = integral_constant<bool,false>;
	//注意区分true_type，false_type与true,false的区别。
	//true_type，false_type：代表类型（类类型）
	//true,false：代表值
	//注意于bool的区别，bool代表true也可以代表false。而true_type类型代表的就是true，false_type类型代表的就是false.
	//记住几点：
		//a)TrueType和FalseType代表一个类类型，TrueType（std::true_type）代表一种true(真)的含义，而False_Type(std::false_type)代表一种false（假）的含义。
		//b)一般是当作基类被继承。当作为基类被继承时，派生类也就具备了真或假的这种意味。
	         //is，比如is_pointer、is_union、is_function等类模板，都是继承自类似BoolConstant<true>或者BoolConstant<false>这样的基类来实现的。
	    //c)可以当作一种返回类型被使用，比如：
		//_nmsp1::FalseType myfunc1(); //返回“假”这种含义
		//_nmsp1::TrueType myfunc2(); //返回“真”这种含义



	


	//true_type  func();
	////true  func2();
	//bool  func2();
	
	/*
	_nmsp1::FalseType myfunc1(); //返回“假”这种含义
	_nmsp1::TrueType myfunc2(); //返回“真”这种含义
	*/

	_nmsp1::AClass<int, true> tmpobj1;
	_nmsp1::AClass<string, false> tmpobj2;



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
