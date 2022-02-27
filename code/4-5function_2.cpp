
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

//------------------------------------
//引入一个CFObjHandler类模板，作为可调用对象处理器。
//可调用对象处理器
template <typename T, typename... Args>
class CFObjHandler {
 public:
    virtual T invoke(Args... args) const {};  //虚函数，后续要创建子类
};

template <typename U, typename T, typename... Args>
class CFObjHandlerChild : public CFObjHandler<T, Args...> {
 public:
    //构造函数
    CFObjHandlerChild(U&& tmpfuncobj) : functor(std::forward<U>(tmpfuncobj))
    // CFObjHandlerChild(U tmpfuncobj) :functor(std::forward<U>(tmpfuncobj))
    // CFObjHandlerChild(U& tmpfuncobj) :functor(std::forward<U>(tmpfuncobj))
    {
    }

    virtual T invoke(Args... args) const {  //调用可调用对象
        return functor(std::forward<Args>(args)...);
    };

 private:
    U functor;  // U是一个可调用对象类型，functor用于保存可调用对象。
};

// CallFuncObj的类模板，实现std::function的功能。
//泛化版本(只进行了声明，是因为有特化版本必须得有泛化版本)
template <typename T>
class CallFuncObj;

//特化版本
template <typename T, typename... Args>
class CallFuncObj<T(Args...)> {
 public:
    //构造函数模板
    template <typename U>
    CallFuncObj(U&& acobj) {  //可以接收各种可调用对象（函数对象，lambda表达式等)
        // U的类型是void(&)(int);
        //比如名字叫做lambda_1——类类型。此时acobj的类型是右值引用类型。
        handler = new CFObjHandlerChild<U, T, Args...>(std::forward<U>(acobj));
    }
    //析构函数
    ~CallFuncObj() {
        delete handler;
    }

 public:
    //重载()，实现该类对象的可调用
    T operator()(Args... args) const {
        //使用了std::forward实现参数的完美转发，保持原始实参的佐治或者右值性。
        return handler->invoke(std::forward<Args>(args)...);
    }

 private:
    CFObjHandler<T, Args...>* handler;  //可调用对象处理器
};

void callObjFunc2(CallFuncObj<void(int)> cobj) {
    cobj(120);  //会调用CallFuncObj类模板的operator()成员函数
}

}  // namespace _nmsp1

int main() {
    //第五节 std::function的实现
    //（2）实现类似std::function的功能
    _nmsp1::callObjFunc2(_nmsp1::myfunc);
    _nmsp1::callObjFunc2([](int tmpvalue) {
        std::cout << "lambda表达式执行了，tmpvalue = " << tmpvalue << endl;
    });

    //要创建CallFuncObj<void(int)> 类型的对象，此时U的类型是void (&)(int);
    _nmsp1::CallFuncObj<void(int)> f1 = _nmsp1::myfunc;
    f1(1200);
    _nmsp1::CallFuncObj<void(int)> f2 = [](int tmpvalue) {
        std::cout << "lambda表达式执行了，tmpvalue = " << tmpvalue << endl;
    };
    f2(1200);

    auto ftest = [](int tmpvalue) {
        std::cout << "lambda表达式执行了，tmpvalue = " << tmpvalue << endl;
    };
    _nmsp1::CallFuncObj<void(int)> f3 = ftest;
    f3(1200);

    return 0;
}
