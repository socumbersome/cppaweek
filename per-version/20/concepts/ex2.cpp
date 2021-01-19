#include <iostream>

template<typename T>
concept Fooable = requires (T x) {
    { x.foo() };
};

struct DoesFoo {
    void foo() { std::cout << "foo" << std::endl; }
};

struct DoesntFoo {
    void bar() { std::cout << "bar" << std::endl; }
};

template<Fooable T>
void willfoo(T x) {
    x.foo();
}

template<typename T>
concept HasFT = requires (T x) {
    typename T::Foo;
};

struct DoesHaveFT {
    struct Foo {
        void shout() { std::cout << "aaa!" << std::endl; }
    };
    Foo mem;
};

template<HasFT T>
void somef(T x) {
    typename T::Foo y = x.mem;
    y.shout();
}

int main() {
    willfoo(DoesFoo{}); // (1)
    // willfoo(DoesntFoo{}); // (2)
    somef(DoesHaveFT{});
}
