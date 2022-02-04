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

namespace _nmsp1
{	
	template <class T1,class T2>
	void print_is_same()
	{
		cout << "T1类型为：" << typeid(T1).name() << endl;
		cout << "T2类型为：" << typeid(T2).name() << endl;
		cout << "T1类型和T2类型是否相等：" << std::is_same<T1, T2>() << endl;
		//cout << "T1类型和T2类型是否相等：" << std::is_same<T1, T2>::value << endl;
		             //值为1则表示2个类型相等，值为0表示2个类型不等，is_same是标准库中用于判断两个类型是否相同的类模板，
		             // std::is_same<T1,T2>()写法写成 std::is_same<T1,T2>::value  效果也是一样的
	}

	//c++14中定义了大量别名
	//template<class T>
	//using remove_reference_t = typename remove_reference<T>::type;
}
namespace _nmsp2
{
	//泛化版本
	template <typename T>
	struct RemoveReference
	{
		using type = T;
	};

	//特化版本
	template <typename T>
	struct RemoveReference<T&>
	{
		using type = T;
	};
	template <typename T>
	struct RemoveReference<T&&>
	{
		using type = T;
	};
	//别名模板
	template <typename T>
	using RemoveReference_t = typename RemoveReference<T>::type;

}

namespace _nmsp3
{
	template<typename T>
	struct AddLValueReference
	{
		using type = T&; //int && & ，引用折叠：有左值 引用，结果必然为左值 引用，所以type = int &
	};
	template<typename T>
	using AddLValueReference_t = typename AddLValueReference<T>::type; //实际上可以直接简化为using AddLValueReference_t = T&;，这样就不用定义AddLValueReference了。

	//--------------------------
	template<typename T>
	struct AddRValueReference
	{
		using type = T&&;
	};
	template<typename T>
	using AddRValueReference_t = typename AddRValueReference<T>::type; //实际上可以直接简化为using AddRValueReference_t = T&&;，这样就不用定义AddRValueReference了。


}

int main()
{ 	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口

	//（4）引用类型的移除和增加
	//（4.1）引用类型的移除
	//std::remove_reference类模板。
	//（4.2）引用类型的增加：根据给定的类型来创建一个左值或者右值引用
	//std::add_lvalue_reference类模板：给进来 一个类型，返回该类型对应的左值引用类型
	//std::add_rvalue_reference类模板：给进来 一个类型，返回该类型对应的右值引用类型
	//std::is_lvalue_reference和std::is_rvalue_reference类模板：判断某个类型是否是左值引用类型或者右值引用类型。



	
	/*std::remove_reference<int>::type a;
	std::remove_reference<int&>::type b;
	std::remove_reference<int&&>::type c;*/
	/*std::remove_reference_t<int> a;
	std::remove_reference_t<int &> b;
	std::remove_reference_t<int&&> c;
	_nmsp1::print_is_same<decltype(a), decltype(b)>();
	_nmsp1::print_is_same<decltype(a), decltype(c)>();*/

	/*
	int&& a2 = 12;
	//_nmsp2::RemoveReference_t<decltype(a2)> b2 = "dd";  //error C2440: “初始化”: 无法从“const char [3]”转换为“int”
	_nmsp2::RemoveReference_t<decltype(a2)> b2 = 125;
	int i = 64;
	int& c2 = i;
	_nmsp2::RemoveReference_t<decltype(c2)> d2 = 500;
	using boost::typeindex::type_id_with_cvr;
	cout << "b2= " << type_id_with_cvr<decltype(b2)>().pretty_name() << endl;
	cout << "d2= " << type_id_with_cvr<decltype(d2)>().pretty_name() << endl;*/

	/*
	int a = 15;
	std::add_lvalue_reference<decltype(a)>::type b = a; //b的类型为int &
	std::add_rvalue_reference<decltype(a)>::type c = 16; //c的类型为int &&

	using btype = std::add_lvalue_reference_t<int>; //_t是个别名模板
	cout << std::is_same<int&, btype>() << endl;  //1

	using ctype = std::add_rvalue_reference_t<int>;
	cout << std::is_lvalue_reference<btype>::value << endl; //1
	cout << std::is_rvalue_reference<ctype>::value << endl; //1

	std::add_rvalue_reference_t<int&> cc1 = a; //cc1类型为int &，这里涉及到引用折叠， &  和&& 折叠后得到 &,后面专门解释一下
	std::add_rvalue_reference_t<int&&> cc2 = 16; //cc2的类型为int &&，这里涉及到引用折叠，&&和&&折叠得到&&。

	*/

	/*
	int anew = 15;
	_nmsp3::AddLValueReference_t<decltype(anew)> bnew = anew; //decltype(anew)的类型是int，bnew的类型为int &
	int&& anew2 = 16;
	_nmsp3::AddLValueReference_t<decltype(anew2)> bnew2 = anew;//decltype(anew2)的类型是int&&，bnew的类型为int &
	*/

	int argnew = 15;
	_nmsp3::AddRValueReference_t<decltype(argnew)> brgnew = 18; //brgnew的类型为int &&

	int&& argnew2 = 15;
	_nmsp3::AddRValueReference_t<decltype(argnew2)> brgnew2 = 18;//brgnew2的类型为int &&

	int tmpvalue = 16;
	int& argnew3 = tmpvalue;
	_nmsp3::AddRValueReference_t<decltype(argnew3)> brgnew3 = tmpvalue; //brgnew3的类型为int &，因为根据引用折叠规则，左值引用和右值引用遇到一起，结果是左值引用。



	




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
