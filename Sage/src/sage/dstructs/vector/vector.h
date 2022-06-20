#pragma once

#include "src/sage/dstructs/allocator/allocator.h"
#include "src/sage/dstructs/iterators/iterator_forward.h"
#include "src/sage/dstructs/iterators/iterator_lagacy_random_access.h"
#include "src/sage/dstructs/iterators/iterator_operations.h"
#include "src/sage/dstructs/iterators/iterator_reverse.h"
#include "src/sage/dstructs/vector/vector_base.h"
#include "src/sage/utils/memory/memory.h"

namespace sage {

/** @brief Dynamic array
 *   (constructor)
 *   (destructor)
 *   operator=
 *   assign
 *   + get_allocator
 *   + at
 *   + operator[]
 *   + front
 *   + back
 *   + data
 *   + begin
 *   + cbegin
 *   + end
 *   + cend
 *   + rbegin
 *   + crbegin
 *   + rend
 *   + crend
 *   + empty
 *   + size
 *   + max_size
 *   + reserve
 *   + capacity
 *   shrink_to_fit
 *   + clear
 *   insert
 *   emplace
 *   erase
 *   push_back
 *   emplace_back
 *   pop_back
 *   resize
 *   + swap
 **/
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

    /** @brief Default constructor creates no elements. **/
    vector()
        : VecBase() {
    }

    /** @brief Construct vector without elements.
     * @param alloc Custom allocator object.
     **/
    explicit vector(const allocator_type& alloc)
        : VecBase(alloc) {
    }

    /** @brief Constructs the vector of size copies. **/
    explicit vector(size_type size, const_reference val = value_type(), const allocator_type& alloc = allocator_type())
        : VecBase(size, alloc) {
        sage::uninitialized_fill(this->_start, size, val, this->_alloc);  //> copy elements
        this->_finish = this->_storage_end;
    }

    /** @brief Vector copy constructor. **/
    vector(const vector& vec)
        : VecBase(vec.size(), vec.get_allocator()) {
        this->_finish = sage::uninitialized_copy(vec.begin(), vec.end(), this->_start, this->_alloc);
    }

    /** @brief Vector move constructor. **/
    vector(vector&& other)
        : VecBase{std::move(other)} {
    }

    /** @brief Construct vector from an initializer list. **/
    vector(std::initializer_list<value_type> ilist, const allocator_type& alloc = allocator_type())
        : VecBase(alloc) {
        this->initialize_range(ilist.begin(), ilist.end(), std::random_access_iterator_tag());
    }

