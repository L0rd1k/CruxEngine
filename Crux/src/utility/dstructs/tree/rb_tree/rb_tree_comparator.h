#pragma once

namespace crux {

/** @brief Custom key value type initialization. **/
template <typename Key>
class rb_tree_key_compare {
public:
    Key key_compare;
    /** @brief Deafult constructor. **/
    rb_tree_key_compare()
        : key_compare() {
    }

    /** @brief Constructor with params.
     * @param[in] cmpr Const object reference to tree key.
     **/
    rb_tree_key_compare(const Key& cmpr)
        : key_compare(cmpr) {
    }

    /** @brief Default copy constructor. **/
    rb_tree_key_compare(const rb_tree_key_compare&) = default;

    /** @brief Move constructor.
     * @param[in] other Object to value comparator type .
     **/
    rb_tree_key_compare(rb_tree_key_compare&& other) noexcept
        : key_compare(other.key_compare) {
    }
};

}  // namespace crux