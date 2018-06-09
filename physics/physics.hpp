#ifndef PHYSICS_HPP___
#define PHYSICS_HPP___

#include <type_traits>
#include <utility>
#include <cmath>
#include <array>

namespace si {

/**
 * Force measure to take only arithmetic types
 */
static constexpr bool enforce_arithmetic = true;

/**
 * The measure class should be optimized out of existence
 * in the object files. Compile with this set to true and
 * then with it set to false -- the object file sizes
 * should be the exact same.
 */
static constexpr bool test_optimizer = false;



namespace detail {

template <int... N>
struct int_list : std::integer_sequence<int, N...> {
  static constexpr std::size_t dimensions = sizeof...(N);
};

template <int N, int... R>
struct int_list<N, R...> : std::integer_sequence<int, N, R...> {
  static constexpr std::size_t dimensions = 1 + sizeof...(R);
  static constexpr std::array<int, dimensions> dims {N, R...};
  static inline constexpr int get_dim(int I) {
    return dims.at(I);
  }
};

template <bool chooser, typename A, typename B>
struct select;

template <typename A, typename B>
struct select<true, A, B> {
  using type = A;
};

template <typename A, typename B>
struct select<false, A, B> {
  using type = B;
};

template <bool chooser, typename A, typename B>
using select_t = typename select<chooser, A, B>::type;

} // detail

//
// Consider two measure classes
// 
// measure<T1, D1...>     measure<T2, D2...>
// 
// To respect type safety, these
// 
//   +  Can be added iff T1 = T2 and D1... = D2...
//   -  Can be subtracted iff T1 = T2 and D1... = D2...
//   *  Can be multipled iff T1 = T2.
//     Then result D is (D1 + D2)...
//   /  Can be divided iff T1 = T2.
//     Then result D is (D1 - D2)...
// 
//   %  We'll support it because we can, but as strictly
//     as possible: modules can be applied iff
//     T1 = T2 and D1... = D2...
//   

template <typename M1, typename M2>
struct can_sum {
  static constexpr bool value = false;
  using left_type = M1;
  using right_type = M2;
};

template <template <typename, int...> typename Measure,
          typename T, int... D>
struct can_sum<Measure<T, D...>, Measure<T, D...>> {
  static constexpr bool value = true;
  using left_type = Measure<T, D...>;
  using right_type = Measure<T, D...>;
};

template <typename M1, typename M2>
static constexpr bool can_sum_v = can_sum<M1, M2>::value;





template <typename M1, typename M2>
struct multiplication_result;

template <template <typename, int...> typename Measure,
          typename T, int... D1, int... D2>
struct multiplication_result<Measure<T, D1...>, Measure<T, D2...>> {
  using result_type = Measure<T, (D1 + D2)...>;
  using left_type = Measure<T, D1...>;
  using right_type = Measure<T, D2...>;
  using type = result_type;
};

template <typename M1, typename M2>
using multiplication_result_t = typename multiplication_result<M1, M2>::type;

template <typename M1, typename M2>
using mult_t = multiplication_result_t<M1, M2>;




template <typename M1, typename M2>
struct division_result;

template <template <typename, int...> typename Measure,
          typename T, int... D1, int... D2>
struct division_result<Measure<T, D1...>, Measure<T, D2...>> {
  using result_type = Measure<T, (D1 - D2)...>;
  using left_type = Measure<T, D1...>;
  using right_type = Measure<T, D2...>;
  using type = result_type;
  using numerator_type = left_type;
  using denominator_type = right_type;
};

template <typename M1, typename M2>
using division_result_t = typename division_result<M1, M2>::type;

template <typename M1, typename M2>
using div_t = division_result_t<M1, M2>;





template <typename M, int Exponent>
struct power_result;

template <template <typename, int...> typename Measure,
          typename T, int... D, int Exponent>
struct power_result<Measure<T, D...>, Exponent> {
  static constexpr int exponent = Exponent;
  using result_type = Measure<T, (D * Exponent)...>;
  using base_type = Measure<T, D...>;
  using type = result_type;
};

template <typename M, int Exponent>
using power_result_t = typename power_result<M, Exponent>::type;

template <typename M, int Exponent>
using power_t = power_result_t<M, Exponent>;





namespace detail {

template <typename M>
struct strip_measure;

template <template <typename, int...> typename Measure,
          typename T, int... D>
struct strip_measure<Measure<T, D...>> {
  using type = Measure<T>;
};

template <typename M>
using strip_measure_t = typename strip_measure<M>::type;





template <typename M, int V, int Q>
struct fill_measure;

template <template <typename, int...> typename Measure,
          typename T, int... D, int V, int Q>
struct fill_measure<Measure<T, D...>, V, Q> {
  using type = typename fill_measure<Measure<T, V, D...>, V, Q - 1>::type;
};

template <template <typename, int...> typename Measure,
          typename T, int... D, int V>
struct fill_measure<Measure<T, D...>, V, 0> {
  using type = Measure<T, D...>;
};

template <typename M, int V, int Q>
using fill_measure_t = typename fill_measure<M, V, Q>::type;





template <typename M, int Q>
struct scalar_measure;

template <template <typename M, int...> typename Measure,
          typename T, int... D, int Q>
struct scalar_measure<Measure<T, D...>, Q> {
  using type = typename fill_measure<Measure<T>, 0, Q>::type;
};

template <typename M, int Q>
using scalar_measure_t = typename scalar_measure<M, Q>::type;





template <typename M>
struct scalar;

template <template <typename, int...> typename Measure,
          typename T, int... D>
struct scalar<Measure<T, D...>> {
  using type = typename scalar_measure<Measure<T>, sizeof...(D)>::type;
};

template <typename M>
using scalar_t = typename scalar<M>::type;





template <typename M>
struct is_measure : std::false_type {};

template <template <typename, int...> typename Measure,
          typename T, int... D>
struct is_measure<Measure<T, D...>> : std::true_type {};

template <typename M>
static constexpr bool is_measure_v = is_measure<M>::value;

template <typename M>
struct enable_if_measure
  : public std::enable_if<is_measure_v<M>, M> {};

template <typename M>
using enable_if_measure_t = typename enable_if_measure<M>::type;

template <typename... M>
struct enable_if_measures {
  using type = std::true_type;
};

template <typename M, typename... R>
struct enable_if_measures<M, R...>
  : std::enable_if<is_measure_v<M>, enable_if_measures<R...>> {};

template <typename... M>
using enable_if_measures_t = typename enable_if_measures<M...>::type;

} // detail



template <typename T, int... D>
class measure : public detail::int_list<D...> {
  static_assert(!enforce_arithmetic || std::is_arithmetic<T>::value);

public:
  using value_type = T;

protected:
  using measure_type = measure<T, D...>;
  using self_type = measure<T, D...>;
  using stripped_type = measure<T>;
  using scalar_type = detail::scalar_t<self_type>;

private:
  using self_t = self_type;
  T value_;

public:
  inline constexpr
  measure() = default;

