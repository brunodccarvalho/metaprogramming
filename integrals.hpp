//
// Created by elbru on 25/04/2018.
//

#ifndef METAPROGRAMMING_INTEGRALS_HPP
#define METAPROGRAMMING_INTEGRALS_HPP

#include <cstddef>

namespace integrals {
/**
 * @UTILITY array_size (lol)
 * source: https://stackoverflow.com/questions/1500363/compile-time-sizeof-array-without-using-a-macro
 */
template <typename T, std::size_t N>
constexpr std::size_t array_size(const T(&array)[N]) {
    char (&array_size_impl(const T(&array)[N]))[N];
    return sizeof(array_size_impl(array));
}



}

#endif //METAPROGRAMMING_INTEGRALS_HPP
