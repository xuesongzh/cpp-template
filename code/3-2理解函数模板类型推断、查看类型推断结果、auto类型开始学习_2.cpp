// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>
#include <initializer_list>

#include <boost/type_index.hpp>


using namespace std;
//#pragma warning(disable : 4996) 

//函数模板
//template <typename T,unsigned L1> //L1就是数组长度
template <typename T>
//void myfunc(T&& tmprv) 
void myfunc(T  tmprv)
//void myfunc(T (&tmprv)[L1] )
//void myfunc(std::initializer_list<T>  tmprv)
{
	cout << "--------------------------------begin----------------" << endl;
	using boost::typeindex::type_id_with_cvr;
	cout << "T=" << type_id_with_cvr<T>().pretty_name() << endl; //显示T的类型
	cout << "tmprv=" << type_id_with_cvr<decltype(tmprv)>().pretty_name() << endl; //显示tmprv的类型
	cout << "--------------------------------end------------------" << endl;	

	//tmprv = nullptr;
	//*tmprv = 'Y'; //编译报错：error C3892: “tmprv”: 不能给常量赋值

	//tmprv = 12;
	//int& tmpvaluec = tmprv;
	//tmpvaluec = 1200;

	//cout << L1 << endl;
}

template <typename T>
//void tf(const T& tmprv) //这里把auto替换成T,xy就相当于这里的tmprv
void tf(T&& tmprv)
{
	cout << "--------------------------------begin----------------" << endl;
	using boost::typeindex::type_id_with_cvr;
	cout << "T=" << type_id_with_cvr<T>().pretty_name() << endl; //显示T的类型
	cout << "tmprv=" << type_id_with_cvr<decltype(tmprv)>().pretty_name() << endl; //显示tmprv的类型
	cout << "--------------------------------end------------------" << endl;
}

namespace _nmsp1
{		
	

}

void testFunc() {}

