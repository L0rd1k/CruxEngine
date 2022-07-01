#pragma once

#include <inttypes.h>
#include <string>
#include <vector>

#include "src/sage/utils/logger/log.h"

namespace sage {

enum class ShaderType {
    Undefined = -1,
    fVec = 1,
    fVec2 = 2,
    fVec3 = 3,
    fVec4 = 4,
    Mat3 = 5,
    Mat4 = 6,
    iVec = 7,
    iVec2 = 8,
    iVec3 = 9,
    iVec4 = 10,
    Bool = 11,
};

static uint32_t getShaderTypeSize(ShaderType type);

struct BufferElement {
public:
    std::string name;
    ShaderType type;
    uint32_t size;
    uint32_t offset;
    bool normalized;

    BufferElement() = default;
    BufferElement(ShaderType type, const std::string& name, bool normalized = false);
    uint32_t getElementsCount() const;
};

class BufferLayout {
public:
    BufferLayout() = default;
    BufferLayout(const std::initializer_list<BufferElement>& elements);
    uint32_t getStride() const;
    const std::vector<BufferElement>& getElements() const;
    std::vector<BufferElement>::iterator begin();
    std::vector<BufferElement>::iterator end();
    std::vector<BufferElement>::const_iterator begin() const;
    std::vector<BufferElement>::const_iterator end() const;

private:
    void calculatStrideOffset();

private:
    std::vector<BufferElement> _elements;
    uint32_t _stride = 0;
};

}  // namespace sage