#include "AiryEngineCore/Rendering/OpenGL/IndexBuffer.hpp"

#include <glad/glad.h>

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

    IndexBuffer::IndexBuffer(const void* data, const size_t count):
        count(count)
    {
        glGenBuffers(1, &this->id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
        const VertexBuffer::EUsage usage = VertexBuffer::EUsage::Static;
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, usage_to_GLenum(usage));
    }

    IndexBuffer::IndexBuffer(const void* data, const size_t count, const VertexBuffer::EUsage usage):
        count(count)
    {
        glGenBuffers(1, &this->id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, usage_to_GLenum(usage));
    }

    IndexBuffer::~IndexBuffer() { glDeleteBuffers(1, &this->id); }

    IndexBuffer& IndexBuffer::operator=(IndexBuffer&& indexBuffer) noexcept
    {
        this->id = indexBuffer.id;
        indexBuffer.id = 0;
        return *this;
    }

    IndexBuffer::IndexBuffer(IndexBuffer&& indexBuffer) noexcept:
        id(indexBuffer.id),
        count(indexBuffer.count)
    {
        indexBuffer.id = 0;
        indexBuffer.count = 0;
    }

    void IndexBuffer::bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id); }

    void IndexBuffer::unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

}