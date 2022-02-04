// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>


//#include <boost/type_index.hpp>
using namespace std;
//#pragma warning(disable : 4996) 

namespace _nmsp1
{
	//多态
	//人类
	class Human
	{
	public:
		virtual void eat()
		{
			cout << "人类以吃米饭和面食为主!" << endl;
		}
		virtual ~Human() {} //作为父类时一般应该有一个虚析构函数,在《C++设计模式》中给大家讲解
	};
	//男人
	class Men :public Human
	{
	public:
		virtual void eat()
		{
			cout << "男人喜欢吃面食!" << endl;
		}
	};
	//女人
	class Women :public Human
	{
	public:
		virtual void eat()
		{
			cout << "女人喜欢吃米饭!" << endl;
		}
	};


}
namespace _nmsp2
{
	//模板中的多态不需要父类
	//男人
	class Men
	{
	public:
		void eat()
		{
			cout << "男人喜欢吃面食!" << endl;
		}
	};
	//女人
	class Women
	{
	public:
		void eat()
		{
			cout << "女人喜欢吃米饭!" << endl;
		}
	};

	//函数模板
	template<typename T>
	void eatTmpl(T& obj)
	{
		obj.eat();
	}
}


int main()
{
	//第五节 多态在模板中的应用
	//从表现形式上 回顾一下 多态的概念
	//(1)有父类有子类（有继承关系），父类中必须含有虚函数，子类重写父类中的虚函数。
	//(2)父类指针指向子类对象或者父类引用绑定（指向）子类对象。
	//(3)当以父类的指针或者引用调用子类中重写了的虚函数时，就能看出多态的表现来了，因为调用的是子类的虚函数。

	//模板中的多态，并不需要用到父类以及继承的概念，子类也不需要虚函数(压根就不存在父类指针指向子类对象或者父类引用绑定子类对象这种概念)
	//编译期间内，编译器会实例化出eatTmpl<Men>和eatTmpl<Women>这两个函数。

	//总结：
	//传统多态：也叫动态多态（运行时多态），因为要访问虚函数表指针，所以对执行期间的性能多少会有一些影响。
	//模板多态：也叫静态多态，编译期间就确定了具体调用谁，就不存在执行期间的性能问题
	      //只要支持相同的语法，就允许不同类型的对象以同样的方式被操纵——都有eat成员函数，那么就允许调用该成员函数，因为这是在编译期间完成的多态。






	/*
	_nmsp1::Men objmen;
	_nmsp1::Women objwomen;

	//父类引用绑定（指向）子类对象，以表现多态
	_nmsp1::Human& yinbase1 = objmen;
	_nmsp1::Human& yinbase2 = objwomen;

	yinbase1.eat();
	yinbase2.eat();*/


	_nmsp2::Men objmen;
	_nmsp2::Women objwomen;

	_nmsp2::eatTmpl(objmen); //男人喜欢吃面食!
	_nmsp2::eatTmpl(objwomen);//女人喜欢吃米饭!





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
