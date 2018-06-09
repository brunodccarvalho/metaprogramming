#include "physics.hpp"
#include "physics_double.hpp"

#include <iostream>

using namespace si;
using namespace si::base;
using namespace si::literals;

void exercise() {
  length_t var = 0.1;
  length_t lol = 0.1_Zm;
  power_t<length_t, 3> var3 = lol * lol * lol;

  std::cout << var3 << std::endl;
  std::cout << length_dim<decltype(var3)> << std::endl;
}


int main() {
  exercise();
  return 0;
}
