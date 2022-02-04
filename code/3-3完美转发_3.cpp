// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>

//#include <boost/type_index.hpp>
using namespace std;
#pragma warning(disable : 4996) 


//函数模板
//template <typename T>
//void myfunc(T  tmprv)
//{
//	cout << "--------------------------------begin----------------" << endl;
//	using boost::typeindex::type_id_with_cvr;
//	cout << "T=" << type_id_with_cvr<T>().pretty_name() << endl; //显示T的类型
//	cout << "tmprv=" << type_id_with_cvr<decltype(tmprv)>().pretty_name() << endl; //显示tmprv的类型
//	cout << "--------------------------------end------------------" << endl;
//}

namespace _nmsp1
{		
	class Human
	{
	public:
		////构造函数
		//Human(const string& tmpname) :m_sname(tmpname)
		//{
		//	cout << "Human(const string &tmpname)执行" << endl;
		//}
		////Human(string&& tmpname) :m_sname(tmpname)
		//Human(string&& tmpname) :m_sname(std::move(tmpname)) //move并不具备移动能力，把一个左值转换成一个右值。
		//{
		//	cout << "Human(string&& tmpname)执行" << endl;
		//}

		//构造函数模板
		template<typename T>
		Human(T&& tmpname) : m_sname(std::forward<T>(tmpname))
		{
			cout << "Human(T&& tmpname)执行" << endl;
		}

		//拷贝构造函数
		Human(const Human& th) : m_sname(th.m_sname)
		{
			cout << "Human(const Human& th)拷贝构造函数执行" << endl;
		}

		//移动构造函数
		Human(Human&& th) : m_sname(std::move(th.m_sname))
		{
			cout << "Human(Human&& th)移动构造函数执行" << endl;
		}

	private:
		string m_sname;
	};
}

namespace _nmsp2
{
	//void funcLast(int v1, int& v2) //目标函数
	//{
	//	++v2; //改变v2的值，让其自增1
	//	cout << v1 + v2 << endl;
	//}

	int funcLast(int v1, int& v2) //目标函数
	{
		++v2; //改变v2的值，让其自增1
		cout << v1 + v2 << endl;
		return v1 + v2;
	}

	//
	//template<typename F, typename T1,typename T2>	
	//void funcMiddle_Temp(F f, T1&& t1, T2&& t2)  //转发函数
	//{		
	//	f(
	//		std::forward<T1>(t1),
	//		std::forward<T2>(t2) 
	//	);
	//}

	//支持任意数量、类型参数的完美转发
	/*template <typename F, typename...T>
	void funcMiddle_Temp(F f, T&&... t)
	{
		f(std::forward<T>(t)...);
	}*/

	template <typename F, typename...T>
	//auto funcMiddle_Temp(F f, T&&... t)->decltype(  f(std::forward<T>(t)...)   )
	decltype(auto) funcMiddle_Temp(F f, T&&... t)
	{
		return f(std::forward<T>(t)...);
	}

}

namespace _nmsp3
{
	//目标函数
	void funcLast4(char* p)
	{
		//if (p != NULL)
		if (p != nullptr)
		{
			strncpy(p, "abc",3);
		}
	}

	//转发函数
	template <typename F, typename...T>
	void funcMiddle_Temp(F f, T&&... t)
	{
		f(std::forward<T>(t)...);
	}

}

int main()
{ 
	//第三节 完美转发
	//（1）完美转发的概念和步骤演绎
	 //a)直接调用：  funcLast();
	 //b)转发： 通过funcMiddle()间接调用funcLast。funcMiddle相当于一个跳板函数。如果有参数，那么参数也需要通过funcMiddle中转传递给funcLast()
	 //c)完美转发：const,左值，右值。实参的属性完全不丢失，原原本本的通过funcMiddle转发给funcLast，这种转发就是完美转发。
	  //万能引用：实参的所有信息都会传递到万能引用当中去从而让编译器推导出来函数模板最终的形参类型 (引用折叠)。
	  //完美转发：就是让程序员可以书写接受任意实参的函数模板（funcMiddle_Temp），并将其转发到目标函数（funcLast2)，目标函数会接收到与
	   //转发函数（funcMiddle_Temp）所接收的完全相同（当然包括类型相同比如保持参数的左值、右值特性）的参数。
	  //要实现完美转发，就要用到std::forward了。
	 //（2）std::forward ：C++11中专门为转发而存在的函数。这个函数要么返回一个左值，要么返回一个右值。
	    //万能引用类型才是forward能够发挥作用的重要条件。
	     //理解：
	     //(a)实参原来是个左值j，到了形参中还是左值t2。forward能够转化回原来该实参的左值或者右值性。所以，forward之后还是个左值。
	     //(b)实参原来是个右值20，到了形参中变成了左值t1。forward能够转化回原来该实参的左值或者右值性。所以，forward之后还是个右值。
	            //forward这个函数有强制把左值转换成右值的能力。所以：forward这个函数只对原来是个右值这种情况有用。
	    //forward的能力：保持原始实参的左值性或者右值性
	//总结：完美转发：比较好的解决了参数转发的问题。
	//（3）普通参数的完美转发:auto &&

	//（4）在构造函数模板中使用完美转发范例
	//（5）在可变参数模板中使用完美转发范例
 	 //（5.1）常规的在可变参模板使用完美转发
	 //（5.2）将目标函数中的返回值通过转发函数返回给调用者函数
	    //用到的技术：auto结合decltype构成返回类型后置语法。
	//（6）完美转发失败的情形一例
	  //使用NULL或者0作为空指针进行参数传递时导致完美转发失败的情况。
	    //C++11引入nullptr(空指针)
	


	/*
	string sname = "ZhangSan";
	_nmsp1::Human myhuman1(sname);
	_nmsp1::Human myhuman2(string("LiSi")); //"LiSi"是const char[5]类型，而string("LiSi")是string类型。

	//_nmsp1::Human myhuman3(myhuman1); //实际编译器去调用了构造函数模板，而不是调用了拷贝构造函数。 std::enable_if
	_nmsp1::Human myhuman4(std::move(myhuman1));

	const _nmsp1::Human myhuman5(string("WangWu"));
	_nmsp1::Human myhuman6(myhuman5);
	*/

	/*
	int j = 70;
	_nmsp2::funcMiddle_Temp(_nmsp2::funcLast, 20, j);
	cout << "j = " << j << endl;
	*/

	/*
	int j = 70;
	int k = _nmsp2::funcMiddle_Temp(_nmsp2::funcLast, 20, j);
	cout << "j = " << j << endl;
	cout << "k = " << k << endl;
	*/

	char* p = new char[100];
	memset(p, 0, 100);
	//_nmsp3::funcMiddle_Temp(_nmsp3::funcLast4, NULL);  
	//_nmsp3::funcLast4(NULL);
	_nmsp3::funcMiddle_Temp(_nmsp3::funcLast4, nullptr);













	
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
