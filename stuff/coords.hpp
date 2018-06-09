#ifndef METAPROGRAMMING_COORDS_2_D_HPP
#define METAPROGRAMMING_COORDS_2_D_HPP

#include <functional>
#include <array>

void test_coords();

template <typename Q, std::size_t N>
class coords {
  private:
    std::array<Q, N> _coords;
  public:
    template <std::size_t D> coords(const Q(&coords)[D]);
    coords(const coords& other);
    coords(coords&& other) noexcept;
};

#endif //METAPROGRAMMING_COORDS_2_D_HPP
