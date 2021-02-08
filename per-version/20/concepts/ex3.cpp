#include <type_traits>

template<typename A, typename B, typename C, typename D>
concept ThreeIntegralsAndSecondPointer =
    std::is_integral<A>::value && std::is_pointer<B>::value && 
    std::is_integral<C>::value && std::is_integral<D>::value;

template<typename T, typename R>
concept Conc = requires (T x, T y, R z) {
    {*z + (x - y) + 0.1f} -> ThreeIntegralsAndSecondPointer<R, T, T>; // (1)
};

template<typename T, typename R>
requires Conc<T, R>
void concf(T x, R y) {
    // blah blah
    return;
}

int main() {
    concf(2, new int(3));
}
