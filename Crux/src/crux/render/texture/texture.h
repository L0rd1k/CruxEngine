#pragma once

#include <inttypes.h>

namespace crux {

/** @brief Texture interface class. **/
class Texture {
public:
    /** @brief Default destructor. **/
    virtual ~Texture() = default;

    /** @brief Abstracting texture width value. **/
    virtual uint32_t getWidth() const = 0;

    /** @brief Abstracting texture height value. **/
    virtual uint32_t getHeight() const = 0;

    /** @brief Abstracting binding an existing texture object to the specified texture unit.
     * @param[in] slot Texture object, by default 0. **/
    virtual void bind(uint32_t slot = 0) const = 0;
};

/** @brief Texture2D interface class. **/
class Texture2D : public Texture {
};

}  // namespace crux