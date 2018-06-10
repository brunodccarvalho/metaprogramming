#include "physics/utf8_encoder.hpp"

namespace si {

namespace utf8 {

const char* const exponent_table[] {
  u8"\u2070",
  u8"\u00b9",
  u8"\u00b2",
  u8"\u00b3",
  u8"\u2074",
  u8"\u2075",
  u8"\u2076",
  u8"\u2077",
  u8"\u2078",
  u8"\u2079"
};

const char* const cdot = u8"\u00b7";

const char* const exponent_minus = u8"\u207b";

const char* const exponent_plus = u8"\u207a";

std::string exponent(int num, bool delete_one) {
  if (num == 0) return exponent_table[0];
  if (num == 1) {
    if (delete_one) return u8"";
    else return exponent_table[1];
  }

  bool is_negative = num < 0;
  if (is_negative) num = -num;

  std::string str;

  while (num > 0) {
    str = exponent_table[num % 10] + str;
    num /= 10;
  }

  if (is_negative) str = exponent_minus + str;

  return str;
}

std::string quantity(std::string symbol, int num) {
  return symbol + exponent(num);
}

} // utf8

} // si
