
#include <functional>
#include <iostream>

using namespace std;

namespace _nmsp1 {
void myfunc(int tmpvalue) {  //普通函数
    std::cout << "myfunc执行了：tmpvalue = " << tmpvalue << endl;
}

void callObjFunc(std::function<void(int)> cobj) {
    cobj(120);
}
}  // namespace _nmsp1

int main() {
    //第五节 std::function的实现
    //（1）讲述标准库中的std::function
    // std::function：是可调用对象包装器，是C++11新标准引入的类模板。接收各种可调用对象并进行实际的调用。
    //函数名（函数指针）、具有operator()成员函数的类对象、lambda表达式等等，都属于可调用对象。
    _nmsp1::callObjFunc(_nmsp1::myfunc);
    _nmsp1::callObjFunc([](int tmpvalue) {
        std::cout << "lambda表达式执行了，tmpvalue = " << tmpvalue << endl;
    });

    return 0;
}
