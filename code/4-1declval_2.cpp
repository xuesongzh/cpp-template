// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>
#include <boost/type_index.hpp>

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
	class A
	{
	public:
		A(int i) //构造函数
		{
			printf("A::A()函数执行了,this=%p\n", this);
		}
	
		double myfunc() //普通成员函数
		{
			printf("A::myfunc()函数执行了,this=%p\n", this);
			return 12.1;
		}

	private:
		~A() {}
	};

	template <typename T>
	//T mydeclval() noexcept; //这里返回T &
	T& mydeclval() noexcept;
	//T&& mydeclval() noexcept;


	class ALR
	{
	public:
		void onAnyValue()
		{
			cout << "ALR::onAnyValue()函数执行了！" << endl;
		}

		void onLvalue()& //只能被类ALR的左值对象调用
		{
			cout << "ALR::onLvalue()函数执行了！" << endl;
		}

		void onRvalue()&& //只能被类ALR的右值对象调用
		{
			cout << "ALR::onRvalue()函数执行了！" << endl;
		}
	};

}
namespace _nmsp2
{
	int myfunc(int a, int b) //函数类型一般是由函数的返回值和参数类型决定，与函数名没有关系，所以myfunc代表的函数类型是: int(int,int);
	{
		return a + b;
	}

	template<typename T_F, typename... U_Args>
	decltype(std::declval<T_F>()   (std::declval<U_Args>()...)) TestFnRtnImpl(T_F func, U_Args... args)//std::declval<>中的U_Args写成U_Args&&或者U_Args&
		                           //decltype(std::declval<T_F>()   (std::declval<U_Args>()...))写法的作用：根据函数类型以及函数参数类型，推导函数返回值类型。
	//decltype(T_F(U_Args...)) TestFnRtnImpl(T_F func, U_Args... args) -报错：decltype不是这么用的，decltype后面元口号中出现的一般都是变量、对象、表达式、函数名、函数指针名等等。
	{
		auto rtnvalue = func(args...);
		return rtnvalue;
	}
		
	template<typename T_F, typename... U_Args>
	auto TestFnRtnImpl2(T_F func, U_Args... args)->decltype(func(args...)) //decltype(func(args...))：int类型，也就是myfunc的返回类型。
		                                                                    //decltype(func)：int(*)(int,int)类型，函数指针类型
	{
		auto rtnvalue = func(args...);
		return rtnvalue;
	}
	
}

