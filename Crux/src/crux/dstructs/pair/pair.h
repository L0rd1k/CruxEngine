#pragma once

#include "pair_base.h"

namespace crux {

template <typename Type1, typename Type2>
class pair : private pair_base {
public:
    using value_type1 = Type1;
    using value_type2 = Type2;

    value_type1 first;   //> Copy of the first element;
    value_type2 second;  //> Copy of the second element;

    explicit constexpr pair()
        : first(), second() {}

    pair(const value_type1& val1, const value_type2& val2)
        : first(val1), second(val2) {
    }

    void swap(pair& p) noexcept {
        std::swap(first, p.first);
        std::swap(second, p.second);
    }

    pair& operator=(const pair& p) {
        first = p.first;
        second = p.second;
        return *this;
    }
    
    pair& operator=(pair&& p)  {
        first = std::forward<value_type1>(p.first);
        second = std::forward<value_type2>(p.second);
        return *this;
    }

};

template <typename T1, typename T2>
inline constexpr bool operator==(const crux::pair<T1, T2>& val1, const crux::pair<T1, T2>& val2) {
    return val1.first == val2.first && val1.second == val2.second;
}

template <typename T1, typename T2>
inline constexpr bool operator!=(const crux::pair<T1, T2>& val1, const crux::pair<T1, T2>& val2) {
    return !(val1 == val2);
}

template <typename T1, typename T2>
inline constexpr bool operator<(const crux::pair<T1, T2>& val1, const crux::pair<T1, T2>& val2) {
    return val1.first < val2.first || (!(val2.first < val1.first) && val1.second < val2.second);
}

template <typename T1, typename T2>
inline constexpr bool operator>(const crux::pair<T1, T2>& val1, const crux::pair<T1, T2>& val2) {
    return val2 < val1;
}

template <typename T1, typename T2>
inline constexpr bool operator<=(const crux::pair<T1, T2>& val1, const crux::pair<T1, T2>& val2) {
    return !(val2 < val1);
}

template <typename T1, typename T2>
inline constexpr bool operator>=(const crux::pair<T1, T2>& val1, const crux::pair<T1, T2>& val2) {
    return !(val1 < val2);
}

template <typename T1, typename T2>
inline void swap(crux::pair<T1, T2>& val1, crux::pair<T1, T2>& val2) noexcept {
    val1.swap(val2);
}

template <typename T1, typename T2>
inline crux::pair<T1, T2> make_pair(T1&& val1, T2&& val2) {
    return pair<T1, T2>(std::forward<T1>(val1), std::forward<T2>(val2));
}

}  // namespace crux
