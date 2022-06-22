#pragma once

#include <inttypes.h>

#include "iterator_operations.h"

namespace sage {

/** @brief Bidirectional iterators are iterators that can be used to access 
 * the sequence of elements in a range in both directions 
 * (towards the end and towards the beginning).
 * @details
 * 1) Copy-consructible, copy-assignable and destructible: X b(a); b = a;
 * 2) Supports equality/inequality comparisons: a == b; a != b
 * 3) Can be dereferenced as an rvalue: *a; a->m
 * 4) Can be incremented: ++a; (void)a++; *a++
 * 5) Default-constructible: X a; X()
 * 6) Multi-pass: neither dereferencing nor incrementing affects dereferenceability
 * 7) Can be decremented: --a; a--; *a--
 * **/
template <typename Type>
class BidirectionalIterator {
public:

    using value_type = Type;
    using reference = Type&;
    using pointer = Type*;
    using difference_type = std::ptrdiff_t;  
    using iterator_category = std::bidirectional_iterator_tag;

    BidirectionalIterator() : _dataPtr(nullptr) {
    }

    BidirectionalIterator(pointer const valType) : _dataPtr(valType) {
    }

    BidirectionalIterator(const BidirectionalIterator& itr) : _dataPtr(itr._dataPtr) {
    }

    virtual ~BidirectionalIterator() {
    }

    reference operator*() const {
        return *(_dataPtr);
    }

    pointer operator->() const {
        return _dataPtr;
    }

    BidirectionalIterator& operator++() {
        ++_dataPtr;
        return *this;
    }

    BidirectionalIterator& operator++(const int32_t) {
        BidirectionalIterator& temp = *this;
        ++(*this);
        return temp;
    }

    BidirectionalIterator<value_type>& operator--() {
        --_dataPtr;
        return *this;
    }

    BidirectionalIterator<value_type> operator--(const int32_t) {
        BidirectionalIterator<value_type> temp = *this;
        --(*this);
        return temp;
    }

    BidirectionalIterator& operator=(const BidirectionalIterator& itr) {
        if (&itr != this) {
            _dataPtr = itr._dataPtr;
        }
        return *this;
    }

    bool operator==(const BidirectionalIterator& itr) const {
        return _dataPtr == itr._dataPtr;
    }

    bool operator!=(const BidirectionalIterator& itr) const {
        return _dataPtr != itr._dataPtr;
    }

private:
    pointer _dataPtr;
};

}  // namespace sage