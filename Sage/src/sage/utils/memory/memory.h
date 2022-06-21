#pragma once

#include "src/sage/dstructs/iterators/iterator_forward.h"

namespace sage {

template <typename ForwardIterator, typename Size, typename Type, typename Allocator>
void uninitialized_fill(ForwardIterator first, Size size, const Type& type, Allocator& alloc) {
    ForwardIterator current = first;
    try {
        for (; size > 0; --size, ++current) {
            alloc.construct(&*current, type);
        }
    } catch (...) {
        std::_Destroy(first, current, alloc);
        __throw_exception_again;
    }
}

template <typename InputIterator, typename ForwardIterator, typename Allocator>
ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result, Allocator& alloc) {
    ForwardIterator current = result;
    try {
        for (; first != last; ++first, ++current) {
            alloc.construct(&*current, *first);
        }
        return current;
    } catch (...) {
        std::_Destroy(result, current, alloc);
        __throw_exception_again;
    }
}

template <typename ForwardIterator, typename Size, typename Allocator>
void uninitialized_default(ForwardIterator first, Size n, Allocator& alloc) {
    ForwardIterator current = first;
    try {
        for (; n > 0; --n, ++current) {
            std::cout << " > " << *first << std::endl;
            alloc.construct(&*current, *first);
        }
    } catch (...) {
        std::_Destroy(first, current, alloc);
        __throw_exception_again;
    }
}

template <typename InputIterator, typename ForwardIterator, typename Allocator>
inline ForwardIterator uninitialized_move(InputIterator first, InputIterator last, ForwardIterator result, Allocator& alloc) {
    return sage::uninitialized_copy(std::make_move_iterator(first), std::make_move_iterator(last),
                                    result, alloc);
}

}  // namespace sage