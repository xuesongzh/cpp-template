// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

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
	struct mylist_iterator
	{
		using iterator_category = bidirectional_iterator_tag;
		//......
	};


	//T代表迭代器类型，U代表的是可调用对象类型（可调用对象常常被用作算法中的参数）
	template <typename T,typename U>
	T my_find_if(T first, T last, U funcobj)
	{
		for (; first != last; ++first)
		{
			if (funcobj(*first))
			{
				break;
			}
		}
		return first;
	}

}

bool myfuncfind(int val)
{
	if (val > 0)
		return true; //返回true就停止遍历
	return false;
}


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口
	//第二节 迭代器分类、find_if算法的简单实现
	//（1）迭代器分类
	//（1.1）迭代器的分类
	//mylist_iterator类模板
	//STL：迭代器分成5类（5个结构），5.1.2已经详细讲解过。
	//（1.2）迭代器分类目的详述
	//迭代器分类的意义：针对不同种类的迭代器来设计或者优化算法，书写布偶听的逻辑处理代码来提高程序的执行效率。

	//（2）一个典型算法——find_if的简单实现
	//find_if
	//第三个参数：谓词 predicate：可以理解成用在算法中作为参数来定义某些运算规则或者指明算法要进行何种操作的可调用对象，
	    //可调用对象在调用后一般都会返回true或者false。






	//bidirectional_iterator_tag
	//std::list<int>::iterator
	//cout << typeid(_nmsp1::mylist_iterator<int>::iterator_category).name() << endl;

	/*
	std::vector<int> msgList10; 
	msgList10.push_back(1);
	msgList10.push_back(2);
	std::sort(msgList10.begin(), msgList10.end()); //#include <algorithm>
	*/

	std::list<int> msgList2;
	msgList2.push_back(2);
	msgList2.push_back(1);
	msgList2.push_back(3);

	//auto result = std::find_if(msgList2.begin(), msgList2.end(), [](int val)
	//	{
	//		if (val > 0)
	//			return true; //返回true就停止遍历
	//		return false;
	//	}	
	//);
	//auto result = std::find_if(msgList2.begin(), msgList2.end(), myfuncfind);
	auto result = _nmsp1::my_find_if(msgList2.begin(), msgList2.end(), myfuncfind);

	if (result == msgList2.end())
	{
		cout << "没找到" << endl;
	}
	else
	{
		cout << "找到了，结果为" << *result << endl;
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



////别名模板
//template <class _Iter> //_Iter代表迭代器类型
//using _Iter_cat_t = typename iterator_traits<_Iter>::iterator_category; //为萃取机定义别名模板（5.1.2节看到过）
//
////变量模板（元函数）
//template <class _From, class _To>
//constexpr bool is_convertible_v = __is_convertible_to(_From, _To);
//
//template <class _Iter>
//constexpr bool _Is_input_iter_v = is_convertible_v<_Iter_cat_t<_Iter>, input_iterator_tag>;
//
//template <class _Iter>
//constexpr bool _Is_fwd_iter_v = is_convertible_v<_Iter_cat_t<_Iter>, forward_iterator_tag>;
//
//template <class _Iter>
//constexpr bool _Is_bidi_iter_v = is_convertible_v<_Iter_cat_t<_Iter>, bidirectional_iterator_tag>;
//
//template <class _Iter>
//constexpr bool _Is_random_iter_v = is_convertible_v<_Iter_cat_t<_Iter>, random_access_iterator_tag>;

