#ifndef PHYSICS_GENERATORS_LITERALS_HPP___
#define PHYSICS_GENERATORS_LITERALS_HPP___

#ifndef PHYSICS_GENERATE_ONE_LITERAL_HERE

#define PHYSICS_GENERATE_ONE_LITERAL_HERE(type, base, text, prefix, mul)  \
                                                                          \
static inline constexpr base                                              \
operator""_##prefix##text(long double literal) noexcept {                 \
  return static_cast<type>(literal) * static_cast<type>(mul);             \
}                                                                         \
                                                                          \
static inline constexpr base                                              \
operator""_##prefix##text(unsigned long long literal) noexcept {          \
  return static_cast<type>(literal) * static_cast<type>(mul);             \
}                                                                         \

#endif

#ifndef PHYSICS_GENERATE_LITERALS

#define PHYSICS_GENERATE_LITERALS(type, base, text)                       \
/* none */                                                                \
PHYSICS_GENERATE_ONE_LITERAL_HERE(type, base, text,  , 1e0)               \
/* deca */                                                                \
PHYSICS_GENERATE_ONE_LITERAL_HERE(type, base, text,da, 1e1)               \
/* hecto */                                                               \
PHYSICS_GENERATE_ONE_LITERAL_HERE(type, base, text, h, 1e2)               \
/* kilo */                                                                \
PHYSICS_GENERATE_ONE_LITERAL_HERE(type, base, text, k, 1e3)               \
/* mega */                                                                \
PHYSICS_GENERATE_ONE_LITERAL_HERE(type, base, text, M, 1e6)               \
/* giga */                                                                \
PHYSICS_GENERATE_ONE_LITERAL_HERE(type, base, text, G, 1e9)               \
/* tera */                                                                \
PHYSICS_GENERATE_ONE_LITERAL_HERE(type, base, text, T, 1e12)              \
/* peta */                                                                \
PHYSICS_GENERATE_ONE_LITERAL_HERE(type, base, text, P, 1e15)              \
/* exa */                                                                 \
PHYSICS_GENERATE_ONE_LITERAL_HERE(type, base, text, E, 1e18)              \
/* zetta */                                                               \
PHYSICS_GENERATE_ONE_LITERAL_HERE(type, base, text, Z, 1e21)              \
/* deci */                                                                \
PHYSICS_GENERATE_ONE_LITERAL_HERE(type, base, text, d, 1e-1)              \
/* centi */                                                               \
PHYSICS_GENERATE_ONE_LITERAL_HERE(type, base, text, c, 1e-2)              \
/* milli */                                                               \
PHYSICS_GENERATE_ONE_LITERAL_HERE(type, base, text, m, 1e-3)              \
/* micro */                                                               \
PHYSICS_GENERATE_ONE_LITERAL_HERE(type, base, text, u, 1e-6)              \
/* nano */                                                                \
PHYSICS_GENERATE_ONE_LITERAL_HERE(type, base, text, n, 1e-9)              \
/* pico */                                                                \
PHYSICS_GENERATE_ONE_LITERAL_HERE(type, base, text, p, 1e-12)             \
/* femto */                                                               \
PHYSICS_GENERATE_ONE_LITERAL_HERE(type, base, text, f, 1e-15)             \
/* atto */                                                                \
PHYSICS_GENERATE_ONE_LITERAL_HERE(type, base, text, a, 1e-18)             \
/* zepto */                                                               \
PHYSICS_GENERATE_ONE_LITERAL_HERE(type, base, text, z, 1e-21)             \

#endif

#endif // PHYSICS_GENERATORS_LITERALS_HPP___
