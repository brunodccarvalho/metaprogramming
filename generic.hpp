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
 * @UTILITY pop_front (easy), pop_back (hard)
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
          typename... S>
struct pop_back<C<S...>> {
    using type = reverse_t<pop_front_t<reverse_t<C<S...>>>>; // Ar, I'm a pirate!
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
          typename... S>
struct back<C<S...>> {
    using type = front_t<reverse_t<C<S...>>>;
};

template <typename C>
using back_t = typename back<C>::type;



/**
 * @UTILITY instance (average)
 */
template <typename...>
struct instance;

template <template <typename...> typename C,
          typename... S, template <typename...> typename Target>
struct instance<C<S...>, Target<>> {
    using type = Target<S...>;
};

template <typename C, template <typename...> typename Target>
using instance_t = typename instance<C, Target<>>::type;



/**
 * @UTILITY global filter (average)
 * include_if, exclude_if, b_include_if, b_exclude_if
 */
template <template <typename...> typename C,
          template <typename...> typename P, typename... Args>
using include_if_t = std::conditional_t<P<Args...>::value, C<Args...>, C<>>;

template <template <typename...> typename C,
          template <typename...> typename P, typename... Args>
using exclude_if_t = std::conditional_t<P<Args...>::value, C<>, C<Args...>>;

template <template <typename...> typename C, typename B,
          template <typename...> typename P, typename... Args>
using b_include_if_t = std::conditional_t<P<B, Args...>::value, C<Args...>, C<>>;

template <template <typename...> typename C, typename B,
          template <typename...> typename P, typename... Args>
using b_exclude_if_t = std::conditional_t<P<B, Args...>::value, C<>, C<Args...>>;



/**
 * @UTILITY foreach filter (easy)
 * include_each, exclude_each, b_include_each, b_exclude_each
 */
template <template <typename...> typename C,
template <typename...> typename P, typename... Args>
using include_each_t = join_t<include_if_t<C, P, Args>...>;

template <template <typename...> typename C,
template <typename...> typename P, typename... Args>
using exclude_each_t = join_t<exclude_if_t<C, P, Args>...>;

template <template <typename...> typename C, typename B,
template <typename...> typename P, typename... Args>
using b_include_each_t = join_t<b_include_if_t<C, B, P, Args>...>;

template <template <typename...> typename C, typename B,
template <typename...> typename P, typename... Args>
using b_exclude_each_t = join_t<b_exclude_if_t<C, B, P, Args>...>;



/**
 * @SPECIALIZATION common filters (average)
 */
template <template <typename...> typename C, typename... Args>
using exclude_void_t = exclude_each_t<C, std::is_void, Args...>;

template <template <typename...> typename C, typename... Args>
using exclude_empty_t = exclude_each_t<C, std::is_empty, Args...>;

template <template <typename...> typename C, typename B, typename... Args>
using include_subclass_t = b_include_each_t<C, B, std::is_base_of, Args...>;

template <template <typename...> typename C, typename B, typename... Args>
using exclude_subclass_t = b_exclude_each_t<C, B, std::is_base_of, Args...>;








}
using namespace type_manip;
#endif //METAPROGRAMMING_GENERIC_HPP
