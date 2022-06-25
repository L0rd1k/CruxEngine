#pragma once

#include "rb_tree_comparator.h"
#include "rb_tree_node.h"
#include "rb_tree_header.h"

#include "src/sage/dstructs/allocator/allocator.h"

namespace sage {

template <typename Key, typename Value, typename ValueKey, typename Compare, typename Allocator = sage::allocator<Value>>
class rb_tree {
public:
    using node_allocator = typename std::allocator_traits<Allocator>::template rebind<Value>::other;
    using alloc_traits = std::allocator_traits<node_allocator>;
    using key_type = Key;
    using value_type = Value;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using allocator_type = Allocator;

protected:
    using base_ptr = rb_tree_node_base*;
    using const_base_ptr = const rb_tree_node_base*;
    using link_type = rb_tree_node<Value>*;
    using const_link_type = const rb_tree_node<Value>*;

private:
    struct reuse_or_alloc_node {
    public:
        reuse_or_alloc_node(rb_tree& tree) {}
        reuse_or_alloc_node(const rb_tree&) = delete;
        ~reuse_or_alloc_node() {}
        template <typename Arg>
        link_type operator()(const Arg& arg) {}

    private:
        base_ptr extract() {}

    private:
        base_ptr _root;
        base_ptr _nodes;
        rb_tree& _tree;
    };

    struct alloc_node {
    public:
        alloc_node(rb_tree& t)
            : _tree(t) {
        }
        template <typename Arg>
        link_type operator()(Arg&& arg) const {
        }

    private:
        rb_tree& _tree;
    };

public:
    node_allocator& get_node_allocator() noexcept {
        // return *static_cast<node_allocator*>(&this->)
    }

protected:
    template <typename KeyCompare>
    class rb_tree_impl : public node_allocator,
                         public rb_tree_key_compare<KeyCompare>,
                         public rb_tree_header {
    public:
        using base_key_compare = rb_tree_key_compare<KeyCompare>;
        rb_tree_impl() = default;
        rb_tree_impl(rb_tree_impl&&) = default;
        // rb_tree_impl(const rb_tree_impl& x) : 
        //     node_allocator(std::allocator_traits::)
    };
};

}  // namespace sage