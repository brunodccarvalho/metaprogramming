#include "generic.hpp"
#include "typelist.hpp"

#include <tuple>

using namespace generic;

template <typename...>
struct many {};

struct A {};
struct A0 : A {};
struct A1 : A {};
struct A2 : A {};
struct A3 : A {};

struct B {};
struct B0 : B {};
struct B1 : B {};
struct B2 : B {};
struct B3 : B {};

struct C {};
struct D {};

struct X {};
struct Y {};
struct Z {};

using list = typelist<>;
using listA = typelist<A0, A1, A2, A3>;
using listB = typelist<B0, B1, B2>;
using listAB = typelist<A0, A1, A2, A3, B0, B1, B2>;
using listBA = typelist<B0, B1, B2, A0, A1, A2, A3>;
using listABCD = typelist<A0, A1, A2, A3, B0, B1, B2, C, D>;
using listXYZ = typelist<X, Y, Z, X, Y, Z>;

// typelist::get
static_assert((std::is_same<listA::get_t<2>, A2>::value));
static_assert((std::is_same<listB::get_t<0>, B0>::value));

// generic::join
using joinAB = join_t<listA, list, listB, list>; // empty lists disappear
using joinBA = join_t<listB, listA>; // empty lists disappear
static_assert((std::is_same<listAB, joinAB>::value));
static_assert((std::is_same<listBA, joinBA>::value));

// generic::reverse
using reverseA = reverse_t<listA>;
static_assert((std::is_same<typelist<A3, A2, A1, A0>, reverseA>::value));

// generic::is_specialization_of
static_assert((is_specialization_of<listXYZ, typelist>::value));
static_assert(!(is_specialization_of<listXYZ, many>::value));

// generic::flatten
using listlistAlistB = typelist<listA, listB, C, D>;
using flattenAB = flatten_t<listlistAlistB>;

static_assert((std::is_same<listABCD, flattenAB>::value));

// generic::push_front, generic::push_back
using listCDA = typelist<C, D, A0, A1, A2, A3>;
using listBCD = typelist<B0, B1, B2, C, D>;
using push_frontA_CD = push_front_t<listA, C, D>;
using push_backB_CD = push_back_t<listB, C, D>;
static_assert((std::is_same<listCDA, push_frontA_CD>::value));
static_assert((std::is_same<listBCD, push_backB_CD>::value));

// generic::pop_front, generic::pop_back
using pop_frontA = pop_front_t<listA>;
using pop_backA = pop_back_t<listA>;
static_assert((std::is_same<pop_frontA, typelist<A1, A2, A3>>::value));
static_assert((std::is_same<pop_backA, typelist<A0, A1, A2>>::value));

// generic::front, generic::back
static_assert((std::is_same<A0, front_t<listA>>::value));
static_assert((std::is_same<A3, back_t<listA>>::value));
static_assert((std::is_same<B0, front_t<listB>>::value));
static_assert((std::is_same<B2, back_t<listB>>::value));

// generic::instance
using manyA = many<A0, A1, A2, A3>;
using manyB = many<B0, B1, B2>;
using instanceA = listA::instance_t<many>;
using instanceB = listB::instance_t<many>;
static_assert((std::is_same<manyA, instanceA>::value));
static_assert((std::is_same<manyB, instanceB>::value));

// generic::include_if, generic::exclude_if
// Predicate: At least four type parameters
template <typename... Ts>
struct atleast4 {
    static constexpr size_t N = sizeof...(Ts);
    enum { value = N > 3 };
};
static_assert((std::is_same<include_if_t<atleast4, listA>, listA>::value));
static_assert((std::is_same<include_if_t<atleast4, listB>, list>::value));

static_assert((std::is_same<exclude_if_t<atleast4, listA>, list>::value));
static_assert((std::is_same<exclude_if_t<atleast4, listB>, listB>::value));