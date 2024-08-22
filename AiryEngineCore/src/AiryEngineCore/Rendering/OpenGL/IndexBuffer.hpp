#pragma once

#include <iostream>     // is included for using size_t
#include <vector>

#include "AiryEngineCore/Rendering/OpenGL/VertexBuffer.hpp"


namespace AiryEngine {

    class VertexBuffer;

    class IndexBuffer
    {
    public:
        IndexBuffer(const void* data, const size_t count);
        IndexBuffer(const void* data, const size_t count, const VertexBuffer::EUsage usage);
        ~IndexBuffer();

        IndexBuffer& operator=(const IndexBuffer&) = delete;
        IndexBuffer(const IndexBuffer&) = delete;
        IndexBuffer& operator=(IndexBuffer&& indexBuffer) noexcept;  
        IndexBuffer(IndexBuffer&& indexBuffer) noexcept;  

        void bind();
        static void unbind();
        size_t get_count() const { return this->count; }
    
    private:
        unsigned int id = 0;
        size_t count;
    };

}