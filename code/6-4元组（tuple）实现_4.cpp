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

//#include <boost/type_index.hpp>
using namespace std;
//#pragma warning(disable : 4996) 

namespace _nmsp1
{
	
}

namespace tpl
{

	//泛化版本
	template <typename T,typename U = std::void_t<> >
	struct HasMemFunc :std::false_type
	{
	};

	//特化版本
	template<typename T>
	struct HasMemFunc<T, std::void_t<decltype(std::declval<T>().myfunc_MTL())>> :std::true_type
	{
	};
	//----------------------------
	//泛化版本
	template <typename ...Types>
	class TuplE;

	//特化版本1
	template <typename First,typename ...Others>
	class TuplE<First, Others...>
	{
	public:
		First  first;
		TuplE<Others...> others;

	public:
		//构造函数1，支持tpl::TuplE<int,float> mytuple;这种构造方式 
		TuplE()
		{
		}

		//构造函数模板2，支持tpl::TuplE<float, int, std::string> mytuple(12.5f, 100, std::string("abc"));这种构造方式 
		template<typename C_First,typename ... C_Others
			    ,typename = std::enable_if_t< !HasMemFunc<C_First>::value >
				>  //C_First代表一个元素类型比如float，C_Others代表其余一堆元素类型 int, std::string，
		TuplE(C_First&& parf, C_Others&& ... paro) :first(std::forward<C_First>(parf)),  //parf或者first代表第一个元素比如12.5f，
			others(std::forward<C_Others>(paro)...) //others或者paro代表其余元素，比如 100, std::string("abc")
													//others是TuplE<...>类型
		{
			//cout << "TuplE构造函数模板2执行了，first = " << first << endl; //为了避免报错，牵扯开发者精力，不要输出first值，因为有些first值不嫩共用cout正常输出
			cout << "TuplE构造函数模板2执行了！" << endl;
		}

		//拷贝构造函数
		//TuplE( TuplE<First, Others...>& tmptpl) :first(tmptpl.first), others(tmptpl.others)
		TuplE(const TuplE<First, Others...>& tmptpl) :first(tmptpl.first), others(tmptpl.others)
		{
			cout << "TuplE拷贝构造函数执行了！" << endl;
		}

		//拷贝构造函数模板
		template <typename C_First,typename... C_Others>
		TuplE(const TuplE<C_First, C_Others...>& tmptpl) :first(tmptpl.first), others(tmptpl.others)
		{
			cout << "TuplE拷贝构造函数模板执行了！" << endl;
		}

	public:
		void myfunc_MTL() {}   //HasMemFunc

	}; 

	//特化版本2：空元组不需要存储任何内容，支持tpl::TuplE<> mytuple;这种构造方式
	template<>
	class TuplE<>
	{
	public:
		//构造函数
		TuplE()
		{
			m_sign = 0; //随便给个值，方便调试时观察而已
			cout << "TuplE特化版本2的构造函数执行了！" << endl;
		}
		//拷贝构造函数
		TuplE(const TuplE<>&)
		{
			m_sign = 100;//随便给个值，方便调试时观察而已
			cout << "TuplE特化版本2的拷贝构造函数执行了！" << endl;
		}
		int m_sign; //引入的目的其实仅仅是为了设置断点调试时方便观察和确认
	};

	//-------------------------------
	//泛化版本
	template <int index>
	class TPLGetIdx
	{
	public:
		template <typename First,typename ...Others>
		static auto myget(const TuplE<First, Others...>& tmptpl) //auto用的好
		{
			return TPLGetIdx<index - 1>::myget(tmptpl.others);
		}
	};
	//特化版本
	template <>
	class TPLGetIdx<0>
	{
	public:
		template <typename First, typename ...Others>
		static auto myget(const TuplE<First, Others...>& tmptpl) //auto用的好
		{
			return tmptpl.first;
		}
	};

	//函数模板
	template <int index,typename... Types>
	auto TuplEGet(const TuplE<Types...>& tmptpl)
	{
		return TPLGetIdx<index>::myget(tmptpl);
	}

	//泛化版本
	template <typename TPLE> //TPLE代表整个TuplE<...>类型
	class pop_front_type;

	//特化版本
	template <typename FirstElem,typename... OtherElem>
	class pop_front_type<TuplE< FirstElem, OtherElem...> >
	{
	public:
		using type = TuplE<OtherElem...>;
	};

