#include "physics/double/common.hpp"
#include "physics/string.hpp"

#include <cassert>

using namespace si::literals;

auto execute() {
  si::length mile = 1.609344_km;
  si::area square_mile = mile * mile;

  assert(mile > 1_km);

  si::time nano = 3_ns;
  si::speed fast = mile / nano;
  si::acceleration acc = mile / si::pow<2>(nano);

  return fast * acc;
}


int main() {
  std::cout << execute() << std::endl;
  return 0;
}
