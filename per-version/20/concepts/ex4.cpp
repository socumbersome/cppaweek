#include <string>
#include <set>

template<typename T, typename R>
concept NiceSearchableContainer = requires (T x, R z) {
    std::is_integral<T>::value;
    requires requires (R q) { // (1)
        q.find(z);
    };
    R::npos;
};

template<typename T, typename R>
requires NiceSearchableContainer<T, R>
bool foo(T x, R y) {
    return y.find("baz") != R::npos;
}

int main() {
    foo(1, std::string("bar")); // (2)
    foo(2, std::set<int>{3,4}); // (3)
}
