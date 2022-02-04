// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>


//#include <boost/type_index.hpp>
using namespace std;
//#pragma warning(disable : 4996) 

namespace _nmsp1
{
	template <typename T>  //T代表的就是派生类
	class Base //Base是类模板
	{
	public:
		void asDerived()
		{
			T& derived = static_cast<T&>(*this); //派生类对象也是基类对象，所以这种静态类型转换没问题
			derived.myfunc(); //调用派生类的成员函数
		}

	private:
		Base() {};
		friend T; //T派生类变成了友元类
	};

	class Derived1 : public Base<Derived1> //Derived1是个普通类
	{
	public:
		void myfunc()
		{
			cout << "Derived1::myfunc()执行了" << endl;
		}
		//......
	};

	template <typename T>
	class Derived2 : public Base<Derived2<T>> //Derived2是个类模板
	{

	};

	class Derived3 : public Base<Derived3>
	{

	};
}
namespace _nmsp2
{
	template<typename T>
	struct shape
	{
		//把派生类对象是否相等的判断挪到了基类中(使用了在类模板中定义友元函数的手段把全局的operator==放到基类中)
		friend bool operator==(const shape<T>& obj1, const shape<T>& obj2) //在类模板中定义友元
		{
			const T& objtmp1 = static_cast<const T&>(obj1);//派生类对象也是基类对象，所以这种静态类型转换没问题
			const T& objtmp2 = static_cast<const T&>(obj2);
			if (!(objtmp1 < objtmp2) && !(objtmp2 < objtmp1))
				return true;
			return false;
		}
	};

	struct square : public shape<square>
	{
		int sidelength; //边长
	};

	//类外运算符重载
	bool operator<(square const& obj1, square const& obj2)
	{
		if (obj1.sidelength < obj2.sidelength)
		{
			return true;
		}
		return false;
	}

	/*template<typename T>
	bool operator==(const shape<T>& obj1, const shape<T>& obj2)
	{
		const T& objtmp1 = static_cast<const T&>(obj1);
		const T& objtmp2 = static_cast<const T&>(obj2);
		if (!(objtmp1 < objtmp2) && !(objtmp2 < objtmp1))
			return true;
		return false;
	}*/

}
namespace _nmsp3
{
	//基类模板
	template <typename T>
	class Human
	{
	public:
		T& toChild()
		{
			return static_cast<T&>(*this);
		}
		void parenteat()
		{
			toChild().eat(); //派生类给基类提供了调用接口
		}

	private:
		Human() {};
		friend T; //T派生类变成了友元类		
	};

	//子类
	class Men :public Human<Men>
	{
	public:
		void eat()
		{
			cout << "男人喜欢吃面食!" << endl;
		}
	};
	//子类
	class Women :public Human<Women>
	{
	public:
		void eat()
		{
			cout << "女人喜欢吃米饭!" << endl;
		}
	};

	template<typename T>
	void myHumanFuncTest(Human<T>& tmpobj)
	{
		tmpobj.parenteat();
	}
}

int main()
{
	//第六节 模板的一些特殊继承关系说
	//（1）奇异（奇特）的递归模板模式（CRTP）:Curiously Recurring  Template Pattern。是一种模板编程手法：把派生类作为基类的模板参数：
	//（1.1）在基类中使用派生类对象
	//（1.2）基于减少派生类中代码量的考虑:出发点是尽可能把一些代码挪到基类中，从而有效的减少派生类中的代码量；
	//（1.3）基类调用派生类的接口与多态的体现(静态多态编程技术)



	/*
	_nmsp1::Derived1 myd;
	myd.asDerived(); //调用基类的成员函数

	_nmsp1::Derived3 myd3;
	//myd3.asDerived(); //调用基类的成员函数
	*/

	/*
	_nmsp2::square objsq1; //派生类对象
	objsq1.sidelength = 15;
	_nmsp2::square objsq2;
	objsq2.sidelength = 21;
	if (!(objsq1 == objsq2))
	{
		cout << "objsq1和objsq2不相等!" << endl;
	}
	else
	{
		cout << "objsq1和objsq2相等!" << endl;
	}*/

	_nmsp3::Men mymen;
	_nmsp3::Women mywomen;

	mymen.parenteat();
	mywomen.parenteat();
	cout << "---------------------" << endl;
	_nmsp3::myHumanFuncTest(mymen);
	_nmsp3::myHumanFuncTest(mywomen);


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
