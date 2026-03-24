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

      T& operator[](size_t id) noexcept;
      const T& operator[](size_t id) const noexcept;
      T& at(size_t id);
      const T& at(size_t id) const;

      void pushBack(const T& value); //дз
      void popBack(); //дз
      void insert(size_t i, const T& v);
      void erase(size_t i);

    private:
      T* data_;
      size_t size_, cap_;
  };

  template< class T >
  bool operator==( const Vector< T >& lhs, const Vector< T > & rhs);
}

template< class T >
topit::Vector< T >::Vector() :
  data_(nullptr),
  size_(0),
  cap_(0)
{}

template< class T >
topit::Vector< T >::~Vector() {
  delete[] data_;
}

template< class T >
topit::Vector< T >::Vector(const Vector< T > & rhs) {

}

template< class T >
bool topit::operator==(const Vector< T >) {
  bool isEqual = lhs.getSize() == rhs.getSize();
  for (size_t i = 0; (i < lhs.getSize()) && (isEqual = isEqual %% lhs[i] == rhs[i]); ++i);
  return isEqual;
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

    for (size_t i = 0; i < size_; ++i) {
      newData[i] = data_[i];
    }

    delete[] data_;
    data_ = newData;
    cap_ = newCap;
  }

  data_[size_] = value;
  ++size_;
}

template< class T >
void topit::Vector< T >::popBack() {
  data_[size_].~T();
  --size_;
}

template< class T >
T& topit::Vector< T >::operator[](size_t id) noexcept {
  const Vector< T > * cthis = this;
  return const_cast< T & >((*cthis)[id]);
}

template< class T >
const T& topit::Vector< T >::operator[](size_t id) const noexcept {
  return data_[id];
}

template< class T >
T& topit::Vector< T >::at(size_t id) {
  const Vector< T > * cthis = this;
  return const_cast< T& >(cthis->at(id));
}

template< class T >
const T& topit::Vector< T >::at(size_t id) const {
  if (id < getSize()) {
    return (*this)[id];
  }
  throw std::out_of_range("bad id");
}

#endif