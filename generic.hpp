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
          typename... S>
struct join<C<S...>> {
    using type = C<S...>;
};

template <template <typename...> typename C,
          typename... As, typename... Bs, typename... R>
struct join<C<As...>, C<Bs...>, R...> {
    using type = typename join<C<As..., Bs...>, R...>::type;
};

template <typename... Cs>
using join_t = typename join<Cs...>::type;





/**
 * @UTILITY reverse (average)
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
 * @UTILITY instance (easy)
 */
template <template <typename...> typename N, typename...>
struct instance;

template <template <typename...> typename N,
          template <typename...> typename C, typename... S>
struct instance<N, C<S...>> {
    using type = N<S...>;
};

template <typename C, template <typename...> typename N>
using instance_t = typename instance<N, C>::type;





/**
 * @UTILITY global filter (average)
 * include_if, exclude_if, b_include_if, b_exclude_if
 */
template <template <typename...> typename P, typename...>
struct include_if;

template <template <typename...> typename P,
          template <typename...> typename C, typename... S>
struct include_if<P, C<S...>> {
    using type = std::conditional_t<P<S...>::value, C<S...>, C<>>;
};

template <template <typename...> typename P, typename...>
struct exclude_if;

template <template <typename...> typename P,
template <typename...> typename C, typename... S>
struct exclude_if<P, C<S...>> {
    using type = std::conditional_t<P<S...>::value, C<>, C<S...>>;
};

template <template <typename...> typename P, typename...>
struct b_include_if;

template <template <typename...> typename P, typename... B,
          template <typename...> typename C, typename... S>
struct b_include_if<P, C<S...>, B...> {
    using type = std::conditional_t<P<B..., S...>::value, C<S...>, C<>>;
};

template <template <typename...> typename P, typename...>
struct b_exclude_if;

template <template <typename...> typename P, typename... B,
          template <typename...> typename C, typename... S>
struct b_exclude_if<P, C<S...>, B...> {
    using type = std::conditional_t<P<B..., S...>::value, C<>, C<S...>>;
};



template <template <typename...> typename C,
          template <typename...> typename P, typename... S>
using include_if_t = std::conditional_t<P<S...>::value, C<S...>, C<>>;

template <template <typename...> typename C,
          template <typename...> typename P, typename... S>
using exclude_if_t = std::conditional_t<P<S...>::value, C<>, C<S...>>;

// Takes only one B.
template <template <typename...> typename C, typename B,
          template <typename...> typename P, typename... S>
using b_include_if_t = std::conditional_t<P<B, S...>::value, C<S...>, C<>>;

// Takes only one B.
template <template <typename...> typename C, typename B,
          template <typename...> typename P, typename... S>
using b_exclude_if_t = std::conditional_t<P<B, S...>::value, C<>, C<S...>>;





/**
 * @UTILITY foreach filter (hard)
 * include_each, exclude_each, b_include_each, b_exclude_each
 */
template <template <typename...> typename P, typename...>
struct include_each;

template <template <typename...> typename P,
          template <typename...> typename C, typename... S>
struct include_each<P, C<S...>> {
    using type = join_t<std::conditional_t<P<S>::value, C<S>, C<>>...>;
};

template <template <typename...> typename P, typename...>
struct exclude_each;

template <template <typename...> typename P,
          template <typename...> typename C, typename... S>
struct exclude_each<P, C<S...>> {
    using type = join_t<std::conditional_t<P<S>::value, C<>, C<S>>...>;
};

template <template <typename...> typename P, typename...>
struct b_include_each;

template <template <typename...> typename P, typename... B,
          template <typename...> typename C, typename... S>
struct b_include_each<P, C<S...>, B...> {
    using type = join_t<std::conditional_t<P<B..., S>::value, C<S>, C<>>...>;
};

template <template <typename...> typename P, typename...>
struct b_exclude_each;

template <template <typename...> typename P, typename... B,
          template <typename...> typename C, typename... S>
struct b_exclude_each<P, C<S...>, B...> {
    using type = join_t<std::conditional_t<P<B..., S>::value, C<>, C<S>>...>;
};


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





/**
 * @UTILITY transform (average)
 */
template <template <typename...> typename P, typename...>
struct transform;

template <template <typename...> typename P,
          template <typename...> typename C, typename... S>
struct transform<P, C<S...>> {
    using type = C<typename P<S>::type...>;
};

template <typename C, template <typename...> typename P>
using transform_t = typename transform<P, C>::type;





/**
 * @UTILITY all_of, any_of, none_of (hard)
 */
template <template <typename...> typename P, typename...>
struct all_of;

template <template <typename...> typename P,
          template <typename...> typename C,
          typename F, typename... S>
struct all_of<P, C<F, S...>> {
    enum {
        value = std::conditional_t<
                 P<F>::value,
                 all_of<P, C<S...>>,
                 std::false_type>::value
    };
};

template <template <typename...> typename P,
          template <typename...> typename C>
struct all_of<P, C<>> {
    enum { value = true };
};


template <template <typename...> typename P, typename...>
struct any_of;

template <template <typename...> typename P,
          template <typename...> typename C,
          typename F, typename... S>
struct any_of<P, C<F, S...>> {
    enum {
        value = std::conditional_t<
                 P<F>::value,
                 std::true_type,
                 any_of<P, C<S...>>>::value
    };
};

template <template <typename...> typename P,
          template <typename...> typename C>
struct any_of<P, C<>> {
    enum { value = false };
};


template <template <typename...> typename P, typename...>
struct none_of;

template <template <typename...> typename P,
          template <typename...> typename C,
          typename F, typename... S>
struct none_of<P, C<F, S...>> {
    enum {
        value = std::conditional_t<
                 P<F>::value,
                 std::false_type,
                 none_of<P, C<S...>>>::value
    };
};

template <template <typename...> typename P,
          template <typename...> typename C>
struct none_of<P, C<>> {
    enum { value = true };
};






}
using namespace type_manip;
#endif //METAPROGRAMMING_GENERIC_HPP
