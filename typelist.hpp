//
// This header exposes filter-variadic
//

#ifndef METAPROGRAMMING_TYPE_LIST_HPP
#define METAPROGRAMMING_TYPE_LIST_HPP

#include <type_traits>

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
struct typelist<Ts...>::get<i> {
    //static_assert(false, "Invalid typelist::get_t index");
    //using type = void;
};

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



#endif //METAPROGRAMMING_TYPE_LIST_HPP
