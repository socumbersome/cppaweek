#include <iostream>
#include <future>

class Work {
private:
    int value;
public:
    Work() : value(42) {}
    Work(const Work& other) {
        std::cout << "copy constructing Work\n";
        value = other.value;
    }
    std::future<int> spawn() {
        return std::async( [=, *this]() -> int {
            return value;
        });
    }
};

std::future<int> foo() {
    Work tmp;
    return tmp.spawn();
}

int main() {
    std::future<int> f = foo();
    f.wait();
    std::cout << f.get() << std::endl;
}
