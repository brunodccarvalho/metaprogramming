#ifndef METAPROGRAMMING_EQUALITY_HPP
#define METAPROGRAMMING_EQUALITY_HPP

template <typename D>
class comparison {
};

template <typename D>
bool operator>(const comparison<D>& op1, const comparison<D>& op2) {
    const D& d1 = static_cast<const D&>(op1);
    const D& d2 = static_cast<const D&>(op2);
    return d2 < d1;
}

template <typename D>
bool operator==(const comparison<D>& op1, const comparison<D>& op2) {
    const D& d1 = static_cast<const D&>(op1);
    const D& d2 = static_cast<const D&>(op2);
    return !(d1 < d2) && !(d2 < d1);
}

template <typename D>
bool operator!=(const comparison<D>& op1, const comparison<D>& op2) {
    const D& d1 = static_cast<const D&>(op1);
    const D& d2 = static_cast<const D&>(op2);
    return (d1 < d2) && (d2 < d1);
}

template <typename D>
bool operator<=(const comparison<D>& op1, const comparison<D>& op2) {
    const D& d1 = static_cast<const D&>(op1);
    const D& d2 = static_cast<const D&>(op2);
    return d1 < d2 || !(d2 < d1);
}

template <typename D>
bool operator>=(const comparison<D>& op1, const comparison<D>& op2) {
    const D& d1 = static_cast<const D&>(op1);
    const D& d2 = static_cast<const D&>(op2);
    return d2 < d1 || !(d1 < d2);
}

#endif //METAPROGRAMMING_EQUALITY_HPP
