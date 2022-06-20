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
        for(; first != last; ++first, ++current) {
            alloc.construct(&*current, *first);
        }
        return current;
    } catch (...) {
        std::_Destroy(result, current, alloc);
        __throw_exception_again;
    }
}
















// /** @brief Copies elements from the range [first, last) to
//  * an uninitialized memory area beginning at d_first.
//  * @return Iterator to the element past the last element copied. **/
// template <class InputIterator, class ForwardIterator>
// ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator d_first) {
//     using Value = typename std::iterator_traits<ForwardIterator>::value_type;
//     ForwardIterator current = d_first;
//     try {
//         for (; first != last; ++first, (void)++current) {
//             ::new (static_cast<void*>(&*current)) Value(*first);
//         }
//         return current;
//     } catch (...) {
//         for (; d_first != current; ++d_first) {
//             d_first->~Value();
//         }
//         throw;
//     }
// }

// template <class ForwardIterator, class Type>
// void uninitialized_fill(ForwardIterator first, ForwardIterator last, const Type& value) {
//     using Value = typename std::iterator_traits<ForwardIterator>::value_type;
//     ForwardIterator current = first;
//     try {
//         for (; current != last; ++current) {
//             //> Construct copy of x in *ptr;
//             ::new (static_cast<void*>(&*current)) Value(value);
//         }
//     } catch (...) {
//         for (; first != current; ++first) {
//             first->~Value();  //> Destroy elements;
//         }
//         throw;
//     }
// }

// template <class InputIterator, class ForwardIterator>
// ForwardIterator uninitialized_move(InputIterator first, InputIterator last, ForwardIterator d_first) {
//     using Value = typename std::iterator_traits<ForwardIterator>::value_type;
//     ForwardIterator current = d_first;
//     try {
//         for (; first != last; ++first, (void)++current) {
//             ::new (const_cast<void*>(static_cast<const volatile void*>(&*current))) Value(std::move(*first));
//         }
//         return current;
//     } catch (...) {
//         std::destroy(d_first, current);
//         throw;
//     }
// }

// template <typename InputIterator, typename ForwardIterator, typename Allocator>
// ForwardIterator uninitialized_copy_a(InputIterator first, InputIterator last, ForwardIterator result, Allocator& alloc) {
//     ForwardIterator cur = result;
//     try {
//         for (; first != last; ++first, ++cur)
//             alloc.construct(&*cur, *first);
//         return cur;
//     } catch (...) {
//         std::_Destroy(result, cur, alloc);
//         __throw_exception_again;
//     }
// }

// template <typename InputIterator, typename ForwardIterator, typename Allocator>
// inline ForwardIterator uninitialized_move_a(InputIterator first, InputIterator last,
//                                             ForwardIterator result, Allocator& alloc) {
//     return sage::uninitialized_copy_a(std::make_move_iterator(first), std::make_move_iterator(last), result, alloc);
// }

}  // namespace sage