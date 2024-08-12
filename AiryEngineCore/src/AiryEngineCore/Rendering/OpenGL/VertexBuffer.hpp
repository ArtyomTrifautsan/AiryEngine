#pragma once

#include <iostream>     // is included for using size_t
#include <vector>
#include <memory>

namespace AiryEngine {

    struct VertexData;

    enum class ShaderDataType
    {
        Float,
        Float2,
        Float3,
        Float4,
        Int,
        Int2,
        Int3,
        Int4,
    };


    struct BufferElement
    {
        ShaderDataType type;
        uint32_t component_type;
        size_t components_count;
        size_t size;
        size_t offset;

        BufferElement(const ShaderDataType type);
    };


    class BufferLayout
    {
    public:
        BufferLayout(std::initializer_list<BufferElement> elements):
        elements(std::move(elements))
        {
            size_t offset = 0;
            this->stride = 0;
            for (auto& element : this->elements)
            {
                element.offset = offset;
                offset += element.size;
                this->stride += element.size;
            }
        }

        const std::vector<BufferElement>& get_elements() const { return this->elements; }
        size_t get_stride() const { return this->stride; }

    private:
        std::vector<BufferElement> elements;
        size_t stride = 0;
    };


    class VertexBuffer
    {
    public:

        enum class EUsage
        {
            Static,
            Dynamic,
            Stream
        };

        VertexBuffer(const void* data, const size_t size, BufferLayout buffer_layout, const EUsage usage = VertexBuffer::EUsage::Static);
        //VertexBuffer(std::vector<float>& data, const size_t size, BufferLayout buffer_layout, const EUsage usage = VertexBuffer::EUsage::Static);
        ~VertexBuffer();

        VertexBuffer& operator=(const VertexBuffer&) = delete;
        VertexBuffer(const VertexBuffer&) = delete;
        VertexBuffer& operator=(VertexBuffer&& vertexBuffer) noexcept;  
        VertexBuffer(VertexBuffer&& vertexBuffer) noexcept;  

        void bind();
        static void unbind();

        const BufferLayout& get_layout() const { return this->bufferLayout; }
    
    private:
        unsigned int id = 0;
        BufferLayout bufferLayout;

        void convert_data(int* intermediate_data_buffer, unsigned int intermediate_data_buffer_size, std::shared_ptr<std::vector<VertexData>> data);
    };

}