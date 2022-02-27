
#include <iostream>
#include <list>
#include <vector>

using namespace std;

namespace _nmsp1 {
//输出某个容器对应的迭代器种类的代码。
void _display_category(random_access_iterator_tag mytag) {
    cout << "random_access_iterator_tag" << endl;
}
void _display_category(bidirectional_iterator_tag mytag) {
    cout << "bidirectional_iterator_tag" << endl;
}
void _display_category(forward_iterator_tag mytag) {
    cout << "forward_iterator_tag" << endl;
}
void _display_category(output_iterator_tag mytag) {
    cout << "output_iterator_tag" << endl;
}
void _display_category(input_iterator_tag mytag) {
    cout << "input_iterator_tag" << endl;
}

template <typename T>
void display_category(T iter) {
    typename iterator_traits<T>::iterator_category cagy;  //萃取机
    _display_category(cagy);

    if (typeid(typename iterator_traits<T>::iterator_category) == typeid(random_access_iterator_tag)) {
        cout << "发现了某个容器的迭代器是random_access_iterator_tag类型" << endl;
    }
};

//-------------------------------

class _List_iterator {  // list容器对应的迭代器，是一个类或者类模板
 public:
    using iterator_category = bidirectional_iterator_tag;  //代表list容器的迭代器属于哪个种类的一个类型别名
                                                           //....
};
template <class T>
class list {
 public:
    using iterator = _List_iterator;
    //......
};

// list<int>::iterator::iterator_category  就代表着 bidirectional_iterator_tag

class _Vector_iterator {
 public:
    using iterator_category = random_access_iterator_tag;  //代表vector容器的迭代器属于哪个种类的一个类型别名
                                                           //....
};
template <class T>
class vector {
 public:
    using iterator = _Vector_iterator;
    //......
};

template <typename IterT>  // IterT是一个迭代器类型
struct iterator_traits {   //固定萃取类模板
    using iterator_category = typename IterT::iterator_category;
    //.....
};

}  // namespace _nmsp1

int main() {
    //（2）迭代器范例
    // 5类迭代器：
    // a)输出型迭代器：struct output_iterator_tag
    // b)输入型迭代器：struct input_iterator_tag
    // c)前向迭代器：struct forward_iterator_tag
    // d)双向迭代器：struct bidirectional_iterator_tag
    // e)随机访问迭代器：struct random_access_iterator_tag
    // vector容器-随机访问类型迭代器。
    // list容器-双向迭代器。
    //正确的区分某个容器对应的迭代器种类是显得特别重要的。

    // 实参创建了一个临时的_Vector_iterator类对象，此时display_category中的T被推断为_Vector_iterator类型
    // iterator_traits<_Vector_iterator>::iterator_category cagy;代码行等价于
    //_Vector_iterator::iterator_category cagy，最终等价于random_access_iterator_tag cagy
    _nmsp1::display_category(vector<int>::iterator());
    _nmsp1::display_category(list<int>::iterator());

    //本节帮助大家了解如何通过 固定萃取技术从容器中萃取出对应的迭代器种类。
    //（1）在容器中，标示出所属迭代器的种类
    //（2）fixed trait类模板 iterator_traits的实现

    // 固定萃取类模板iterator_traits：给进去迭代器的类型，萃取出迭代器的种类——给进去一种类型，萃取出另外一种类型。

    return 0;
}