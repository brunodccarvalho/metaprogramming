#include <iostream>
#include <typeinfo>

#include "typelist.hpp"

using w_empty = typelist<>;
using w_ints = typelist<short, int, long, long long>;
using w_doubles = typelist<float, double, long double>;
using w_chars = typelist<char, wchar_t, char*>;
using w_bools = typelist<bool, bool&>;
using w_random = typelist<short* const * const, const int&, long&&, volatile double>;

using w_many = join_t<w_empty, w_ints, w_chars, w_doubles, w_empty>;
using w_join = join_t<w_empty, w_ints, w_chars, w_doubles, w_bools>;
using w_rjoin = join_t<w_empty, w_random, w_bools, w_empty>;
using w_reverse = reverse_t<w_many>;

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

void print_demangler() {
    w_empty empty;
    w_ints ints;
    w_doubles doubles;
    w_chars chars;
    w_bools bools;
    w_many many;
    w_join join;
    w_rjoin rjoin;
    w_reverse reverse;

    std::string s_empty   = typeid(empty  ).name();
    std::string s_ints    = typeid(ints   ).name();
    std::string s_doubles = typeid(doubles).name();
    std::string s_chars   = typeid(chars  ).name();
    std::string s_bools   = typeid(bools  ).name();
    std::string s_many    = typeid(many   ).name();
    std::string s_join    = typeid(join   ).name();
    std::string s_rjoin   = typeid(rjoin  ).name();
    std::string s_reverse = typeid(reverse).name();

    std::cout << "$ Demangler" << std::endl;
    std::cout << "empty   = "  << s_empty   << std::endl;
    std::cout << "ints    = "  << s_ints    << std::endl;
    std::cout << "doubles = "  << s_doubles << std::endl;
    std::cout << "chars   = "  << s_chars   << std::endl;
    std::cout << "bools   = "  << s_bools   << std::endl;
    std::cout << "many    = "  << s_many    << std::endl;
    std::cout << "join    = "  << s_join    << std::endl;
    std::cout << "rjoin   = "  << s_rjoin   << std::endl;
    std::cout << "reverse = "  << s_reverse << std::endl;
    std::cout << "w_many::N    = " << w_many::N    << std::endl;
    std::cout << "w_join::N    = " << w_join::N    << std::endl;
    std::cout << "w_rjoin::N   = " << w_rjoin::N   << std::endl;
    std::cout << "w_reverse::N = " << w_reverse::N << std::endl;
}

int main(){
    std::cout << "Hello, World!" << std::endl << std::endl;
    print_basic_types();
    print_demangler();
    return 0;
}