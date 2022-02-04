// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>

//#include <boost/type_index.hpp>
using namespace std;
//#pragma warning(disable : 4996) 


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
	//void funcLast(int v1, int v2)
	void funcLast(int v1, int& v2)
	{
		++v2; //改变v2的值，让其自增1
		cout << v1 + v2 << endl;
	}

	void funcLast2(int&& v1, int& v2)
	{
		cout << v1 << endl;
		cout << v2 << endl;
	}

	//函数模板（跳板函数）：把收到的参数以及这些参数相对应的类型不变的转发给其他函数（完美转发）
	template<typename F, typename T1,typename T2>
	//void funcMiddle_Temp(F f, T1 t1, T2 t2) //f:函数指针类型void(*)(int,int)，而funcLast是函数类型void(int,int)
	void funcMiddle_Temp(F f, T1&& t1, T2&& t2)
	{
		f(t1, t2);
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
	 


	/*int i = 50;
	_nmsp1::funcLast(41, i); //92*/

	/*
	int j = 70;
	_nmsp1::funcMiddle_Temp(_nmsp1::funcLast, 20, j); //91
	*/

	/*
	int i = 50;
	_nmsp1::funcLast(41, i); //直接调用，92,执行完i=51         
	*/

	/*
	int j = 70;
	_nmsp1::funcMiddle_Temp(_nmsp1::funcLast, 20, j); //91,执行完本函数，j = 71？70呢？ = 70
	                                                   //当前情况下j被funcMiddle_Temp推断成了int而不是int&
	                                                    //void funcMiddle_Temp(void(*f)(int,int &),int t1,int t2){...}
														*/

	/*
	int j = 70;
	_nmsp1::funcMiddle_Temp(_nmsp1::funcLast, 20, j);  //91,T1=int, t1 = int &&，      T2 = int & , t2 = int &
		                                                  //j = 71;

														  */
	int j = 70;
	//_nmsp1::funcLast2(20, j); //20,70
	_nmsp1::funcMiddle_Temp(_nmsp1::funcLast2, 20, j);
	                                                 //20->t1(int &&)，但是t1本身是左值。

	/*int&& abc = 1;
	abc = 15;*/




	
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
