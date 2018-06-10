#ifndef PHYSICS_UTF8_ENCODER_HPP___
#define PHYSICS_UTF8_ENCODER_HPP___

#include <string>

namespace si {

namespace utf8 {

extern const char* const exponent_table[10];

extern const char* const cdot;

extern const char* const exponent_minus;

extern const char* const exponent_plus;

std::string exponent(int num, bool delete_one = true);

std::string quantity(std::string spec, int num);

} // utf8

} // si

#endif // PHYSICS_UTF8_ENCODER_HPP___
