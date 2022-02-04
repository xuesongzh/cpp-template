// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>


//#include <boost/type_index.hpp>
using namespace std;
//#pragma warning(disable : 4996) 

namespace _nmsp0
{
	//上节课的代码回忆:通过递归继承方式展开类型、非类型、模板模板参数包

	//主模板定义（泛化版本的类模板）
	template <typename ...Args>
	class myclasst
	{
	public:
		myclasst()
		{
			printf("myclasst::myclasst()泛化版本执行了,this = %p\n", this);
		}
	};
	//template <typename ...Args>class myclasst; //主模板声明(前向声明/前置声明)

	template <typename First, typename ... Others>
	class myclasst<First, Others...> :private myclasst<Others...> //偏特化
	{
	public:
		myclasst() :m_i(0)
		{
			printf("myclasst::myclasst()偏特化版本执行了，this = %p,sizeof...(Others)=%d\n", this, sizeof...(Others));
		}

		myclasst(First parf, Others... paro) :m_i(parf), myclasst<Others...>(paro...)
		{
			cout << "---------------------begin-----------------" << endl;
			printf("myclasst::myclasst(parf,...paro)执行了,this = %p\n", this);
			cout << "m_i = " << m_i << endl;
			cout << "---------------------end-----------------" << endl;
		}
		First m_i;
	};	
	template<>
	class myclasst<> //一个特殊的特化版本，看起来象全特化，不是全特化，可变参模板不存在全特化
	{
	public:
		myclasst()
		{
			printf("myclasst::myclasst()特殊的特化版本执行了,this = %p\n", this);
		}
	};
}

namespace _nmsp1
{ 	
	//class B
	//{
	//	//.....
	//};
	//class A
	//{
	//public:
	//	B b;  //A中包含B对象，b作为类A的成员变量
	//};

	//主模板定义（泛化版本的类模板）
	template <typename ...Args>
	class myclasst
	{
	public:
		myclasst()
		{
			printf("myclasst::myclasst()泛化版本执行了,this = %p\n", this);
		}
	};
	//template <typename ...Args>class myclasst; //主模板声明(前向声明/前置声明)

	template <typename First, typename ... Others>
	class myclasst<First, Others...> //:private myclasst<Others...> //偏特化
	{
	public:
		myclasst() :m_i(0)
		{
			printf("myclasst::myclasst()偏特化版本执行了，this = %p,sizeof...(Others)=%d\n", this, sizeof...(Others));
		}

		myclasst(First parf, Others... paro) :m_i(parf) , m_o(paro...)   //, myclasst<Others...>(paro...)
		{
			cout << "---------------------begin-----------------" << endl;
			printf("myclasst::myclasst(parf,...paro)执行了,this = %p\n", this);
			cout << "m_i = " << m_i << endl;
			cout << "---------------------end-----------------" << endl;
		}
		First m_i;
		myclasst<Others...> m_o; //****************
	};
	template<>
	class myclasst<> //一个特殊的特化版本，看起来象全特化，不是全特化，可变参模板不存在全特化
	{
	public:
		myclasst()
		{
			printf("myclasst::myclasst()特殊的特化版本执行了,this = %p\n", this);
		}
	};
}
namespace _nmsp2
{
	//泛化版本
	template <int mycount,int mymaxcount,typename ...T> //mycount用于统计，从0开始，mymaxcount表示参数数量，可以用sizeof...取得。
	class myclasst4
	{
	public:
		//静态成员函数，借助tuple(类型)，借助get，就能够把每个参数提取出来
		static void mysfunc(const tuple<T...>& t)
		{
			cout << "value = " << get<mycount>(t) << endl; //可以把每个参数取出来并输出
			myclasst4< mycount + 1, mymaxcount, T...>::mysfunc(t); //计数每次+1，这里是递归调用，自己调用自己
		}
	};

	//偏特化版本，用于结束递归调用
	template <int mymaxcount, typename ...T>
	class myclasst4<mymaxcount, mymaxcount, T...> //注意<>中两个都是mymaxcount
	{
	public:
		static void mysfunc(const tuple<T...>& t)
		{
			//这里其实不用干啥
		}
	};


