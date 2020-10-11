#include <iostream>
#include <vector>

class T {
    std::vector<int> data_;
public:
    T(std::vector<int> data) : data_(data) {}
    std::vector<int>& items() { return data_; }
};

T foo() {
    std::vector<int> v{2,3,7};
    return T(v);
}

int main() {
    std::cout << "Without init statement: " << std::endl;
    for (auto& x : foo().items()) {
        std::cout << "element " << x << std::endl;
    }

    std::cout << "\nWith init statement (1): " << std::endl;
    for (auto t = foo(); auto& x : t.items()) {
        std::cout << "element " << x << std::endl;
    }

    std::cout << "\nWith init statement (2): " << std::endl;
    for (auto& its = foo().items(); auto& x : its) {
        std::cout << "element " << x << std::endl;
    }

    std::cout << "\n(2) desugared: " << std::endl;
    {
        auto& its = foo().items();
        auto&& _range = its;
        auto _begin = _range.begin();
        auto _end = _range.end();
        for( ; _begin != _end; ++_begin) {
            auto& x = *_begin;
            std::cout << "element " << x << std::endl;
        }
    }

    std::cout << "\n(1) desugared: " << std::endl;
    {
        auto t = foo();
        auto&& _range = t.items();
        auto _begin = _range.begin();
        auto _end = _range.end();
        for( ; _begin != _end; ++_begin) {
            auto& x = *_begin;
            std::cout << "element " << x << std::endl;
        }
    }
}
