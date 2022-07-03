#pragma once 

#include "src/crux/dstructs/pair/pair.h"
#include "src/crux/dstructs/allocator/allocator.h"

namespace crux {

template<typename Key, typename Type, typename Compare = std::less<Key>, typename Allocator = crux::allocator<crux::pair<const Key, Type>>>
class map {
public:
    using key_type = Key;
    using mapped_type = Type;
    using value_type = crux::pair<const key_type, mapped_type>;
    using size_type = std::size_t;
    using key_compare = Compare;
    using difference_type = std::ptrdiff_t;
    using allocator_type = Allocator;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = typename std::allocator_traits<Allocator>::pointer;
    using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;
    using iterator = crux::LegacyRandomAccessIterator<value_type>;
    using const_iterator = crux::LegacyRandomAccessIterator<const value_type>;
    using reverse_iterator = crux::reverse_iterator<iterator>;
    using const_reverse_iterator = crux::reverse_iterator<const_iterator>;
private:    
    using pair_allocator_type = typename std::allocator_traits<Allocator>::template rebind<value_type>::other;
    
};

}