// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>
#include <vector>

#include <boost/type_index.hpp>

//#include <boost/type_index.hpp>
using namespace std;
//#pragma warning(disable : 4996) 

//函数模板
template <typename T>
//void myfunc(const T& tmprv)
void myfunc(T* tmprv)
{
	cout << "--------------------------------begin----------------" << endl;
	using boost::typeindex::type_id_with_cvr;
	cout << "T=" << type_id_with_cvr<T>().pretty_name() << endl; //显示T的类型
	cout << "tmprv=" << type_id_with_cvr<decltype(tmprv)>().pretty_name() << endl; //显示tmprv的类型
	cout << "--------------------------------end------------------" << endl;

	//tmprv = 15;
}
namespace _nmsp1
{		


}

//void mf(int& tmprv)
//{
//	tmprv = 12;
//}

//template <typename T>
////void mf(T& tmprv)
//void mf(T tmprv)
//{
//	tmprv = 12;
//
//	cout << "--------------------------------begin----------------" << endl;
//	using boost::typeindex::type_id_with_cvr;
//	cout << "T=" << type_id_with_cvr<T>().pretty_name() << endl; //显示T的类型
//	cout << "tmprv=" << type_id_with_cvr<decltype(tmprv)>().pretty_name() << endl; //显示tmprv的类型
//	cout << "--------------------------------end------------------" << endl;
//}

int main()
{ 	
	/*int ii = 1;
	int& jj = ii;
	mf(jj);
	cout << ii << endl;*/

	//第二节 理解函数模板类型推断、查看类型推断结果、auto类型推断
	//（1）如何查看类型推断结果
	 //当前要解决的问题：如何查看类型推断结果——指编译器给我们进行类型推断的结果
	    //最终目的：希望大家通过“查看编译器类型推断结果”的手段来学习并掌握C++类型推断的规则。
	//如何查看编译器帮助我们进行类型推断的结果。依赖Boost库——如何利用这个库把编译器推断出来的类型信息打印出来。
	 //https://www.boost.org/

	//（2）理解函数模板类型推断
	  //myfunc中T的类型不仅仅取决于实参100,还取决于tmprv的类型（const T&）有关。
	//看一看，函数模板的形参（tmprv）是如下类型时编译器推断出的 类型模板参数的类型（T）,以及最终的函数形参类型（tmprv）
	//（2.1）引用或指针类型
	//根据结果，得到 一些结论：
	//(1)若实参是引用类型，那么引用部分会被忽略，T不会被推导为引用类型，这个需要记一下。
	//(2)当向引用类型的形参tmprv传入const类型实参时了，那么形参tmprv会成为const引用（原来是个引用）。
	  //这里可以看到，实参的const属性会成为类型模板参数T类型推导的组成部分，所以不用担心在myfunc中能够修改原来const属性的实参。
	  //a)若实参是引用类型，那么引用部分会被忽略，T不会被推导为引用类型。
	  //b)T中的const没有了，因为函数模板的形参tmprv里出现const。但不管怎么说，只要实参带const，形参tmprv中终究还是会带着const。
	//通过上面的范例，小节一下编码技巧：
	//a)形参中引用有两个作用：1是可以通过对形参的修改来修改实参。2是传递引用比传值效率高，
	   //所以，一般来说，函数模板中的形参建议优先考虑“T &tmprv”这样的形态，
	       //这样的形态就不怕实参中的引用被忽略掉而导致开发者想通过对形参的修改达到修改实参的本意无法达成。
	//b)如何既想享受形参为引用带来的效率上的提高，又不希望通过形参来修改实参，则函数模板中的形参建议考虑“const T &tmprv”这样的形态。
	//(3)如果tmprv是个指针看看啥情况。
	//根据结果显示，得到一些结论：
	//(a)tmprv中如果没有const，则实参中的const会被带到类型T中去。如果tmprv中有const，则T类型中不会带const。
	//(b)不妨观察一下：(a)这个结论对于myfunc中形参为T& tmprv或者const T& tmprv也适用。

	   





	//myfunc(100);

	/*
	int i = 18; //i的类型是int
	const int j = i; //j的类型是const int
	const int& k = i; //k的类型是const int &
	myfunc(i);   //猜测一下：T =int，tmprv = int &。实际结果：T =int，tmprv = int &  ,猜测正确
	myfunc(j);   //因为j类型中有一个const，猜不出来。实际结果：T=int const  tmprv=int const &
	myfunc(k);   //猜不出来。实际结果：T=int const  tmprv=int const &
	*/

	/*
	int i = 18; //i的类型是int
	const int j = i; //j的类型是const int
	const int& k = i; //k的类型是const int &
	myfunc(i);   //实际结果：T=int   tmprv=int const &
	myfunc(j);   //实际结果：T=int   tmprv=int const &
	myfunc(k);   //实际结果：T=int   tmprv=int const &
	*/

	int i = 18;
	const int* pi = &i;
	myfunc(&i); //实际结果：T = int   tmprv = int *
	myfunc(pi); //实际结果：T = int const    tmprv = int const *



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
