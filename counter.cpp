#include "counter.hpp"

template <typename D>
std::size_t instance_counter<D>::_total_instances = 0;

template <typename D>
std::size_t instance_counter<D>::_alive_instances = 0;

template <typename D>
std::size_t instance_counter<D>::total_instances() const {
    return _total_instances;
}

template <typename D>
std::size_t instance_counter<D>::alive_instances() const {
    return _alive_instances;
}

template <typename D>
instance_counter<D>::instance_counter() {
    ++_total_instances;
    ++_alive_instances;
}

template <typename D>
instance_counter<D>::instance_counter(const instance_counter<D>&) {
    ++_total_instances;
    ++_alive_instances;
}

template <typename D>
instance_counter<D>::instance_counter(instance_counter<D>&&) noexcept {
    ++_total_instances;
    ++_alive_instances;
}

template <typename D>
instance_counter<D>::~instance_counter() {
    --_alive_instances;
}