#include "physics/double/common.hpp"
#include "physics/string.hpp"

#include <cassert>

using namespace si::literals;

auto execute() {
  si::length mile = 1.609344_km;
  si::area square_mile = mile * mile;

  std::cout << square_mile << std::endl;

  assert(mile > 1_km);

  si::time nano = 3_ns;
  si::speed fast = mile / nano;

  std::cout << fast << std::endl;

  si::acceleration acc = mile / si::pow<2>(nano);
  std::cout << fast * acc << std::endl;

  si::capacitance cap = 75.65;
  std::cout << cap << std::endl;

  si::dunit<18,43,51,768,-12309,-500,1040> something = 150;
  std::cout << something << std::endl;

  nano = something.from();
  std::cout << nano << std::endl;

  auto length4 = square_mile * 7_m * 1_m + mile * 8_m * mile * mile;
  std::cout << length4 << std::endl;

  auto also4 = 7 * square_mile * 7 + mile * 8 * mile;
  std::cout << also4 << std::endl;

  si::scalar a = 7;
  a = a + 3;

  std::cout << a << std::endl;
  std::cout << mile + 1000 << std::endl;
  //assert(nano < fast);
}


int main() {
  execute();
  return 0;
}
