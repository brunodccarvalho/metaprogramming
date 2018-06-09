#ifndef METAPROGRAMMING_STATIC_ARRAY_HPP
#define METAPROGRAMMING_STATIC_ARRAY_HPP

#include <cstddef> // std::size_t

template <typename T, std::size_t N>
constexpr std::size_t array_size(const T(&array)[N]) {
    char (&array_size_impl(const T(&array)[N]))[N];
    return sizeof(array_size_impl(array));
}

template <typename T, std::size_t R>
struct Tarray {
	// Data...
	T M[R];
  public:
  	// Option #1
};

#endif //METAPROGRAMMING_STATIC_ARRAY_HPP
