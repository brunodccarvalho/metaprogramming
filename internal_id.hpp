#ifndef METAPROGRAMMING_INTERNAL_ID_HPP
#define METAPROGRAMMING_INTERNAL_ID_HPP

template <typename D>
class internal_id {
  private:
    static int _id_counter;
    const int _internal_id;
  public:
    internal_id();
    internal_id(const internal_id&);
    internal_id(internal_id&&) noexcept;

    int _id() const;
};

#endif //METAPROGRAMMING_INTERNAL_ID_HPP
