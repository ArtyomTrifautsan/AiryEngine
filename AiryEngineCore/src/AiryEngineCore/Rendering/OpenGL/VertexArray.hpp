#pragma once

#include <iostream>     // is included for using size_t

#include "VertexBuffer.hpp"

namespace AiryEngine {

    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();

        VertexArray& operator=(const VertexArray&) = delete;
        VertexArray(const VertexArray&) = delete;
        VertexArray& operator=(VertexArray&& vertexArray) noexcept;  
        VertexArray(VertexArray&& vertexArray) noexcept;  

        void add_buffer(VertexBuffer& vertexBuffer);
        void bind() const;
        static void unbind();
    
    private:
        unsigned int id = 0;
        unsigned int elementsCount = 0;
    };

}