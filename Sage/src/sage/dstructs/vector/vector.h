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
 *   + (constructor)
 *   + (destructor)
 *   +/- operator=
 *
 *   +/- assign
 *
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
 *   + shrink_to_fit
 *   + clear
 *   insert
 *   + emplace
 *   + erase
 *   + push_back
 *   + emplace_back
 *   + pop_back
 *   + resize
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
     * @param alloc Custom allocator object. **/
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

    /** @brief Assign value to vector. **/
    void assign(size_type n, const_reference val) {
        std::cout << "Vector::assign";
        this->fill_assign(n, val);
    }

    /** @brief Swap data between two vectors. **/
    void swap(vector& vec) {
        std::swap(this->_start, vec._start);
        std::swap(this->_finish, vec._finish);
        std::swap(this->_storage_end, vec._storage_end);
        /** @warning check. **/
        std::__alloc_swap<allocator_type>::_S_do_it(this->_alloc, vec._alloc);
    }

    // template <typename InputIterator>
    // void assign(InputIterator first, InputIterator last) {
    // }

    /** @brief  Inserts given value into %vector before specified iterator. **/
    iterator insert(iterator pos, const_reference x) {
        const size_type n = pos - this->begin();
        if(this->_finish != this->_storage_end && pos == this->end()) {
            this->get_allocator().construct(this->_finish, x);
            ++this->_finish;
        } else {
            if(this->_finish != this->_storage_end) {
                Type x_copy = x;
                this->insert_aux(pos, std::move(x_copy));
            } else {
                this->insert_aux(pos, x);
            }
        }
        return iterator(this->_start + n);
    }

    /** @brief  Inserts given value into %vector before specified iterator. **/
    iterator insert(iterator pos, value_type&& x) {
        return emplace(pos, std::move(x));
    }

    /** @brief Access to the data in the vector. **/
    reference operator[](size_type n) {
        return *(this->_start + n);
    }

    /** @brief Access to the data in the vector. **/
    const_reference operator[](size_type n) const {
        return *(this->_start + n);
    }

    /** @brief Safe way to get data object by index. **/
    reference at(size_type n) {
        if (n >= this->size()) {
            std::__throw_out_of_range(__N("sage::vector: Pos out of range."));
        }
        return (*this)[n];
    }

    /** @brief Safe way to get data object by index. **/
    const_reference at(size_type n) const {
        if (n >= this->size()) {
            std::__throw_out_of_range(__N("sage::vector: Pos out of range."));
        }
        return (*this)[n];
    }

    /** @brief Increase vector capacity. **/
    void reserve(size_type n) {
        if (n > this->max_size()) {
            std::__throw_length_error(__N("sage::vector: Reserve"));
        }
        if (n > this->capacity()) {
            const size_type old_size = this->size();
            pointer temp = this->allocate_and_copy(n, std::make_move_iterator(this->_start),
                                                   std::make_move_iterator(this->_finish));
            std::_Destroy(this->_start, this->_finish, this->_alloc);
            this->_alloc.deallocate(this->_start, this->_storage_end - this->_start);
            this->_start = temp;
            this->_finish = temp + old_size;
            this->_storage_end = this->_start + n;
        }
    }

    /** @brief Add data to the end if the vector. **/
    void push_back(const_reference x) {
        if (this->_finish != this->_storage_end) {
            this->get_allocator().construct(this->_finish, x);
            ++this->_finish;
        } else {
            this->insert_aux(end(), x);
        }
    }

    /** @brief Add data to the end if the vector. **/
    void push_back(value_type&& x) {
        emplace_back(std::move(x));
    }

    /** @brief Remove last element from vector. **/
    void pop_back() {
        --(this->_finish);
        this->_alloc.destroy(this->_finish);
    }

    /** @brief Insert data in vector on spcific position. **/
    template <typename... Args>
    iterator emplace(iterator pos, Args&&... args) {
        const size_type n = pos - this->begin();
        if (this->_finish != this->_storage_end && pos == this->end()) {
            this->get_allocator().construct(this->_finish, std::forward<Args>(args)...);
            ++this->_finish;
        } else {
            this->insert_aux(pos, std::forward<Args>(args)...);
            return iterator(this->_start + n);
        }
    }

    /** @brief Appends a new element to the end of the container. **/
    template <typename... Args>
    void emplace_back(Args&&... args) {
        if (this->_finish != this->_storage_end) {
            this->get_allocator().construct(this->_finish, std::forward<Args>(args)...);
            ++(this->_finish);
        } else {
            insert_aux(this->end(), std::forward<Args>(args)...);
        }
    }

    /** @brief Remove element at the given position. **/
    iterator erase(iterator pos) {
        if (pos + 1 != this->end()) {
            std::move(pos + 1, this->end(), pos);
        }
        --this->_finish;
        this->get_allocator().destroy(this->_finish);
        return pos;
    }

    /** @brief Remove elements at the given range. **/
    iterator erase(iterator first, iterator last) {
        if (first != last) {
            if (last != this->end()) {
                std::move(last, this->end(), first);
            }
            pointer pos = first.base() + (this->end() - last);
            std::_Destroy(pos, this->_finish, this->_alloc);
            this->_finish = pos;
        }
        return first;
    }

    /** @brief Get pointer of first vector element. **/
    pointer data() {
        return front();
    }

    /** @brief Get const pointer of first vector element. **/
    const_pointer data() const {
        return front();
    }

    /** @brief Returns the number of elements that can be held in currently allocated storage. **/
    size_type capacity() const {
        return size_type(this->_storage_end - this->_start);
    }

    /** @brief Returns the number of elements.
     * @brief Current vector size. **/
    size_type size() const {
        return size_type(this->_finish - this->_start);
    }

    /** @brief Return max possible size of vector.
     * @return Max vector size. **/
    size_type max_size() const {
        return this->get_allocator().max_size();
    }

    /** @brief Resize vector to specific size.
     * @param[in] n Number of elements to resize. **/
    void resize(size_type n) {
        if (n > this->size()) {
            this->default_append(n - this->size());
        } else if (n < this->size()) {
            pointer pos = this->_start + n;
            std::_Destroy(pos, this->_finish, this->_alloc);
            this->_finish = pos;
        }
    }

    /** @brief Equate capacity() to size(). **/
    void shrink_to_fit() {
        sage::_shrink_to_fit<vector>::do_shrink(*this);
    }

    /** @brief Check if vector is + . **/
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

    /** @brief Returns reverse iterator to the begin. **/
    reverse_iterator rbegin() {
        return reverse_iterator(end());
    }

    /** @brief Returns a const reverse iterator to the begin. **/
    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(end());
    }

    /** @brief Returns reverse iterator to the end. **/
    reverse_iterator rend() {
        return reverse_iterator(begin());
    }

    /** @brief Returns a const reverse iterator to the end. **/
    const_reverse_iterator rend() const {
        return const_reverse_iterator(begin());
    }

    /** @brief Returns a const iterator to the start **/
    const_iterator cbegin() const {
        return const_iterator(this->_start);
    }

    /** @brief Returns a const iterator to the end **/
    const_iterator cend() const {
        return const_iterator(this->_finish);
    }

    /** @brief Returns a const reverse iterator to the begin. **/
    const_reverse_iterator crbegin() const {
        return const_reverse_iterator(end());
    }

    /** @brief Returns a const reverse iterator to the end. **/
    const_reverse_iterator crend() const {
        return const_reverse_iterator(begin());
    }

    /** @brief Erase all object's elements. **/
    void clear() {
        std::_Destroy(this->_start, this->_finish, this->_alloc);
        this->_finish = this->_start;
    }

    /** @brief Get reference to the first element of vector. **/
    reference front() {
        return *begin();
    }

    /** @brief Get const reference to the first element of vector. **/
    const_reference front() const {
        return *begin();
    }

    /** @brief Get reference to the last element of vector. **/
    reference back() {
        return *(end() - 1);
    }

    /** @brief Get const reference to the last element of vector. **/
    const_reference back() const {
        return *(end() - 1);
    }

