#include <iostream>
#include <type_traits>

using namespace std;

template <typename T>
class arith_1 {
public:
    // Asserts at complie time and shows the message if fails
    static_assert(
        std::is_same<T, int>::value || std::is_same<T, float>::value, 
        "Type not allowed"
    );

    static T sum(T v_1, T v_2) {
        return v_1 + v_2;
    }

    static T mult(T v_1, T v_2) {
        return v_1 * v_2;
    }
};

// Subsutituion fails
template<typename T, typename Enable = void>
class arith_2 {};

/// This specialization is only enabled for double or float.
template<typename T>
class arith_2<T, typename std::enable_if<std::is_same<T, int>::value || std::is_same<T, float>::value>::type> {
public:
    static T sum(T v_1, T v_2) {
        return v_1 + v_2;
    }

    static T mult(T v_1, T v_2) {
        return v_1 * v_2;
    }
};

int main()
{

    std::cout << arith_1<double>::sum(3, 4) << std::endl;

    return EXIT_SUCCESS;
}