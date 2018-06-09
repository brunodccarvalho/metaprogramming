#include "coords.hpp"
#include "integrals.hpp"

template <typename Q, std::size_t N>
template <std::size_t D>
coords<Q,N>::coords(const Q(&coords)[D]) {
    static_assert(D == N, "Invalid Initialization of coords");
};
/*
template <typename Q, std::size_t N>
coords<Q,N>::coords(const coords<Q,N>& other):
    _coords(other._coords) {
    static_assert(other._coords.size() == N);
};

template <typename Q, std::size_t N>
coords<Q,N>::coords(coords<Q,N>&& other) noexcept:
    _coords(std::move(other._coords)) {
};
*/

static coords<int, 3> b({1,2,3});

void test_coords() {
    //coords<unsigned, 3> a({1,3,2});
}