	//可变参函数模板
	template <typename ...T>
	void myfunctuple(const tuple<T...>& t)
	{
		myclasst4<0, sizeof...(T), T...>::mysfunc(t);//这里注意，第一个参数是0，表示计数从宁0开始
	}
}
namespace _nmsp3
{
	template<typename... myclassPList>
	class myclasst5 : public myclassPList...
	{
	public:
		myclasst5() : myclassPList()...
		{
			cout << "myclasst5::myclasst5,this = " << this << endl;
		}
	};
	class PA1
	{
	public:
		PA1()
		{
			cout << "PA1::PA1,this = " << this << endl;
		}
	private:
		char m_s1[100];
	};
	class PA2
	{
	public:
		PA2()
		{
			cout << "PA2::PA2,this = " << this << endl;
		}
	private:
		char m_s1[200];
	};

	class PA3
	{
	public:
		PA3()
		{
			cout << "PA3::PA3,this = " << this << endl;
		}
	private:
		char m_s1[300];
	};

}
namespace _nmsp4
{
	template<typename ...Args> //泛化版本
	class myclasst
	{
	public:
		myclasst()
		{
			printf("myclasst泛化版本执行了,this=%p,sizeof...(Args)=%d\n", this, sizeof...(Args));
		}
	};

	template<typename First,typename...Others>
	class myclasst<First, Others...> //特化版本
	{
	public:
		myclasst()
		{
			printf("myclasst<First, Others...>偏特化版本执行了,this=%p,sizeof...(Others)=%d\n", this, sizeof...(Others));
		}
	};

	template<typename Arg>
	class myclasst <Arg>
	{
	public:
		myclasst()
		{
			printf("myclasst<Arg>偏特化版本执行了,this=%p\n", this);
		}
	};

	template<typename Arg1,typename Arg2>
	class myclasst <Arg1,Arg2>
	{
	public:
		myclasst()
		{
			printf("myclasst<Arg1,Arg2>偏特化版本执行了,this=%p\n", this);
		}
	};
}

int main()
{
	//第四节 可变参模板
	//（4）可变参类模板
	//（4.2）通过递归组合方式展开参数包
	   //组合关系也称为复合关系，实际上就是 一种包含关系
	//（4.3）通过tuple和递归调用展开参数包
	  //(1)tuple的概念和简单演示
	   //tuple：元组——可变参类模板
	  //(2)如何用tuple和递归调用展开参数包:实现思路，有一个计数器（变量），从0开始，每处理一个参数，计数器+1，一直到把所有参数处理完。
	      //最后，提供一个模板片特化，作为递归调用结束。
	//（4.4）基类参数包的展开:演示一下某个类的基类也可以是可变参
	//（4.5）特化
	//可变参模板不存在全特化，所以只有偏特化





	/*
	//_nmsp1::myclasst<int, float, double> myc(12, 13.5, 23);
	tuple<float, int, int> mytuple(12.5f, 100, 52); //一个tuple（元组），一堆各种类型数据的组合
	//元组和打印，用标准库中的get（函数模板）
	cout << get<0>(mytuple) << endl;  //12.5f
	cout << get<1>(mytuple) << endl;  //100
	cout << get<2>(mytuple) << endl;  //52
	_nmsp2::myfunctuple(mytuple);*/

	/*
	tuple<float, int, int> mytuple(12.5f, 100, 52);
	_nmsp2::myfunctuple(mytuple);*/

	/*
	_nmsp3::myclasst5<_nmsp3::PA1, _nmsp3::PA2, _nmsp3::PA3> obj;
	cout << "sizeof(obj)=" << sizeof(obj) << endl;*/

	_nmsp4::myclasst<int> myc1;
	_nmsp4::myclasst<int,float> myc2;
	_nmsp4::myclasst<int,float,double> myc3;
	_nmsp4::myclasst<int,float,double,char> myc4;
	_nmsp4::myclasst<> myc5;



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
