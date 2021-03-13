#include <iostream>
#include <vector>
#include <string>
#include <span>

template<typename T>
void every_second(std::span<T> s) {
    for(bool skip = false; auto& elem : s) {
        if(!skip) {
            std::cout << elem;
        }
        skip = !skip;
    }
    std::cout << " - processed" << std::endl;
}

int main() {
    int buffer[5] = {1,2,3,4,5};
    int buffer2[] = {6,7,8,9,10,11};
    char* buffer3 = new char[3];
    buffer3[0] = 'c'; buffer3[1] = 'a'; buffer3[2] = 't';
    std::vector<int> v{2,3,5,7};
    std::string s{"interesting"};
    std::vector<std::string> vs{{"cat", "does", "moew"}};
    
    every_second<int>(buffer);
    every_second<int>(buffer2);
    every_second<char>({buffer3, 3});
    // every_second<char>({buffer3, 42}); // oops, compiles!
    every_second<int>(v);
    every_second<char>(s);
    every_second<std::string>(vs);
}
