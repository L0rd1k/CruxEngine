#pragma once

#include "src/crux/dstructs/allocator/allocator.h"
#include "src/crux/dstructs/iterators/iterator_lagacy_random_access.h"
#include "src/crux/dstructs/iterators/iterator_operations.h"
#include "src/crux/dstructs/iterators/iterator_reverse.h"

namespace crux {

/** @brief Vector memory class. **/
template <typename Type, typename Allocator = crux::allocator<Type>>
class vector_base {
public:
    using value_type = Type;
    using allocator_type = Allocator;
    using size_type = size_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = typename std::allocator_traits<Allocator>::pointer;
    using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;
    using iterator = crux::LegacyRandomAccessIterator<Type>;
    using const_iterator = crux::LegacyRandomAccessIterator<const Type>;
    using reverse_iterator = crux::reverse_iterator<iterator>;
    using const_reverse_iterator = crux::reverse_iterator<const_iterator>;

    vector_base()
        : _alloc() {
    }

    vector_base(const allocator_type& alloc)
        : _alloc(alloc) {
    }

    vector_base(size_type n) : _alloc() {
        this->_start = this->_alloc.allocate(n);
        this->_finish = this->_start;
        this->_storage_end = this->_start + n;
    }

    vector_base(size_type n, const allocator_type& alloc)
        : _alloc(alloc) {
        this->_start = this->_alloc.allocate(n);
        this->_finish = this->_start;
        this->_storage_end = this->_start + n;
    }

    /** @brief Move operator. **/
    vector_base(vector_base&& a)
        : _alloc(a._alloc),
          _start(a._start),
          _finish(a._finish),
          _storage_end(a._storage_end) {
        a._start = a._finish = a._storage_end = nullptr;  //> Clear ownership of any memory.
    }

    /** @brief Destructor. **/
    ~vector_base() {
        _alloc.deallocate(_start, _storage_end - _start);
    }

    /** @brief Move assignment operator. **/
    vector_base& operator=(vector_base&& a) {
        std::swap(*this, a);
        return *this;
    }

    /** @brief No copy constructor. **/
    vector_base(const vector_base&) = delete;
    /** @brief No copy assignment. **/
    vector_base& operator=(const vector_base&) = delete;

    pointer _start;         //> start of allocation
    pointer _finish;        //> end of element sequence, start of space allocated for possible expansion
    pointer _storage_end;   //> end of allocated space
    allocator_type _alloc;  //> allocator
};

}  // namespace crux