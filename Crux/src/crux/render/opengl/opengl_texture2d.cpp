#include "opengl_texture2d.h"

namespace crux {

OpenGlTexture2D::OpenGlTexture2D(const std::string path) {
}

OpenGlTexture2D::~OpenGlTexture2D() {
}

uint32_t OpenGlTexture2D::getWidth() const {
    return _width;
}

uint32_t OpenGlTexture2D::getHeight() const {
    return _height;
}

void OpenGlTexture2D::bind(uint32_t slot) const {
    glBindTextureUnit(slot, _rendererId);
}

}  // namespace crux