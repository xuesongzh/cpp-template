
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

    T& operator*()  //返回迭代器所指向的元素，注意返回的类型是T&
    {
        return node->data;
    }

    mylist_iterator& operator++()  //重载前置++， 注意++在前，形如：++i;
    {
        node = node->next;  //指向了mylist容器中的下一个元素
        return *this;
    }

    mylist_iterator operator++(int)  //重载后置++，圆括号中多了个int，只是为了与前置++做区分，注意++在后面，形如i++
                                     //所以遍历的时候提倡用前置++（避免产生临时对象）
    {
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
    explicit mylist()  //默认构造函数
    {
        void* point = new char[sizeof(mylist_node<T>)];
        head = reinterpret_cast<mylist_node<T>*>(point);
        // head = new mylist_node<T>();

        head->next = head;
        head->prev = head;
    }
    ~mylist()  //析构函数
    {
        clear();  //注意位置，要放到delete (void *)head语句行之前
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

 public:
    void push_back(const T& tmpelem) {
        //创建一个待加入的节点
        mylist_node<T>* pnewnode = new mylist_node<T>(tmpelem);
        if (head->next == head) {  //等价于if(begin() == end())
            //当前容器为空
            pnewnode->next = head;
            pnewnode->prev = head;

            head->next = pnewnode;
            head->prev = pnewnode;
        } else {
            //当前容器不为空
            pnewnode->next = head;
            pnewnode->prev = head->prev;

            head->prev->next = pnewnode;
            head->prev = pnewnode;
        }
    }

 private:
    void clear() {
        if (head->next != head) {
            //当前容器不为空
            mylist_node<T>* currnode = head->next;  // currnode指向第一个节点
            while (currnode != head)                //指向的不是“特殊mylist_node对象节点”
            {
                mylist_node<T>* nextnode = currnode->next;  //指向当前节点后的节点（下一个节点）
                delete currnode;                            //释放当前节点所指向的内存
                currnode = nextnode;                        //让currnode指向下一个节点
            }
        }
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
    //（3）插入新元素
    //（4）释放容器中元素所占用的内存
    _nmsp1::mylist<_nmsp1::A> msgList;
    msgList.push_back(_nmsp1::A(2));
    msgList.push_back(_nmsp1::A(1));
    msgList.push_back(_nmsp1::A(3));
    for (_nmsp1::mylist<_nmsp1::A>::iterator pos = msgList.begin(); pos != msgList.end(); ++pos) {
        cout << (*pos).m_i << endl;
    }

    return 0;
}
