#pragma once

#include "src/sage/dstructs/allocator/allocator.h"
#include "src/sage/dstructs/iterators/iterator_forward.h"
#include "src/sage/dstructs/iterators/iterator_lagacy_random_access.h"
#include "src/sage/dstructs/iterators/iterator_operations.h"
#include "src/sage/dstructs/iterators/iterator_reverse.h"
#include "src/sage/dstructs/vector/vector_base.h"
#include "src/sage/utils/memory/memory.h"

namespace sage {

/** @brief
 * **/
template <typename Type, typename Allocator = sage::allocator<Type>>
class vector : protected vector_base<Type, Allocator> {
private:
    using VecBase = vector_base<Type, Allocator>;

public:
    using value_type = Type;
    using allocator_type = Allocator;
    using size_type = size_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = typename std::allocator_traits<Allocator>::pointer;
    using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;
    using iterator = sage::LegacyRandomAccessIterator<Type>;
    using const_iterator = sage::LegacyRandomAccessIterator<const Type>;
    using reverse_iterator = sage::reverse_iterator<iterator>;
    using const_reverse_iterator = sage::reverse_iterator<const_iterator>;

    explicit vector(const allocator_type& alloc = allocator_type())
        : VecBase(alloc) {
    }

    /** @brief Constructs the vector. **/
    explicit vector(size_type size, const_reference val = Type(), const Allocator& alloc = Allocator())
        : VecBase(alloc, size) {
        uninitialized_fill(this->_start, this->_start + size, val);  //> copy elements
    }

    /** @brief The copy constructor. **/
    vector(const vector& vec)
        : VecBase(vec._alloc, vec.size()) {
        std::cout << "Copy constructor: " << vec.size() << " " << vec.capacity() << std::endl;
        this->_finish = sage::uninitialized_copy(vec.begin(), vec.end(), this->_start);
    }

    /** @brief Move constructor. **/
    vector(vector&& other)
        : VecBase{std::move(other)} {
    }

    ~vector() {
        std::_Destroy(this->_start, this->_finish, this->_alloc);
    }

    /** @brief Copy-assignment operator. **/
    vector& operator=(const vector& vec) {
        std::cout << "Copy assignment operator" << std::endl;
        if (capacity() < vec.size()) {              //> allocate new vector representation:
            vector<Type, Allocator> temp_Vec(vec);  //> copy allocato
            std::swap(*this, temp_Vec);                 //> swap
            return *this;                           //> implicitly destroy the old value
        }
        if (this == &vec) return *this;  //> Self assignment optimization;


        size_type curSize = size();
        size_type vecSize = vec.size();
        this->_alloc = vec._alloc;  //> Copy allocator
        if (vecSize <= curSize) {
            std::copy(vec.begin(), vec.begin() + vecSize, this->_start);
            for (pointer ptr = this->_start + vecSize; ptr != this->_storage_end; ++ptr) {
                ptr->~Type();
            }
        } else {
            std::copy(vec.begin(), vec.begin() + curSize, this->_start);
            uninitialized_copy(vec.begin() + curSize, vec.end(), this->_storage_end);
        }
        this->_storage_end = this->_start + vecSize;
        return *this;
    }

    vector& operator=(vector&& vec) {
        // clear();
        // swap(*this, vec);
    }

    void swap(vector& vec) {
        std::swap(this->_start, vec._start);
        std::swap(this->_finish, vec._finish);
        std::swap(this->_storage_end, vec._storage_end);
        std::__alloc_swap<allocator_type>::_S_do_it(this->_alloc, vec._alloc);
    }

    reference operator[](size_type n) {
        return *(this->_start + n);
    }

    void reserve(size_type n) {
        if (n <= capacity()) {
            return;
        }
        VecBase vec_b{this->_alloc, n};
        std::cout << "Vector base created" << std::endl;
        uninitialized_move(this->_start, this->_start + size(), vec_b._start);
        std::cout << "Uninitialized move" << std::endl;
        std::swap(*this, vec_b);
        std::cout << "Swap" << std::endl;
    }

    /** @brief Returns the number of elements that can be held in currently allocated storage. **/
    size_type capacity() const {
        return size_type(this->_storage_end - this->_start);
    }

    /** @brief Returns the number of elements. **/
    size_type size() const {
        return size_type(this->_finish - this->_start);
    }

    /** @brief Returns an iterator to the beginning **/
    iterator begin() {
        return iterator(this->_start);
    }

    /** @brief Returns a const iterator to the beginning **/
    const_iterator begin() const {
        return const_iterator(this->_start);
    }

    /** @brief Returns an iterator to the end **/
    iterator end() {
        return iterator(this->_finish);
    }

    /** @brief Returns a const iterator to the end **/
    const_iterator end() const {
        return const_iterator(this->_finish);
    }

    void clear() {
        std::_Destroy(this->_start, this->_finish, this->_alloc);
        this->_finish = this->_start;
    }
};

template <class T>
bool operator!=(const vector<T>& lhs, const vector<T>& rhs) {
    return !(lhs == rhs);
}

template <class T>
bool operator==(const vector<T>& lhs, const vector<T>& rhs) {
    if (lhs.size() != rhs.size()) {
        return false;
    }
    for (size_t i = 0; i < lhs.size(); ++i) {
        if (lhs[i] != rhs[i]) {
            return false;
        }
    }
    return true;
}

}  // namespace sage