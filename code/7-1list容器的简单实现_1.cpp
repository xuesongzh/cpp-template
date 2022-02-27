

#include <iostream>
#include <list>

using namespace std;

namespace _nmsp1 {
template <typename T>
struct mylist_node {
    //构造函数，根据容器中的实际的元素来构造一个myulist_node对象
    //为防止隐式转换导致隐含的错误，构造函数全部用explicit修饰
    explicit mylist_node(const T& x) : data(x), next(nullptr), prev(nullptr) {
    }

    mylist_node* next;
    mylist_node* prev;
    T data;
};

//---------------------
template <typename T>  // T代表的是容器中的元素类型
struct mylist_iterator {
    //为防止隐式转换导致隐含的错误，构造函数全部用explicit修饰
    explicit mylist_iterator() : node(nullptr) {}                         //默认构造函数
    explicit mylist_iterator(mylist_node<T>* tmpnode) : node(tmpnode) {}  //构造函数

    T& operator*() {  //返回迭代器所指向的元素，注意返回的类型是T&
        return node->data;
    }

    mylist_iterator& operator++() {  //重载前置++， 注意++在前，形如：++i;
        node = node->next;           //指向了mylist容器中的下一个元素
        return *this;
    }

    mylist_iterator operator++(int) {  //重载后置++，圆括号中多了个int，只是为了与前置++做区分，注意++在后面，形如i++
                                       //所以遍历的时候提倡用前置++（避免产生临时对象）
        mylist_iterator tmp(*this);
        node = node->next;  //也可以写成 ++*this，如果这样写，这里的++会调用重载的前置++
        return tmp;
    }

    bool operator!=(const mylist_iterator& tmpobj) {
        return node != tmpobj.node;
    }

    bool operator==(const mylist_iterator& tmpobj) {
        return node == tmpobj.node;
    }

    mylist_node<T>* node;  //定义指向容器中元素的指针
};

template <typename T>
class mylist {
 public:
    using iterator = mylist_iterator<T>;  //迭代器类型

 public:
    explicit mylist() {  //默认构造函数
        void* point = new char[sizeof(mylist_node<T>)];
        head = reinterpret_cast<mylist_node<T>*>(point);
        // head = new mylist_node<T>();

        head->next = head;
        head->prev = head;
    }

    ~mylist() {  //析构函数
        delete (void*)head;
        head = nullptr;
    }

 public:
    iterator begin() {
        return iterator(head->next);  //注意：head->next始终指向第一个元素
    }
    iterator end() {
        return iterator(head);
    }

 private:
    mylist_node<T>* head;
};

//----------------
class A {
 public:
    explicit A(int tmpi) : m_i(tmpi) {}
    int m_i;
};
}  // namespace _nmsp1

int main() {
    //第七章  STL标准模板库代码-list以及迭代器、find_if
    //第一节 list容器的简单实现
    //常用的容器: vector,list,map等：容纳同类型的多个元素
    std::list<int> msgList;
    msgList.push_back(1);   //末尾插入1，list容器中的内容：1
    msgList.push_front(2);  //开头插入2，list容器中的内容：2,1
    msgList.push_back(3);   //末尾插入3，list容器中的内容：2，1,3
    for (std::list<int>::iterator it = msgList.begin(); it != msgList.end(); ++it) {
        cout << *it << endl;
    }

    //（1）基础代码
    // mylist_node来描述节点，为mylist定义一个迭代器mylist_iterator
    //（2）插入新元素前的准备

    _nmsp1::mylist<_nmsp1::A> msgList;
    if (msgList.end() == msgList.begin()) {
        // msgList容器是空的
        cout << "msgList容器为空！" << endl;
    }

    return 0;
}
