// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>
#include <list>


#ifdef _DEBUG   //只在Debug（调试）模式下
#ifndef DEBUG_NEW
#define DEBUG_NEW new(_NORMAL_BLOCK,__FILE__,__LINE__) //重新定义new运算符
#define new DEBUG_NEW
#endif
#endif

//#include <boost/type_index.hpp>
using namespace std;
//#pragma warning(disable : 4996) 

namespace _nmsp1
{	
	template<typename T>
	struct mylist_node
	{
		//构造函数，根据容器中的实际的元素来构造一个myulist_node对象
		//为防止隐式转换导致隐含的错误，构造函数全部用explicit修饰
		explicit mylist_node(const T& x) :data(x), next(nullptr), prev(nullptr)
		{

		}

		mylist_node* next;
		mylist_node* prev;
		T data;
	};

	//---------------------
	template <typename T> //T代表的是容器中的元素类型
	struct mylist_iterator
	{
		//为防止隐式转换导致隐含的错误，构造函数全部用explicit修饰
		explicit mylist_iterator() : node(nullptr) {} //默认构造函数
		explicit mylist_iterator(mylist_node<T>* tmpnode) :node(tmpnode) {} //构造函数

		T& operator*() //返回迭代器所指向的元素，注意返回的类型是T&
		{
			return node->data;
		}

		mylist_iterator& operator++() //重载前置++， 注意++在前，形如：++i;
		{
			node = node->next; //指向了mylist容器中的下一个元素
			return *this;
		}

		mylist_iterator operator++(int) //重载后置++，圆括号中多了个int，只是为了与前置++做区分，注意++在后面，形如i++
										//所以遍历的时候提倡用前置++（避免产生临时对象）
		{
			mylist_iterator tmp(*this);
			node = node->next; //也可以写成 ++*this，如果这样写，这里的++会调用重载的前置++
			return tmp;
		}

		bool operator != (const mylist_iterator& tmpobj)
		{
			return node != tmpobj.node;
		}

		bool operator == (const mylist_iterator& tmpobj)
		{
			return node == tmpobj.node;
		}


		mylist_node<T>* node;//定义指向容器中元素的指针
	};

	template<typename T>
	class mylist
	{
	public:
		using iterator = mylist_iterator<T>; //迭代器类型

	public:
		explicit mylist() //默认构造函数
		{
			void* point = new char[sizeof(mylist_node<T>)];
			head = reinterpret_cast<mylist_node<T> *>(point);
			//head = new mylist_node<T>();

			head->next = head;
			head->prev = head;
		}
		~mylist() //析构函数
		{
			delete (void*)head;
			head = nullptr;
		}

	public:
		iterator begin()
		{
			return iterator(head->next); //注意：head->next始终指向第一个元素
		}
		iterator end()
		{
			return iterator(head);
		}
	private:
		mylist_node<T>* head;
	};
	
	//----------------
	class A
	{
	public:
		explicit A(int tmpi) :m_i(tmpi) {}
		int m_i;
	};
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口
		
	//第七章  STL标准模板库代码-list以及迭代器、find_if
	//第一节 list容器的简单实现
	//常用的 容器，vector,list,map等：容纳同类型的多个元素
	//自己实现的mylist，区别于系统的list。
	//（1）基础代码
	//元素 或者 节点 ：mylist_node来描述元素
	//为mylist定义一个迭代器mylist_iterator
	//（2）插入新元素前的准备




	/*
	std::list<int> msgList; //文件头#include <list>
	msgList.push_back(1); //末尾插入1，list容器中的内容：1
	msgList.push_front(2); //开头插入2，list容器中的内容：2,1
	msgList.push_back(3); //末尾插入3，list容器中的内容：2，1,3
	for (std::list<int>::iterator pos = msgList.begin(); pos != msgList.end(); ++pos)
	{
		cout << *pos << endl;
	}*/

	_nmsp1::mylist<_nmsp1::A> msgList;
	if (msgList.end() == msgList.begin())
	{
		//msgList容器是空的
		cout << "msgList容器为空！" << endl;
	}
	if (msgList.end() != msgList.begin())
	{ 
		//msgList容器不是空的
		cout << "msgList容器不为空！" << endl;
	}


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

