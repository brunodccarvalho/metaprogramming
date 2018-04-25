#include "internal_id.hpp"

#include "functional"

template <typename D>
static int internal_id<D>::_id_counter =  1;

template <typename D>
internal_id<D>::internal_id():
    _internal_id(_id_counter++) {
}

template <typename D>
internal_id<D>::internal_id(const internal_id<D>&):
    _internal_id(_id_counter++) {
}

template <typename D>
internal_id<D>::internal_id(internal_id<D>&& other):
    _internal_id(std::move(other._internal_id)) {
}

template <typename D>
int internal_id<D>::_id() const {
    return _internal_id;
}