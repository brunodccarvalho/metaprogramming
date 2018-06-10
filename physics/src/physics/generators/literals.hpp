#ifndef PHYSICS_GENERATORS_LITERALS_HPP___
#define PHYSICS_GENERATORS_LITERALS_HPP___

#ifndef PHYSICS_GENERATE_ONE_LITERAL_HERE

#define PHYSICS_GENERATE_ONE_LITERAL_HERE(T, ret, suffix, prefix, mul)  \
                                                                        \
static inline constexpr ret                                             \
operator""_##prefix##suffix(long double literal) noexcept {             \
  return static_cast<T>(literal) * static_cast<T>(mul);                 \
}                                                                       \
                                                                        \
static inline constexpr ret                                             \
operator""_##prefix##suffix(unsigned long long literal) noexcept {      \
  return static_cast<T>(literal) * static_cast<T>(mul);                 \
}                                                                       \

#endif

#ifndef PHYSICS_GENERATE_LITERALS

#define PHYSICS_GENERATE_LITERALS(T, ret, suffix)                       \
/* none */                                                              \
PHYSICS_GENERATE_ONE_LITERAL_HERE(T, ret, suffix,  , 1e0)               \
/* deca */                                                              \
PHYSICS_GENERATE_ONE_LITERAL_HERE(T, ret, suffix,da, 1e1)               \
/* hecto */                                                             \
PHYSICS_GENERATE_ONE_LITERAL_HERE(T, ret, suffix, h, 1e2)               \
/* kilo */                                                              \
PHYSICS_GENERATE_ONE_LITERAL_HERE(T, ret, suffix, k, 1e3)               \
/* mega */                                                              \
PHYSICS_GENERATE_ONE_LITERAL_HERE(T, ret, suffix, M, 1e6)               \
/* giga */                                                              \
PHYSICS_GENERATE_ONE_LITERAL_HERE(T, ret, suffix, G, 1e9)               \
/* tera */                                                              \
PHYSICS_GENERATE_ONE_LITERAL_HERE(T, ret, suffix, T, 1e12)              \
/* peta */                                                              \
PHYSICS_GENERATE_ONE_LITERAL_HERE(T, ret, suffix, P, 1e15)              \
/* exa */                                                               \
PHYSICS_GENERATE_ONE_LITERAL_HERE(T, ret, suffix, E, 1e18)              \
/* zetta */                                                             \
PHYSICS_GENERATE_ONE_LITERAL_HERE(T, ret, suffix, Z, 1e21)              \
/* deci */                                                              \
PHYSICS_GENERATE_ONE_LITERAL_HERE(T, ret, suffix, d, 1e-1)              \
/* centi */                                                             \
PHYSICS_GENERATE_ONE_LITERAL_HERE(T, ret, suffix, c, 1e-2)              \
/* milli */                                                             \
PHYSICS_GENERATE_ONE_LITERAL_HERE(T, ret, suffix, m, 1e-3)              \
/* micro */                                                             \
PHYSICS_GENERATE_ONE_LITERAL_HERE(T, ret, suffix, u, 1e-6)              \
/* nano */                                                              \
PHYSICS_GENERATE_ONE_LITERAL_HERE(T, ret, suffix, n, 1e-9)              \
/* pico */                                                              \
PHYSICS_GENERATE_ONE_LITERAL_HERE(T, ret, suffix, p, 1e-12)             \
/* femto */                                                             \
PHYSICS_GENERATE_ONE_LITERAL_HERE(T, ret, suffix, f, 1e-15)             \
/* atto */                                                              \
PHYSICS_GENERATE_ONE_LITERAL_HERE(T, ret, suffix, a, 1e-18)             \
/* zepto */                                                             \
PHYSICS_GENERATE_ONE_LITERAL_HERE(T, ret, suffix, z, 1e-21)             \

#endif

#endif // PHYSICS_GENERATORS_LITERALS_HPP___
