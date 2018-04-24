#include <iostream>
#include <string>
#include <tuple>

#include <typeinfo>
#include <cassert>

#include "typelist.hpp"
#include "generic.hpp"

using namespace generic;

using w_empty = typelist<>;
using w_ints = typelist<short, int, long, long long>;
using w_doubles = typelist<float, double, long double>;
using w_chars = typelist<char, wchar_t, char*>;
using w_bools = typelist<bool, bool&, bool&&>;
using w_random = typelist<short* const* const, const int&, long&&, volatile double>;

using w_many = join_t<w_empty, w_ints, w_chars, w_doubles, w_empty>;
using w_join = join_t<w_empty, w_ints, w_chars, w_doubles, w_bools>;
using w_rjoin = join_t<w_empty, w_random, w_bools, w_empty>;
using w_rev = reverse_t<w_many>;

using w_push_back = push_back_t<w_ints, const int, bool**>;
using w_push_front = push_front_t<w_chars, const int, bool**>;
using w_pop_back = pop_back_t<w_ints>;
using w_pop_front = pop_front_t<w_ints>;

using w_some = typelist<bool, int, char, double>;
using t_ints = instance_t<w_some, std::tuple>;
using t_reve = reverse_t<instance_t<w_some, std::tuple>>;

void print_basic_types() {
    w_ints::get_t<0> ints0 = 73;
    w_ints::get_t<1> ints1 = 73;
    w_ints::get_t<2> ints2 = 73;
    w_ints::get_t<3> ints3 = 73;
    //w_ints::get_t<4> ints4 = 73;
    w_doubles::get_t<0> d0 = 73.90;
    w_doubles::get_t<1> d1 = 73.90;
    w_doubles::get_t<2> d2 = 73.90;

    std::cout << "$ Types and sizes" << std::endl;
    std::cout << "sizeof = " << sizeof(w_empty) << std::endl;
    std::cout << "sizeof = " << sizeof(w_ints) << std::endl;
    std::cout << "sizeof = " << sizeof(w_doubles) << std::endl;
    std::cout << "sizeof = " << sizeof(w_chars) << std::endl;
    std::cout << "sizeof = " << sizeof(w_bools) << std::endl;
    std::cout << "ints0 (short)     = " << typeid(ints0).name() << std::endl;
    std::cout << "ints1 (int)       = " << typeid(ints1).name() << std::endl;
    std::cout << "ints2 (long)      = " << typeid(ints2).name() << std::endl;
    std::cout << "ints3 (long long) = " << typeid(ints3).name() << std::endl;
    std::cout << "db0 (float)       = " << typeid(d0).name() << std::endl;
    std::cout << "db1 (double)      = " << typeid(d1).name() << std::endl;
    std::cout << "db2 (long double) = " << typeid(d2).name() << std::endl;
    std::cout << std::endl;
}

void print_demangler_1() {
    w_empty empty;
    w_ints ints;
    w_doubles doubles;
    w_chars chars;
    w_bools bools;
    w_many many;
    w_join join;
    w_rjoin rjoin;
    w_rev rev;

    std::string s_empty   = typeid(empty  ).name();
    std::string s_ints    = typeid(ints   ).name();
    std::string s_doubles = typeid(doubles).name();
    std::string s_chars   = typeid(chars  ).name();
    std::string s_bools   = typeid(bools  ).name();
    std::string s_many    = typeid(many   ).name();
    std::string s_join    = typeid(join   ).name();
    std::string s_rjoin   = typeid(rjoin  ).name();
    std::string s_rev     = typeid(rev).name();

    std::cout << "$ Demangler" << std::endl;
    std::cout << "empty   = "  << s_empty   << std::endl;
    std::cout << "ints    = "  << s_ints    << std::endl;
    std::cout << "doubles = "  << s_doubles << std::endl;
    std::cout << "chars   = "  << s_chars   << std::endl;
    std::cout << "bools   = "  << s_bools   << std::endl;
    std::cout << "many    = "  << s_many    << std::endl;
    std::cout << "join    = "  << s_join    << std::endl;
    std::cout << "rjoin   = "  << s_rjoin   << std::endl;
    std::cout << "rev     = "  << s_rev     << std::endl;
    std::cout << "w_many::N    = " << w_many::N    << std::endl;
    std::cout << "w_join::N    = " << w_join::N    << std::endl;
    std::cout << "w_rjoin::N   = " << w_rjoin::N   << std::endl;
    std::cout << "w_rev::N     = " << w_rev::N     << std::endl;
    std::cout << std::endl;
}

void print_demangler_2() {
    w_push_back push_back;
    w_push_front push_front;
    w_pop_back pop_back;
    w_pop_front pop_front;

    std::string s_push_back  = typeid(push_back ).name();
    std::string s_push_front = typeid(push_front).name();
    std::string s_pop_back   = typeid(pop_back  ).name();
    std::string s_pop_front  = typeid(pop_front ).name();

    std::cout << "$ Demangler 2" << std::endl;
    std::cout << "s_push_back  = " << s_push_back  << std::endl;
    std::cout << "s_push_front = " << s_push_front << std::endl;
    std::cout << "s_pop_back   = " << s_pop_back   << std::endl;
    std::cout << "s_pop_front  = " << s_pop_front  << std::endl;
    std::cout << "w_push_back::N  = " << w_push_back::N  << std::endl;
    std::cout << "w_push_front::N = " << w_push_front::N << std::endl;
    std::cout << "w_pop_back::N   = " << w_pop_back::N   << std::endl;
    std::cout << "w_pop_front::N  = " << w_pop_front::N  << std::endl;
    std::cout << std::endl;
}

void print_demangler_3() {
    t_ints ints;
    t_reve reve;

    std::string s_ints = typeid(ints).name();
    std::string s_reve = typeid(reve).name();

    static_assert((std::is_same<t_ints, std::tuple<bool, int, char, double>>::value));
    static_assert((std::is_same<t_reve, std::tuple<double, char, int, bool>>::value));

    std::cout << "$ Demangler 3" << std::endl;
    std::cout << "s_ints = " << s_ints << std::endl;
    std::cout << "s_reve = " << s_reve << std::endl;
    std::cout << std::endl;
}

int main(){
    std::cout << "Hello, World!" << std::endl << std::endl;
    print_basic_types();
    print_demangler_1();
    print_demangler_2();
    print_demangler_3();
    return 0;
}