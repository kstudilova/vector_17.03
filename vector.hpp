#ifndef VECTOR_HPP
#define VECTOR_HPP

//кр
//строгая гарантия copy-and-swap
//тесты для копирования и перемещения
//insertх2, eraseх2 с тестами

//дз
//строгая гарантия, copy-and-swap
//итераторы вектора
// придумать несколько insert/erase с итераторами
//по 2 шт + тесты

#include <initializer_list>
#include <algorithm>
#include <cstddef>
#include <memory>
#include <cassert>

namespace topit {

  template< class T >
  struct Vector {
    
    public:
      Vector();
      ~Vector();
      Vector(const Vector< T >&);
      Vector(Vector< T >&&) noexcept;
      Vector(size_t size, const T& init);
      explicit Vector(std::initializer_list< T > il);
  
      Vector< T >& operator=(const Vector< T >&);
      Vector< T >& operator=(Vector< T >&&) noexcept;

      void swap(Vector< T >& rhs) noexcept;

      bool isEmpty() const noexcept; 
      size_t getSize() const noexcept; 
      size_t getCapacity() const noexcept;

      //Классная работа 30.03
      void reserve(size_t); //delta/required
      void shrinkToFit();
      void pushBackCount(size_t k, const T& value);
      template< class IT >
      void pushBackRange(IT b, size_t c);
      //всю работу с памятью переписать на placement new ДЗ 30.03
      //избавиться о  требования конструктора по умолчанию для T ДЗ 30.03

      T& operator[](size_t id) noexcept;
      const T& operator[](size_t id) const noexcept;
      T& at(size_t id);
      const T& at(size_t id) const;

      void pushBack(const T& value); 
      void popBack(); 

      void insert(size_t i, const T& v);
      void erase(size_t i);

      void insert(size_t i, const Vector< T >& rhs, size_t start, size_t end);
      void erase(size_t i, const Vector< T >& rhs, size_t start, size_t end);

      template< class VectorIterator, class FwdIterator >
      void insert(VectorIterator pos, FwdIterator start, FwdIterator end);

    private:
      T* data_;
      size_t size_, cap_;
      explicit Vector(size_t size);

      void unsafePushBack(const T& value); //КР 30.03
  };

  template< class T >
  bool operator==( const Vector< T >& lhs, const Vector< T > & rhs);
}

template< class T >
topit::Vector< T >::Vector(std::initializer_list< T > il) :
  Vector(il.size())
{
  size_t i = 0;
  for (auto it = il.begin(); it != il.end(); ++it) {
    data_[i++] = *it;
  }
}

template< class T >
topit::Vector< T >::Vector(size_t size):
  data_(size ? new T[size] : nullptr),
  size_(size),
  cap_(size)
{}

template< class T >
topit::Vector< T >::~Vector() {
  delete[] data_;
}

template< class T >
void topit::Vector< T >::swap(Vector< T >& rhs) noexcept {
  std::swap(data_, rhs.data_);
  std::swap(size_, rhs.size_);
  std::swap(cap_, rhs.cap_);
}

template< class T >
topit::Vector< T >& topit::Vector< T >::operator=(Vector< T >&& rhs) noexcept {
  Vector< T > cpy(std::move(rhs));
  swap(cpy);
  return *this;
}

template< class T >
topit::Vector< T >& topit::Vector< T >::operator=(const Vector< T >& rhs) {
  if (this == std::addressof(rhs)){
    return *this;
  }
  Vector< T > cpy = rhs;
  swap(cpy);
  return *this;
}

template< class T >
topit::Vector< T >::Vector(Vector< T >&& rhs) noexcept :
  data_(rhs.data_),
  size_(rhs.size_),
  cap_(rhs.cap_)
{
  rhs.data_ = nullptr;
}

template< class T >
topit::Vector< T >::Vector(const Vector< T > & rhs) :
  Vector(rhs.getSize())
{
  for (size_t i = 0; i < rhs.getSize(); ++i) {
    data_[i] = rhs[i];
  }
}

template< class T >
topit::Vector< T >::Vector(size_t size, const T& init) :
  Vector(size)
{
  for (size_t i = 0; i < size; ++i) {
    data_[i] = init;
  }
}

template< class T >
bool topit::operator==(const Vector< T > & lhs, const Vector< T > & rhs) {
  bool isEqual = lhs.getSize() == rhs.getSize();
  for (size_t i = 0; (i < lhs.getSize()) && (isEqual = isEqual && lhs[i] == rhs[i]); ++i);
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
template< class IT >
void topit::Vector< T >::pushBackRange(IT b, size_t c) { 
  // Если памяти не хватает на с
  // - делаем так, чтоб хватало на k*
  // Добавляем в конец*
}

template< class T >
void topit::Vector< T >::pushBackCount(size_t k, const T& val) {
  // Если памяти не хватает на k
  // - делаем так, чтоб хватало на k*
  // Добавляем в конец*
}

template< class T >
void topit::Vector< T >::unsafePushBack(const T& val) {
  assert(size_ < cap_);
  // Добавить в конец
}
//pushBackCount
//unsafePushBack


template< class T >
void topit::Vector< T >::popBack() {
  data_[size_].~T();
  --size_;
}

template< class T >
T& topit::Vector< T >::operator[](size_t id) noexcept {
  const Vector< T > * cthis = this;
  const T& ret = (*cthis)[id];
  return const_cast< T & >(ret);
}

template< class T >
const T& topit::Vector< T >::operator[](size_t id) const noexcept { //ВЕРНО
  return data_[id];
}

template< class T >
T& topit::Vector< T >::at(size_t id) {
  const Vector< T > * cthis = this;
  const T& ret = cthis->at(id);
  return const_cast< T& >(ret);
}

template< class T >
const T& topit::Vector< T >::at(size_t id) const {
  if (id < getSize()) {
    return (*this)[id];
  }
  throw std::out_of_range("bad id");
}

#endif
