#include <glad/glad.h>

#include "VertexBuffer.hpp"
#include "AiryEngineCore/Log.hpp"

namespace AiryEngine {

    constexpr unsigned int shader_data_type_to_components_count(const ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float:
            case ShaderDataType::Int:
                return 1;
            
            case ShaderDataType::Float2:
            case ShaderDataType::Int2:
                return 2;
            
            case ShaderDataType::Float3:
            case ShaderDataType::Int3:
                return 3;
            
            case ShaderDataType::Float4:
            case ShaderDataType::Int4:
                return 4;
        }

        LOG_ERROR("shader_data_type_to_components_count: unkwown ShaderDatatype!");
        return 0;
    }

    constexpr size_t shader_data_type_size(const ShaderDataType type)
    {
        switch(type)
        {
            case ShaderDataType::Float:
            case ShaderDataType::Float2:
            case ShaderDataType::Float3:
            case ShaderDataType::Float4:
                return sizeof(GLfloat) * shader_data_type_to_components_count(type);
            
            case ShaderDataType::Int:
            case ShaderDataType::Int2:
            case ShaderDataType::Int3:
            case ShaderDataType::Int4:
                return sizeof(GLint) * shader_data_type_to_components_count(type);
        }

        LOG_ERROR("shader_data_type_size: unkwown ShaderDatatype!");
        return GL_FLOAT; 
    }

    constexpr unsigned int shader_data_type_to_component_type(const ShaderDataType type)
    {
        switch(type)
        {
            case ShaderDataType::Float:
            case ShaderDataType::Float2:
            case ShaderDataType::Float3:
            case ShaderDataType::Float4:
                return GL_FLOAT;
            
            case ShaderDataType::Int:
            case ShaderDataType::Int2:
            case ShaderDataType::Int3:
            case ShaderDataType::Int4:
                return GL_INT;
        }

        LOG_ERROR("shader_data_type_to_components_type: unkwown ShaderDataType!");
        return 0; 
    }

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


    BufferElement::BufferElement(const ShaderDataType _type):
        type(_type),
        component_type(shader_data_type_to_component_type(_type)),
        components_count(shader_data_type_to_components_count(_type)),
        size(shader_data_type_size(_type)),
        offset(0)
    {
    }

    VertexBuffer::VertexBuffer(const void* data, const size_t size, BufferLayout buffer_layout, const EUsage usage):
        bufferLayout(std::move(buffer_layout))
    {
        glGenBuffers(1, &this->id);
        glBindBuffer(GL_ARRAY_BUFFER, this->id);
        glBufferData(GL_ARRAY_BUFFER, size, data, usage_to_GLenum(usage));
    }

    // VertexBuffer::VertexBuffer(std::vector<float>& data, const size_t size, BufferLayout buffer_layout, const EUsage usage):
    //     bufferLayout(std::move(buffer_layout))
    // {
    //     glGenBuffers(1, &this->id);
    //     glBindBuffer(GL_ARRAY_BUFFER, this->id);
    //     glBufferData(GL_ARRAY_BUFFER, size, &data.front(), usage_to_GLenum(usage));
    // }

    VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &this->id); }

    VertexBuffer& VertexBuffer::operator=(VertexBuffer&& vertexBuffer) noexcept
    {
        this->id = vertexBuffer.id;
        vertexBuffer.id = 0;
        return *this;
    }

    VertexBuffer::VertexBuffer(VertexBuffer&& vertexBuffer) noexcept:
        id(vertexBuffer.id),
        bufferLayout(std::move(vertexBuffer.bufferLayout))
    {
        vertexBuffer.id = 0;
    }

    void VertexBuffer::bind() { glBindBuffer(GL_ARRAY_BUFFER, this->id); }

    void VertexBuffer::unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }


    // void VertexBuffer::convert_data(int* intermediate_data_buffer, unsigned int intermediate_data_buffer_size, std::shared_ptr<std::vector<VertexData>> data)
    // {
    //     int size_data;
    //     size_data = sizeof(*data);
    // }
}