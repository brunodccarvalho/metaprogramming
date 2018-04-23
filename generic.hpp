//
// Created by elbru on 23/04/2018.
//

#ifndef METAPROGRAMMING_GENERIC_HPP
#define METAPROGRAMMING_GENERIC_HPP

// A collection of TMP challenges.

namespace type_manip {
/**
 * @UTILITY join (average)
 */
template <typename...>
struct join;

template <template <typename...> typename C,
          typename... As, typename... Bs>
struct join<C<As...>, C<Bs...>> {
    using type = C<As..., Bs...>;
};

template <template <typename...> typename C,
          typename... As, typename... Bs, typename... R>
struct join<C<As...>, C<Bs...>, R...> {
    using type = typename join<C<As..., Bs...>, R...>::type;
};

/*
template <template <typename...> typename T, typename... Ts>
struct join<T<Ts>...> {
    using type = T<Ts...>;
};
*/

template <typename... Cs>
using join_t = typename join<Cs...>::type;


/**
 * @UTILITY reverse (hard)
 */
template <typename...>
struct reverse;

template <typename...>
struct reverse_impl;

template <template <typename...> typename C,
          typename F, typename... R, typename... S>
struct reverse_impl<C<S...>, F, R...> {
    using type = typename reverse_impl<C<F, S...>, R...>::type;
};

template <template <typename...> typename C, typename... S>
struct reverse_impl<C<S...>> {
    using type = C<S...>;
};

template <template <typename...> typename C, typename... S>
struct reverse<C<S...>> {
    using type = typename reverse_impl<C<>, S...>::type;
};

template <typename C>
using reverse_t = typename reverse<C>::type;



/**
 * @UTILITY push_front, push_back (easy)
 */
template <typename...>
struct push_front;

template <template <typename...> typename C,
typename... R, typename... S>
struct push_front<C<S...>, R...> {
    using type = C<R..., S...>;
};

template <typename C, typename... R>
using push_front_t = typename push_front<C, R...>::type;

template <typename...>
struct push_back;

template <template <typename...> typename C,
          typename... R, typename... S>
struct push_back<C<S...>, R...> {
    using type = C<S..., R...>;
};

template <typename C, typename... R>
using push_back_t = typename push_back<C, R...>::type;



/**
 * @UTILITY pop_front, pop_back (easy)
 */
template <typename...>
struct pop_front;

template <template <typename...> typename C,
typename F, typename... S>
struct pop_front<C<F, S...>> {
    using type = C<S...>;
};

template <typename C>
using pop_front_t = typename pop_front<C>::type;

template <typename...>
struct pop_back;

template <template <typename...> typename C,
typename L, typename... S>
struct pop_back<C<S..., L>> {
    using type = C<S...>;
};

template <typename C>
using pop_back_t = typename pop_back<C>::type;



/**
 * @ACCESS front, back (easy)
 */
template <typename...>
struct front;

template <template <typename...> typename C,
          typename F, typename... S>
struct front<C<F, S...>> {
    using type = F;
};

template <typename C>
using front_t = typename front<C>::type;

template <typename...>
struct back;

template <template <typename...> typename C,
          typename B, typename... S>
struct back<C<S..., B>> {
    using type = B;
};

template <typename C>
using back_t = typename back<C>::type;









}
using namespace type_manip;
#endif //METAPROGRAMMING_GENERIC_HPP