	//---------------
	/*
	template <typename... ElemsTypes,typename NewType>
	auto push_front(const TuplE<ElemsTypes...>& tmptuple, const NewType& tmpvalue)
	{
		return TuplE<NewType, ElemsTypes...>(tmpvalue, tmptuple);
	}*/
	//向空TuplE的开头插入元素，用于结束递归
	template <typename NewType>
	auto push_front(const TuplE<>& tmptuple, const NewType& tmpvalue)
	{
		return TuplE<NewType>(tmpvalue);
	}
	//向非空TuplE的开头插入元素，利用递归
	template <typename FirstType,typename... OtherType,typename NewType>
	auto push_front(const TuplE<FirstType, OtherType...>& tmptuple, const NewType& tmpvalue)
	{
		return TuplE<NewType, FirstType, OtherType... >
			(tmpvalue, push_front(tmptuple.others,tmptuple.first) );
	}

	//-----------------
	
	//向空TuplE的结尾插入元素，用于结束递归
	template <typename NewType>
	auto push_back(const TuplE<>&, const NewType& tmpvalue)
	{
		return TuplE<NewType>(tmpvalue);
	}
	//向非空TuplE的结尾插入元素，利用递归
	template<typename FirstType,typename ...OtherType,typename NewType>
	//auto：函数返回类型，实际相当于TuplE<FirstType,OtherType...,NewType>
	auto push_back(const TuplE<FirstType, OtherType...>& tmptuple, const NewType& tmpvalue)
	{
		return TuplE<FirstType, OtherType..., NewType>
			(tmptuple.first,push_back(tmptuple.others,tmpvalue));
	}
	

	/*
	template <typename... ElemsTypes, typename NewType>
	auto push_back(const TuplE<ElemsTypes...>& tmptuple, const NewType& tmpvalue)
	{
		return TuplE< ElemsTypes..., NewType>(tmptuple, tmpvalue);
	}*/

	//-------------------
	template <typename ... ElemsTypes>
	auto pop_front(const TuplE<ElemsTypes...>& tmptuple)
	{
		return tmptuple.others;
	}
	//-------------------
	//普通函数reverse
	auto reverse(const TuplE<>&)
	{
		return TuplE<>();
	}
	//函数模板reverse
	template<typename FirstType,typename... OtherType>
	auto reverse(const TuplE<FirstType, OtherType...>& tmptuple)
	{
		return push_back(reverse(tmptuple.others), tmptuple.first); //利用reverse递归可以逐步取得TuplE中每个元素，
		                                                         //而后用push_back把取得的元素放到TuplE末尾,即可达到颠倒的效果
	}


}


//Make_TuplE演示了类型推导技术：函数模板可以通过实参中给进来的元素值推导出元素类型（注意体会这种推导手段）。
template <typename... Types>
auto Make_TuplE(Types&& ..._Args) //形参是万能引用（转发引用）
{	
	return tpl::TuplE<std::decay_t<Types>...>(std::forward<Types>(_Args)...);
}


//向integer_sequence开头插入元素：泛化版本
template<typename INTSEQ, unsigned int NewElem>
struct IntSeq_PushFront;

//向integer_sequence开头插入元素：特化版本
template<typename T, unsigned int... Elems, unsigned int NewElem>
struct IntSeq_PushFront <  std::integer_sequence<T, Elems...>, NewElem  >
{
	using type = std::integer_sequence<T, NewElem, Elems...>;
};

//泛化版本
template<typename T, unsigned int N, unsigned int Count = 1> //从1开始记数
struct Integer_Sequence_Reverse
{
	using type = typename IntSeq_PushFront<typename
		Integer_Sequence_Reverse<T, N - 1>::type, N - Count >::type;
};

//特化版本
template<typename T, unsigned int N>
struct Integer_Sequence_Reverse<T, N, N>
{
	using type = std::integer_sequence<T, N - 1>;
};
//定义别名模板
template<typename T, unsigned int N>
using Integer_Sequence_Reverse_T = typename Integer_Sequence_Reverse<T, N>::type;

