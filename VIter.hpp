#ifndef VITER_HPP
#define VITER_HPP

#include <cstddef>

namespace topit {
  template< class T >
  struct Vector;

  template< class T >
  class VectorIterator {
  public:
    explicit VectorIterator(T* ptr) noexcept;

    template< class U >
    VectorIterator(const VectorIterator< U >& other) noexcept;
    
    T& operator*() const noexcept;
    T* operator->() const noexcept;
    T& operator[](std::ptrdiff_t i) const noexcept;

    VectorIterator& operator++() noexcept;
    VectorIterator operator++(int) noexcept;
    VectorIterator& operator--() noexcept;
    VectorIterator operator--(int) noexcept;

    VectorIterator& operator+=(std::ptrdiff_t n) noexcept;
    VectorIterator& operator-=(std::ptrdiff_t n) noexcept;
    VectorIterator operator+(std::ptrdiff_t n) const noexcept;
    VectorIterator operator-(std::ptrdiff_t n) const noexcept;
    std::ptrdiff_t operator-(const VectorIterator& other) const noexcept;

    bool operator==(const VectorIterator& other) const noexcept;
    bool operator!=(const VectorIterator& other) const noexcept;
    bool operator<(const VectorIterator& other) const noexcept;
    bool operator>(const VectorIterator& other) const noexcept;
    bool operator<=(const VectorIterator& other) const noexcept;
    bool operator>=(const VectorIterator& other) const noexcept;

  private:
    T* ptr_;
    friend struct Vector< T >;
    template< class U >
    friend class VectorIterator;
  };
}

#endif