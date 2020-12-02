#include <iostream>
#include <numeric>
#include <execution>
#include <mutex>

int main() {
    std::vector<int> v{2,3,5,7,9,10,11,14};

    int sum = 0;
    std::mutex m;
    std::for_each(std::execution::par_unseq, std::begin(v), std::end(v),
        [&](int i) { // this can deadlock!
            std::lock_guard<std::mutex> lock{m};
            sum += i*i;
    });
}
