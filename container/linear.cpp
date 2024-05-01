#include "linear.hpp"

namespace lasd {

// Linear Container
/* ************************************************************************** */

// Operators

template <typename Data>
inline bool LinearContainer<Data>::operator==(const LinearContainer<Data> &con) const noexcept {
  if (size != con.size) {
    return false;
  }

  for (unsigned long i = 0; i < size; ++i) {
    if ((*this)[i] != con[i]) {
      return false;
    }
  }
  return true;
}

template <typename Data>
inline bool LinearContainer<Data>::operator!=( const LinearContainer<Data> &con) const noexcept {
  return !(*this == con);
}

// Specific Methods

template <typename Data>
inline const Data &LinearContainer<Data>::Front() const {
  if (size == 0) {
    throw std::length_error("Struttura vuota");
  }
  return (*this)[0];
}

template <typename Data> inline Data &LinearContainer<Data>::Front() {
  if (size != 0) {
    throw std::length_error("Struttura vuota");
  }
  return (*this)[0];
}

template <typename Data>
inline const Data &LinearContainer<Data>::Back() const {
  if (size == 0) {
    throw std::length_error("Struttura vuota");
  }
  return (*this)[size - 1];
}

template <typename Data> inline Data &LinearContainer<Data>::Back() {
  if (size == 0) {
    throw std::length_error("Struttura vuota");
  }
  return (*this)[size - 1];
}
// Overrided Methods

template <typename Data>
inline void LinearContainer<Data>::Traverse(TraverseFun func) const {
  PreOrderTraverse(func);
}

template <typename Data>
inline void
LinearContainer<Data>::PreOrderTraverse(const TraverseFun func) const {
  for (unsigned long i = 0; i < size; ++i) {
    func((*this)[i]);
  }
}

template <typename Data>
inline void
LinearContainer<Data>::PostOrderTraverse(const TraverseFun func) const {

  for (unsigned long i = size; i > 0;) {
    func((*this)[--i]);
  }
}

template <typename Data> inline void LinearContainer<Data>::Map(MapFun func) {
  PreOrderMap(func);
}

template <typename Data>
inline void LinearContainer<Data>::PreOrderMap(MapFun func) {
  for (unsigned long i = 0; i < size; ++i) {
    func((*this)[i]);
  }
}

template <typename Data>
inline void LinearContainer<Data>::PostOrderMap(MapFun func) {
  for (unsigned long i = size; i > 0;) {
    func((*this)[--i]);
  }
}

/* ************************************************************************** */

// Sortable Linear Container
/* ************************************************************************** */

// Operators

template <typename Data>
inline bool SortableLinearContainer<Data>::operator==(const SortableLinearContainer<Data> &con) const noexcept {
 
  return LinearContainer<Data>::operator==(con);
}

template <typename Data>
inline bool SortableLinearContainer<Data>::operator!=(const SortableLinearContainer<Data> &con) const noexcept {
  
  return !(*this == con);
}

// Specific Methods

template <typename Data>
inline void SortableLinearContainer<Data>::Sort() noexcept {
  quickSort(0, size - 1);
}

template <typename Data>
void SortableLinearContainer<Data>::quickSort(unsigned long p,unsigned long q) noexcept {
  if (p >= q) {
    return;
  }

  if (q - p < 16) {
    insertionSort(p, q);
    return;
  }

  unsigned long h = partition(p, q);
  quickSort(p, h);
  quickSort(h + 1, q);
}

template <typename Data>
void SortableLinearContainer<Data>::insertionSort(unsigned long p, unsigned long q) noexcept {
  Data currentVal;
  unsigned long t;

  for (unsigned long i = p + 1; i <= q; i++) {

    currentVal = (*this)[i];
    t = i;
    while (t != ULONG_MAX && t > p && (*this)[t - 1] > currentVal) {
      (*this)[t] = (*this)[t - 1];
      --t;
    }
    (*this)[t] = currentVal;
  }
}

template <typename Data>
unsigned long
SortableLinearContainer<Data>::partition(unsigned long p,unsigned long q) noexcept {
  unsigned long i = p - 1;
  unsigned long j = q + 1;

  std::swap((*this)[p], (*this)[randomMedian(p, q)]);
  Data pivot = (*this)[p];

  do {
    do {
      --j;
    } while (pivot < (*this)[j]);

    do {
      ++i;
    } while (pivot > (*this)[i]);

    if (i < j) {
      std::swap((*this)[i], (*this)[j]);
    }
  } while (i < j);

  return j;
}

template <typename Data>
unsigned long
SortableLinearContainer<Data>::randomMedian(unsigned long p, unsigned long q) const noexcept {
  std::default_random_engine genx(std::random_device{}());
  std::uniform_int_distribution<unsigned long> dist(p, q);

  unsigned long i1 = dist(genx);
  unsigned long i2 = dist(genx);
  unsigned long i3 = dist(genx);
  Data a = (*this)[i1];
  Data b = (*this)[i2];
  Data c = (*this)[i3];

  if ((a < b && b < c) || (c < b && b < a))
    return i2;
  else if ((b < a && a < c) || (c < a && a < b))
    return i1;
  else
    return i3;
}

/* ************************************************************************** */
} // namespace lasd