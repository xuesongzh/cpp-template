
#include <iostream>
#include <list>
#include <vector>

using namespace std;

namespace _nmsp1 {

//泛化版本
template <typename T>
struct GetEleType;

//特化版本
template <typename T>
struct GetEleType<std::vector<T>> {
    using type = T;
};
template <typename T>
struct GetEleType<std::list<T>> {
    using type = T;
};

template <typename T, std::size_t N>  //这个特化版本增加了一个模板参数
struct GetEleType<T[N]> {             //萃取出数组元素个数
    using type = T;
    static const std::size_t size = N;
};

//泛化版本，用泛化版本实现对容器类型的支持
template <typename T>
struct GetEleType2 {
    using type = typename T::value_type;  //针对容器
};

//针对数组的特化版本（内容不变）
template <typename T, std::size_t N>
struct GetEleType2<T[N]> {
    using type = T;
    static const std::size_t size = N;
};

//别名模板
template <typename T>
using EleType = typename GetEleType2<T>::type;

//---------------
//函数模板
template <typename T>
void PrintEleType(const T& container) {
    // cout << "容器(数组)的元素类型为：" << typeid(GetEleType<T>::type).name() << endl;
    cout << "容器(数组)的元素类型为：" << typeid(EleType<T>).name() << endl;
}
}  // namespace _nmsp1

int main() {
    //（3）通过容器（数组）类型萃取元素类型范例
    //（3.1）用GetEleType类模板进行常规实现
    cout << "vector<double>的元素类型为：" << typeid(_nmsp1::GetEleType<vector<double>>::type).name() << endl;
    cout << "list<int>的元素类型为：" << typeid(_nmsp1::GetEleType<list<int>>::type).name() << endl;
    cout << "float[45]的元素类型为：" << typeid(_nmsp1::GetEleType<float[45]>::type).name() << endl;
    cout << "float[45]的数组元素数量为：" << _nmsp1::GetEleType<float[45]>::size << endl;

    //（3.2）引入函数模板PrintEleType
    vector<double> mydblvec;
    _nmsp1::PrintEleType(mydblvec);

    list<int> myintlist;
    _nmsp1::PrintEleType(myintlist);

    float myfloatarr[45];
    _nmsp1::PrintEleType(myfloatarr);

    //（3.2）GetEleType类模板的改进
    // template <class T>
    // struct vector
    //{
    //	.....
    //	using value_type = T:
    // };
    cout << "vector<double>的元素类型为：" << typeid(vector<double>::value_type).name() << endl;

    return 0;
}