int main()
{ 	

	//第二节 理解函数模板类型推断、查看类型推断结果、auto类型推断
	//（2）理解函数模板类型推断
	  //myfunc中T的类型不仅仅取决于实参100,还取决于tmprv的类型（const T&）有关。
	//看一看，函数模板的形参（tmprv）是如下类型时编译器推断出的 类型模板参数的类型（T）,以及最终的函数形参类型（tmprv）
	//（2.1）引用或指针类型
		//根据结果，得到 一些结论：
		//(1)若实参是引用类型，那么引用部分会被忽略，T不会被推导为引用类型，这个需要记一下。
		//(2)当向引用类型的形参tmprv传入const类型实参时了，那么形参tmprv会成为const引用（原来是个引用）。
		  //这里可以看到，实参的const属性会成为类型模板参数T类型推导的组成部分，所以不用担心在myfunc中能够修改原来const属性的实参。
		  //a)若实参是引用类型，那么引用部分会被忽略，T不会被推导为引用类型。
		  //b)T中的const没有了，因为函数模板的形参tmprv里出现const。但不管怎么说，只要实参带const，形参tmprv中终究还是会带着const。
		//通过上面的范例，小节一下编码技巧：
		//a)形参中引用有两个作用：1是可以通过对形参的修改来修改实参。2是传递引用比传值效率高，
		   //所以，一般来说，函数模板中的形参建议优先考虑“T &tmprv”这样的形态，
			   //这样的形态就不怕实参中的引用被忽略掉而导致开发者想通过对形参的修改达到修改实参的本意无法达成。
		//b)如何既想享受形参为引用带来的效率上的提高，又不希望通过形参来修改实参，则函数模板中的形参建议考虑“const T &tmprv”这样的形态。
		//(3)如果tmprv是个指针看看啥情况。
		//根据结果显示，得到一些结论：
		//(a)tmprv中如果没有const，则实参中的const会被带到类型T中去。如果tmprv中有const，则T类型中不会带const。
		//(b)不妨观察一下：(a)这个结论对于myfunc中形参为T& tmprv或者const T& tmprv也适用。

	//（2.2）万能引用类型
	//（2.3）传值方式
	   //a)若实参是引用类型，则引用部分会被忽略，T不会被推导为引用类型。除非手工指定为引用类型(不建议这样写代码)。
	   //b)若实参是const类型，则const部分会被忽略，T不会推导为const类型（毕竟产生的是新副本）；
	//（2.4）传值方式的引申——std::ref与std::cref
	  //当函数模板定义中使用传值方式时，可以通过std::ref和std::cref来以引用方式传递参数。
	//（2.5）数组做实参
	//（2.6）函数名做实参
	//（2.7）初始化列表做实参

	//总结：
	//a)推断中，引用类型实参的引用类型等于不存在。
	//b)万能引用，实参为左值或者右值，推断的结果不同。
	//c)按值传递的实参，传递给形参时const属性不起作用，但传递进去指针则另当别论。
	//d)数组或者函数类型在类型推断中会被看做是指针，除非函数模板的形参是个引用。
	//e)初始化列表不能直接推断成initializer_list类型，必须在函数模板的形参中明确指出使用initializer_list类型。

	//（3）auto类型常规推断:用于变量的自动类型推断。
	  //声明变量的时候根据变量初始化的类型自动为此变量选择匹配的类型，不需要程序员显式的指定类型。
	  //auto的特点如下：
	   //a)auto的自动类型推断发生在编译期间。
	   //b)auto定义变量必须立即初始化，这样编译器才能推断出他的实际类型。编译的时候才能确定auto类型以及整个变量的类型。
	            //然后在编译期间就可以用真正的类型替换掉auto这个类型占位符了。
	   //c)auto的使用比较灵活，可以和指针、引用、const等限定符结合使用。
	//auto推断出来后会代表一个具体类型，auto相当于函数模板类型推断中的参数T。
	//（3.1）传值方式（非指针，非引用）
	//auto后面直接接变量名，这就叫传值方式。
	//总结传值方式对auto类型：会抛弃引用，const等限定符。
	//（3.2）指针或者引用类型但不是万能引用
	//auto后面接一个&这就叫引用类型。
	//总结传指针或者引用方式针对auto类型：不会抛弃const限定符，但是会抛弃引用。
	//（3.3）万能引用类型
	//与讲解函数模板类型推断时万能引用的情形完全相同。








	/*
	int i = 18; //i的类型是int
	const int j = i; //j的类型是const int
	const int& k = i; //k的类型是const int &
	myfunc(i); //T = int & ，tmprv = int &
	myfunc(j); //T = int const & ,tmprv = int const &
	myfunc(k); //T = int const & ,tmprv = int const &

	myfunc(100);//T = int ,tmprv = int &&
	*/

	/*
	int i = 18; //i的类型是int
	const int j = i; //j的类型是const int
	const int& k = i; //k的类型是const int &
	myfunc(i); //T = int  ，tmprv = int 
	myfunc(j); //T = int  ，tmprv = int 
	myfunc(k); //T = int  ，tmprv = int */

	//int& m = i;	
	//myfunc<int &>(m);

	/*
	char mystr[] = "I Love China";
	const char* const p = mystr; //第一个const表示p指向的目标中的内容不能通过p改变
	                               //第二个const表示p指向一个内容后，p不可以再指向其他内容（p不可以指向不同目标）。
	myfunc(p);  //T = char const *,tmprv=char const * ，传递给myfunc后，第二个const没有了，第一个const是保留的。
	               //这表示进入到myfunc函数模板内部后，tmprv指向的内容不能通过tmprv改变，但是tmprv可以指向其他内存地址。
	                     //也就是说tmprv(p)的常量性被忽略了，而tmprv（p）所指向的内容的常量性会被保留。 
	                       //结论记一下：如果传递的是const char *或者const char[],这个const会被保留。
	*/

	/*
	int m = 180;
	myfunc(std::ref(m)); //std::ref和std::cref象对象包装器，编译器通过创建一个 class std::reference_wrapper<T>类型的对象
	                      //T=class std::reference_wrapper<int> ,tmprv=class std::reference_wrapper<int>
	cout << "m=" << m << endl;
	*/

	/*
	const char mystr[] = "I Love China!";
	myfunc(mystr); //T=char const *  , tmprv=char const *
	*/
	/*
	const char mystr[] = "I Love China!";
	myfunc(mystr); //T=char const [14],tmprv=char const (&)[14]--(&)代表数组的一个引用。
	*/

	//myfunc(testFunc); //T=void (__cdecl*)(void),tmprv=void (__cdecl*)(void)
	//myfunc(testFunc); //T=void __cdecl(void),tmprv=void (__cdecl&)(void)——tmprv是一个函数引用类型：void(&)(void)

	//myfunc({1,2,3}); //T=int,tmprv=class std::initializer_list<int>


	//auto x = 27; //auto有一个类型，x也有 一个类型。
	            //x =int ,auto = int。

	auto x = 27; //估计x = int,auto =int
	const auto x2 = x; //估计x2 = const int,auto =int
	const auto& xy = x; //这个auto并不是传值方式，估计xy = const int &，auto = int
	auto xy2 = xy; //估计：xy2 = int,auto =int;。

	/*using boost::typeindex::type_id_with_cvr;	
	cout << "xy2=" << type_id_with_cvr<decltype(xy2)>().pretty_name() << endl; */

	//tf(x); //实参中给的是x；  T=int，tmprv=int const &

	auto& xy3 = xy; //估计 xy3 = const int &,auto = const int。针对auto类型：引用会被丢弃，const属性会被保留。
	auto y = new auto(100); //估计：y = int *，auto = int *，auto可以用于new。
	const auto* xp = &x; //估计：xp = cont int *,auto = int
	auto* xp2 = &x; //估计：xp2 = int *,auto = int
	auto xp3 = &x; //估计：xp3 = int *，auto = int * ，xp3不声明为指针，也能推导出指针类型。
	
	auto&& wnyy0 = 222; //估计：万能引用，222是右值，auto = int,wnyy0 = int &&（右值引用类型）
	auto&& wnyy1 = x;   //估计：万能引用，x是左值，所以：auto  = int &，wnyy1 = int &。
	auto&& wnyy2 = x2;  //编译器推断：auto = int const &，wnyy2 = int const &。
	//tf(x2);




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
