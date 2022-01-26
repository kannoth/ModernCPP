#include <iostream>

// Simple compile time 
// example 
template<int N>
void simple_loop() {

    // Your computation
    std::cout << N << std::endl;

    // Recursive call 
    if constexpr (N > 0) {
        simple_loop<N - 1>();
    }
}

// Compile time foreach
// with index
template <size_t Max>
struct for_each_ {
  template <size_t Index>
  static void work() {

    // Your computation
    std::cout << Index << std::endl;

    // Recursive call
    if constexpr (Index +1 < Max) 
        for_each_<Max>::work<Index + 1>();

  }
};

int main () {
  for_each_<100>::work<0>();
  simple_loop<10>();
  return 0;
}