#include <glad/glad.h>

#include "VertexArray.hpp" 
#include "VertexBuffer.hpp" 
#include "IndexBuffer.hpp"
#include "AiryEngineCore/Log.hpp"

namespace AiryEngine {

    VertexArray::VertexArray() { glGenVertexArrays(1, &this->id); }

    VertexArray::~VertexArray() { glDeleteVertexArrays(1, &this->id); }

    VertexArray& VertexArray::operator=(VertexArray&& vertexArray) noexcept
    {
        this->id = vertexArray.id;
        this->elementsCount = vertexArray.elementsCount;
        vertexArray.id = 0;
        vertexArray.elementsCount = 0;
        return *this;
    }

    VertexArray::VertexArray(VertexArray&& vertexArray) noexcept
    {
        this->id = vertexArray.id;
        this->elementsCount = vertexArray.elementsCount;
        vertexArray.id = 0;
        vertexArray.elementsCount = 0;
    }

    void VertexArray::bind() const { glBindVertexArray(this->id); }

    void VertexArray::unbind() { glBindVertexArray(0); }

    void VertexArray::add_vertex_buffer(VertexBuffer& vertexBuffer)
    {
        bind();
        vertexBuffer.bind();

        for (const BufferElement& currentElement : vertexBuffer.get_layout().get_elements())
        {
            glEnableVertexAttribArray(this->elementsCount);
            glVertexAttribPointer( 
                this->elementsCount, 
                static_cast<GLint>(currentElement.components_count), 
                currentElement.component_type, 
                GL_FALSE, 
                static_cast<GLsizei>(vertexBuffer.get_layout().get_stride()), 
                reinterpret_cast<const void*>(currentElement.offset) 
            );
            this->elementsCount += 1;
        }
    }

    void VertexArray::set_index_buffer(IndexBuffer& indexBuffer)
    {
        bind();
        indexBuffer.bind();
        this->indicesCount = indexBuffer.get_count();
        
    }

}