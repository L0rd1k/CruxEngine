#pragma once

#include "iterator_operations.h"

namespace sage {

/** @brief Forward iterators are iterators that can be used 
 * to access the sequence of elements in a range in the 
 * direction that goes from its beginning towards its end.
 * @details
 * 1) Copy-consructible, copy-assignable and destructible: X b(a); b = a;
 * 2) Supports equality/inequality comparisons: a == b; a != b
 * 3) Can be dereferenced as an rvalue: *a; a->m
 * 4) Can be incremented: ++a; (void)a++; *a++
 * 5) Default-constructible
 * 6) Multi-pass: neither dereferencing nor incrementing affects dereferenceability
 * **/
template <typename Type>
class ForwardIterator {
public:

    using value_type = Type;
    using reference = Type&;
    using pointer = Type*;

    ForwardIterator() : _dataPtr(nullptr) {
    }

    ForwardIterator(pointer const valType) : _dataPtr(valType) {
    }

    ForwardIterator(const ForwardIterator& itr) : _dataPtr(itr._dataPtr) {
    }

    virtual ~ForwardIterator() {
    }

    reference operator*() const {
        return *(_dataPtr);
    }

    pointer operator->() const {
        return _dataPtr;
    }

    ForwardIterator& operator++() {
        ++_dataPtr;
        return *this;
    }

    ForwardIterator& operator++(const int32_t) {
        ForwardIterator& temp = *this;
        ++(*this);
        return temp;
    }

    ForwardIterator &operator=(const ForwardIterator &itr) {
        if (&itr != this) {
            _dataPtr = itr._dataPtr;
        }
        return *this;
    }

    bool operator==(const ForwardIterator &itr) const {
        return _dataPtr == itr._dataPtr;
    }

    bool operator!=(const ForwardIterator& itr) const {
        return _dataPtr != itr._dataPtr;
    }

private:
    pointer _dataPtr;
};

}  // namespace sage