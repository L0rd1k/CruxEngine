#pragma once

#include <inttypes.h>

#include <string>
#include <vector>

#include "src/sage/render/renderer.h"
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

static uint32_t getShaderTypeSize(ShaderType type) {
    switch (type) {
        case ShaderType::fVec:
            return 4;
        case ShaderType::fVec2:
            return 4 * 2;
        case ShaderType::fVec3:
            return 4 * 3;
        case ShaderType::fVec4:
            return 4 * 4;
        case ShaderType::Mat3:
            return 4 * 3 * 3;
        case ShaderType::Mat4:
            return 4 * 4 * 4;
        case ShaderType::iVec:
            return 4;
        case ShaderType::iVec2:
            return 4 * 2;
        case ShaderType::iVec3:
            return 4 * 3;
        case ShaderType::iVec4:
            return 4 * 4;
        case ShaderType::Bool:
            return 1;
        default: {
            Log::warning("Unknown shader data type(type size)");
            return 0;
        }
    }
    return 0;
}

struct BufferElement {
    std::string name;
    ShaderType type;
    uint32_t size;
    uint32_t offset;
    bool normalized;

    BufferElement() {
    }

    BufferElement(ShaderType type, const std::string& name, bool normalized = false)
        : type(type), name(name), size(getShaderTypeSize(type)), offset(0), normalized(normalized) {
    }

    uint32_t getElementsCount() const {
        switch (type) {
            case ShaderType::fVec:
                return 1;
            case ShaderType::fVec2:
                return 2;
            case ShaderType::fVec3:
                return 3;
            case ShaderType::fVec4:
                return 4;
            case ShaderType::Mat3:
                return 9;
            case ShaderType::Mat4:
                return 16;
            case ShaderType::iVec:
                return 1;
            case ShaderType::iVec2:
                return 2;
            case ShaderType::iVec3:
                return 3;
            case ShaderType::iVec4:
                return 4;
            case ShaderType::Bool:
                return 1;
            default: {
                Log::warning("Unknown shader data size(elem count)");
                return 0;
            }
        }
        return 0;
    }
};

class BufferArrLayout {
public:
    BufferArrLayout() {}
    BufferArrLayout(const std::initializer_list<BufferElement>& elements)
        : _elements(elements) {
        calculatStrideOffset();
    }
    inline uint32_t getStride() const {
        return _stride;
    }
    inline const std::vector<BufferElement>& getElements() const {
        return _elements;
    }
    std::vector<BufferElement>::iterator begin() {
        return _elements.begin();
    };
    std::vector<BufferElement>::iterator end() {
        return _elements.end();
    };
    std::vector<BufferElement>::const_iterator begin() const {
        return _elements.begin();
    }
    std::vector<BufferElement>::const_iterator end() const {
        return _elements.end();
    }

private:
    void calculatStrideOffset() {
        uint32_t offset = 0;
        _stride = 0;
        for (auto& elem : _elements) {
            elem.offset = offset;
            offset += elem.size;
            _stride += elem.size;
        }
    }

private:
    std::vector<BufferElement> _elements;
    uint32_t _stride = 0;
};

class VertexBuffer {
public:
    virtual ~VertexBuffer();
    virtual void bind() const = 0;
    virtual void unbind() const = 0;
    virtual void setLayout(const BufferArrLayout& layout) = 0;
    virtual const BufferArrLayout& getLayout() const = 0;
    static VertexBuffer* init(float* vertices, uint32_t size);
};

class IndexBuffer {
public:
    virtual ~IndexBuffer();
    virtual void bind() const = 0;
    virtual void unbind() const = 0;
    virtual uint32_t getSize() const = 0;
    static IndexBuffer* init(uint32_t* indices, uint32_t size);
};

}  // namespace sage