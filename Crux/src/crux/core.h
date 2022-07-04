#pragma once

#include <memory>

template<typename Type>
using crux_unique = std::unique_ptr<Type>;

template<typename Type>
using crux_shared = std::shared_ptr<Type>;