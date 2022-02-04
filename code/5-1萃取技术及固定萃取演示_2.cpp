// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>
//#include <boost/type_index.hpp>
#include <vector>
#include <list>

using namespace std;
//#pragma warning(disable : 4996) 

namespace _nmsp1
{	
	//输出某个容器对应的迭代器种类的代码。
	void _display_category(random_access_iterator_tag mytag)
	{
		cout << "random_access_iterator_tag" << endl;
	}
	void _display_category(bidirectional_iterator_tag mytag)
	{
		cout << "bidirectional_iterator_tag" << endl;
	}
	void _display_category(forward_iterator_tag mytag)
	{
		cout << "forward_iterator_tag" << endl;
	}
	void _display_category(output_iterator_tag mytag)
	{
		cout << "output_iterator_tag" << endl;
	}
	void _display_category(input_iterator_tag mytag)
	{
		cout << "input_iterator_tag" << endl;
	}

	template <typename T>
	void display_category(T iter)
	{
		typename iterator_traits<T>::iterator_category cagy;//萃取机
		_display_category(cagy);

		if (typeid(typename iterator_traits<T>::iterator_category) == typeid(random_access_iterator_tag))
		{
			cout << "发现了某个容器的迭代器是random_access_iterator_tag类型" << endl;
		}
	};


	//-------------------------------
	/*
	class _List_iterator //list容器对应的迭代器，是一个类或者类模板
	{
	public:
		using iterator_category = bidirectional_iterator_tag; //代表list容器的迭代器属于哪个种类的一个类型别名
		//....
	};
	template <class T>
	class list
	{
	public:
		using iterator = _List_iterator;
		//......
	};
	//不难想象
	//list<int>::iterator::iterator_category  就代表着 bidirectional_iterator_tag	

	class _Vector_iterator
	{
	public:
		using iterator_category = random_access_iterator_tag; //代表vector容器的迭代器属于哪个种类的一个类型别名
		//....
	};
	template <class T>
	class vector
	{
	public:
		using iterator = _Vector_iterator;
		//......
	};
	*/
	/*
	template <typename IterT>  //IterT是一个迭代器类型
	struct iterator_traits //固定萃取类模板
	{
		using iterator_category = typename IterT::iterator_category;
		//.....
	};*/

}


int main()
{ 	
	//第一节 萃取技术及fixed traits（固定萃取）演示
	//（2）迭代器范例
	//5类迭代器：
	//a)输出型迭代器：struct output_iterator_tag
	//b)输入型迭代器：struct input_iterator_tag
	//c)前向迭代器：struct forward_iterator_tag
	//d)双向迭代器：struct bidirectional_iterator_tag
	//e)随机访问迭代器：struct random_access_iterator_tag
	//vector容器-随机访问类型迭代器。
	//list容器-双向迭代器。 ___________《C++从入门到精通》
	//正确的区分某个容器对应的迭代器种类是显得特别重要的。

	//本节帮助大家了解如何通过 固定萃取技术从容器中萃取出对应的迭代器种类。
	//（1）在容器中，标示出所属迭代器的种类
	//（2）fixed trait类模板 iterator_traits的实现

	//-----------
	//(1)display_category(vector<int>::iterator()); 代码行，实参创建了一个临时的_Vector_iterator类对象，
	         //此时display_category中的T被推断为_Vector_iterator类型
	//(2)display_category中的代码行typename iterator_traits<T>::iterator_category cagy;等价于
			//iterator_traits<_Vector_iterator>::iterator_category cagy;
	//(3)因为在iterator_traits类模板定义中，存在using代码行。。。。,因此
	        //iterator_traits<_Vector_iterator>::iterator_category cagy;代码行等价于
	        //_Vector_iterator::iterator_category;
	//(4)根据_Vector_iterator类中存在这using定义，所以_Vector_iterator::iterator_category等价于
	        //random_access_iterator_tag

	//所以，最终， iterator_traits<T>::iterator_category cagy;代码行最终等价于
	//random_access_iterator_tag cagy;

	//iterator_traits：给进去迭代器的类型，萃取出迭代器的种类——给进去一种类型，萃取出另外一种类型。




	


	_nmsp1::display_category(vector<int>::iterator()); 
	_nmsp1::display_category(list<int>::iterator());

	
	

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


/*
void _display_category(random_access_iterator_tag mytag)
{
	cout << "random_access_iterator_tag" << endl;
}
void _display_category(bidirectional_iterator_tag mytag)
{
	cout << "bidirectional_iterator_tag" << endl;
}
void _display_category(forward_iterator_tag mytag)
{
	cout << "forward_iterator_tag" << endl;
}
void _display_category(output_iterator_tag mytag)
{
	cout << "output_iterator_tag" << endl;
}
void _display_category(input_iterator_tag mytag)
{
	cout << "input_iterator_tag" << endl;
}
template <typename T>
void display_category(T iter)
{
	typename iterator_traits<T>::iterator_category cagy;//萃取机
	_display_category(cagy);
};

*/