#include <glad/glad.h>

#include "VertexBuffer.hpp"
#include "AiryEngineCore/Log.hpp"

namespace AiryEngine {

    constexpr GLenum usage_to_GLenum(const VertexBuffer::EUsage usage)
    {
        switch (usage)
        {
            case VertexBuffer::EUsage::Static: return GL_STATIC_DRAW;
            case VertexBuffer::EUsage::Dynamic: return GL_DYNAMIC_DRAW;
            case VertexBuffer::EUsage::Stream: return GL_STREAM_DRAW;
        }

        LOG_ERROR("Unknown VertexBufferUsage");
        return GL_STREAM_DRAW;
    }


    VertexBuffer::VertexBuffer(const void* data, const size_t size)
    {
        glGenBuffers(1, &this->id);
        glBindBuffer(GL_ARRAY_BUFFER, this->id);
        const EUsage usage = VertexBuffer::EUsage::Static;
        glBufferData(GL_ARRAY_BUFFER, size, data, usage_to_GLenum(usage));
    }

    VertexBuffer::VertexBuffer(const void* data, const size_t size, const EUsage usage)
    {
        glGenBuffers(1, &this->id);
        glBindBuffer(GL_ARRAY_BUFFER, this->id);
        glBufferData(GL_ARRAY_BUFFER, size, data, usage_to_GLenum(usage));
    }

    VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &this->id); }

    VertexBuffer& VertexBuffer::operator=(VertexBuffer&& vertexBuffer) noexcept
    {
        this->id = vertexBuffer.id;
        vertexBuffer.id = 0;
        return *this;
    }

    VertexBuffer::VertexBuffer(VertexBuffer&& vertexBuffer) noexcept
    {
        this->id = vertexBuffer.id;
        vertexBuffer.id = 0;
    }

    void VertexBuffer::bind() { glBindBuffer(GL_ARRAY_BUFFER, this->id); }

    void VertexBuffer::unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

}