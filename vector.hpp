#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>

namespace topit {
  
  template< class T >
  struct Vector {
    
    public:
      Vector();
      ~Vector();
      Vector(const Vector&);
      Vector(Vector&&);
      Vector& operator=(const Vector&);
      Vector& operator=(Vector&&);

      bool isEmpty() const noexcept; //дз
      bool getSize() const noexcept; //дз
      bool getCapacity() const noexcept; //дз

      void popBack(); //дз
      void pushBack(const T& value); //дз
      void insert(size_t i, const T& v);
      void erase(size_t i);

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

template< class T >
void topit::Vector< T >::pushBack(const T& value) {

}

#endif