    /** @brief Construct vector from iterator range. **/
    template <typename InputIterator>
    vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) {
        this->initialize_dispatch(first, last);
    }

    /** @brief Vector destructor. **/
    ~vector() {
        std::_Destroy(this->_start, this->_finish, this->_alloc);
    }

    /** @brief Returns the associated allocator. **/
    allocator_type get_allocator() const {
        return allocator_type(this->_alloc);
    }

    /** @brief Copy-assignment operator. **/
    vector& operator=(const vector& vec) {
        if (this == &vec) return *this;       //> Self assignment optimization;
        if (this->capacity() < vec.size()) {  //> allocate new vector representation:
            pointer result = this->get_allocator().allocate(vec.size());
            try {
                sage::uninitialized_copy(vec.begin(), vec.end(), result, this->_alloc);  //> copy allocation
            } catch (...) {
                this->get_allocator().deallocate(result, vec.size());
                __throw_exception_again;
            }
            std::_Destroy(this->_start, this->_finish, this->_alloc);
            this->get_allocator().deallocate(this->_start, this->_storage_end - this->_start);
            this->_start = result;
            this->_storage_end = this->_start + vec.size();
        } else if (size() >= vec.size()) {
            std::_Destroy(std::copy(vec.begin(), vec.end(), begin(), end(), this->_alloc));
        } else {
            std::copy(vec._start, vec._start + size(), this->_start);
            sage::uninitialized_copy(vec._start + size(), vec._finish, this->_finish, this->_alloc);
        }
        this->_finish = this->_start + vec.size();
        return *this;
    }

    /** @brief Move copy-assignment operator. **/
    vector& operator=(vector&& vec) {
        this->clear();
        this->swap(*this, vec);
    }

    /** @brief Swap data between two vectors. **/
    void swap(vector& vec) {
        std::swap(this->_start, vec._start);
        std::swap(this->_finish, vec._finish);
        std::swap(this->_storage_end, vec._storage_end);
        /** @warning check. **/
        std::__alloc_swap<allocator_type>::_S_do_it(this->_alloc, vec._alloc);
    }

    // reference operator[](size_type n) {
    //     return *(this->_start + n);
    // }

    // const_reference operator[](size_type n) const {
    //     return *(this->_start + n);
    // }

    // reference at(size_type n) {
    //     if (n >= this->size()) {
    //         std::__throw_out_of_range(__N("sage::vector: Pos out of range."));
    //     }
    //     return (*this)[n];
    // }

    // const_reference at(size_type n) const {
    //     if (n >= this->size()) {
    //         std::__throw_out_of_range(__N("sage::vector: Pos out of range."));
    //     }
    //     return (*this)[n];
    // }

    // void reserve(size_type n) {
    //     if (n > this->max_size()) {
    //         std::__throw_length_error(__N("sage::vector: Reserve"));
    //     }
    //     if (n > this->capacity()) {
    //         const size_type old_size = size();
    //         pointer temp = allocate_and_copy(n, this->_start, this->_finish);
    //         std::_Destroy(this->_start, this->_finish, this->_alloc);
    //         this->_alloc.deallocate(this->_start, this->_storage_end - this->_start);
    //         this->_start = temp;
    //         this->_finish = temp + old_size;
    //         this->_storage_end = this->_start + n;
    //     }
    // }

    // void push_back(const value_type& x) {
    //     if (this->_finish != this->_storage_end) {
    //         this->_alloc.construct(this->_finish, x);
    //         ++this->_finish;
    //     } else {
    //         insert_aux(end(), x);
    //     }
    // }

    // pointer data() {
    //     return front();
    // }

    // const_pointer data() const {
    //     return front();
    // }

    /** @brief Returns the number of elements that can be held in currently allocated storage. **/
    size_type capacity() const {
        return size_type(this->_storage_end - this->_start);
    }

    /** @brief Returns the number of elements. **/
    size_type size() const {
        return size_type(this->_finish - this->_start);
    }

    size_type max_size() const {
        return this->get_allocator().max_size();
    }

    bool empty() const {
        return begin() == end();
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

    reverse_iterator rbegin() {
        return reverse_iterator(end());
    }

    const_reverse_iterator crbegin() const {
        return const_reverse_iterator(end());
    }

    reverse_iterator rend() {
        return reverse_iterator(begin());
    }

    const_reverse_iterator crend() const {
        return const_reverse_iterator(begin());
    }

    /** @brief Erase all object's elements. **/
    void clear() {
        std::_Destroy(this->_start, this->_finish, this->_alloc);
        this->_finish = this->_start;
    }

    reference front() {
        return *begin();
    }

    const_reference front() const {
        return *begin();
    }

    reference back() {
        return *(end() - 1);
    }

    const_reference back() const {
        return *(end() - 1);
    }

protected:
    template <typename ForwardIterator>
    void initialize_range(ForwardIterator first, ForwardIterator last, std::forward_iterator_tag) {
        const size_type n = sage::distance(first, last);
        this->_start = this->get_allocator().allocate(n);
        this->_storage_end = this->_start + n;
        this->_finish = sage::uninitialized_copy(first, last, this->_start, this->_alloc);
    }

    template <typename InputIterator>
    void initialize_dispatch(InputIterator first, InputIterator last) {
        using iter_category = typename std::iterator_traits<InputIterator>::iterator_category;
        this->initialize_range(first, last, iter_category());
    }


    //     template <typename ForwardIterator>
    //     pointer allocate_and_copy(size_type n, ForwardIterator first, ForwardIterator last) {
    //         pointer result = this->_alloc.allocate(n);
    //         try {
    //             uninitialized_copy_a(first, last, result, this->_alloc);
    //             return result;
    //         } catch (...) {
    //             this->_alloc.deallocate(result, n);
    //             __throw_exception_again;
    //         }
    //     }

    //     size_type check_length(size_type n, const char* msg) const {
    //         if (max_size() - size() < n) {
    //             std::__throw_length_error(__N(msg));
    //         }
    //         const size_type len = size() + std::max(size(), n);
    //         return (len < size() || len > max_size()) ? max_size() : len;
    //     }

    //     void insert_aux(iterator pos, const value_type& x) {
    //         if (this->_finish != this->_storage_end) {
    //             std::cout << "Finish != StorageEnd" << std::endl;
    //             this->_alloc.construct(this->_finish, *(this->_finish - 1));
    //             ++this->_finish;
    //             value_type x_copy = x;
    //             std::move_backward(pos.base(), this->_finish - 2, this->_finish - 1);
    //             *pos = x_copy;
    //         } else {
    //             const size_type len = check_length(size_type(1), "sage::vector: insert_aux");
    //             std::cout << "Length: " << len << std::endl;
    //             const size_type prev_elements = pos - begin();
    //             std::cout << "Prev Element: " << prev_elements << std::endl;
    //             pointer new_start(this->get_allocator().allocate(len));
    //             pointer new_finish(new_start);
    //             std::cout << new_start << " " << new_finish << std::endl;

    //             try {
    //                 this->get_allocator().construct(new_start + prev_elements, x);
    //                 std::cout << (new_start + prev_elements) << " " << &*begin() << " " << &*(this->begin()) << std::endl;

    //                 new_finish = 0;
    //                 new_finish = sage::uninitialized_move_a(this->_start, pos.base(), new_start, this->_alloc);
    //                 ++new_finish;
    //                 new_finish = sage::uninitialized_move_a(pos.base(), this->_finish, new_finish, this->_alloc);
    //             } catch (...) {
    //                 if (!new_finish) {
    //                     this->_alloc.destroy(new_start + prev_elements);
    //                 } else {
    //                     std::_Destroy(new_start, new_finish, this->_alloc);
    //                     this->_alloc.deallocate(new_start, len);
    //                     __throw_exception_again;
    //                 }
    //                 std::_Destroy(this->_start, this->_finish, this->_alloc);
    //                 this->_alloc.deallocate(this->_start, this->_storage_end - this->_start);
    //                 this->_start = new_start;
    //                 this->_finish = new_finish;
    //                 this->_storage_end = new_start + len;
    //             }
    //         }
    //     }
};

template <typename T, typename Alloc>
inline void swap(sage::vector<T, Alloc>& x, sage::vector<T, Alloc>& y) {
    x.swap(y);
}

// template <class T>
// bool operator!=(const vector<T>& lhs, const vector<T>& rhs) {
//     return !(lhs == rhs);
// }

// template <class T>
// bool operator==(const vector<T>& lhs, const vector<T>& rhs) {
//     if (lhs.size() != rhs.size()) {
//         return false;
//     }
//     for (size_t i = 0; i < lhs.size(); ++i) {
//         if (lhs[i] != rhs[i]) {
//             return false;
//         }
//     }
//     return true;

// }

}  // namespace sage