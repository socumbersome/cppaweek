#include <iostream>

template<typename T>
concept AlwaysTrue = true;

template<typename T>
concept AlwaysFalse = false;

template<AlwaysTrue T>
int atfunc(T x) {
    return 42;
}
/* // equivalent declaration: (2)
template<typename T>
    requires AlwaysTrue<T>
int atfunc(T x);
*/

template<AlwaysFalse T>
int affunc(T x) {
    return 2;
}

 // (4)
int affunc(double x) {
    return 3;
}

struct MyType {
    int myfun() { return 3; }
};

int main() {
    std::cout << atfunc(3) << atfunc("abc") << atfunc(MyType{}) << std::endl; // (1)
    std::cout << affunc(2) << std::endl; // (3)
}
