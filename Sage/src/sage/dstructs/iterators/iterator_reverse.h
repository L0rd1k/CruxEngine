#pragma once

#include "iterator_operations.h"

namespace sage {

/** @brief This class reverses the direction in which a bidirectional
 *  or random-access iterator iterates through a range. **/
template <typename Iter>
class reverse_iterator {
public:

    using iterator_type = Iter;
    using value_type = typename Iter::value_type;
    using reference = typename Iter::value_type&;
    using pointer = typename Iter::value_type*;
    using difference_type = std::ptrdiff_t;  

    reverse_iterator() : _dataPtr(nullptr) {
    }

    reverse_iterator(const iterator_type itr) : _dataPtr(itr) {
    }

    template<typename IterType>
    reverse_iterator(const reverse_iterator<IterType> itr) : 
    _dataPtr(itr.base()) {
    }

    virtual ~reverse_iterator() {
    }

    iterator_type base() const {
        return _dataPtr;
    }

    reference operator*() const {
        iterator_type temp = _dataPtr;
        return *(--temp);
    }

    pointer operator->() const {
        return Prev(_dataPtr).operator->();
    }

    reverse_iterator<iterator_type>& operator++() {
        --_dataPtr;
        return *this;
    }

    reverse_iterator<iterator_type> operator++(const int32_t) {
        reverse_iterator<iterator_type> temp = *this;
        ++(*this);
        return temp;
    }

    reverse_iterator<iterator_type>& operator--() {
        ++_dataPtr;
        return *this;
    }

    reverse_iterator<iterator_type> operator--(const int32_t) {
        reverse_iterator<iterator_type> temp = *this;
        --(*this);
        return temp;
    }

    reverse_iterator<iterator_type>& operator=(const reverse_iterator<iterator_type>& itr) {
        if (&itr != this) {
            _dataPtr = itr._dataPtr;
        }
        return *this;
    }

    reverse_iterator<iterator_type>& operator+=(const int32_t pos) {
        _dataPtr -= pos;
        return *this;
    }

    reverse_iterator<iterator_type>& operator-=(const int32_t pos) {
        _dataPtr += pos;
        return *this;
    }

    reference operator[](const int32_t pos) const {
        return base()[-pos - 1];
    }

private:
    iterator_type _dataPtr;
};

template <typename Itr>
reverse_iterator<Itr> operator+(const reverse_iterator<Itr> &it, const int32_t n) {
    return reverse_iterator<Itr>(it.base() - n);
}

template <typename Itr>
reverse_iterator<Itr> operator+(const int32_t n, const reverse_iterator<Itr> &it) {
    return reverse_iterator<Itr>(it.base() - n);
}

template <typename Itr>
reverse_iterator<Itr> operator-(const reverse_iterator<Itr> it, const int32_t n) {
    return reverse_iterator<Itr>(it.base() + n);
}

template <typename Itr1, typename Itr2>
int32_t operator-(const reverse_iterator<Itr1> itr1, const reverse_iterator<Itr2> itr2) {
    return itr2.base() - itr1.base();
}

template <typename Itr1, typename Itr2>
bool operator==(const reverse_iterator<Itr1> itr1, const reverse_iterator<Itr2> itr2) {
    return itr1.base() == itr2.base();
}

template <typename Itr1, typename Itr2>
bool operator!=(const reverse_iterator<Itr1> itr1, const reverse_iterator<Itr2> itr2) {
    return !(itr1 == itr2);
}

template <typename Itr1, typename Itr2>
bool operator<(const reverse_iterator<Itr1> itr1, const reverse_iterator<Itr2> itr2) {
    return itr1.base() > itr2.base();
}

template <typename Itr1, typename Itr2>
bool operator>(const reverse_iterator<Itr1> itr1, const reverse_iterator<Itr2> itr2) {
    return itr1.base() < itr2.base();
}

template <typename Itr1, typename Itr2>
bool operator<=(const reverse_iterator<Itr1> itr1, const reverse_iterator<Itr2> itr2) {
    return itr1.base() >= itr2.base();
}

template <typename Itr1, typename Itr2>
bool operator>=(const reverse_iterator<Itr1> itr1, const reverse_iterator<Itr2> itr2) {
    return itr1.base() <= itr2.base();
}

}  // namespace sage