#include <iostream>

using namespace std;

// Recursion ends with non-template
// overload
void print() {}

// Overloaded function
template<typename T, typename ... Types>
void print(T firstArg, Types ... args) {
    std::cout << firstArg << std::endl;
    print(args ...);
}

int main() {

    print("string", 3.14f, 23, 'c' );
    
    return EXIT_SUCCESS;
}
