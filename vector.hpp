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
      size_t getSize() const noexcept; //дз
      size_t getCapacity() const noexcept; //дз

      void pushBack(const T& value); //дз
      void popBack(); //дз
      void insert(size_t i, const T& v);
      void erase(size_t i);

    private:
      T* data_;
      size_t size_, cap_;
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
  return size_ == 0;
}

template< class T >
size_t topit::Vector< T >::getSize() const noexcept {
  return size_;
}

template< class T >
size_t topit::Vector< T >::getCapacity() const noexcept {
  return cap_;
}

template< class T >
void topit::Vector< T >::pushBack(const T& value) {
  if (size_ == cap_) {
    size_t newCap = (cap_ == 0) ? 1 : cap_ * 2;
    T* newData = new T[newCap];

    for (size_t i = 0; i < size; ++i) {
      newData[i] = data_[i];
    }

    delete data_[];
    data_ = newData;
    cap_ = newCap;
  }

  data_[size_] = value;
  ++size_;
}

template< class T >
void topit::Vector< T >::popBack() {
  data[size_].~T();
  --size_;
}

#endif