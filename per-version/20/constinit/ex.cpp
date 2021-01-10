#include <iostream>

constinit int x = 2 + 3; // (1)

int main() {
    // constinit int y = 3 + 4; // (2)
    constinit thread_local int z = 3 + 4; // (3)

    x++; z++; // (4)
    std::cout << x << "; " << z << std::endl;
}