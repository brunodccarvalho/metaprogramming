#ifndef PHYSICS_STREAM_HPP___
#define PHYSICS_STREAM_HPP___

#include "physics/physics.hpp"
#include "physics/utf8_encoder.hpp"

#include <iostream>

namespace si {

template <typename M, typename = detail::enable_if_unit_t<M>>
constexpr std::string quantity_to_string() {
  std::string str;

  for (int i = 0, j = 0; i < unit_dimensions; ++i) {
    if (M::get_dim(i) != 0) {
      if (j++ > 0) str += utf8::cdot;
      str += utf8::quantity(symbol_table[i], M::get_dim(i));
    }
  }

  return str;
}

template <typename M, typename = detail::enable_if_unit_t<M>>
std::string to_string(const M& num) {
  typename M::value_type tmp(num);
  return std::to_string(tmp) + " " + quantity_to_string<M>();
}

template <typename M, typename = detail::enable_if_unit_t<M>>
std::ostream& operator<<(std::ostream& out, const M& num) {
  typename M::value_type tmp(num);
  return out << tmp << " " << quantity_to_string<M>();
}

template <typename M, typename = detail::enable_if_unit_t<M>>
std::istream& operator>>(std::istream& in, M& num) {
  typename M::value_type tmp;
  in >> tmp;
  num = tmp;
  return in;
}

} // si

#endif // PHYSICS_STREAM_HPP___
