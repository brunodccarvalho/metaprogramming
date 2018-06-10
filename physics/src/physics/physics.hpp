#ifndef PHYSICS_HPP___
#define PHYSICS_HPP___

#include "physics/core.hpp"

namespace si {

/**
 * Dimensions of the SI unit. If you want to modify this
 * you'll have to modify the unit template further down
 * which specializes measure, and also namespace generaL_base.
 */
static constexpr int unit_dimensions = 7;

/**
 * The symbols of each dimension of unit. Used by string.hpp
 * to perform conversion to string and output to streams.
 */
static constexpr const char* symbol_table[] = {
  "m",      // Length          m    Meter
  "g",      // Mass            g    Mass
  "s",      // Time            s    Second
  "A",      // Current         A    Ampere
  "K",      // Temperature     K    Kelvin
  "cd",     // Luminous        cd   Candela
  "mol"     // Substance       mol  Mole
};

/**
 * The measure class should be optimized out of existence
 * in the object files. Compile with this set to true and
 * then with it set to false -- the object file sizes
 * should be the exact same.
 */
static constexpr bool test_optimizer = false;



namespace detail {

template <typename M>
struct is_unit : std::false_type {};

template <template <typename, int...> typename Measure,
          typename T, int... D>
struct is_unit<Measure<T, D...>>
  : std::integral_constant<bool, sizeof...(D) == unit_dimensions> {};

template <typename M>
static constexpr bool is_unit_v = is_unit<M>::value;

template <typename M>
struct enable_if_unit
  : public std::enable_if<is_unit_v<M>, M> {};

template <typename... M>
struct enable_if_units {
  using type = std::true_type;
};

template <typename M, typename... R>
struct enable_if_units<M, R...>
  : std::enable_if<is_unit_v<M>, enable_if_units<R...>> {};

template <typename M>
using enable_if_unit_t = typename enable_if_unit<M>::type;

template <typename... M>
using enable_if_units_t = typename enable_if_units<M...>::type;

}



template <typename T, // representative arithmetic type
          int Length      = 0, // m    Meter
          int Mass        = 0, // kg   Mass
          int Time        = 0, // s    Second
          int Current     = 0, // A    Ampere
          int Temperature = 0, // K    Kelvin
          int Luminous    = 0, // cd   Candela
          int Substance   = 0> // mol  Mole
using unit = detail::select_t<test_optimizer,
                T,
                measure<T, Length, Mass, Time, Current,
                Temperature, Luminous, Substance>
                >;



template <int L, int M, int T, int C, int K, int Q, int S>
using funit = unit<float, L, M, T, C, K, Q, S>;

template <int L, int M, int T, int C, int K, int Q, int S>
using dunit = unit<double, L, M, T, C, K, Q, S>;

template <int L, int M, int T, int C, int K, int Q, int S>
using ldunit = unit<long double, L, M, T, C, K, Q, S>;



template <typename T, typename = detail::enable_if_unit_t<T>>
static constexpr int length_dim = T::get_dim(0);

template <typename T, typename = detail::enable_if_unit_t<T>>
static constexpr int mass_dim = T::get_dim(1);

template <typename T, typename = detail::enable_if_unit_t<T>>
static constexpr int time_dim = T::get_dim(2);

template <typename T, typename = detail::enable_if_unit_t<T>>
static constexpr int current_dim = T::get_dim(3);

template <typename T, typename = detail::enable_if_unit_t<T>>
static constexpr int temperature_dim = T::get_dim(4);

template <typename T, typename = detail::enable_if_unit_t<T>>
static constexpr int luminous_dim = T::get_dim(5);

template <typename T, typename = detail::enable_if_unit_t<T>>
static constexpr int substance_dim = T::get_dim(6);



namespace generic_base {

template <typename T>
using scalar      = unit<T, 0, 0, 0, 0, 0, 0, 0>;

template <typename T>
using distance    = unit<T, 1, 0, 0, 0, 0, 0, 0>;

template <typename T>
using mass        = unit<T, 0, 1, 0, 0, 0, 0, 0>;

template <typename T>
using time        = unit<T, 0, 0, 1, 0, 0, 0, 0>;

template <typename T>
using current     = unit<T, 0, 0, 0, 1, 0, 0, 0>;

template <typename T>
using temperature = unit<T, 0, 0, 0, 0, 1, 0, 0>;

template <typename T>
using luminous    = unit<T, 0, 0, 0, 0, 0, 1, 0>;

template <typename T>
using substance   = unit<T, 0, 0, 0, 0, 0, 0, 1>;

} // generic_base

} // si

#endif // PHYSICS_HPP___
