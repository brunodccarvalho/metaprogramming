#ifndef PHYSICS_LITERAL_GENERATOR_HPP___
#define PHYSICS_LITERAL_GENERATOR_HPP___

// <!-- begin preprocessor dark magic
#ifndef PHYSICS_GENERATE_LITERALS

#define PHYSICS_GENERATE_PARTIAL_HERE(type, base, text, prefix, mul) \
                                                                     \
static inline constexpr base                                         \
operator""_##prefix##text(long double literal) noexcept {            \
  return static_cast<type>(literal) * static_cast<type>(mul);        \
}                                                                    \
                                                                     \
static inline constexpr base                                         \
operator""_##prefix##text(unsigned long long literal) noexcept {     \
  return static_cast<type>(literal) * static_cast<type>(mul);        \
}                                                                    \

#define PHYSICS_GENERATE_LITERALS(type, base, text)                  \
                                                                     \
PHYSICS_GENERATE_PARTIAL_HERE(type, base, text,  , 1e0)              \
                                                                     \
PHYSICS_GENERATE_PARTIAL_HERE(type, base, text,da, 1e1)              \
                                                                     \
PHYSICS_GENERATE_PARTIAL_HERE(type, base, text, h, 1e2)              \
                                                                     \
PHYSICS_GENERATE_PARTIAL_HERE(type, base, text, k, 1e3)              \
                                                                     \
PHYSICS_GENERATE_PARTIAL_HERE(type, base, text, M, 1e6)              \
                                                                     \
PHYSICS_GENERATE_PARTIAL_HERE(type, base, text, G, 1e9)              \
                                                                     \
PHYSICS_GENERATE_PARTIAL_HERE(type, base, text, T, 1e12)             \
                                                                     \
PHYSICS_GENERATE_PARTIAL_HERE(type, base, text, P, 1e15)             \
                                                                     \
PHYSICS_GENERATE_PARTIAL_HERE(type, base, text, E, 1e18)             \
                                                                     \
PHYSICS_GENERATE_PARTIAL_HERE(type, base, text, Z, 1e21)             \
                                                                     \
PHYSICS_GENERATE_PARTIAL_HERE(type, base, text, d, 1e-1)             \
                                                                     \
PHYSICS_GENERATE_PARTIAL_HERE(type, base, text, c, 1e-2)             \
                                                                     \
PHYSICS_GENERATE_PARTIAL_HERE(type, base, text, m, 1e-3)             \
                                                                     \
PHYSICS_GENERATE_PARTIAL_HERE(type, base, text, u, 1e-6)             \
                                                                     \
PHYSICS_GENERATE_PARTIAL_HERE(type, base, text, n, 1e-9)             \
                                                                     \
PHYSICS_GENERATE_PARTIAL_HERE(type, base, text, p, 1e-12)            \
                                                                     \
PHYSICS_GENERATE_PARTIAL_HERE(type, base, text, f, 1e-15)            \
                                                                     \
PHYSICS_GENERATE_PARTIAL_HERE(type, base, text, a, 1e-18)            \
                                                                     \
PHYSICS_GENERATE_PARTIAL_HERE(type, base, text, z, 1e-21)            \

#endif
// ---> end preprocessor dark magic

#endif // PHYSICS_LITERAL_GENERATOR_HPP___
