#pragma once

#include <inttypes.h>

#include <cassert>
#include "../iterators/iterator_lagacy_random_access.h"
#include "../iterators/iterator_reverse.h"
namespace sage {

template <typename Type, int32_t ArrSize>
class array {
public:
    using iterator = sage::LegacyRandomAccessIterator<Type>;
    using citerator = sage::LegacyRandomAccessIterator<const Type>;
    using riterator = sage::reverse_iterator<iterator>;
    using creverse_iterator = sage::reverse_iterator<citerator>;
    /** @brief Access the first element. **/
    Type& front() {
        assert(ArrSize > 0);
        return _data_buffer[0];
    }

    /** @brief Access the first element. **/
    const Type& front() const {
        assert(ArrSize > 0);
        return _data_buffer[0];
    }

    /** @brief Access the last element. **/
    Type& back() {
        assert(ArrSize > 0);
        return _data_buffer[ArrSize - 1];
    }

    /** @brief Access the last element. **/
    const Type& back() const {
        assert(ArrSize > 0);
        return _data_buffer[ArrSize - 1];
    }

    /** @brief Direct access to the underlying array. **/
    Type* data() {
        return _data_buffer;
    }

    /** @brief Direct access to the underlying array. **/
    const Type* data() const {
        return _data_buffer;
    }

    /** @brief Fill the container with specified value. **/
    void fill(const Type& value) {
        for (int32_t i = 0; i < ArrSize; ++i) {
            _data_buffer[i] = value;
        }
    }

    /** @brief Checks whether the container is empty. **/
    bool empty() const {
        return (ArrSize == 0);
    }

    /** @brief Returns the number of elements. **/
    int32_t size() const {
        return ArrSize;
    }

    /** @brief Access specified element. **/
    Type& operator[](int32_t pos) {
        assert(pos < ArrSize);
        return _data_buffer[pos];
    }

    /** @brief Access specified element. **/
    const Type& operator[](int32_t pos) const {
        assert(pos < ArrSize);
        return _data_buffer[pos];
    }

    iterator begin() {
        return iterator(_data_buffer);
    }

    citerator begin() const {
        return cbegin();
    }

    citerator cbegin() const {
        return citerator(_data_buffer);
    } 

    riterator rbegin() {
        return reverse_iterator(end());
    }

    creverse_iterator rbegin() const {
        return creverse_iterator(end());
    }

    iterator end() {
        return iterator(_data_buffer + ArrSize);
    }

    citerator end() const {
        return cend();
    }
    
    citerator cend() const {
        return citerator(_data_buffer + ArrSize);
    }

    riterator rend() {
        return riterator(begin());
    }

    creverse_iterator rend() const {
        return creverse_iterator(begin());
    }

    Type _data_buffer[ArrSize];
};

template<typename Type, int32_t ArrSize>
bool operator==(const array<Type, ArrSize>& arr1, const array<Type, ArrSize>& arr2) {
    for(int32_t pos = 0; pos < arr1.size(); ++pos) {
        if(arr1[pos] != arr2[pos]) {
            return false;
        }
    }
    return true;
}

template<typename Type, int32_t ArrSize>
bool operator!=(const array<Type, ArrSize>& arr1, const array<Type, ArrSize>& arr2) {
    return !(arr1 == arr2);
}

};  // namespace sage