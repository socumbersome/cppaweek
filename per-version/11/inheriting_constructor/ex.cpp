#include <iostream>

class A {
public:
    A(int a = 2) : x_{a} {
        std::cout << "A's `int` ctor, a = " << a << std::endl;
    }
    A(double d) : x_{d} {
        std::cout << "A's `double` ctor, d = " << d << std::endl;
    }

    virtual void print() {
        std::cout << "A's print: " << x_ << std::endl;
    }
protected:
    int x_;
};

class B : A {
public:
    using A::A; // inheriting constructors from A
    
    B(double d) : A{d}, y_{d + 1} {
        std::cout << "B's `double` ctor, d = " << d << std::endl;
    }

    virtual void print() override {
        std::cout << "B's print: " << x_ << ", " << y_ << std::endl;
    }
protected:
    double y_;
};

class NoDefaultCtor {
public:
    NoDefaultCtor() = delete;
    NoDefaultCtor(int a) : a_{a} {}

    int a_;
};

class C : A {
public:
    using A::A; // inheriting constructors from A
    
    virtual void print() override {
        std::cout << "C's print: " << x_ << ", and some ndc..." << std::endl;
    }
protected:
    NoDefaultCtor ndc;
};

int main() {
    auto a1 = A();
    a1.print();
    auto a2 = A(3.14);
    a2.print();
    std::cout << "Now B's" << std::endl;
    auto b1 = B(3);
    b1.print();
    auto b2 = B(3.14);
    b2.print();
    
    // below gives a compile time error
    // auto c1 = C(2);
}
