// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>
//#include <boost/type_index.hpp>

using namespace std;
//#pragma warning(disable : 4996) 

namespace _nmsp1
{	
	//remove_all_extents的实现源码：
	template <class T>
	struct remove_all_extents { // remove all array extents
		using type = T;
	};

	template <class T, size_t N>
	struct remove_all_extents<T[N]> {
		using type = typename remove_all_extents<T>::type; //元编程：多数情况下都会涉及到递归
	};

	template <class T>
	struct remove_all_extents<T[]> { //[]表示是一个无边界数组
		using type = typename remove_all_extents<T>::type;
	};

}

int main()
{ 		
	//第六节 std::remove_all_extents
	//remove_all_extents是C++11中引入的类模板。能力是把一个数组中的数组类型部分移除掉，只保留元素类型。
	//int a[12]; //a的类型=int[12];	
	//a.cpp中定义了一个int g_array[10];全局数组。若想在其他.cpp原文件中使用这个全局数组。
	//递归问题	
	//分析一下  remove_all_extents<T>::type
	//(1)c的类型int[2][8][9]，所以remove_all_extents<decltype(c)>::type（理解时把这种写法理解成函数调用）
	      //就等价于remove_all_extents<int[2][8][9]>::type，这个写法就会导致编译器实例化出remove_all_extents<int[2][8][9]>类。
	//(2)remove_all_extents<int[2][8][9]>::type这种写法，正好满足remove_all_extents的第一个特化版本。这个时候特别值得注意的是：
	      //满足该特化版本时，非类型模板参数N的值是2（而不是9，这里不要搞反），
	        //所以，remove_all_extents<int[2][8][9]>::type实际得到的类型是remove_all_extents<int[8][9]>::type;
	         //这里可以看到，通过remove_all_extents就把第一维的数字2给拿掉了，紧接着就开始进入递归了。
	//(3)递归开始，第二次满足的又是remove_all_extents的第一个特化版本，因此拿掉的是第二维的数字8，
	        //所以,remove_all_extents<int[8][9]>::type;得到的类型变成了remove_all_extents<int[9]>::type,第二维数字又被拿掉了。
	//(4)继续递归，第三次满足的又是remove_all_extents的第一个特化版本，因此拿掉的是第三维的数字9，
			//所以,remove_all_extents<int[9]>::type;得到的类型变成了remove_all_extents<int>::type,第三维数字又被拿掉了。
	//(5)继续递归，第四次满足的确是remove_all_extents的泛化版本，这也预示着递归结束了，因为泛化版本的代码是using type = T;，
	          //T这里是int类型，因此remove_all_extents<int>::type最终就成了类型int。

	//总结：remove_all_extents类模板的实现用到了 递归模板实例化 的技术手段，想象一下：
	//cout << typeid(std::remove_all_extents<decltype(c)>::type).name() << endl;代码行
	//得到最终结果时中间一共实例化出来了几个以remove_all_extents开头的类呢？
	//a)remove_all_extents<int[2][8][9]>;
	//b)remove_all_extents<int[8][9]>;
	//c)remove_all_extents<int[9]>;
	//d)remove_all_extents<int>;
	//调用关系：
	//(i)std::remove_all_extents<decltype(c)>::type  等价于
	//(i)std::remove_all_extents<decltype(int[2][8][9])>::type  //把type看成函数调用
	//(i)    using type = typename remove_all_extents<int[8][9]>::type; //把[2]去掉了 
	//(i)        //展开remove_all_extents<int[8][9]>::type;如下
	//(i)        using type = typename remove_all_extents<int[9]>::type; //把[8]去掉了 
	//(i)            //展开remove_all_extents<int[9]>::type;如下
	//(i)            using type = int //把[9]去掉了，递归结束了往回返
	//(i)        using type = int;
	//(i)    using type = int;
	//(i)//最终结果
	//(i)int










	float a[12]; //a的类型int[12];
	int b[5][8]; //b的类型int[5][8];
	int c[2][8][9]; //c的类型int[2][8][9];

	cout << typeid(std::remove_all_extents<decltype(a)>::type).name() << endl;  //float
	cout << typeid(std::remove_all_extents<decltype(b)>::type).name() << endl;   //int
	cout << typeid(std::remove_all_extents<decltype(c)>::type).name() << endl;    //int

	extern int g_array[]; //外部变量说明，无边界数组，类型为int[]
	cout << typeid(std::remove_all_extents<decltype(g_array)>::type).name() << endl;    //int






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
