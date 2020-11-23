#include <vector>
#include <iostream>

template<class Reactor>
class Foo {
public:
    std::vector<int> v;
    [[no_unique_address]] Reactor reactor_;

    void add(int i) {
        v.push_back(i);
        reactor_(i);
    }
};

template<class Reactor>
class Bar { // differs from Foo only with not having `no_unique_address`
public:
    std::vector<int> v;
    Reactor reactor_;

    void add(int i) {
        v.push_back(i);
        reactor_(i);
    }
};


class Logger {
public:
    void operator() (int a) {
        std::cout << "Logger: " << a << std::endl;
    }
};

class StatefulLogger {
    size_t i_ = 0;
public:
    void operator() (int a) {
        i_++;
        std::cout << "StatefulLogger: " << a << " (" << i_ << " item)" << std::endl;
    }
};

int main() {
    Foo<Logger> foo1;
    foo1.add(2); foo1.add(4);
    Foo<StatefulLogger> foo2;
    foo2.add(2); foo2.add(4);
    Bar<Logger> bar;

    std::cout << "Addresses (of members as well):" << std::endl;
    std::cout << "foo1: " << &foo1 << "; " << &foo1.v << "; " << &foo1.reactor_ << std::endl; 
    std::cout << "foo2: " << &foo2 << "; " << &foo2.v << "; " << &foo2.reactor_ << std::endl;
    std::vector<int> v;

    std::cout << "Sizes of objects:" << std::endl;
    std::cout << "foo1: " << sizeof(foo1) << "; foo2: " << sizeof(foo2) 
        << "; bar: " << sizeof(bar) << " (vector<int> size = "
        << sizeof(v) << ")" << std::endl;

    std::cout << "Sizes of types:" << std::endl;
    std::cout << sizeof(Logger) << "; " << sizeof(StatefulLogger)
        << "; " << sizeof(Foo<Logger>) << "; " << sizeof(Foo<StatefulLogger>) << std::endl;

    auto reactoradr = &foo1.reactor_;
    auto fooadr = &foo1;
    std::cout << "reactoradr " << reactoradr << " ; fooadr " << fooadr << std::endl;
    reactoradr->operator()(7);
    // fooadr->operator()(8); // compile-time error
}
