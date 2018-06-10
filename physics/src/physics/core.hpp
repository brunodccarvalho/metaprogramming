#ifndef PHYSICS_CORE_HPP___
#define PHYSICS_CORE_HPP___

#include <type_traits>  // std::enable_if as usual
#include <utility>      // std::integer_sequence
#include <cmath>        // std::pow

namespace si {

/**
 * Force measure to take only arithmetic types.
 */
static constexpr bool enforce_arithmetic = true;



namespace detail {

template <std::size_t I, int... N>
struct get_int;

template <std::size_t I, int F, int... R>
struct get_int<I, F, R...> : get_int<I - 1, R...> {};

template <int F, int... R>
struct get_int<0, F, R...> {
  using rest = std::integer_sequence<int, R...>;
  static constexpr int value = F;
};

template <std::size_t I, int... S>
static constexpr int get_int_v = get_int<I, S...>::value;



template <int... N>
struct dim_list : std::integer_sequence<int, N...> {
  static constexpr std::size_t dimensions = sizeof...(N);

  static constexpr int get_dim(std::size_t I) {
    constexpr int array[] { N... };
    return array[I];
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



template <typename M>
struct strip_measure;

template <template <typename, int...> typename Measure,
          typename T, int... D>
struct strip_measure<Measure<T, D...>> {
  using type = Measure<T>;
};

template <typename M>
using strip_measure_t = typename strip_measure<M>::type;



template <typename M, int V>
struct fill_measure;

template <template <typename, int...> typename Measure,
          typename T, int... D, int V>
struct fill_measure<Measure<T, D...>, V> {
  using type = Measure<T, (D * 0 + V)...>;
};

template <typename M, int V, int Q>
using fill_measure_t = typename fill_measure<M, V>::type;



template <typename M>
struct scalar : fill_measure<M, 0> {};

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
struct is_scalar : std::integral_constant<bool,
  is_measure_v<M> && std::is_same_v<M, scalar_t<M>>> {};

template <typename M>
static constexpr bool is_scalar_v = is_scalar<M>::value;



template <typename M>
struct enable_if_measure
  : public std::enable_if<is_measure_v<M>, M> {};

template <typename... M>
struct enable_if_measures {
  using type = std::true_type;
};

template <typename M, typename... R>
struct enable_if_measures<M, R...>
  : std::enable_if<is_measure_v<M>, enable_if_measures<R...>> {};

template <typename M>
using enable_if_measure_t = typename enable_if_measure<M>::type;

template <typename... M>
using enable_if_measures_t = typename enable_if_measures<M...>::type;



template <typename A>
struct enable_if_arithmetic
  : std::enable_if<!enforce_arithmetic || std::is_arithmetic_v<A>, A> {};

template <typename A>
using enable_if_arithmetic_t = typename enable_if_arithmetic<A>::type;



template <typename M>
struct enable_if_scalar
  : std::enable_if<is_scalar_v<M>, M> {};

template <typename M>
using enable_if_scalar_t = typename enable_if_scalar<M>::type;

} // detail



//
// Consider two measure classes
// 
// measure<T1, D1...>     measure<T2, D2...>
// 
// To uphold type safety, these
// 
//   +  Can be added iff T1 = T2 and D1... = D2...
//   -  Can be subtracted iff T1 = T2 and D1... = D2...
//   *  Can be multipled iff T1 = T2.
//     Then result D is (D1 + D2)...
//   /  Can be divided iff T1 = T2.
//     Then result D is (D1 - D2)...
// 
//   %  We'll support it because we can, but as strictly
//     as possible: modulus can be applied iff
//     T1 = T2 and D1... = D2...
//   

template <typename M1, typename M2>
struct sum_result;

template <template <typename, int...> typename Measure,
          typename T, int... D>
struct sum_result<Measure<T, D...>, Measure<T, D...>> {
  using type = Measure<T, D...>;
  using left_type = type;
  using right_type = type;
  using result_type = type;
};

template <typename M1, typename M2>
using sum_result_t = typename sum_result<M1, M2>::type;



template <typename M1, typename M2>
struct multiplication_result;

template <template <typename, int...> typename Measure,
          typename T, int... D1, int... D2>
struct multiplication_result<Measure<T, D1...>, Measure<T, D2...>> {
  using type = Measure<T, (D1 + D2)...>;
  using left_type = Measure<T, D1...>;
  using right_type = Measure<T, D2...>;
  using result_type = type;
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
  using type = Measure<T, (D1 - D2)...>;
  using left_type = Measure<T, D1...>;
  using right_type = Measure<T, D2...>;
  using result_type = type;
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
using pow_t = power_result_t<M, Exponent>;



template <typename T, int... D>
class measure : public detail::dim_list<D...> {
  static_assert(!enforce_arithmetic || std::is_arithmetic<T>::value);