  inline constexpr
  measure(const self_t& other) = default;

  inline constexpr
  measure(self_t&& other) = default;

  inline constexpr
  measure(const T& number) : value_(number) {};

  inline constexpr
  measure(T&& number) : value_(std::move(number)) {};

  template <typename M, typename = detail::enable_if_measure_t<M>>
  inline constexpr explicit
  measure(const M& other) : value_(other.value_) {}

  template <typename M, typename = detail::enable_if_measure_t<M>>
  inline constexpr explicit
  measure(M&& other) : value_(std::move(other.value_)) {}

  inline constexpr self_t&
  operator=(const self_t& other) = default;

  inline constexpr self_t&
  operator=(self_t&& other) = default;

  inline constexpr self_t&
  operator=(const T& number) {
    return this->value_ = number, *this;
  }

  inline constexpr self_t&
  operator=(T&& number) noexcept {
    return this->value_ = std::move(number), *this;
  }

  inline constexpr
  operator T() const {
    return value_;
  }

  inline constexpr explicit
  operator bool() const {
    return static_cast<bool>(value_);
  }

  inline constexpr bool
  operator!() const {
    return !value_;
  }

  friend inline constexpr bool
  operator<(const self_t& l, const self_t& r) {
    return l.value_ < r.value_;
  }

  friend inline constexpr bool
  operator>(const self_t& l, const self_t& r) {
    return l.value_ > r.value_;
  }

  friend inline constexpr bool
  operator==(const self_t& l, const self_t& r) {
    return l.value_ == r.value_;
  }

  friend inline constexpr bool
  operator!=(const self_t& l, const self_t& r) {
    return l.value_ != r.value_;
  }

  friend inline constexpr bool
  operator>=(const self_t& l, const self_t& r) {
    return l.value_ >= r.value_;
  }

  friend inline constexpr bool
  operator<=(const self_t& l, const self_t& r) {
    return l.value_ <= r.value_;
  }

  friend inline constexpr self_t
  operator+(const self_t& l, const self_t& r) {
    return l.value_ + r.value_;
  }

  friend inline constexpr self_t
  operator-(const self_t& l, const self_t& r) {
    return l.value_ - r.value_;
  }

  friend inline constexpr self_t
  operator%(const self_t& l, const self_t& r) {
    return l.value_ % r.value_;
  }

