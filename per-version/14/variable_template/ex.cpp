#include <chrono>
#include <thread>
#include <iostream>

template<class T>
constexpr T pi = T(3.1415926535897932385L);  // variable template

template<class T>
T pi2 = T(3.1415926535897932385L);

template<class T>
T circular_area(T r) // function template
{
    return pi<T> * r * r; // pi<T> is a variable template instantiation
}

struct S {
    S(bool b) : b_(b) {}

    int maybe_expensive(int a) {
        std::cout << "Starting expensive computation; a = " << a << std::endl;
        if (b_) {
            std::cout << __FUNCTION__ << " is expensive" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        std::cout << "Finished expensive computation" << std::endl;
        return a*a;
    }

    bool b_;
};

template<class T>
int myvar = 1 + T(true).maybe_expensive(3);

int main() {
    std::cout << pi2<double> << std::endl;
    std::cout << pi2<int> << std::endl;
    std::cout << circular_area(pi<double>) << std::endl;
    std::cout << circular_area(pi<int>) << std::endl;
    std::cout << circular_area(pi<bool>) << std::endl;

    std::cout << "Will use myvar" << std::endl;
    std::cout << myvar<S> << std::endl;
    std::cout << myvar<S> << std::endl;
}
