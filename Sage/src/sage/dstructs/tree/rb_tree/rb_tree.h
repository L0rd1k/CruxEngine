#pragma once

#include "rb_tree_node.h"
#include "src/sage/dstructs/allocator/allocator.h"

namespace sage {

template <typename Key, typename Value, typename ValueKey, typename Compare, typename Allocator = sage::allocator<Value>>
class rb_tree {
public:
    using node_allocator = typename std::allocator_traits<Allocator>::template rebind<Value>::other;
    using alloc_traits = std::allocator_traits<node_allocator>;

protected:
    using base_ptr = rb_tree_node_base*;
    using const_base_ptr = const rb_tree_node_base*;
    using link_type = rb_tree_node<Value>*;
    using const_link_type = const rb_tree_node<Value>*;

private:
    struct reuse_or_alloc_node {
    public:
        reuse_or_alloc_node(rb_tree& tree) {}

    private:
        base_ptr _root;
        base_ptr _nodes;
        rb_tree _tree;
    };

    
};

}  // namespace sage