  template <typename M1, typename M2, typename>
  friend inline constexpr multiplication_result_t<M1, M2>
  operator*(const M1& l, const M2& r);

  template <typename M1, typename M2, typename>
  friend inline constexpr division_result_t<M1, M2>
  operator/(const M1& l, const M2& r);

  template <int Exponent, typename M, typename>
  friend inline constexpr power_result_t<M, Exponent>
  power(M arg);

  inline constexpr self_t&
  operator+=(const self_t& other) {
    return this->value_ += other.value_, *this;
  }

  inline constexpr self_t&
  operator-=(const self_t& other) {
    return this->value_ -= other.value_, *this;
  }

  inline constexpr self_t&
  operator%=(const self_t& other) {
    return this->value_ %= other.value_, *this;
  }

  inline constexpr self_t&
  operator*=(const T& scalar) {
    return this->value_ *= scalar, *this;
  }

  inline constexpr self_t&
  operator/=(const T& scalar) {
    return this->value_ /= scalar, *this;
  }

  inline constexpr self_t&
  operator*=(const scalar_type& other) {
    return this->value_ *= other.value_, *this;
  }

  inline constexpr self_t&
  operator/=(const scalar_type& other) {
    return this->value_ /= other.value_, *this;
  }

  inline constexpr self_t&
  operator++() {
    return ++this->value_, *this;
  }

  inline constexpr self_t
  operator++(int) {
    return this->value_++;
  }

  inline constexpr self_t&
  operator--() {
    return --this->value_, *this;
  }

  inline constexpr self_t
  operator--(int) {
    return this->value_--;
  }

  inline constexpr self_t
  operator+() const {
    return +this->value_;
  }

  inline constexpr self_t
  operator-() const {
    return -this->value_;
  }

  template <typename M, typename = detail::enable_if_measure_t<M>>
  inline constexpr M to() const;
};



template <typename M1, typename M2, typename = detail::enable_if_measures_t<M1, M2>>
inline constexpr multiplication_result_t<M1, M2>
operator*(const M1& l, const M2& r) {
  return l.value_ * r.value_;
}

template <typename M1, typename M2, typename = detail::enable_if_measures_t<M1, M2>>
inline constexpr division_result_t<M1, M2>
operator/(const M1& l, const M2& r) {
  return l.value_ / r.value_;
}

template <int Exponent, typename M, typename = detail::enable_if_measure_t<M>>
inline constexpr power_result_t<M, Exponent>
power(M arg) {
  return std::pow(arg.value_, Exponent);
}

template <typename T, int... D>
template <typename M, typename>
inline constexpr M measure<T, D...>::to() const {
  return static_cast<M>(*this);
}



template <int... D>
using float_measure = measure<float, D...>;

template <int... D>
using double_measure = measure<double, D...>;

template <int... D>
using long_double_measure = measure<long double, D...>;



template <typename T, // representative arithmmetic type
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


template <typename T, typename = detail::enable_if_measure_t<T>>
static constexpr int length_dim = T::get_dim(0);

template <typename T, typename = detail::enable_if_measure_t<T>>
static constexpr int mass_dim = T::get_dim(1);

template <typename T, typename = detail::enable_if_measure_t<T>>
static constexpr int time_dim = T::get_dim(2);

template <typename T, typename = detail::enable_if_measure_t<T>>
static constexpr int current_dim = T::get_dim(3);

template <typename T, typename = detail::enable_if_measure_t<T>>
static constexpr int temperature_dim = T::get_dim(4);

template <typename T, typename = detail::enable_if_measure_t<T>>
static constexpr int luminous_dim = T::get_dim(5);

template <typename T, typename = detail::enable_if_measure_t<T>>
static constexpr int substance_dim = T::get_dim(6);



namespace generic_base {

template <typename T>
using scalar_t       = unit<T>;

template <typename T>
using distance_t     = unit<T, 1, 0, 0, 0, 0, 0, 0>;

template <typename T>
using mass_t         = unit<T, 0, 1, 0, 0, 0, 0, 0>;

template <typename T>
using time_t         = unit<T, 0, 0, 1, 0, 0, 0, 0>;

template <typename T>
using current_t      = unit<T, 0, 0, 0, 1, 0, 0, 0>;

template <typename T>
using temperature_t  = unit<T, 0, 0, 0, 0, 1, 0, 0>;

template <typename T>
using luminous_t     = unit<T, 0, 0, 0, 0, 0, 1, 0>;

template <typename T>
using substance_t    = unit<T, 0, 0, 0, 0, 0, 0, 1>;

} // generic_base

}

#endif // PHYSICS_HPP___
