#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>

namespace topit {
  
  template< class T >
  struct Vector {
    
    public:
      Vector();
      ~Vector();

      bool isEmpty() const noexcept;

    private:
      T* data;
      size_t size, cap;
  };
}

template< class T >
topit::Vector< T >::Vector() :
  data_(nullptr),
  size_(0),
  cap_(0),
{}

template< class T >
topit::Vector< T >::~Vector() {
  delete[] data_;
}

template< class T >
bool topit::Vector< T >::isEmpty() const noexcept {
  return !size_;
}

#endif