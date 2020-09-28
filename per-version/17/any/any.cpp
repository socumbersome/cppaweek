#include <any>
#include <iostream>
#include <typeinfo>

struct S {
    S(int x, double y) :
        x_(x), y_(y) {
        std::cout << "constructing " << this << std::endl;
    }

    S(const S& other) {
        std::cout << "copy constructing " << this << " from " << &other << std::endl;
        x_ = other.x_;
        y_ = other.y_;
    }

    ~S() { std::cout << "destructor of " << this << std::endl; }

    int x_;
    double y_;
};

int main() {
    int n = 3;
    std::any a = n;
    
    try {
        std::cout << std::any_cast<double>(a) << std::endl;
    } catch (std::bad_any_cast e) {
        std::cout << "Exception with `double`: " << e.what() << std::endl;
    }

    a = "hello"; // we can assign a value of totally different type
                 // to std::any, no problem at all
    try {
        std::cout << std::any_cast<char*>(a) << std::endl;
    } catch (std::bad_any_cast e) {
        std::cout << "Exception with `char*`: " << e.what() << std::endl;
    }

#if __cpp_rtti
    std::cout << "a's type is: " << a.type().name() << std::endl;
#else
    std::cout << "RTTI is disabled, thus `type` method not available" << std::endl;
#endif
    std::cout << std::any_cast<char const*>(a) << std::endl;
    
    S s = S(1, 2.3);
    std::cout << "assigning s to a" << std::endl;
    a = s;

    std::cout << "assigning a to a2" << std::endl;
    std::any a2 = a;
    
    S s2 = S(2, 3.4);
    std::cout << "assigning s2 to a" << std::endl;
    a = s2;

    std::cout << "\nmain end\n\n";
}
