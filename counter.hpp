#ifndef METAPROGRAMMING_COUNTER_HPP
#define METAPROGRAMMING_COUNTER_HPP

#include <cstddef>

template <typename D>
class instance_counter {
  private:
    static std::size_t _total_instances, _alive_instances;
    ~instance_counter();
  public:
    instance_counter();
    instance_counter(const instance_counter&);
    instance_counter(instance_counter&&) noexcept;

    std::size_t total_instances() const;
    std::size_t alive_instances() const;
};



#endif //METAPROGRAMMING_COUNTER_HPP
