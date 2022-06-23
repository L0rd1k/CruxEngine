#pragma once

namespace sage {

class pair_base {
public:
    pair_base() = default;
    ~pair_base() = default;
    pair_base(const pair_base&) = default;
    pair_base& operator=(const pair_base&) = delete;
};

}