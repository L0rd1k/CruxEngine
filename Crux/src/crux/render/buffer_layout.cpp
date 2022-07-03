#include "buffer_layout.h"

namespace crux {

/*********** BUFFER ELEMENT *************/

BufferElement::BufferElement(ShaderType type,
                             const std::string& name,
                             bool normalized)
    : type(type),
      name(name),
      size(getShaderTypeSize(type)),
      offset(0),
      normalized(normalized) {
}

uint32_t BufferElement::getElementsCount() const {
    switch (type) {
        case ShaderType::fVec:  return 1;
        case ShaderType::fVec2: return 2;
        case ShaderType::fVec3: return 3;
        case ShaderType::fVec4: return 4;
        case ShaderType::Mat3:  return 9;
        case ShaderType::Mat4:  return 16;
        case ShaderType::iVec:  return 1;
        case ShaderType::iVec2: return 2;
        case ShaderType::iVec3: return 3;
        case ShaderType::iVec4: return 4;
        case ShaderType::Bool:  return 1;
        default: {
            Log::warning("Unknown shader data size(elem count)");
            return 0;
        }
    }
    return 0;
}

/*********** BUFFER LAYOUT *************/

BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements)
    : _elements(elements) {
    calculatStrideOffset();
}

uint32_t BufferLayout::getStride() const {
    return _stride;
}
const std::vector<BufferElement>& BufferLayout::getElements() const {
    return _elements;
}
std::vector<BufferElement>::iterator BufferLayout::begin() {
    return _elements.begin();
};
std::vector<BufferElement>::iterator BufferLayout::end() {
    return _elements.end();
};
std::vector<BufferElement>::const_iterator BufferLayout::begin() const {
    return _elements.begin();
}
std::vector<BufferElement>::const_iterator BufferLayout::end() const {
    return _elements.end();
}

void BufferLayout::calculatStrideOffset() {
    uint32_t offset = 0;
    _stride = 0;
    for (auto& elem : _elements) {
        elem.offset = offset;
        offset += elem.size;
        _stride += elem.size;
    }
}

static uint32_t getShaderTypeSize(ShaderType type) {
    switch (type) {
        case ShaderType::fVec:  return 4;
        case ShaderType::fVec2: return 4 * 2;
        case ShaderType::fVec3: return 4 * 3;
        case ShaderType::fVec4: return 4 * 4;
        case ShaderType::Mat3:  return 4 * 3 * 3;
        case ShaderType::Mat4:  return 4 * 4 * 4;
        case ShaderType::iVec:  return 4;
        case ShaderType::iVec2: return 4 * 2;
        case ShaderType::iVec3: return 4 * 3;
        case ShaderType::iVec4: return 4 * 4;
        case ShaderType::Bool:  return 1;
        default: {
            Log::warning("Unknown shader data type(type size)");
            return 0;
        }
    }
    return 0;
}

}  // namespace crux