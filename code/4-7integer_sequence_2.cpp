// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>
//#include <boost/type_index.hpp>

using namespace std;
//#pragma warning(disable : 4996) 

namespace _nmsp1
{	
	/*template <class T, T... Ints>
	struct integer_sequence 
	{
		using value_type = T;

		static constexpr size_t size() noexcept 
		{
			return sizeof...(Ints);
		}
	};*/

	//-----------------------------------
	//向integer_sequence末尾插入元素：
	//泛化版本
	template<typename INTSEQ, unsigned int NewElem> //INTSEQ代表整个的std::integer_sequence< ......>类型
	struct IntSeq_PushBack; //因为不使用泛化版本，所以泛化版本可以只声明不定义。

	//向std::integer_sequence末尾插入元素：特化版本
	template<typename T, unsigned int... Elems,unsigned int NewElem> //泛化版本一般要求可变参放在最后，特化版本一般无此要求
	struct IntSeq_PushBack<  std::integer_sequence<T, Elems... >, NewElem >
	{
		using type = std::integer_sequence<T, Elems..., NewElem>;
	};
	//-----------------------------------
	//泛化版本
	template <typename T,unsigned int N>
	struct Integer_Sequence //实现std::make_integer_sequence功能
	{
		//依次遍历出4,3,2,1，应该往末尾插入元素，所以还应该引入IntSeq_PushBack操作。
		using type = typename IntSeq_PushBack<  typename Integer_Sequence< T,N-1 >::type,N-1 >::type; //这里理解成函数调用，把type理解成所调用的函数名

	};

	//特化版本
	template <typename T>
	struct Integer_Sequence<T, 1> //这里是1，意味着递归到1就可以了
	{
		using type = std::integer_sequence<T, 0>; //这是0，注意。
	};
	//---------
	//定义别名模板
	template <typename T, unsigned int N>
	using Integer_Sequence_T = typename Integer_Sequence<T, N>::type;

}
namespace _nmsp2
{
	//-----------------------------------
	//向integer_sequence开头插入元素：
	//泛化版本
	template<typename INTSEQ, unsigned int NewElem> //INTSEQ代表整个的std::integer_sequence< ......>类型
	struct IntSeq_PushFront; //因为不使用泛化版本，所以泛化版本可以只声明不定义。

	//向std::integer_sequence开头插入元素：特化版本
	template<typename T, unsigned int... Elems, unsigned int NewElem> //泛化版本一般要求可变参放在最后，特化版本一般无此要求
	struct IntSeq_PushFront<  std::integer_sequence<T, Elems... >, NewElem >
	{
		using type = std::integer_sequence<T, NewElem,Elems... >;
	};
		
	//-----------------------------------
	//泛化版本
	template <typename T, unsigned int N,unsigned Count=1> //从1开始计数
	struct Integer_Sequence_Reverse
	{		
		using type = typename IntSeq_PushFront<  typename Integer_Sequence_Reverse< T, N - 1 >::type, N - Count >::type;

	};

	//特化版本
	template <typename T,unsigned int N>
	struct Integer_Sequence_Reverse<T, N,N>
	{
		using type = std::integer_sequence<T, N-1>;
	};
	//---------
	//定义别名模板
	template <typename T, unsigned int N>
	using Integer_Sequence_Reverse_T = typename Integer_Sequence_Reverse<T, N>::type;
}
namespace _nmsp3
{
	//泛化版本
	template <std::size_t Num,std::size_t RepeatTime, typename INTSEQ = std::integer_sequence<std::size_t> >  // INTSEQ代表整个的std::integer_sequence< ......>类型
	class Repeat_Integer;

	//特化版本1：
	template <std::size_t Num, std::size_t RepeatTime, std::size_t... index >
	class Repeat_Integer<Num, RepeatTime, std::integer_sequence<std::size_t, index...> > :
		public Repeat_Integer<Num, RepeatTime - 1, std::integer_sequence<std::size_t, index..., Num>>
	{
	};

	//特化版本2（用于结束递归）
	template <std::size_t Num, std::size_t... index >
	class Repeat_Integer<Num, 0, std::integer_sequence<std::size_t, index...> >
	{
	public:
		using type = std::integer_sequence<std::size_t, index...>;
	};

	//定义别名模板
	template <std::size_t Num, std::size_t RepeatTime>
	using Repeat_Integer_T = typename Repeat_Integer<Num, RepeatTime>::type;


}

