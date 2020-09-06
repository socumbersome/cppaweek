#include <new>
#include <iostream>

struct A {
    A() { std::cout << "A's constructor" << std::endl; }
    virtual int f();
};

struct B : A {
    B() { std::cout << "B's constructor" << std::endl; }
    virtual int f() {
        std::cout << "B's f" << std::endl;
        new (this) A; return 1;
    }
};

int A::f() {
    std::cout << "A's f" << std::endl;
    new (this) B; return 2;
}

int main() {
    std::cout << "1st phase" << std::endl;
    A a1;
    std::cout << "'a1' got stack allocated" << std::endl;
    int direct1 = a1.f();
    std::cout << "direct1 = " << direct1 << std::endl;
    int addrof1 = (&a1)->f();
    std::cout << "addrof1 = " << addrof1 << std::endl;
    int laundered1 = std::launder(&a1)->f();
    std::cout << "laundered1 = " << laundered1 << std::endl;

    std::cout << std::endl << "2nd phase" << std::endl;
    A a2;
    std::cout << "'a2' got stack allocated" << std::endl;
    for(int i = 1; i < 5; i++) {
        int launderedi = std::launder(&a2)->f();
        std::cout << "(" << i << " iter) launderedi = " << launderedi << std::endl;    
    }
}