private:
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

    template <typename InputIterator>
    void assign_aux(InputIterator first, InputIterator last) {
        pointer current(this->_start);
        for (; first != last && current != this->_finish; ++current, ++first) {
            *current = *first;
        }
        if (first == last) {
            std::_Destroy(current, this->_finish, this->_alloc);
            this->_finish = current;
        } else {
            this->insert(end(), first, last);
        }
    }

    template <typename... Args>
    void insert_aux(iterator pos, Args&&... args) {
        if (this->_finish != this->_storage_end) {
            this->get_allocator().construct(this->_finish, std::move(*(this->_finish - 1)));
            ++this->_finish;
            std::move_backward(pos.base(), this->_finish - 2, this->_finish - 1);
            *pos = Type(std::forward<Args>(args)...);
        } else {
            size_type lens;
            if (this->max_size() - this->size() < size_type(1)) {
                std::__throw_length_error(__N("sage::vector insert_aux"));
            }
            const size_type len = this->size() + std::max(this->size(), size_type(1));
            lens = (len < this->size() || len > max_size()) ? this->max_size() : len;

            const size_type elem_before = pos - this->begin();
            pointer n_start(this->get_allocator().allocate(lens));
            pointer n_finish(n_start);
            try {
                this->get_allocator().construct(n_start + elem_before,
                                                std::forward<Args>(args)...);
                n_finish = 0;
                n_finish = sage::uninitialized_move(this->_start, pos.base(), n_start, this->_alloc);
                ++n_finish;
                n_finish = sage::uninitialized_move(pos.base(), this->_finish, n_finish, this->_alloc);
            } catch (...) {
                if (!n_finish) {
                    this->get_allocator().destroy(n_start + elem_before);
                } else {
                    std::_Destroy(n_start, n_finish, this->_alloc);
                }
                this->get_allocator().deallocate(n_start, lens);
                __throw_exception_again;
            }
            std::_Destroy(this->_start, this->_finish, this->_alloc);
            this->get_allocator().deallocate(this->_start, this->_storage_end - this->_start);
            this->_start = n_start;
            this->_finish = n_finish;
            this->_storage_end = n_start + lens;
        }
    }

    vector fill_assign(size_type size, const_reference val) {
        if (size > this->capacity()) {
            vector temp(size, val, this->_alloc);
            temp.swap(*this);
        } else if (size > this->size()) {
            std::fill(begin(), end(), val);
            sage::uninitialized_fill(this->_finish, size - this->size(), val, this->_alloc);
            this->_finish += size - this->size();
        } else {
            pointer pos = std::fill_n(this->_finish, size, val);
            std::_Destroy(pos, this->_finish, this->_alloc);
            this->_finish = pos;
        }
    }

    void default_append(size_type n) {
        if (n != 0) {
            if (size_type(this->_storage_end - this->_finish) >= n) {
                sage::uninitialized_default(this->_finish, n, this->_alloc);
                this->_finish += n;
            } else {
                size_type lens = 0;
                if (this->max_size() - this->size() < n) {
                    std::__throw_length_error(__N("sage::vector default_append"));
                }
                const size_type len = this->size() + std::max(this->size(), n);
                lens = (len < this->size() || len > this->max_size()) ? this->max_size() : len;
                const size_type old_size = this->size();
                pointer n_start(this->get_allocator().allocate(lens));
                pointer n_finish(n_start);
                try {
                    n_finish = sage::uninitialized_move(this->_start, this->_finish, n_start, this->_alloc);
                    std::cout << *n_finish << std::endl;
                    sage::uninitialized_default(n_finish, n, this->_alloc);
                    n_finish += n;
                } catch (...) {
                    std::_Destroy(n_start, n_finish, this->_alloc);
                    this->get_allocator().deallocate(n_start, lens);
                    __throw_exception_again;
                }
                std::_Destroy(this->_start, this->_finish, this->_alloc);
                this->get_allocator().deallocate(this->_start, this->_storage_end - this->_start);
                this->_start = n_start;
                this->_finish = n_finish;
                this->_storage_end = n_start + lens;
            }
        }
    }

    template <typename ForwardIterator>
    pointer allocate_and_copy(size_type n, ForwardIterator first, ForwardIterator last) {
        pointer result = this->_alloc.allocate(n);
        try {
            sage::uninitialized_copy(first, last, result, this->_alloc);
            return result;
        } catch (...) {
            this->get_allocator().deallocate(result, n);
            __throw_exception_again;
        }
    }
};

template <typename T, typename Alloc>
inline void swap(sage::vector<T, Alloc>& x, sage::vector<T, Alloc>& y) {
    x.swap(y);
}

template <class T>
bool operator!=(const vector<T>& lhs, const vector<T>& rhs) {
    return !(lhs == rhs);
}

template <class T>
bool operator==(const vector<T>& lhs, const vector<T>& rhs) {
    if (lhs.size() != rhs.size())
        return false;
    for (size_t i = 0; i < lhs.size(); ++i) {
        if (lhs[i] != rhs[i]) {
            return false;
        }
    }
    return true;
}

}  // namespace sage