int main()
{ 	
	//第七节 std::integer_sequence:C++14中引入的一个类模板。
	//std::integer_sequence<
	//产生整型数字序列，0,1,2,3,4,5
	//T：int,unsigned int,char,short。
	//Ints：非类型模板参数包，一堆数字，这堆数字类型相同，都是T类型。

	//std::make_integer_sequence，别名模板，就可以理解成是一个 std::integer_sequence，大概他的伪代码的感觉：
	//template<class T, T N>
	//using make_integer_sequence=std::integer_sequence<T,0,1,2,3,....N-1序列>;
	//std::make_index_sequence，别名模板，与make_integer_sequence非常类似，伪代码的感觉
	//template<std::size_t N>
	//using make_index_sequence=std::integer_sequence<std::size_t,0,1,2,3,....N-1序列>;//	std::size_t = unsigned int;

	//（1）正向排列数字生成一个类型——Integer_Sequence
	//研究如何通过类型make_integer_sequence<int,5>得到类型：std::integer_sequence<int,0,1,2,3,4>

	//(i)Integer_Sequence_T<int, 4> tmpobj3;   //等价于
	//(i)Integer_Sequence<int, 4>::type tmpobj3;   //把type看成函数调用
	//(i)    using type = typename IntSeq_PushBack<  typename Integer_Sequence< T,3 >::type,3 >::type;
	//(i)        //展开上行后面这个 Integer_Sequence< int,3 >::type 如下:
	//(i)        using type = typename IntSeq_PushBack<  typename Integer_Sequence< int,2 >::type,2 >::type;
	//(i)            //展开上行后面这个 Integer_Sequence< int,2 >::type 如下:
	//(i)            using type = typename IntSeq_PushBack<  typename Integer_Sequence< int,1 >::type,1 >::type;
	//(i)                //展开上行后面这个 Integer_Sequence< int,1 >::type ，调用的是特化版本
	//(i)                using type = std::integer_sequence<int, 0>;  //递归结束，开始往回返
	//(i)            //递归往回返的时候注意IntSeq_PushBack是向std::integer_sequence末尾插入内容
	//(i)            using type = std::integer_sequence<int, 0,1>
	//(i)        using type = std::integer_sequence<int, 0,1,2>
	//(i)    using type = std::integer_sequence<int, 0,1,2,3>
	//(i)//最终结果
	//(i) std::integer_sequence<int, 0,1,2,3>

	//（2）逆向排列数字生成一个类型Integer_Sequence_Reverse
	//(i)Integer_Sequence_Reverse_T<int, 4> tmpobj4;   //等价于
	//(i)Integer_Sequence_Reverse<int, 4>::type tmpobj4; //把type看成函数调用
	//(i)    using type = IntSeq_PushFront<Integer_Sequence_Reverse< int,3>::type, 3 >::type;
	//(i)        //展开上行后面这个Integer_Sequence_Reverse< int,3>::type如下
	//(i)        using type = IntSeq_PushFront<Integer_Sequence_Reverse< int,2>::type, 2 >::type;
	//(i)            //展开上行后面这个Integer_Sequence_Reverse< int,2>::type如下
	//(i)            using type = IntSeq_PushFront<Integer_Sequence_Reverse< int,1>::type, 1 >::type;
	//(i)                //展开上行后面这个Integer_Sequence_Reverse< int,1>::type，调用的是特化版本
	//(i)                using type = std::integer_sequence<int, 0>; //递归结束往回返
	//(i)            using type = std::integer_sequence<int, 1,0>
	//(i)        using type = std::integer_sequence<int, 2,1,0>
	//(i)    using type = std::integer_sequence<int,3,2,1,0>
	//(i)//最终结果
	//(i)std::integer_sequence<int,3,2,1,0>

	//（3）将一个数字重复多次生成一个类型Repeat_Integer
	//前面是通过递归调用的方式实现。现在这里通过递归继承的方式实现。
	/*（1）因为Repeat_Integer<1, 4>::type tmpobj5; 代码行的存在，导致系统会根据Repeat_Integer特化版本1实例化出如下类：
	Repeat_Integer<1, 4, std::integer_sequence<std::size_t>>
	（2）接着说tmpobj5，要想实例化出：
	Repeat_Integer<1, 4, std::integer_sequence<std::size_t>>
	根据继承关系，编译器必须要实例化出他的父类，其实也就是：
	Repeat_Integer<Num, 3, std::integer_sequence<std::size_t, 1>>
	上面这个写法注意：std::integer_sequence模板参数的末尾，已经多出个1了，而且此时的index代表的不在是0个参数，而是1个参数了。
	......
	（3）在递归结束时，即 使用Repeat_Integer的特化版本2来实例化Repeat_Integer时，使用了using来定义类型别名type，
		  此时type就相当于类型std::integer_sequence<std::size_t, 1, 1, 1, 1>，因为是一种类继承关系，所以父类中定义的type在
		 子类中即可使用，因此Repeat_Integer<1, 4>::type这种写法毫无问题。*/








	
	/*
	std::make_integer_sequence<int, 5> tmpobj;
	cout << "tmpobj的类型为：" << typeid(decltype(tmpobj)).name() << endl;
	*/

	/*
	std::make_index_sequence<4> tmpobj2;
	cout << "tmpobj2的类型为：" << typeid(decltype(tmpobj2)).name() << endl;
	*/

	/*
	_nmsp1::Integer_Sequence_T<int, 4> tmpobj3;
	cout << "tmpobj3的类型为：" << typeid(decltype(tmpobj3)).name() << endl;



	_nmsp2::Integer_Sequence_Reverse_T<int, 4> tmpobj4;
	cout << "tmpobj4的类型为：" << typeid(decltype(tmpobj4)).name() << endl;
	*/

	_nmsp3::Repeat_Integer<1, 4>::type tmpobj5;
	cout << "tmpobj5的类型为：" << typeid(decltype(tmpobj5)).name() << endl; //希望显示的结果：struct std::integer_sequence<unsigned int,1,1,1,1>

	_nmsp3::Repeat_Integer<1, 4, std::integer_sequence<std::size_t,12,18,19> >::type tmpobj6;
	cout << "tmpobj6的类型为：" << typeid(decltype(tmpobj6)).name() << endl;



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
