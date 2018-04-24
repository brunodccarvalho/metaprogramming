#ifndef METAPROGRAMMING_GENERIC_HPP
#define METAPROGRAMMING_GENERIC_HPP

// A collection of TMP challenges.

#include <type_traits>

namespace generic {
/**
 * @UTILITY is_specialization_of (easy)
 */
template <typename T, template <typename...> typename C>
struct is_specialization_of {
    enum { value = false };
};

template <template <typename...> typename C, typename... S>
struct is_specialization_of<C<S...>, C> {
    enum { value = true };
};

template <typename T, template <typename...> typename C>
constexpr bool is_specialization_of_v = is_specialization_of<T, C>::value;





/**
 * @UTILITY is_template_instantiation (average)
 * Warning: Only accepts certain formats
 */
template <typename T>
struct is_template_instantiation {
    enum { value = false };
};

template <template <typename...> typename C, typename... S>
struct is_template_instantiation<C<S...>> {
    enum { value = true }; // template <type...>
};

template <template <template <typename...> typename...> typename C,
          template <typename...> typename... T>
struct is_template_instantiation<C<T...>> {
    enum { value = true }; // template <template...>
};

template <template <template <typename...> typename, typename...> typename C,
          template <typename...> typename T, typename... S>
struct is_template_instantiation<C<T, S...>> {
    enum { value = true }; // template <template, type...>
};

template <typename T>
constexpr bool is_template_instantiation_v = is_template_instantiation<T>::value;





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
 * @UTILITY transform (easy)
 */
template <template <typename...> typename Funct, typename...>
struct transform;

template <template <typename...> typename Funct,
          template <typename...> typename C, typename... S>
struct transform<Funct, C<S...>> {
    using type = C<typename Funct<S>::type...>;
};

template <template <typename...> typename Funct, typename C>
using transform_t = typename transform<Funct, C>::type;





/**
 * @UTILITY flatten (hard)
 * C<S1, S2, C<S3, S4>, C<S5...>, S6...> -> C<S1, S2, S3, S4, S5..., S6...>
 */
template <typename>
struct flatten;

template <typename, typename...>
struct flatten_impl;

template <template <typename...> typename C, typename... S,
          typename... T, typename... R>
struct flatten_impl<C<S...>, C<T...>, R...> {
    using type = typename flatten_impl<C<S..., T...>, R...>::type;
};

template <template <typename...> typename C, typename... S,
          typename T, typename... R>
struct flatten_impl<C<S...>, T, R...> {
    using type = typename flatten_impl<C<S..., T>, R...>::type;
    using sfinae = typename std::enable_if<!is_specialization_of_v<T, C>>::type;
    // if T is an instance of C, this is a substitution error.
};

template <template <typename...> typename C, typename... S>
struct flatten_impl<C<S...>> {
    using type = C<S...>;
};

template <template <typename...> typename C, typename... S>
struct flatten<C<S...>> {
    using type = typename flatten_impl<C<>, S...>::type;
};

template <typename C>
using flatten_t = typename flatten<C>::type;





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
 * @UTILITY get (average)
 */
template <std::size_t, typename...>
struct get;

template <std::size_t i>
struct get<i> {};

template <std::size_t i, typename T, typename... R>
struct get<i, T, R...> {
    using type = typename get<i-1,R...>::type;
};

template <typename T, typename... L>
struct get<0, T, L...> {
    using type = T;
};

template <std::size_t, typename>
struct v_get;

template <std::size_t i, template <typename...> typename C, typename... S>
struct v_get<i, C<S...>> {
    using type = typename get<i, S...>::type;
};

template <std::size_t i, typename... Ts>
using get_t = typename get<i, Ts...>::type;

template <std::size_t i, typename C>
using v_get_t = typename v_get<i, C>::type;





/**
 * @UTILITY size (trivial)
 */
template <typename C>
struct size;

template <template <typename...> typename C, typename... S>
struct size<C<S...>> {
    enum { value = sizeof...(S) };
};

template <typename C>
constexpr std::size_t size_v = size<C>::value;





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
 * include_if, exclude_if (predicate takes no extra arguments)
 *   Extra arguments (B) as a parameter pack:
 * a_include_if, a_exclude_if (take extra arguments as a parameter pack,
 * and the arguments are placed after the types)
 * b_include_if, b_exclude_if (takes extra arguments as a parameter pack,
 * and the arguments are placed before the types)
 *   Extra arguments (B) as a type collection:
 * av_include_if, av_exclude_if (take extra arguments as a type collection,
 * and the arguments are placed after the types)
 * bv_include_if, bv_exclude_if (takes extra arguments as a type collection,
 * and the arguments are placed before the types)
 */
template <template <typename...> typename P, typename...>
struct include_if;

template <template <typename...> typename P,
          template <typename...> typename C, typename... S>
struct include_if<P, C<S...>> {
    using type = std::conditional_t<P<S...>::value, C<S...>, C<>>;
    enum {
        value = P<S...>::value
    };
};

template <template <typename...> typename P, typename...>
struct exclude_if;

template <template <typename...> typename P,
template <typename...> typename C, typename... S>
struct exclude_if<P, C<S...>> {
    using type = std::conditional_t<P<S...>::value, C<>, C<S...>>;
    enum {
        value = !P<S...>::value
    };
};



template <template <typename...> typename P, typename...>
struct a_include_if;

template <template <typename...> typename P, typename... B,
          template <typename...> typename C, typename... S>
struct a_include_if<P, C<S...>, B...> {
    using type = std::conditional_t<P<S..., B...>::value, C<S...>, C<>>;
    enum {
        value = P<S..., B...>::value
    };
};

template <template <typename...> typename P, typename...>
struct a_exclude_if;

template <template <typename...> typename P, typename... B,
          template <typename...> typename C, typename... S>
struct a_exclude_if<P, C<S...>, B...> {
    using type = std::conditional_t<P<S..., B...>::value, C<>, C<S...>>;
    enum {
        value = !P<S..., B...>::value
    };
};



template <template <typename...> typename P, typename...>
struct b_include_if;

template <template <typename...> typename P, typename... B,
          template <typename...> typename C, typename... S>
struct b_include_if<P, C<S...>, B...> {
    using type = std::conditional_t<P<B..., S...>::value, C<S...>, C<>>;
    enum {
        value = P<B..., S...>::value
    };
};

template <template <typename...> typename P, typename...>
struct b_exclude_if;

template <template <typename...> typename P, typename... B,
          template <typename...> typename C, typename... S>
struct b_exclude_if<P, C<S...>, B...> {
    using type = std::conditional_t<P<B..., S...>::value, C<>, C<S...>>;
    enum {
        value = !P<B..., S...>::value
    };
};



template <template <typename...> typename P, typename, typename>
struct av_include_if;

template <template <typename...> typename P,
          template <typename...> typename T, typename... B,
          template <typename...> typename C, typename... S>
struct av_include_if<P, C<S...>, T<B...>> {
    using type = std::conditional_t<P<S..., B...>::value, C<S...>, C<>>;
    enum {
        value = !P<S..., B...>::value
    };
};

template <template <typename...> typename P, typename, typename>
struct av_exclude_if;

template <template <typename...> typename P,
          template <typename...> typename T, typename... B,
          template <typename...> typename C, typename... S>
struct av_exclude_if<P, C<S...>, T<B...>> {
    using type = std::conditional_t<P<S..., B...>::value, C<>, C<S...>>;
    enum {
        value = !P<S..., B...>::value
    };
};



template <template <typename...> typename P, typename, typename>
struct bv_include_if;

template <template <typename...> typename P,
          template <typename...> typename T, typename... B,
          template <typename...> typename C, typename... S>
struct bv_include_if<P, C<S...>, T<B...>> {
    using type = std::conditional_t<P<B..., S...>::value, C<S...>, C<>>;
    enum {
        value = P<B..., S...>::value
    };
};



template <template <typename...> typename P, typename, typename>
struct bv_exclude_if;

template <template <typename...> typename P,
          template <typename...> typename T, typename... B,
          template <typename...> typename C, typename... S>
struct bv_exclude_if<P, C<S...>, T<B...>> {
    using type = std::conditional_t<P<B..., S...>::value, C<>, C<S...>>;
    enum {
        value = !P<B..., S...>::value
    };
};



template <template <typename...> typename P, typename C>
using include_if_t = typename include_if<P, C>::type;

template <template <typename...> typename P, typename C>
using exclude_if_t = typename exclude_if<P, C>::type;

template <template <typename...> typename P, typename C, typename... B>
using a_include_if_t = typename a_include_if<P, C, B...>::type;

template <template <typename...> typename P, typename C, typename... B>
using a_exclude_if_t = typename a_exclude_if<P, C, B...>::type;

template <template <typename...> typename P, typename C, typename... B>
using b_include_if_t = typename b_include_if<P, C, B...>::type;

template <template <typename...> typename P, typename C, typename... B>
using b_exclude_if_t = typename b_exclude_if<P, C, B...>::type;

template <template <typename...> typename P, typename C, typename TB>
using av_include_if_t = typename av_include_if<P, C, TB>::type;

template <template <typename...> typename P, typename C, typename TB>
using av_exclude_if_t = typename av_exclude_if<P, C, TB>::type;

template <template <typename...> typename P, typename C, typename TB>
using bv_include_if_t = typename bv_include_if<P, C, TB>::type;

template <template <typename...> typename P, typename C, typename TB>
using bv_exclude_if_t = typename bv_exclude_if<P, C, TB>::type;



template <template <typename...> typename P, typename C>
constexpr bool include_if_v = include_if<P, C>::value;

template <template <typename...> typename P, typename C>
constexpr bool exclude_if_v = exclude_if<P, C>::value;

template <template <typename...> typename P, typename C, typename... B>
constexpr bool a_include_if_v = a_include_if<P, C, B...>::value;

template <template <typename...> typename P, typename C, typename... B>
constexpr bool a_exclude_if_v = a_exclude_if<P, C, B...>::value;

template <template <typename...> typename P, typename C, typename... B>
constexpr bool b_include_if_v = b_include_if<P, C, B...>::value;

template <template <typename...> typename P, typename C, typename... B>
constexpr bool b_exclude_if_v = b_exclude_if<P, C, B...>::value;

template <template <typename...> typename P, typename C, typename TB>
constexpr bool av_include_if_v = av_include_if<P, C, TB>::value;

template <template <typename...> typename P, typename C, typename TB>
constexpr bool av_exclude_if_v = av_exclude_if<P, C, TB>::value;

template <template <typename...> typename P, typename C, typename TB>
constexpr bool bv_include_if_v = bv_include_if<P, C, TB>::value;

template <template <typename...> typename P, typename C, typename TB>
constexpr bool bv_exclude_if_v = bv_exclude_if<P, C, TB>::value;





/**
 * @UTILITY foreach filter (average)
 * include_each, exclude_each (predicate takes no extra arguments)
 *   Extra arguments (B) as a parameter pack:
 * a_include_each, a_exclude_each (take extra arguments as a parameter pack,
 * and the arguments are placed after the types)
 * b_include_each, b_exclude_each (takes extra arguments as a parameter pack,
 * and the arguments are placed before the types)
 *   Extra arguments (B) as a type collection:
 * av_include_each, av_exclude_each (take extra arguments as a type collection,
 * and the arguments are placed after the types)
 * bv_include_each, bv_exclude_each (takes extra arguments as a type collection,
 * and the arguments are placed before the types)
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
struct a_include_each;

template <template <typename...> typename P, typename... B,
          template <typename...> typename C, typename... S>
struct a_include_each<P, C<S...>, B...> {
    using type = join_t<std::conditional_t<P<S, B...>::value, C<S>, C<>>...>;
};

template <template <typename...> typename P, typename...>
struct a_exclude_each;

template <template <typename...> typename P, typename... B,
          template <typename...> typename C, typename... S>
struct a_exclude_each<P, C<S...>, B...> {
    using type = join_t<std::conditional_t<P<S, B...>::value, C<>, C<S>>...>;
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



template <template <typename...> typename P, typename...>
struct av_include_each;

template <template <typename...> typename P,
          template <typename...> typename T, typename... B,
          template <typename...> typename C, typename... S>
struct av_include_each<P, C<S...>, T<B...>> {
    using type = join_t<std::conditional_t<P<S, B...>::value, C<S>, C<>>...>;
};

template <template <typename...> typename P, typename...>
struct av_exclude_each;

template <template <typename...> typename P,
          template <typename...> typename T, typename... B,
          template <typename...> typename C, typename... S>
struct av_exclude_each<P, C<S...>, T<B...>> {
    using type = join_t<std::conditional_t<P<S, B...>::value, C<>, C<S>>...>;
};



template <template <typename...> typename P, typename...>
struct bv_include_each;

template <template <typename...> typename P,
          template <typename...> typename T, typename... B,
          template <typename...> typename C, typename... S>
struct bv_include_each<P, C<S...>, T<B...>> {
    using type = join_t<std::conditional_t<P<B..., S>::value, C<S>, C<>>...>;
};

template <template <typename...> typename P, typename...>
struct bv_exclude_each;

template <template <typename...> typename P,
          template <typename...> typename T, typename... B,
          template <typename...> typename C, typename... S>
struct bv_exclude_each<P, C<S...>, T<B...>> {
    using type = join_t<std::conditional_t<P<B..., S>::value, C<>, C<S>>...>;
};



template <template <typename...> typename P, typename C>
using include_each_t = typename include_each<P, C>::type;

template <template <typename...> typename P, typename C>
using exclude_each_t = typename exclude_each<P, C>::type;

template <template <typename...> typename P, typename C, typename... B>
using a_include_each_t = typename a_include_each<P, C, B...>::type;

template <template <typename...> typename P, typename C, typename... B>
using a_exclude_each_t = typename a_exclude_each<P, C, B...>::type;

template <template <typename...> typename P, typename C, typename... B>
using b_include_each_t = typename b_include_each<P, C, B...>::type;

template <template <typename...> typename P, typename C, typename... B>
using b_exclude_each_t = typename b_exclude_each<P, C, B...>::type;

template <template <typename...> typename P, typename C, typename TB>
using av_include_each_t = typename av_include_each<P, C, TB>::type;

template <template <typename...> typename P, typename C, typename TB>
using av_exclude_each_t = typename av_exclude_each<P, C, TB>::type;

template <template <typename...> typename P, typename C, typename TB>
using bv_include_each_t = typename bv_include_each<P, C, TB>::type;

template <template <typename...> typename P, typename C, typename TB>
using bv_exclude_each_t = typename bv_exclude_each<P, C, TB>::type;





/**
 * @COMMON common filters (average)
 */
template <template <typename...> typename P, typename C>
using exclude_void_t = exclude_each_t<std::is_void, C>;

template <template <typename...> typename P, typename C>
using exclude_empty_t = exclude_each_t<std::is_empty, C>;

template <template <typename...> typename P, typename C, typename... B>
using include_subclass_t = b_exclude_each_t<std::is_void, C, B...>;

template <template <typename...> typename P, typename C, typename... B>
using exclude_subclass_t = b_exclude_each_t<std::is_empty, C, B...>;





/**
 * @UTILITY all_of, any_of, none_of and friends (hard)
 */
// --- all_of, any_of, none_of

template <template <typename...> typename P, typename>
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

template <template <typename...> typename P, typename C>
constexpr bool all_of_v = all_of<P, C>::value;



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

template <template <typename...> typename P, typename C>
constexpr bool any_of_v = any_of<P, C>::value;



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

template <template <typename...> typename P, typename C>
constexpr bool none_of_v = none_of<P, C>::value;





// --- a_all_of, a_any_of, a_none_of

template <template <typename...> typename P, typename...>
struct a_all_of;

template <template <typename...> typename P, typename... B,
          template <typename...> typename C,
          typename F, typename... S>
struct a_all_of<P, C<F, S...>, B...> {
    enum {
        value = std::conditional_t<
                 P<F, B...>::value,
                 a_all_of<P, C<S...>, B...>,
                 std::false_type>::value
    };
};

template <template <typename...> typename P, typename... B,
          template <typename...> typename C>
struct a_all_of<P, C<>, B...> {
    enum { value = true };
};

template <template <typename...> typename P, typename C, typename... B>
constexpr bool a_all_of_v = a_all_of<P, C, B...>::value;


template <template <typename...> typename P, typename...>
struct a_any_of;

template <template <typename...> typename P, typename... B,
          template <typename...> typename C,
          typename F, typename... S>
struct a_any_of<P, C<F, S...>, B...> {
    enum {
        value = std::conditional_t<
                 P<F, B...>::value,
                 std::true_type,
                 a_any_of<P, C<S...>, B...>>::value
    };
};

template <template <typename...> typename P, typename... B,
          template <typename...> typename C>
struct a_any_of<P, C<>, B...> {
    enum { value = false };
};

template <template <typename...> typename P, typename C, typename... B>
constexpr bool a_any_of_v = a_any_of<P, C, B...>::value;



template <template <typename...> typename P, typename...>
struct a_none_of;

template <template <typename...> typename P, typename... B,
          template <typename...> typename C,
          typename F, typename... S>
struct a_none_of<P, C<F, S...>, B...> {
    enum {
        value = std::conditional_t<
                 P<F, B...>::value,
                 std::false_type,
                 a_none_of<P, C<S...>, B...>>::value
    };
};

template <template <typename...> typename P, typename... B,
          template <typename...> typename C>
struct a_none_of<P, C<>, B...> {
    enum { value = true };
};

template <template <typename...> typename P, typename C, typename... B>
constexpr bool a_none_of_v = a_none_of<P, C, B...>::value;





// b_all_of, b_any_of, b_none_of

template <template <typename...> typename P, typename...>
struct b_all_of;

template <template <typename...> typename P, typename... B,
          template <typename...> typename C,
          typename F, typename... S>
struct b_all_of<P, C<F, S...>, B...> {
    enum {
        value = std::conditional_t<
                 P<B..., F>::value,
                 b_all_of<P, C<S...>, B...>,
                 std::false_type>::value
    };
};

template <template <typename...> typename P, typename... B,
          template <typename...> typename C>
struct b_all_of<P, C<>, B...> {
    enum { value = true };
};

template <template <typename...> typename P, typename C, typename... B>
constexpr bool b_all_of_v = b_all_of<P, C, B...>::value;


template <template <typename...> typename P, typename...>
struct b_any_of;

template <template <typename...> typename P, typename... B,
          template <typename...> typename C,
          typename F, typename... S>
struct b_any_of<P, C<F, S...>, B...> {
    enum {
        value = std::conditional_t<
                 P<B..., F>::value,
                 std::true_type,
                 b_any_of<P, C<S...>, B...>>::value
    };
};

template <template <typename...> typename P, typename... B,
          template <typename...> typename C>
struct b_any_of<P, C<>, B...> {
    enum { value = false };
};

template <template <typename...> typename P, typename C, typename... B>
constexpr bool b_any_of_v = b_any_of<P, C, B...>::value;



template <template <typename...> typename P, typename...>
struct b_none_of;

template <template <typename...> typename P, typename... B,
          template <typename...> typename C,
          typename F, typename... S>
struct b_none_of<P, C<F, S...>, B...> {
    enum {
        value = std::conditional_t<
                 P<B..., F>::value,
                 std::false_type,
                 b_none_of<P, C<S...>, B...>>::value
    };
};

template <template <typename...> typename P, typename... B,
          template <typename...> typename C>
struct b_none_of<P, C<>, B...> {
    enum { value = true };
};

template <template <typename...> typename P, typename C, typename... B>
constexpr bool b_none_of_v = b_none_of<P, C, B...>::value;





// --- av_all_of, av_any_of, av_none_of

template <template <typename...> typename P, typename...>
struct av_all_of;

template <template <typename...> typename P, typename... B,
          template <typename...> typename C,
          template <typename...> typename T,
          typename F, typename... S>
struct av_all_of<P, C<F, S...>, T<B...>> {
    enum {
        value = std::conditional_t<
                 P<F, B...>::value,
                 av_all_of<P, C<S...>, T<B...>>,
                 std::false_type>::value
    };
};

template <template <typename...> typename P, typename... B,
          template <typename...> typename C,
          template <typename...> typename T>
struct av_all_of<P, C<>, T<B...>> {
    enum { value = true };
};

template <template <typename...> typename P, typename C, typename TB>
constexpr bool av_all_of_v = av_all_of<P, C, TB>::value;


template <template <typename...> typename P, typename...>
struct av_any_of;

template <template <typename...> typename P, typename... B,
          template <typename...> typename C,
          template <typename...> typename T,
          typename F, typename... S>
struct av_any_of<P, C<F, S...>, T<B...>> {
    enum {
        value = std::conditional_t<
                 P<F, B...>::value,
                 std::true_type,
                 av_any_of<P, C<S...>, T<B...>>>::value
    };
};

template <template <typename...> typename P, typename... B,
          template <typename...> typename C,
          template <typename...> typename T>
struct av_any_of<P, C<>, T<B...>> {
    enum { value = false };
};

template <template <typename...> typename P, typename C, typename TB>
constexpr bool av_any_of_v = av_any_of<P, C, TB>::value;



template <template <typename...> typename P, typename...>
struct av_none_of;

template <template <typename...> typename P, typename... B,
          template <typename...> typename C,
          template <typename...> typename T,
          typename F, typename... S>
struct av_none_of<P, C<F, S...>, T<B...>> {
    enum {
        value = std::conditional_t<
                 P<F, B...>::value,
                 std::false_type,
                 av_none_of<P, C<S...>, T<B...>>>::value
    };
};

template <template <typename...> typename P, typename... B,
          template <typename...> typename C,
          template <typename...> typename T>
struct av_none_of<P, C<>, T<B...>> {
    enum { value = true };
};

template <template <typename...> typename P, typename C, typename TB>
constexpr bool av_none_of_v = av_none_of<P, C, TB>::value;





// bv_all_of, bv_any_of, bv_none_of

template <template <typename...> typename P, typename...>
struct bv_all_of;

template <template <typename...> typename P, typename... B,
          template <typename...> typename C,
          template <typename...> typename T,
          typename F, typename... S>
struct bv_all_of<P, C<F, S...>, T<B...>> {
    enum {
        value = std::conditional_t<
                 P<B..., F>::value,
                 bv_all_of<P, C<S...>, T<B...>>,
                 std::false_type>::value
    };
};

template <template <typename...> typename P, typename... B,
          template <typename...> typename C,
          template <typename...> typename T>
struct bv_all_of<P, C<>, T<B...>> {
    enum { value = true };
};

template <template <typename...> typename P, typename C, typename TB>
constexpr bool bv_all_of_v = bv_all_of<P, C, TB>::value;


template <template <typename...> typename P, typename...>
struct bv_any_of;

template <template <typename...> typename P, typename... B,
          template <typename...> typename C,
          template <typename...> typename T,
          typename F, typename... S>
struct bv_any_of<P, C<F, S...>, T<B...>> {
    enum {
        value = std::conditional_t<
                 P<B..., F>::value,
                 std::true_type,
                 bv_any_of<P, C<S...>, T<B...>>>::value
    };
};

template <template <typename...> typename P, typename... B,
          template <typename...> typename C,
          template <typename...> typename T>
struct bv_any_of<P, C<>, T<B...>> {
    enum { value = false };
};

template <template <typename...> typename P, typename C, typename TB>
constexpr bool bv_any_of_v = bv_any_of<P, C, TB>::value;



template <template <typename...> typename P, typename...>
struct bv_none_of;

template <template <typename...> typename P, typename... B,
          template <typename...> typename C,
          template <typename...> typename T,
          typename F, typename... S>
struct bv_none_of<P, C<F, S...>, T<B...>> {
    enum {
        value = std::conditional_t<
                 P<B..., F>::value,
                 std::false_type,
                 bv_none_of<P, C<S...>, T<B...>>>::value
    };
};

template <template <typename...> typename P, typename... B,
          template <typename...> typename C,
          template <typename...> typename T>
struct bv_none_of<P, C<>, T<B...>> {
    enum { value = true };
};

template <template <typename...> typename P, typename C, typename TB>
constexpr bool bv_none_of_v = bv_none_of<P, C, TB>::value;





/**
 * @UTILITY contains_all, contains_any, contains_none, (hard)
 * Checks if a container contains all/any/none given types
 */
template <typename...>
struct contains_all;

template <template <typename...> typename C, typename... S,
          typename T, typename... Ts>
struct contains_all<C<S...>, T, Ts...> {
    enum {
        value = std::conditional_t<
                b_any_of<std::is_same, C<S...>, T>::value,
                contains_all<C<S...>, Ts...>,
                std::false_type>::value
    };
};

template <template <typename...> typename C, typename... S>
struct contains_all<C<S...>> {
    enum { value = true };
};



template <typename...>
struct contains_any;

template <template <typename...> typename C, typename... S,
          typename T, typename... Ts>
struct contains_any<C<S...>, T, Ts...> {
    enum {
        value = std::conditional_t<
                b_any_of<std::is_same, C<S...>, T>::value,
                std::true_type,
                contains_any<C<S...>, Ts...>>::value
    };
};

template <template <typename...> typename C, typename... S>
struct contains_any<C<S...>> {
    enum { value = false };
};



template <typename...>
struct contains_none;

template <template <typename...> typename C, typename... S,
          typename T, typename... Ts>
struct contains_none<C<S...>, T, Ts...> {
    enum {
        value = std::conditional_t<
                b_any_of<std::is_same, C<S...>, T>::value,
                std::false_type,
                contains_none<C<S...>, Ts...>>::value
    };
};

template <template <typename...> typename C, typename... S>
struct contains_none<C<S...>> {
    enum { value = true };
};


}

#endif //METAPROGRAMMING_GENERIC_HPP
