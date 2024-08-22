#pragma once

#include <iostream>     // is included for using size_t


namespace AiryEngine {

    class VertexBuffer;
    class IndexBuffer;

    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();

        VertexArray& operator=(const VertexArray&) = delete;
        VertexArray(const VertexArray&) = delete;
        VertexArray& operator=(VertexArray&& vertexArray) noexcept;  
        VertexArray(VertexArray&& vertexArray) noexcept;  

        void add_vertex_buffer(VertexBuffer& vertexBuffer);
        void set_index_buffer(IndexBuffer& vertexBuffer);
        void bind() const;
        static void unbind();
        size_t get_indices_count() const { return this->indicesCount; }
    
    private:
        unsigned int id = 0;
        unsigned int elementsCount = 0;
        size_t indicesCount = 0;
    };

}