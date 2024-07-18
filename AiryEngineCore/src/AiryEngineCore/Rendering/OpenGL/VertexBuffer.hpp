#pragma once

#include <iostream>     // is included for using size_t

namespace AiryEngine {

    class VertexBuffer
    {
    public:

        enum class EUsage
        {
            Static,
            Dynamic,
            Stream
        };

        VertexBuffer(const void* data, const size_t size);
        VertexBuffer(const void* data, const size_t size, const EUsage usage);
        ~VertexBuffer();

        VertexBuffer& operator=(const VertexBuffer&) = delete;
        VertexBuffer(const VertexBuffer&) = delete;
        VertexBuffer& operator=(VertexBuffer&& vertexBuffer) noexcept;  
        VertexBuffer(VertexBuffer&& vertexBuffer) noexcept;  

        void bind();
        static void unbind();
    
    private:
        unsigned int id = 0;
    };

}