// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>
#include <vector>

using namespace std;
//#pragma warning(disable : 4996) 

namespace _nmsp1
{	
	template <typename T>
	struct MEB
	{
		using type = T;
	};

	//// STRUCT TEMPLATE enable_if
	//template <bool _Test, class _Ty = void>   //泛化版本
	//struct enable_if {}; // no member "type" when !_Test

	//template <class _Ty> //偏特化版本:怎么理解：只有这个偏特化版本存在，才存在一个名字叫做type的类型别名（类型）
	//struct enable_if<true, _Ty> { // type is _Ty for _Test
	//	using type = _Ty;
	//};


}

namespace _nmsp2
{
	template <typename T>
	//typename std::enable_if<(sizeof(T) > 2)>::type funceb() // void funceb(){}
	//std::enable_if_t<(sizeof(T) > 2)> funceb()
	std::enable_if_t<(sizeof(T) > 2),T> funceb() //int funceb(){}
	{
		T myt = {};
		return myt;
	}

	//template <bool _Test, class _Ty = void>
	//using enable_if_t = typename enable_if<_Test, _Ty>::type; //别名模板


}
namespace _nmsp3
{
	//给类型模板定义一个别名(别名模板)
	template <typename T>
	using StrProcType = std::enable_if_t<std::is_convertible<T, std::string>::value >;

	class Human
	{
	public:
		////构造函数
		//Human(const string& tmpname) :m_sname(tmpname)
		//{
		//	cout << "Human(const string &tmpname)执行" << endl;
		//}
		////Human(string&& tmpname) :m_sname(tmpname)
		//Human(string&& tmpname) :m_sname(std::move(tmpname)) //move并不具备移动能力，把一个左值转换成一个右值。
		//{
		//	cout << "Human(string&& tmpname)执行" << endl;
		//}

		//构造函数模板
		//template<typename T>
		template<
			typename T,
			//typename  = std::enable_if_t<std::is_convertible<T, std::string>::value >
							//如果T能够成功转换成std::string类型，那么typename  = std::enable_if_t<std::is_convertible<T, std::string>::value > 等价于
			                       //typename  = void
			typename = StrProcType<T>			             
		>
		Human(T&& tmpname) : m_sname(std::forward<T>(tmpname))
		{
			cout << "Human(T&& tmpname)执行" << endl;
		}

		//拷贝构造函数
		Human(const Human& th) : m_sname(th.m_sname)
		{
			cout << "Human(const Human& th)拷贝构造函数执行" << endl;
		}

		//移动构造函数
		Human(Human&& th) : m_sname(std::move(th.m_sname))
		{
			cout << "Human(Human&& th)移动构造函数执行" << endl;
		}

	private:
		string m_sname;
	};



}


int main()
{ 
	//第四节 std::enable_if的使用
	//要逐步的领略 泛型编程 与以往 面向对象编程 的不同之处了
	//（1）一个简单范例:对于重载的函数或者函数模板的选择上，编译器内部有一个自己的规则，
	         //并不是简单粗暴的对函数就优先选择，对函数模板就靠后选择。

	//（2）替换失败并不是一个错误（SFINAE）:每个学习这门课程的人必须听懂，而且必须理解好。
	//SFINAE:Substitution Failure Is Not An Error，翻译成中文是“替换失败并不是一个错误”
	//SFINAE看成是C++语言的一种特性或者说一种模板设计中要遵循的重要原则，非常重要，务必理解好。
	 //SFINAE特性是针对“函数模板重载”而言。
	//针对于函数模板而言，当用一个具体类型替换函数模板的参数时，可能会产生意想不到的问题 ：
	          //比如产生一些毫无意义甚至是看起来语法上有错误的代码，对于这些代码，编译器并不一定报错，有可能是忽略——
	               //编译器认为这个函数模板不匹配针对本次的函数调用，就当这个函数模板不存在一样。
	                //转而去选择其他更匹配的函数或者函数模板，这就是所谓的“替换失败并不是 一个错误”说法的由来。
	//SFINAE特性：我（编译器）虽然看不出你（实例化了的模板）的对错（错误一般指无效的类型，无效的表达式等），但是我能决定是否选择你，
	      //当我觉得不合适的时候，我虽然不说你错，但是我忽略你（而不会选择你）；
	//（3）enable_if
	//1. 基础认识:C++11新标准中引入的类模板（结构模板）。使用体现了C++编译器的SFINAE特性。
	 //定位为一个helper模板（助手模板），用于辅助其他模板的设计，表现一种：编译器的分支逻辑（编译期就可以确定走哪条分支）。
	  //偏特化完全可以理解成一种条件分支语句。
	//2. 范例：enable_if用于函数模板中：典型应用是作为函数模板的返回类型。
	//3. 范例：enable_if用于类模板中
	//_nmsp3::Human myhuman3(myhuman1);代码行解决办法：针对构造函数模板，如果给进来的参数是一个string类型的参数，就让这个构造函数模板生效。
	     //否则就让这个构造函数模板被忽略即可。也就是说，如果使用enable_if于构造函数模板中，enable_if的条件只需要设置成“形参类型==string类型”即可。
	//std::is_convertible，C++11一如。两个模板参数分别是From 和To：用于判断能否从某个类型隐式的转换到另外一个类型。返回一个bool值——true或者false。







	//_nmsp1::MEB<int>::type abc = 15; //_nmsp1::MEB<int>::type 就代表int类型
	//std::enable_if< (3 > 2)>::type* mypoint1 = nullptr;  //void *mypoint1 = nullptr
	//std::enable_if< (3 < 2)>::type* mypoint1 = nullptr;

	//_nmsp2::funceb<int>();
	//_nmsp2::funceb<char>();

	//cout << "string=>float:" << std::is_convertible<string, float>::value << endl;
	//cout << "float=>int:" << std::is_convertible<float, int>::value << endl;


	string sname = "ZhangSan";
	_nmsp3::Human myhuman1(sname);
	_nmsp3::Human myhuman3(myhuman1); //实际编译器去调用了构造函数模板，而不是调用了拷贝构造函数。


	
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

class Human
{
public:
	////构造函数
	//Human(const string& tmpname) :m_sname(tmpname)
	//{
	//	cout << "Human(const string &tmpname)执行" << endl;
	//}
	////Human(string&& tmpname) :m_sname(tmpname)
	//Human(string&& tmpname) :m_sname(std::move(tmpname)) //move并不具备移动能力，把一个左值转换成一个右值。
	//{
	//	cout << "Human(string&& tmpname)执行" << endl;
	//}

	//构造函数模板
	template<typename T>
	Human(T&& tmpname) : m_sname(std::forward<T>(tmpname))
	{
		cout << "Human(T&& tmpname)执行" << endl;
	}

	//拷贝构造函数
	Human(const Human& th) : m_sname(th.m_sname)
	{
		cout << "Human(const Human& th)拷贝构造函数执行" << endl;
	}

	//移动构造函数
	Human(Human&& th) : m_sname(std::move(th.m_sname))
	{
		cout << "Human(Human&& th)移动构造函数执行" << endl;
	}

private:
	string m_sname;
};

*/


/*

string sname = "ZhangSan";
_nmsp1::Human myhuman1(sname);
_nmsp1::Human myhuman3(myhuman1); //实际编译器去调用了构造函数模板，而不是调用了拷贝构造函数。

*/
