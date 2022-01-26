#include <iostream>
#include <array>

using namespace std;


template<typename T, unsigned int N>
class Buffer {
public:
    Buffer(std::array<T, N> content) : content_(content){}
private:
    std::array<T, N> content_;
};

int main() {

    // specialized with 8 bit character
    Buffer<char, 4> b_char8{{'I','E','S','E'}};
    // specialized with 16 bit character
    Buffer<char16_t, 4> b_char16{{'I','E','S','E'}};

    return EXIT_SUCCESS;
}
