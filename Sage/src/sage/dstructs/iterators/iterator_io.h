#pragma once

#include "iterator_operations.h"

namespace sage {
/**
 * @brief Empty class to identify the category of an iterator as an input iterator
 * @details Input iterators are iterators that can be used in sequential input operations, 
 * where each value pointed by the iterator is read only once and then the iterator is incremented.
 * 1) Copy-consructible, copy-assignable and destructible: X b(a); b = a;
 * 2) Supports equality/inequality comparisons: a == b; a != b
 * 3) Can be dereferenced as an rvalue: *a; a->m
 * 4) Can be incremented: ++a; (void)a++; *a++
 **/
template <typename Type>
class IOIterator {
public:

    using value_type = Type;
    using reference = Type&;
    using pointer = Type*;
    using difference_type = std::ptrdiff_t;  
    using iterator_category = std::input_iterator_tag;

    virtual ~IOIterator() {
    }

    IOIterator(const IOIterator& itr) : _dataPtr(itr._dataPtr) {
    }

    IOIterator<value_type>& operator++() {
        ++_dataPtr;
        return *this;
    }

    IOIterator<value_type> operator++(const int32_t) {
        IOIterator<value_type> temp = *this;
        ++(*this);
        return temp;
    }

    /** @brief Accesses the underlying iterator. **/
    pointer base() const {
        return _dataPtr;
    }

    /** @brief Dereferencing operator. **/
    reference operator*() const {
        return *(_dataPtr);
    }

    pointer operator->() const {
        return _dataPtr;
    }

    IOIterator &operator=(const IOIterator &itr) {
        if (&itr != this) {
            _dataPtr = itr._dataPtr;
        }
        return *this;
    }

private:
    pointer _dataPtr;
};

/** @brief Checking for equality. **/
template <typename Itr1, typename Itr2>
bool operator==(const IOIterator<Itr1> itr1, const IOIterator<Itr2> itr2) {
    return itr1.base() == itr2.base();
}

/** @brief Checking for inequality. **/
template <typename Itr1, typename Itr2>
bool operator!=(const IOIterator<Itr1> itr1, const IOIterator<Itr2> itr2) {
}

};  // namespace sage