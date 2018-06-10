#ifndef COMPILE_STRINGIFY_HPP___
#define COMPILE_STRINGIFY_HPP___

// Failed attempt to write a compile time
// stringify method for ints.

#include <type_traits>
#include <utility>

namespace stringify {

namespace detail {

template <typename...>
struct type_join;

template <template <typename...> typename C,
          typename... As, typename... Bs, typename... R>
struct type_join<C<As...>, C<Bs...>, R...> {
  using type = typename type_join<C<As..., Bs...>, R...>::type;
};

template <template <typename...> typename C,
          typename... S>
struct type_join<C<S...>> {
  using type = C<S...>;
};

template <typename... Cs>
using type_join_t = typename type_join<Cs...>::type;





template <typename V, typename...>
struct value_join;

template <typename V, template <V...> typename C,
          V... As, V... Bs, typename... R>
struct value_join<V, C<As...>, C<Bs...>, R...> {
  using type = typename value_join<C<As..., Bs...>, R...>::type;
  using value_type = V;
};

template <typename V, template <V...> typename C,
          V... S>
struct value_join<V, C<S...>> {
  using type = C<S...>;
  using value_type = V;
};

template <typename V, typename... C>
using value_join_t = typename value_join<V, C...>::type;





template <typename V, V... S>
struct array_of {
  using value_type = V;
  static constexpr std::size_t num = 1 + sizeof...(S);
  static constexpr V array[] { S..., 0 };
  static constexpr V get(std::size_t n) {
    return array[n];
  }
  static constexpr const V* get() {
    return array;
  }
};





template <typename V, typename... C>
struct array_concat;

template <typename V, template <typename, V...> typename C,
          V... As, V... Bs, typename... R>
struct array_concat<V, C<V, As...>, C<V, Bs...>, R...>
  : array_concat<V, C<V, As..., Bs...>, R...> {};

template <typename V, template <typename, V...> typename C,
          V... S>
struct array_concat<V, C<V, S...>> : C<V, S...> {};





template <typename V, V* Ps, typename C>
struct array_spread_impl;

template <typename V, V* Ps,
          template <typename, std::size_t...> typename C,
          typename Q, std::size_t... Is>
struct array_spread_impl<V, Ps, C<Q, Is...>>
  : array_of<V, Ps[Is]...> {};

template <typename V, V* Ps, std::size_t N>
struct array_spread
  : array_spread_impl<V, Ps, std::make_index_sequence<N>> {};

} // detail



template <int I, bool test = (I <= 0)>
struct int_stringify;

template <>
struct int_stringify<0, false> : detail::array_of<char> {};

template <>
struct int_stringify<0, true> : detail::array_of<char, '0'> {};

template <int I>
struct int_stringify<I, true> : int_stringify<-I, false> {};

template <int I>
struct int_stringify<I, false>
  : detail::array_concat<char,
                 int_stringify<I / 10, false>, // We cannot recurse? :(
                 detail::array_of<char, '0' + (I % 10)>
                > {};

} // stringify

#endif // COMPILE_STRINGIFY_HPP___
