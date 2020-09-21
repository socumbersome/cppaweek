#include <utility>

[[nodiscard]] int f() {
    return 2;
}

struct [[nodiscard]] A {
    A(int arg) : a(arg) {}
    int a;
};

A g() {
    return A(3);
}

std::pair<int, A> retpairwithA() {
    return {3, A(4)};
}

int main() {
    f(); // gives a warning
    int x = f();    
    
    g(); // gives a warning
    (void) g(); // no warning, explicitly discarding
    auto y = g();

    retpairwithA(); // no warning!
}