  template <typename, int...>
  friend class measure;

public:
  using value_type = T;
  using measure_type = measure<T, D...>;
  using self_type = measure<T, D...>;
  using stripped_type = measure<T>;
  using scalar_type = measure<T, (D * 0)...>;
  using inverse_type = measure<T, (-D)...>;

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
  measure(T&& number) noexcept : value_(std::move(number)) {};

  template <typename M, typename = detail::enable_if_measure_t<M>>
  inline constexpr explicit
  measure(const M& other) = delete;

  template <typename M, typename = detail::enable_if_measure_t<M>>
  inline constexpr explicit // this might be sufficient
  measure(M&& other) = delete;

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

  template <typename M, typename = detail::enable_if_measure_t<M>>
  inline constexpr self_t&
  operator=(const M& other) = delete;

  template <typename M, typename = detail::enable_if_measure_t<M>>
  inline constexpr self_t& // this might be sufficient
  operator=(M&& other) noexcept = delete;

  inline constexpr explicit
  operator T() const {
    return this->value_;
  }

  inline constexpr explicit
  operator bool() const {
    return static_cast<bool>(this->value_);
  }

  template <typename A, typename = detail::enable_if_arithmetic_t<A>>
  inline constexpr explicit
  operator A() const {
    return static_cast<A>(this->value_);
  }

  inline constexpr bool
  operator!() const {
    return !value_;
  }

  inline constexpr bool
  operator<(const self_t& r) const {
    return this->value_ < r.value_;
  }

  inline constexpr bool
  operator>(const self_t& r) const {
    return this->value_ > r.value_;
  }

  inline constexpr bool
  operator==(const self_t& r) const {
    return this->value_ == r.value_;
  }

  inline constexpr bool
  operator!=(const self_t& r) const {
    return this->value_ != r.value_;
  }

  inline constexpr bool
  operator>=(const self_t& r) const {
    return this->value_ >= r.value_;
  }

  inline constexpr bool
  operator<=(const self_t& r) const {
    return this->value_ <= r.value_;
  }

  inline constexpr self_t
  operator+(const self_t& r) const {
    return this->value_ + r.value_;
  }

  inline constexpr self_t
  operator-(const self_t& r) const {
    return this->value_ - r.value_;
  }

  inline constexpr self_t
  operator%(const self_t& r) const {
    return this->value_ % r.value_;
  }

  inline constexpr self_t
  operator%(const T& r) const {
    return this->value_ % r;
  }

  template <typename M, typename = detail::enable_if_measure_t<M>>
  inline constexpr multiplication_result_t<self_t, M>
  operator*(const M& r) const {
    return this->value_ * r.value_;
  }

  template <typename M, typename = detail::enable_if_measure_t<M>>
  inline constexpr division_result_t<self_t, M>
  operator/(const M& r) const {
    return this->value_ / r.value_;
  }

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
  inline constexpr M
  as() const {
    return static_cast<M>(*this);
  }

  inline constexpr T
  from() const {
    return this->value_;
  }

  friend inline constexpr self_t
  operator*(const self_t& m, const T& scalar) {
    return m.value_ * scalar;
  }

  friend inline constexpr self_t
  operator*(const T& scalar, const self_t& m) {
    return scalar * m.value_;
  }

  friend inline constexpr self_t
  operator/(const self_t& m, const T& scalar) {
    return m.value_ / scalar;
  }

  friend inline constexpr inverse_type
  operator/(const T& scalar, const self_t& m) {
    return scalar / m.value_;
  }
};

template <int Exponent, typename M,
          typename = detail::enable_if_measure_t<M>>
inline constexpr power_result_t<M, Exponent>
pow(M arg) {
  typename M::value_type tmp(arg);
  return std::pow(tmp, Exponent);
}

template <int... D>
using fmeasure = measure<float, D...>;

template <int... D>
using dmeasure = measure<double, D...>;

template <int... D>
using ldmeasure = measure<long double, D...>;

} // si

#endif // PHYSICS_CORE_HPP___
