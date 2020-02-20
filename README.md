# metaprogramming

Learning template metaprogramming solving a C++ metaprogramming
problem.

-----

Physics
-------

A micro-library with less than 2000 lines of code.
It is essentially a numeric type system based on the SI unit system.
Arithmetic types (floats) are soft-wrapped by a template type
`si::unit<...>` and arithmetic is strongly-typed within this system.

Practical example: two variables of type **distance** and **time**
can be divided into a variable of type **speed**, and not anything else.

```cpp
	si::distance mile = 1.609344_km;
	si::time second = 1.0_s;

	// works:
	si::speed miles_per_second = mile / second;

	// doesn't work, wrong type:
	si::acceleration miles_per_second_sq = mile / second;

	// works, deducing si::acceleration:
	auto miles_per_second_sq = mile / (second * second);
```

The code is modular, header-only, and has no dependencies. The underlying
float type of `si::unit` is defined by which header is included; several aliases
exist for the same `si::unit` type (e.g. `si::length` and `si::distance`) and
of course more can be easily added.

The string literals (the `_km` suffixes etc) are generated with most modifiers
(such as `k`, `M`, `G`, `T`..., and `d`, `c`, `m`, `n`, `u`, `p`...) and each
major `si::unit` alias has all its SI suffixes generated and `long double` literals.

The implementation is rather straightforward. The specification of the SI units
system essentially means that `si::unit<...>` should be implemented as

```cpp
    si::unit<L, T, N, I, O, J, M>
    si::unit<Length, Time, AmtSubs, ElecCurrent, Temperature, LumIntensity, Mass>
```

For example:

```cpp
    si::area = si::unit<2,0,0,0,0,0,0>
    si::acceleration = si::unit<1,-2,0,0,0,0,0>

    // F = ma
    si::force = si::unit<1,-2,0,0,0,0,1>
```

-----

Generic
-------

Solutions for metaprogramming problems. Some of these might actually be
usable and useful.

* `is_specialization_of`
* `is_template_instantiation`
* `join`
* `reverse`
* `map` (1 to 1)
* `flatten`, `mixed_flatten`, `deep_flatten`
* `transform` (1 to many)
* `push_front`, `push_back`
* `pop_front`, `pop_back`
* `front`, `back`
* `get`
* `size`
* `instance`
* `include_if`, `exclude_if`
  * `a_include_if`, `a_exclude_if`
  * `b_include_if`, `b_exclude_if`
  * `av_include_if`, `av_exclude_if`
  * `bv_include_if`, `bv_exclude_if`
* `include_each`, `exclude_each`
  * `a_include_each`, `a_exclude_each`
  * `b_include_each`, `b_exclude_each`
  * `av_include_each`, `av_exclude_each`
  * `bv_include_each`, `bv_exclude_each`
* `all_of`, `any_of`, `none_of`
  * `a_all_of`, `a_any_of`, `a_none_of`
  * `b_all_of`, `b_any_of`, `b_none_of`
  * `av_all_of`, `av_any_of`, `av_none_of`
  * `bv_all_of`, `bv_any_of`, `bv_none_of`
* `contains_all`, `contains_any`, `contains_none`
  * `v_contains_all`, `v_contains_any`, `v_contains_none`
