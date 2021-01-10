#include <iostream>

int f();  // forward declaration

constexpr int g(long a, int iter) {
    for(int i = 0; i < iter; i++) {
        a += i;
    }
    if (!std::is_constant_evaluated()) {
        a = 2;
    }
    return a;
}

int x = f();

//int y = g(5, 10); // (1)
//int y = g(5, 1000000); // (2)
//constinit int y = g(5, 10); // (3)
constinit int y = g(5, 1000000); // (4)

int f()
{
    std::cout << "in f(): y = " << y << std::endl;
    return 3*y + 7;
}

int main() {
    std::cout << "in main(): x = " << x << ", y = " << y << std::endl;
}