#pragma once

#include <stdio.h>

#include "rb_tree_node.h"

namespace crux {

class rb_tree_header {
public:
    rb_tree_node_base header;
    size_t node_count;

    rb_tree_header() noexcept {
        this->header.tree_color = rb_tree_color::rb_red;
        this->reset();
    }

    rb_tree_header(rb_tree_header&& x) noexcept {
        if(x.header.root != nullptr) {
            this->move_data(x);
        } else {
            this->header.tree_color = rb_tree_color::rb_red;
            this->reset();
        }
    }

    void move_data(rb_tree_header& x) {
        this->header.tree_color = x.header.tree_color;
        this->header.root = x.header.root;
        this->header.left = x.header.left;
        this->header.right = x.header.right;
        this->header.root->root = &this->header;
        this->node_count = x.node_count;
    }

    void reset() {
        this->header.root = 0;
        this->header.left = &this->header;
        this->header.right = &this->header;
        this->node_count = 0;
    }

};

}  // namespace crux


