#pragma once

#include <inttypes.h>
#include <type_traits>

#include "iterator_operations.h"

namespace sage {
/** @brief  A LegacyRandomAccessIterator is a LegacyBidirectionalIterator
 * that can be moved to point to any element in constant time.
 * @details
 * 1) Copy-consructible, copy-assignable and destructible: X b(a); b = a;
 * 2) Supports equality/inequality comparisons: a == b; a != b
 * 3) Can be dereferenced as an rvalue: *a; a->m
 * 4) Can be incremented: ++a; (void)a++; *a++
 * 5) Default-constructible: X a; X()
 * 6) Multi-pass: neither dereferencing nor incrementing affects dereferenceability
 * 7) Can be decremented: --a; a--; *a--
 * 8) Supports arithmetic operators + and -
 * 9) Supports inequality comparisons (<, >, <= and >=) between iterators
 * 10) Supports compound assignment operations += and -=
 * 11) Supports offset dereference operator ([])
 * **/
template <typename Type>
class LegacyRandomAccessIterator {
private:
    friend class LegacyRandomAccessIterator<const Type>;
public:
    using value_type = Type;
    using reference = Type&;
    using pointer = Type*;
    using difference_type = std::ptrdiff_t;  
    using iterator_category = std::random_access_iterator_tag;

    LegacyRandomAccessIterator() : _dataPtr(nullptr) {
    }

    LegacyRandomAccessIterator(pointer const valType) : _dataPtr(valType) {
    }

    LegacyRandomAccessIterator(const LegacyRandomAccessIterator& itr) : _dataPtr(itr._dataPtr) {
    }

    template<typename CType>
    LegacyRandomAccessIterator(LegacyRandomAccessIterator<CType> itr) {
        static_assert(std::is_same<Type, const CType>::value);
        _dataPtr = itr._dataPtr;
    }

    virtual ~LegacyRandomAccessIterator() {
    }

    reference operator*() const {
        return *(_dataPtr);
    }

    pointer operator->() const {
        return _dataPtr;
    }

    LegacyRandomAccessIterator& operator++() {
        ++_dataPtr;
        return *this;
    }

    LegacyRandomAccessIterator& operator++(const int32_t) {
        LegacyRandomAccessIterator& temp = *this;
        ++(*this);
        return temp;
    }

    LegacyRandomAccessIterator<value_type>& operator--() {
        --_dataPtr;
        return *this;
    }

    LegacyRandomAccessIterator<value_type> operator--(const int32_t) {
        LegacyRandomAccessIterator<value_type> temp = *this;
        --(*this);
        return temp;
    }


    template<typename CType>
    LegacyRandomAccessIterator<value_type>& operator=(LegacyRandomAccessIterator<CType> itr) {
        static_assert(std::is_same<Type, CType>::value);
        _dataPtr = itr._dataPtr;
    }

    LegacyRandomAccessIterator& operator=(const LegacyRandomAccessIterator& itr) {
        if (&itr != this) {
            _dataPtr = itr._dataPtr;
        }
        return *this;
    }

    LegacyRandomAccessIterator& operator+=(int32_t pos) {
        _dataPtr += pos;
        return *this;
    }

    LegacyRandomAccessIterator& operator-=(int32_t pos) {
        _dataPtr -= pos;
        return *this;
    }

    reference operator[](int32_t pos) const {
        return *(_dataPtr + pos);
    }

    bool operator==(const LegacyRandomAccessIterator& itr) const {
        return _dataPtr == itr._dataPtr;
    }

    bool operator!=(const LegacyRandomAccessIterator& itr) const {
        return _dataPtr != itr._dataPtr;
    }

    pointer base() const {
        return _dataPtr;
    }

private:
    pointer _dataPtr;
};

template <typename Type>
LegacyRandomAccessIterator<Type> operator+(LegacyRandomAccessIterator<Type> itr, int32_t n) {
    itr += n;
    return itr;
}

template <typename Type>
LegacyRandomAccessIterator<Type> operator+(int32_t n, LegacyRandomAccessIterator<Type> itr) {
    itr += n;
    return itr;
}

template <typename Type>
LegacyRandomAccessIterator<Type> operator-(LegacyRandomAccessIterator<Type> itr, int32_t n) {
    itr -= n;
    return itr;
}

template <typename Type>
LegacyRandomAccessIterator<Type> operator-(int32_t n, LegacyRandomAccessIterator<Type> itr) {
    itr -= n;
    return itr;
}

template <typename Type>
int32_t operator-(LegacyRandomAccessIterator<Type> itr1, LegacyRandomAccessIterator<Type> itr2) {
    return static_cast<int32_t>(itr1.operator->() - itr2.operator->());
}

template <typename Type>
bool operator<(LegacyRandomAccessIterator<Type> itr1, LegacyRandomAccessIterator<Type> itr2) {
    return itr1.operator->() < itr2.operator->();
}

template <typename Type>
bool operator>(LegacyRandomAccessIterator<Type> itr1, LegacyRandomAccessIterator<Type> itr2) {
    return itr1.operator->() > itr2.operator->();
}

template <typename Type>
bool operator<=(LegacyRandomAccessIterator<Type> itr1, LegacyRandomAccessIterator<Type> itr2) {
    return itr1.operator->() <= itr2.operator->();
}

template <typename Type>
bool operator>=(LegacyRandomAccessIterator<Type> itr1, LegacyRandomAccessIterator<Type> itr2) {
    return itr1.operator->() >= itr2.operator->();
}

};  // namespace sage