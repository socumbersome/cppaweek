#include <cassert>
#include <iostream>
#include <string>

int main() {
    std::string s = "but I have heard it works even if you don't believe in it";
    s.replace(0, 4, "")
        .replace(
            s.find("even"), 4, "only"
        )
        .replace(s.find(" don't"), 6, "");
    
    std::cout << s << std::endl;
    assert(s == "I have heard it works only if you believe in it");
}
