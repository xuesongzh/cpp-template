
#include <iostream>

using namespace std;

namespace _nmsp1 {
// SumFixedTraits类模板
template <typename T>
struct SumFixedTraits;

template <>
struct SumFixedTraits<char> {
    using sumT = int;
    static sumT initValue() { return 0; }
};

template <>
struct SumFixedTraits<int> {
    using sumT = int64_t;
    static sumT initValue() { return 0; }
};

template <>
struct SumFixedTraits<double> {
    using sumT = double;
    static sumT initValue() { return 0.0; }
};
//----------------------
// funcsum函数模板
template <typename T, typename U = SumFixedTraits<T> >  // T = char ,U = SumFixedTraits<char>
auto funcsum(const T* begin, const T* end) {
    // using sumT = typename SumFixedTraits<T>::sumT;
    // sumT sum = SumFixedTraits<T>::initValue();
    typename U::sumT sum = U::initValue();  // typename SumFixedTraits<char>::sumT sum = SumFixedTraits<char>::initValue();
                                            // int sum = 0;

    for (;;) {
        sum += (*begin);
        if (begin == end)
            break;
        ++begin;
    }
    return sum;
}

}  // namespace _nmsp1

int main() {
    //第四节 将trait类模板用作模板参数
    // SumFixedTraits类模板，funcsum函数模板。
    char mychararray[] = "abc";
    cout << (int)(_nmsp1::funcsum(&mychararray[0], &mychararray[2])) << endl;
    cout << (int)(_nmsp1::funcsum<char, _nmsp1::SumFixedTraits<int> >(&mychararray[0], &mychararray[2])) << endl;

    return 0;
}
