#ifndef __CA_H__
#define __CA_H__

template <typename T>
void myfunc(T v1, T v2) {
    std::cout << v1 + v2 << std::endl;
}

//类模板A声明
template <typename C>
class A {
 public:
    template <typename T2>
    A(T2 v1, T2 v2);  //构造函数模板

    template <typename T>
    void myft(T tmpt) {
        std::cout << tmpt << std::endl;
    }

 public:
    void myfuncpt() {
        std::cout << "myfuncpt()执行了" << std::endl;
    }

    C m_ic;
};

//类模板A实现
template <typename C>
template <typename T2>
A<C>::A(T2 v1, T2 v2) {
    std::cout << v1 << v2 << std::endl;
}

#endif
