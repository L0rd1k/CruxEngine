#pragma once 

#include <inttypes.h>

namespace sage {

template <typename Itr>
void advance(Itr &it, const int32_t n) {
    for (int32_t i = 0; i < std::abs(n); ++i) {
        (n > 0) ? ++it : --it;
    }
}

template <typename Itr>
int32_t distance(Itr itr1, Itr itr2) {
    int32_t distance = 0;
    while (itr1 != itr2) {
        ++itr1;
        ++distance;
    }
    return distance;
}

template <typename Itr>
Itr next(Itr it, const int32_t n = 1) {
    sage::advance(it, n);
    return it;
}

template <typename Itr>
Itr prev(Itr it, const int32_t n = 1) {
    sage::advance(it, -n);
    return it;
}

template <class Type, const int32_t Size>
Type* begin(Type (&array)[Size]) {
    return array;
}

template <class Type, const int32_t Size>
Type* end(Type (&array)[Size]) {
    return sage::next(array, Size);
}


}