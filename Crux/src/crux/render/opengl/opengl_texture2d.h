#pragma once

#include <glad/glad.h>

#include <string>

#include "src/crux/render/texture/texture.h"

namespace crux {

/** @brief 2D Texture class. **/
class OpenGlTexture2D : public Texture2D {
public:
    /** @brief Constructor. Add texture sources.
     * @param[in] path Path to texture source **/
    OpenGlTexture2D(const std::string path);

    /** @brief Destructor. Destroy added texture. **/
    virtual ~OpenGlTexture2D();

    /** @brief Get texture width.
     * @return Width value, **/
    virtual uint32_t getWidth() const override;

    /** @brief Get texture height.
     * @return Height value, **/
    virtual uint32_t getHeight() const override;

    /** @brief Bind an existing texture object to the specified texture unit.
     * @param[in] slot Texture object, **/
    virtual void bind(uint32_t slot = 0) const override;

private:
    std::string _path;         //> Path to texture
    uint32_t _width, _height;  //> Texture height and width
    uint32_t _rendererId;      //> Texture id
};

}  // namespace crux