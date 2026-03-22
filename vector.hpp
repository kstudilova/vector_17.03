#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>

namespace topit {
  
  template< class T >
  struct Vector {
    
    public:
      Vector();
      ~Vector();

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

#endif