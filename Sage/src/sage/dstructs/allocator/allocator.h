#pragma once

#include <iostream>
#include <new>

namespace sage {

template <typename Type>
class allocator {
public:
    using value_type = Type;
    using pointer = Type*;
    using const_pointer = const Type*;
    using reference = Type&;
    using const_reference = const Type&;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

    /** @brief Creates a new allocator instance. **/
    allocator() throw(){};

    /** @brief Creates a new allocator instance. **/
    allocator(const allocator&) noexcept {}

    /** @brief Creates a new allocator instance. **/
    template <typename U>
    allocator(const allocator<U>&) noexcept {}

    /** @brief Destructs an allocator instance. **/
    ~allocator() throw() {}

    /** @brief Assignment operator. **/
    allocator<Type>& operator=(const allocator&) {
        return *this;
    }

    /** @brief Assignment operator. **/
    template <class U>
    allocator& operator=(const allocator<U>&) {
        return *this;
    }

    /** @brief Public Member Functions **/
    pointer address(reference x) const noexcept {
        return &x;
    }

    const_pointer address(const_reference x) const noexcept {
        return &x;
    }

    /** @brief Constructs an object in allocated storage. **/
    void construct(pointer p, const Type& val) {
        ::new ((Type*)p) Type(val);
    }

    /** @brief Constructs an objects in allocated storage. **/
    template<typename ... Args>
    void construct(pointer p, Args&&... args) {
        ::new((Type*)p) Type(std::forward<Args>(args)...); 
    }

    /** @brief Destructs an object in allocated storage. **/
    void destroy(pointer p) {
        p->~Type();
    }

    /** @brief Allocates uninitialized storage. **/
    [[nodiscard]] pointer allocate(size_type n) {
        if (n > std::numeric_limits<size_type>::max() / sizeof(Type)) {
            throw std::bad_array_new_length();
        }
        if (auto ptr = static_cast<pointer>(std::malloc(n * sizeof(Type)))) {
            // report(ptr, n);
            return ptr;
        }
        throw std::bad_alloc();
    }

    /** @brief Deallocates storage. **/
    void deallocate(Type* ptr, size_type n) noexcept {
        if (ptr) {
            // report(ptr, n, 0);
            free(ptr);
        }
    }

    /** @brief Returns the largest supported allocation size. **/
    size_type max_size() const {
        return size_t(-1);
    }

    template <typename U>
    struct rebind {
        using other = allocator<U>;
    };

private:
    void report(Type* p, size_type n, bool alloc = true) const {
        std::cout << (alloc ? "Alloc: " : "Dealloc: ") << sizeof(Type) * n
                  << " bytes at " << std::hex << std::showbase
                  << reinterpret_cast<void*>(p) << std::dec << '\n';
    }
};

template <typename T, typename U>
constexpr bool operator==(const allocator<T>&, const allocator<U>&) noexcept {
    return true;
}

template <typename T, typename U>
constexpr bool operator!=(const allocator<T>&, const allocator<U>&) noexcept {
    return false;
}


template <typename Alloc, bool = true>
struct _alloc_swap {
    static void do_swap(Alloc&, Alloc&) {}
};

template <typename Alloc>
struct _alloc_swap<Alloc, false> {
    static void do_swap(Alloc& one, Alloc& two) {
        if(one != two) {
            swap(one, two);
        }
    }
};

template <typename T, bool = true>
struct _shrink_to_fit {
    static void do_shrink(T&) {}
};

template <typename T>
struct _shrink_to_fit<T, true> {
    static void do_shrink(T& t) {
        try {
            T(t).swap(t);
        } catch (...) {
        }
    }
};

}  // namespace sage