//----------------------
template <typename... Elems,std::size_t...Index>
auto TPL_LastReverse(const tpl::TuplE<Elems...>& tmptuple, std::integer_sequence<std::size_t, Index...>)
{
	return Make_TuplE(tpl::TuplEGet<Index>(tmptuple)...); //TuplEGet被调用多次
}
template <typename... Elems>
auto TPL_MidReverse(const tpl::TuplE<Elems...>& tmptuple)
{
	return TPL_LastReverse(tmptuple, Integer_Sequence_Reverse_T<unsigned int, sizeof...(Elems)>()); //std::integer_sequence<int,2,1,0>
}


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口
	
	//第四节 元组（tuple）实现
	//（2）元组基本概念、基础代码的设计和实现
	//Boost-tuple（元组）：tuple是一个里面能够装各种不同类型元素的数组/容器。
	//（2.1）泛化、特化、构造函数的实现
	//可变参类模板的模板参数包的展开方式有两种：a)通过递归继承方式展开，b)通过递归组合方式展开（要讲的）
	//递归组合方式缺点：占用的内存可能相对多一点（一般就是一个字节），因为会涉及到一个“空白基类优化（EBCO）”的话题。
	//tpl::TuplE<float, int, std::string> 拆分成float和tpl::TuplE< int, std::string>
	//tpl::TuplE< int, std::string>拆分成int 和tpl::TuplE<std::string>
	//tpl::TuplE<std::string>拆分成std::string和tpl::TuplE<>
	//（2.2）拷贝构造函数及拷贝构造函数模板的实现--std::enable_if
	//重要的话语：拷贝构造函数模板永远不可能成为拷贝构造函数”，当两个元素类型不同时，构造元素（对象）时
	         //使用的是拷贝构造函数模板而不是拷贝构造函数。
	//（2.3）实现获取tuple中元素的get接口
	//（2.4）std::make_tuple的实现
	//（2.5）总结:无需过分强求完美的设计和实现。做到随时发现问题随时解决问题即可。
	//（3）操作接口（算法）
	//template<typename ...T>
	//class typelist {...};
	//（3.1）从tuple中移除第一个类型（pop_front_type）:对其中的元素 “类型” 进行操作。 
	//（3.2）向tuple的开头和结尾插入一个元素（push_front、push_back）
	//（3.3）从tuple中移除第一个元素（pop_front）
	//（3.4）颠倒（反转）一个tuple中的元素的顺序（reverse）
	//std::integer_sequence类模板。Integer_Sequence_Reverse.










	//tuple<float, int, std::string> mytuple(12.5f, 100, std::string("abc")); //一个tuple（元组）：一堆各种类型数据的组合
	//cout << get<0>(mytuple) << endl; //12.5,get是一个函数模板。

	/*
	int i = 100;
	tpl::TuplE<float, int, std::string> mytuple(12.5f, i, std::string("abc"));
	//tpl::TuplE<float, int, std::string> mytuple2(mytuple);
	cout << "--------" << endl;
	tpl::TuplE<double, int, std::string> mytuple2(mytuple);

	tpl::TuplE<float> tupleet1(12.5f);
	cout << "----------" << endl;
	tpl::TuplE<int, tpl::TuplE<float> > tmptuple1(15, tupleet1);

	//tpl::TuplE<int, tpl::TuplE<float> > tmptuple2(15, tpl::TuplE<float>(12.5f));

	//const tpl::TuplE<float> tupleet10(12.5f);
	//tpl::TuplE<float> tupleet11(tupleet10);

	cout << "----------" << endl;
	cout << tpl::TuplEGet<2>(mytuple) << endl;

	//--------------------
	auto mytuple10 = std::make_tuple(12.5f, 100, std::string("abc")); //3个元素
	std::tuple<float,int,std::string> mytuple11 = std::make_tuple(12.5f, 100, std::string("abc")); //3个元素

	auto mytuple12 = Make_TuplE(12.5f, 100, std::string("abc")); //等价于：std::tuple<float,int,std::string> mytuple12 = Make_Tuple(12.5f, 100, std::string("abc"));
	//std::tuple<float, int, std::string> mytuple13(12.5f, 100, std::string("abc"));
	
	//tpl::TuplE<int, double> wtTpl1(100, 12.5);
	//tpl::TuplE< tpl::TuplE<int, double> > stTpl2(wtTpl1);
	*/

	/*
	tpl::TuplE<float, int, std::string> mytpobj1(12.5f, 100, "abc");
	tpl::pop_front_type<decltype(mytpobj1)>::type mytpobj2(100, "abc");
	cout << tpl::TuplEGet<1>(mytpobj2) << endl;
	*/

	
	tpl::TuplE<> mytpobj3;
	auto mytpobj4 = tpl::push_front(mytpobj3, 12);
	tpl::TuplE<float, int, std::string> mytpobj5(12.5f, 100, "abc");
	auto mytpobj6 = tpl::push_front(mytpobj5, 12);	
	auto mytpobj7 = tpl::push_back(mytpobj5, 12);
	auto mytpobj8 = tpl::pop_front(mytpobj5);

	cout << "--------------构造mytpobj9-----------" << endl;
	auto mytpobj9 = tpl::reverse(mytpobj5);
	cout << "---------------" << endl;

	//--------------------------
	Integer_Sequence_Reverse_T<int, 4> tmpobj4;
	cout << "tmpobj4的类型为：" << typeid(decltype(tmpobj4)).name() << endl;

	cout << "--------------构造mytpobj10-----------" << endl;
	auto mytpobj10 = TPL_MidReverse(mytpobj5);
	cout << "---------------" << endl;

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






























