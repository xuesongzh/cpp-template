// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>
#include <vector>


//#include <boost/type_index.hpp>
using namespace std;
//#pragma warning(disable : 4996) 

namespace _nmsp1
{
	//role角色类，代表玩家，包括攻击力，防御力，血量（生命值）：
	//class role
	//{
	//public:
	//	//构造函数：
	//	role() :m_attack(0.0), m_defence(0.0), m_life(100.0) {}//初始时攻击力防御力都为0，血量100；
	//	role(double att,double def,double life):m_attack(att), m_defence(def), m_life(life) {} 

	//public:
	//	double m_attack; //攻击力
	//	double m_defence; //防御力
	//	double m_life;    //血量（生命值）
	//	//......
	//};
	//class family
	//{
	//public:
	//	vector<role> m_members;
	//	//....其他信息
	//};
	//怪物、NPC（非玩家角色）。 NPC分类：0：代表装饰游戏场景的这种NPC，1：代表商人，卖服装。2：代表把游戏任务派送给玩家。  自言自语的说话。
	//template<typename T>
	//class family
	//{
	//public:
	//	//vector<role> m_members;
	//	vector<T> m_members;
	//	//....其他信息
	//};

	//npc属性类
	struct npcattr
	{
		int m_sort; //npc种类：0：代表装饰游戏场景的这种NPC，1：代表商人，卖服装。2：代表把游戏任务派送给玩家。
		std::string m_lang; //记录自言自语的一句话
	};

	////NPC类
	//class role_npc :public role
	//{
	//public:
	//	//构造函数
	//	role_npc(): role(), m_strucattr{ 0,"" }{}
	//	role_npc(double att, double def, double life, int sort, std::string lang) :role(att, def, life), m_strucattr{ sort,lang } {}

	//public:
	//	npcattr m_strucattr;
	//};

	//玩家角色属性系统，分为三种：力量，敏捷，体质。玩家每升一级，就能得到10个属性点。可以把属性点加到这三种属性上去
	   //最终目的就是提高玩家攻击力，防御力，血量：每加一点力量，攻击力提高1.2，每加一点敏捷，防御力提高1.5。每加一点体质，血量增加0.6。
	//引入玩家属性类：
	struct playerattr
	{
		int m_strength; //力量
		int m_agile;  //敏捷
		int m_constitution; //体质
	};
	////玩家类(真实玩家）
	//class role_player :public role
	//{
	//public:
	//	role_player() : role(), m_strucattr{0,0,0}{}
	//	role_player(double att, double def, double life, int sth, int agi,int cons)
	//				:role(att, def, life), m_strucattr{ sth,agi,cons } {}

	//public:
	//	playerattr m_strucattr;
	//};
	
	template <typename...T>
	class role : public T... //把传入的模板参数当做该类模板的父类
	{
	public:
		role() : T()..., m_attack(0.0), m_defence(0.0), m_life(100.0) {}//初始时攻击力防御力都为0，血量100；
		role(double att, double def, double life) : T()..., m_attack(att), m_defence(def), m_life(life) {}
	public:
		double m_attack; //攻击力
		double m_defence; //防御力
		double m_life;    //血量（生命值）
	};

	template <typename...T>
	class family
	{
	public:
		vector< role<T...> > m_members;
		//....其他信息
	};

	using role_npc = role<npcattr>;
	using role_player = role<playerattr>;
	using role_mixnpc = role<npcattr,playerattr>; //通过混入技术方便的组合，自由的装配各种功能

	using family_npc = family<npcattr>;


}
namespace _nmsp2
{
	template <typename ... T>
	class Base :public T...
	{
	public:
		void myfunc()
		{
			cout << "Base::myfunc()执行了!" << endl;
		}
	};

	template <typename ... T>
	class Derived :public Base<T...>
	{
	public:
		void myfunc() //virtual
		{
			cout << "Derived::myfunc()执行了!" << endl;
		}
	};

	class A
	{
	};
	class AVir
	{
	public:
		virtual void myfunc() {}
	};
}
namespace _nmsp3
{
	class A
	{
	protected:
		~A() {}
	};
	class B :public A {};
}

int main()
{
	//第六节 模板的一些特殊继承关系说
	//（2）混入（Mixins）：是一种编程手法,用于描述类与类之间的一种关系。这种关系类似于多重继承，看起来更象颠倒过来的继承。
	    //混入的实现手段：把传入的模板参数当做该类模板的父类。
	//（2.1）常规范例
	  //引入混入手段取代传统的继承，这种混入实现手段看起来更像是把某个或者某些类混合到当前类中凑成 一个更大的类 
	  //role_npc的效果类似于：class role_npc :public role,public npcattr{...}

	//（2.2）用参数化的方式表达成员函数的虚拟性:是一种设计理念，体现一种开发智慧。
	//一般来说，一个类如果做父类，那么它应该有析构函数并且这个析构函数都应该是一个虚函数。
	 //什么情况下父类中可以没有析构函数或者析构函数可以不为虚函数：
	   //(1)子类并没有析构函数（不需要在析构函数中释放任何new出来的数据）。
	   //(2)代码中不会出现父类指针指向子类对象（多态）的情形。

	//为防止用父类指针new一个子类对象，可以把父类的析构函数用protected来修饰。
	//有兴趣的同学：可以参考Boost库中的noncopyable类。




	   


	/*
	_nmsp1::role_npc mynpc;
	mynpc.m_attack = 15; //攻击
	mynpc.m_defence = 10; //防御
	mynpc.m_life = 120; //血量
	mynpc.m_sort = 1; //npc种类
	mynpc.m_lang = "Are You OK?"; //NPC自言自语时玩家能看到的所说的话


	_nmsp1::family_npc myfamily;
	myfamily.m_members.push_back(mynpc);*/

	/*

	_nmsp2::Base<_nmsp2::A> *pb1 = new _nmsp2::Derived<_nmsp2::A>; //父类指针指向子类对象
	pb1->myfunc(); //Base::myfunc()执行了!


	_nmsp2::Base<_nmsp2::AVir>* pb2 = new _nmsp2::Derived<_nmsp2::AVir>; //父类指针指向子类对象
	pb2->myfunc();  //Derived::myfunc()执行了!*/

	//_nmsp3::A* pa = new _nmsp3::B();
	//delete pa; //编译出错
	//
	

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
