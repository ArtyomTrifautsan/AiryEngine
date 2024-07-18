#include <glad/glad.h>

#include "VertexArray.hpp" 
#include "VertexBuffer.hpp" 
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

    void VertexArray::add_buffer(VertexBuffer& vertexBuffer)
    {
        bind();
        vertexBuffer.bind();

        glEnableVertexAttribArray(this->elementsCount);
        glVertexAttribPointer(this->elementsCount, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        this->elementsCount += 1;
    }

}