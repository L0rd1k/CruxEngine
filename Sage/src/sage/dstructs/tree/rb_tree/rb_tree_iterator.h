#pragma once

#include "rb_tree_header.h"
#include "rb_tree_node.h"

namespace sage {

template <typename Type>
class rb_tree_iterator {
    using value_type = Type;
    using reference = value_type&;
    using pointer = value_type*;
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using self = rb_tree_iterator<Type>;
    using base_ptr = rb_tree_node_base::base_pointer;
    using link_type = rb_tree_node<Type>*;

    base_ptr node;

    rb_tree_iterator() noexcept
        : node() {
    }

    explicit rb_tree_iterator(base_ptr x) noexcept
        : node(x) {
    }

    reference operator*() const noexcept {
        return *static_cast<link_type>(node)->value_ptr();
    }

    pointer operator->() const noexcept {
        return static_cast<link_type>(node)->value_ptr();
    }

    self& operator++() noexcept {
        node = rb_tree_increment(node);
        return *this;
    }

    self operator++(int) noexcept {
        self temp = *this;
        node = rb_tree_increment(node);
        return temp;
    }

    self& operator--() noexcept {
        node = rb_tree_decrement(node);
        return *this;
    }

    self operator--(int) noexcept {
        self temp = *this;
        node = rb_tree_decrement(node);
        return temp;
    }

    bool operator==(const self& x) const noexcept {
        return node == x.node;
    }

    bool operator!=(const self& x) const noexcept {
        return node != x.node;
    }

};

}  // namespace sage