int main()
{ 
	//第四章	标准库的典型内容
	    //介绍C++标准库中典型且常用的函数模板、类模板、别名模板等功能组件以及他们的实现细节。
	    //不要求学完后能运用自如，只要求，在课程辅助下，遇到实际代码时能够顺利阅读就达到了学习效果。
	//第一节 std::declval
	//（1）基本概念和常规范例
	//std::declval--c++11新标准中出现的函数模板，没有函数体（只有声明，没有实现），无法被调用，
	       //一般用于与decltype，sizeof等关键字配合来进行类型推导、占用内存空间计算等。
	//add_rvalue_reference：是C++标准库中的类模板，他的能力是给进来一个类型，他能够返回该类型的右值引用类型。比如：
	   //a)给进来一个int类型,返回的就是int &&
	   //b)给进来一个int &类型，返回的还是int &类型。这里用到了引用折叠。
	   //c)给进来一个int &&类型，返回的还是int &&类型。这里依旧用到了引用折叠知识。
	//std::declval的功能：返回某个类型T的右值引用，不管该类型是否有默认构造函数或者该类型是否可以创建对象。
	   //返回某个类型T的右值引用 这个动作是在编译时完成的，所以很多人把std::declval也称为编译时工具。
	//std::declval的作用：
	 //a)从类型转换的角度来讲，将任意一个类型转换成右值引用类型。
	 //b)从假想创建出某类型对象的角度来说，配合decltype，令在decltype表达式中，不必经过该类型的构造函数就能使用该类型的成员函数。
	//注意，std::declval不能被调用，也不能创建任何对象。但std::declval能在不创建对象的情况下，
	        //达到创建了一个该类型对象的效果或者说程序员可以假定创建出了一个该类型对象。

	//（2）std::declval为什么返回右值引用类型
	//（2.1）返回类型本身是不好的
	  //因为返回类型本身，导致为了遵循语义限制，编译器内部创建了临时的A类对象。
	  //为了绕开语义限制，在设计mydeclval函数模板时，就不要返回类型T了，可以返回T&，也可以返回T&&，
	          //这样从遵循语义限制方面来说，就不会创建临时的A类对象了。这就是返回T&或者T&&的好处。
	//（2.2）返回左值引用还是返回右值引用
	   //decltype(mydeclval<A>)())的返回类型 = class _nmsp1::A &
	   //decltype(mydeclval<A&>)())的返回类型 = class _nmsp1::A &
	   //decltype(mydeclval<A&&>)())的返回类型 = class _nmsp1::A &

		//decltype(mydeclval<A>)())的返回类型 = class _nmsp1::A &&
		//decltype(mydeclval<A&>)())的返回类型 = class _nmsp1::A &
		//decltype(mydeclval<A&&>)())的返回类型 = class _nmsp1::A &&
	//（2.3）调用引用限定符修饰的成员函数范例

	//（3）推导函数返回值范例
	//T_F：是int (*)(int,int)类型，也就是函数指针类型
	//decltype(std::declval<T_F>()   (std::declval<U_Args>()...))：是int类型，也就是myfunc函数的返回类型
	   //a)decltype(std::declval<T_F>() )：是 int (* && )(int,int),函数指针的右值引用类型，其实就简单理解成函数指针类型
	   //b)decltype(std::declval<U_Args>()...)这种写法：推导出来的是两个int &&





	//std::declval


	/*

	//std::declval
	using YT = decltype(std::declval<_nmsp1::A>()); //这里注意不要把std::declval<_nmsp1::A>后面的圆括号对丢掉，否则代码含义就发生变化了。想象函数调用时即便没有参数也要把圆括号带着。
	//利用boost输出类型名比typeid(...).name()用法输出类型名更准确。
	using boost::typeindex::type_id_with_cvr;
	cout << "YT=" << type_id_with_cvr<YT>().pretty_name() << endl; //显示YT的类型
	*/

	/*
	_nmsp1::A myaobj(1); //必须为构造函数提供参数
	using boost::typeindex::type_id_with_cvr;
	cout << "myaobj.myfunc()的返回类型=" << type_id_with_cvr<decltype(myaobj.myfunc())>().pretty_name() << endl;
	*/

	//using boost::typeindex::type_id_with_cvr;
	//cout << "A::myfunc()的返回类型=" << type_id_with_cvr<decltype(std::declval<_nmsp1::A>().myfunc())>().pretty_name() << endl;

	/*
	_nmsp1::A&& ayinobj(); //看起来是一个函数声明的语法 ，该函数返回的类型是A&&，可以看成是返回了一个A&&类型的对象，这种对象就可以看成是类A对象。
//	ayinobj(); //看起来是调用ayinobj这个函数
//	ayinobj().myfunc();
	decltype(ayinobj().myfunc()) mydblvar; //定义了一个double类型的变量mydblvar;
	*/

	/*
	using boost::typeindex::type_id_with_cvr;
	cout << "mydeclval<A>()的返回类型=" <<  type_id_with_cvr<decltype(_nmsp1::mydeclval<_nmsp1::A>() )>().pretty_name() << endl;
	cout << "mydeclval<A>().myfunc()的返回类型=" << type_id_with_cvr<decltype(_nmsp1::mydeclval<_nmsp1::A>().myfunc())>().pretty_name() << endl; //语义限制

	cout << "sizeof(mydeclval<_nmsp1::A>())=" << sizeof(_nmsp1::mydeclval<_nmsp1::A>()) << endl;
	*/

	//------------------------
	/*
	using boost::typeindex::type_id_with_cvr;
	cout << "decltype(mydeclval<A>)())的返回类型=" << type_id_with_cvr<decltype(_nmsp1::mydeclval<_nmsp1::A>())>().pretty_name() << endl;
	cout << "decltype(mydeclval<A&>)())的返回类型=" << type_id_with_cvr<decltype(_nmsp1::mydeclval<_nmsp1::A&>())>().pretty_name() << endl;
	cout << "decltype(mydeclval<A&&>)())的返回类型=" << type_id_with_cvr<decltype(_nmsp1::mydeclval<_nmsp1::A&&>())>().pretty_name() << endl;
	*/

	/*
	_nmsp1::ALR alr;  //左值对象alr
	alr.onLvalue();
	//alr.onRvalue(); //编译错误，因为onRvalue只能被类A的右值对象调用
	_nmsp1::ALR().onRvalue();  //临时对象是右值对象
	//_nmsp1::ALR().onLvalue();  //编译错误，因为onLvalue只能被类A的左值对象调用
	*/

	/*
	decltype(_nmsp1::mydeclval<_nmsp1::ALR>().onAnyValue()); 
	decltype(_nmsp1::mydeclval<_nmsp1::ALR&>().onLvalue()); //返回的 类型是class ALR &，代表返回的是左值对象，左值对象调用onLvalue没问题
	decltype(_nmsp1::mydeclval<_nmsp1::ALR&&>().onRvalue()); //返回的 类型是class ALR &&，代表返回的是右值对象，右值对象调用onRvalue没问题
	//decltype(_nmsp1::mydeclval<_nmsp1::ALR&>().onRvalue());//返回的 类型是class ALR &，代表返回的是左值对象，左值对象调用onRvalue是错误的
	//decltype(_nmsp1::mydeclval<_nmsp1::ALR&&>().onLvalue()); //返回的 类型是class ALR &&，代表返回的是右值对象，右值对象调用onLvalue是错误的
	*/

	/*
	decltype(_nmsp1::mydeclval<_nmsp1::ALR>().onAnyValue());
	decltype(_nmsp1::mydeclval<_nmsp1::ALR&>().onLvalue()); //返回的 类型是class ALR &，代表返回的是左值对象，左值对象调用onLvalue没问题
	//decltype(_nmsp1::mydeclval<_nmsp1::ALR&&>().onRvalue()); //返回的 类型是class ALR &，代表返回的是左值对象，左值对象调用onRvalue是错误的
	//decltype(_nmsp1::mydeclval<_nmsp1::ALR&>().onRvalue());//返回的 类型是class ALR &，代表返回的是左值对象，左值对象调用onRvalue是错误的
	decltype(_nmsp1::mydeclval<_nmsp1::ALR&&>().onLvalue()); //返回的 类型是class ALR &，代表返回的是左值对象，左值对象调用onLvalue没问题
	*/

	/*
	//auto result = _nmsp2::TestFnRtnImpl(_nmsp2::myfunc, 5, 8); //T_F被推断出 int(*)(int,int)
	auto result = _nmsp2::TestFnRtnImpl<int(int,int)>(_nmsp2::myfunc, 5, 8); //T_F被推断出 int(*)(int,int)
	cout << result << endl;
	*/

	/*
	int (*fp_var)(int x, int y); //函数指针类型fp_var = int(*)(int,int)
	int (* &&yy_fp_var)(int x, int y) = std::move(fp_var); //函数指针的右值引用yy_fp_var = int(* &&)(int,int),现在yy_fp_var就可以代表fp_var
	fp_var = _nmsp2::myfunc;
	cout << fp_var(1, 2) << endl;  //3
	cout << yy_fp_var(1, 2) << endl; //3*/

	auto result2 = _nmsp2::TestFnRtnImpl2(_nmsp2::myfunc, 13, 15);
	cout << result2 << endl;
	



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
