#include <iostream>
#include <type_traits>

using namespace std;


template<typename T>
struct is_int32 {
    static bool const value = false;
};

// Specialized template with 
// type integer
template<>
struct is_int32<int32_t> {
    static bool const value = true;
};

template<typename T1, typename T2>
struct are_same {
    static bool const value = false;
};

template<typename T1>
struct are_same<T1, T1>{
    static bool const value = true;
};

template<typename T1, typename T2>
constexpr bool are_same_v = is_same<T1, T2>::value;

// If the type is not a const
template<typename T>
struct remove_const_ {
    using type = T;
};

// If the type is a const type
// then alias it by removing
// const qualifier
template<typename T>
struct remove_const_ <T const>{
    using type = T;
};

//template<typename T>
//using remove_const__t = remove_const_<T>::type;

class Planet {};
class Mars : public Planet {};
class Sun {};


// lets alias int32
using INT32 = int32_t  ;
using FLT32 = float;

int main() {

    std::cout << is_int32<float>::value << std::endl;
    std::cout << is_int32<int>::value << std::endl;
    std::cout << is_int32<INT32>::value << std::endl;


    std::cout << are_same<float, float>::value << std::endl;
    std::cout << are_same_v<float, float> << std::endl;
    std::cout << are_same_v<double, float> << std::endl;
    std::cout << are_same_v<FLT32, float> << std::endl;


    std::cout << are_same_v<int, remove_const_<const int>::type> << std::endl ;
    std::cout << are_same_v<const int, remove_const_<const int>::type> << std::endl ;

    std::cout << "Planet <- Mars " << (std::is_base_of_v<Planet, Mars>)  << std::endl;
    std::cout << "Planet <- Sun " << (std::is_base_of_v<Planet, Sun>) << std::endl;

    return EXIT_SUCCESS;
}