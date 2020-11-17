#include <iostream>
#include <vector>
#include <functional>


template<typename Item, typename ItemTransformed,
template <typename> typename Container>
using Mapper = std::function<Container<ItemTransformed>
    (Container<Item>, std::function<Item(ItemTransformed)>)
>;


int main() {
    Mapper<char, int, std::vector> const mapper =
    [](auto v, auto f) {
        std::vector<int> res;
        res.reserve(v.size());
        std::transform(v.begin(), v.end(),
            std::back_inserter(res), f);
        return res;
    };

    std::vector<char> vc{'a', 'b', 'c'};
    auto vi = mapper(vc, [](char c) { return c - 'a'; });

    for(auto i : vi) {
        std::cout << i << std::endl;
    }

    for(typedef int SoInt; SoInt i : vi) {
        std::cout << i << std::endl;
    }
/*
    for(using SoInty = int; SoInty i : vi) {
        std::cout << i << std::endl;
    }
*/
}
