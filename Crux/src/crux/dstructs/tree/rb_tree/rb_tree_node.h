#pragma once

namespace crux {

enum class rb_tree_color {
    rb_red = false,
    rb_black = true,
};

class rb_tree_node_base {
public:
    using base_pointer = rb_tree_node_base*;
    using const_base_pointer = const rb_tree_node_base*;

    rb_tree_color tree_color;
    base_pointer root;
    base_pointer left;
    base_pointer right;

    static base_pointer minimum(base_pointer x) noexcept {
        while (x->left != 0)
            x = x->left;
        return x;
    }
    static const_base_pointer minimum(const_base_pointer x) noexcept {
        while (x->left != 0)
            x = x->left;
        return x;
    }
    static base_pointer maximum(base_pointer x) noexcept {
        while (x->right != 0)
            x = x->right;
        return x;
    }
    static const_base_pointer maximum(const_base_pointer x) noexcept {
        while (x->right != 0)
            x = x->right;
        return x;
    }
};

template <typename Value>
class rb_tree_node : public rb_tree_node_base {
public:
    using link_type = rb_tree_node<Value>*;
    Value value_field;
    Value* value_ptr() {
        return &*value_field;
    }
    const Value* value_ptr() const {
        return &*value_field;
    }
};

static rb_tree_node_base* local_rb_tree_increment(rb_tree_node_base* x) throw() {
    if (x->right != 0) {
        x = x->right;
        while (x->left != 0) {
            x = x->left;
        }
    } else {
        rb_tree_node_base* y = x->root;
        while (x == y->right) {
            x = y;
            y = y->root;
        }
        if (x->right != y) {
            x = y;
        }
    }
    return x;
}

static rb_tree_node_base* local_rb_tree_decrement(rb_tree_node_base* x) throw() {
    if(x->tree_color == rb_tree_color::rb_red && x->root->root == x) {
        x = x->right;
    } else if (x->left != 0) {
        rb_tree_node_base* y = x->left;
        while(y->right != 0) {
            y = y->right;
        }
        x = y;
    } else {
        rb_tree_node_base* y = x->root;
        while(x == y->left) {
            x = y;
            y = y->root;
        }
        x = y;
    }
    return x;
}

rb_tree_node_base* rb_tree_increment(rb_tree_node_base* x) throw() {
    return local_rb_tree_increment(x);
}

const rb_tree_node_base* rb_tree_increment(const rb_tree_node_base* x) throw() {
    return local_rb_tree_increment(const_cast<rb_tree_node_base*>(x));
}

rb_tree_node_base* rb_tree_decrement(rb_tree_node_base* x) throw() {
    return local_rb_tree_decrement(x);
}

const rb_tree_node_base* rb_tree_decrement(const rb_tree_node_base* x) throw() {
    return local_rb_tree_decrement(const_cast<rb_tree_node_base*>(x));
}

}  // namespace crux