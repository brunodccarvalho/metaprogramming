//
// This header exposes filter-variadic
//

#ifndef METAPROGRAMMING_TYPE_LIST_HPP
#define METAPROGRAMMING_TYPE_LIST_HPP

#include "generic.hpp"

#include <type_traits>
#include <tuple>

/**
 * A template struct enclosing an ordered list
 * of typenames (such as classes, literals, ...),
 * effectively "storing" those types.
 * Exposes methods for instantiating other template
 * or variadic template classes with the stored types.
 * @tparam Ts The types being stored.
 */
template <typename... Ts>
struct typelist;



/**
 * @IMPLEMENTATION typelist
 */
template <typename... Ts>
struct typelist {
  private:
    /**
     * Type Struct
     * type = C<Ts...>
     * Exposes member type which is an instantiation
     * of template container C with the stored types.
     */
    template <template <typename...> typename C>
    struct instance;

    /**
     * Type Struct
     * type = Ts[i]
     * Exposes member type which is the stored
     * type at index i (0-indexed). Does not expose
     * member type if the i-th type doesn't exist.
     */
    template <std::size_t i, typename... L>
    struct get;

  public:
    /**
     * Helper template, extracts type from instance
     */
    template <template <typename...> typename C>
    using instance_t = typename instance<C>::type;

    /**
     * Helper template, extracts type from get
     */
    template <std::size_t i>
    using get_t = typename get<i, Ts...>::type;

    /**
     * Specialization of instance_t for std::tuple.
     */
    using tuple_t = instance_t<std::tuple>;

    /**
     * Number of types being stored
     */
    static constexpr std::size_t N = sizeof...(Ts);
};

/**
 * @IMPLEMENTATION type_list :: instance
 */
template <typename... Ts>
template <template <typename...> typename C>
struct typelist<Ts...>::instance {
    using type = C<Ts...>;
};

/**
 * @IMPLEMENTATION type_list :: get
 */
template <typename... Ts>
template <std::size_t i>
struct typelist<Ts...>::get<i> {};

template <typename... Ts>
template <std::size_t i, typename T, typename... L>
struct typelist<Ts...>::get<i, T, L...> {
    using type = typename typelist<Ts...>::template get<i-1,L...>::type;
};

template <typename... Ts>
template <typename T, typename... L>
struct typelist<Ts...>::get<0, T, L...> {
    using type = T;
};



/**
 * @IMPLEMENTATION filter
 */
namespace filter {
// include_if
// Return typelist<Args...> if Predicate<Args>, and typelist<> otherwise.
template <template <typename...> typename Predicate, typename... Args>
using include_if = std::conditional_t<Predicate<Args...>::value, typelist<Args...>, typelist<>>;

// exclude_if
// Return typelist<> if Predicate<Args>, typelist<Args> otherwise.
// Args is 0 or more types
template <template <typename...> typename Predicate, typename... Args>
using exclude_if = std::conditional_t<Predicate<Args...>::value, typelist<>, typelist<Args...>>;

// b_include_if
// Version of include_if where Predicate takes a fixed argument not to be
// included in the list if it is satisfied.
template <typename B, template <typename, typename...> typename Predicate, typename... Args>
using b_include_if = std::conditional_t<Predicate<B, Args...>::value, typelist<Args...>, typelist<>>;

// b_exclude_if
// Version of exclude_if where Predicate takes a fixed argument not to be
// included in the list if it is not satisfied.
template <typename B, template <typename, typename...> typename Predicate, typename... Args>
using b_exclude_if = std::conditional_t<Predicate<B, Args...>::value, typelist<>, typelist<Args...>>;

// include_each
// Returns a typelist with each individual type filtered, inclusion if matching
template <template <typename...> typename Predicate, typename... Args>
using include_each = typename join<include_if<Predicate, Args>...>::type;

// exclude_each
// Returns a typelist with each individual type filtered, exclusion if matching
template <template <typename...> typename Predicate, typename... Args>
using exclude_each = typename join<exclude_if<Predicate, Args>...>::type;

// b_include_each
template <typename B, template <typename, typename...> typename Predicate, typename... Args>
using b_include_each = typename join<b_include_if<B, Predicate, Args>...>::type;

// b_exclude_each
template <typename B, template <typename, typename...> typename Predicate, typename... Args>
using b_exclude_each = typename join<b_exclude_if<B, Predicate, Args>...>::type;

// Common filters
template <typename... Args> // Exclude void types
using exclude_void = exclude_each<std::is_void, Args...>;

template <typename... Args> // Exclude empty class
using exclude_empty = exclude_each<std::is_empty, Args...>;

template <typename Base, typename... Args> // Include only subclasses of Base
using include_subclass = b_include_each<Base, std::is_base_of, Args...>;

template <typename Base, typename... Args> // Exclude subclasses of Base
using exclude_subclass = b_exclude_each<Base, std::is_base_of, Args...>;
}

#endif //METAPROGRAMMING_TYPE_LIST_HPP
