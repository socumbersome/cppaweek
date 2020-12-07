#include <iostream>

int main() {
    auto alambda = [](auto a, int b) {
        std::cout << "a: " << a << std::endl;
        return b + 1;
    };
    auto ret1 = alambda(2,3);
    auto ret2 = alambda("word", 4);

    auto tlambda = []<typename T>(T a, int b) {
        std::cout << "a: " << a << std::endl;
        return b + 1;
    };

    auto ret3 = tlambda(2,3);
    auto ret4 = tlambda("word", 4);
}
