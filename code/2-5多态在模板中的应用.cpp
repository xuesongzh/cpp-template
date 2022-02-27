
#include <iostream>

using namespace std;

namespace _nmsp1 {
//多态
//人类
class Human {
 public:
    virtual void eat() {
        cout << "人类以吃米饭和面食为主!" << endl;
    }
    virtual ~Human() {}  //作为父类时一般应该有一个虚析构函数
};

//男人
class Men : public Human {
 public:
    virtual void eat() {
        cout << "男人喜欢吃面食!" << endl;
    }
};

//女人
class Women : public Human {
 public:
    virtual void eat() {
        cout << "女人喜欢吃米饭!" << endl;
    }
};

}  // namespace _nmsp1

namespace _nmsp2 {
//模板中的多态不需要父类
//男人
class Men {
 public:
    void eat() {
        cout << "男人喜欢吃面食!" << endl;
    }
};

//女人
class Women {
 public:
    void eat() {
        cout << "女人喜欢吃米饭!" << endl;
    }
};

//函数模板
template <typename T>
void eatTmpl(T& obj) {
    obj.eat();
}

}  // namespace _nmsp2

int main() {
    //第五节 多态在模板中的应用
    //从表现形式上 回顾一下 多态的概念
    //(1)有父类有子类（有继承关系），父类中必须含有虚函数，子类重写父类中的虚函数。
    //(2)父类指针指向子类对象或者父类引用绑定（指向）子类对象。
    //(3)当以父类的指针或者引用调用子类中重写了的虚函数时，就能看出多态的表现来了，因为调用的是子类的虚函数。
    _nmsp1::Men objmen;
    _nmsp1::Women objwomen;

    //父类引用指向子类对象，以表现多态
    _nmsp1::Human& yinbase1 = objmen;
    _nmsp1::Human& yinbase2 = objwomen;
    yinbase1.eat();  //男人喜欢吃面食!
    yinbase2.eat();  //女人喜欢吃米饭!

    //模板中的多态，并不需要用到父类以及继承的概念，子类也不需要虚函数(压根就不存在父类指针指向子类对象或者父类引用绑定子类对象这种概念)
    //编译期间内，编译器会实例化出eatTmpl<Men>和eatTmpl<Women>这两个函数。
    _nmsp2::Men objmen;
    _nmsp2::Women objwomen;

    _nmsp2::eatTmpl(objmen);    //男人喜欢吃面食!
    _nmsp2::eatTmpl(objwomen);  //女人喜欢吃米饭!

    //总结：
    //传统多态：也叫动态多态（运行时多态），因为要访问虚函数表指针，所以对执行期间的性能多少会有一些影响。
    //模板多态：也叫静态多态，编译期间就确定了具体调用谁，就不存在执行期间的性能问题
    //只要支持相同的语法，就允许不同类型的对象以同样的方式被操纵——都有eat成员函数，那么就允许调用该成员函数，因为这是在编译期间完成的多态。

    return 0;
}
