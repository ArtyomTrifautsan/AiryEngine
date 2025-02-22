#include "AiryEngineCore/Rendering/OpenGL/Mesh.hpp"

#include <glm/trigonometric.hpp>
#include <glm/ext/matrix_float4x4.hpp>

#include "AiryEngineCore/Log.hpp"

#include "AiryEngineCore/Camera.hpp"
#include "AiryEngineCore/Rendering/OpenGL/Renderer_OpenGL.hpp"
#include "AiryEngineCore/Rendering/OpenGL/ShaderProgram.hpp"
#include "AiryEngineCore/Rendering/OpenGL/VertexBuffer.hpp"
#include "AiryEngineCore/Rendering/OpenGL/IndexBuffer.hpp"
#include "AiryEngineCore/Rendering/OpenGL/VertexArray.hpp"
#include "AiryEngineCore/Rendering/OpenGL/Texture2D.hpp"


namespace AiryEngine {

    Mesh::Mesh(std::shared_ptr<std::vector<float>> vertices, 
                std::shared_ptr<std::vector<unsigned int>> indices, 
                std::shared_ptr<Material> material)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->material = material;

        setup_render_data_mesh();
    }

    void Mesh::setup_render_data_mesh()
    {
        BufferLayout bufferLayout_vec3_vec3_vec2
        {
            ShaderDataType::Float3,
            ShaderDataType::Float3,
            ShaderDataType::Float2
        };

        this->vertex_buffer = std::make_shared<VertexBuffer>(this->vertices->data(), this->vertices->size() * sizeof(float), bufferLayout_vec3_vec3_vec2);
        this->vertex_array = std::make_shared<VertexArray>();
        this->index_buffer = std::make_shared<IndexBuffer>(this->indices->data(), this->indices->size());
        vertex_array->add_vertex_buffer(*this->vertex_buffer);
        vertex_array->set_index_buffer(*this->index_buffer);

        this->vertex_array->unbind();
    }

    void Mesh::set_texture(std::shared_ptr<Texture2D> texture)
    {
        this->texture = texture;
    }

    void Mesh::set_has_texture(bool has_texture)
    {
        this->has_texture = has_texture;
    }

    void Mesh::set_material(std::shared_ptr<Material> material)
    {
        this->material = material;
    }

    void Mesh::set_diffuse_color(float r, float g, float b)
    {
        this->material->diffuse_color = glm::vec3(r, g, b);
    }

    void Mesh::set_scale(float scale_x, float scale_y, float scale_z)
    {
        if (scale_x > 0) this->scale[0] = scale_x;
        if (scale_y > 0) this->scale[1] = scale_y;
        if (scale_z > 0) this->scale[2] = scale_z;
    }

    void Mesh::set_rotate(float angle_x, float angle_y, float angle_z)
    {
        //this->rotate = angle;
        this->rotate[0] = angle_x;
        this->rotate[1] = angle_y;
        this->rotate[2] = angle_z;
    }

    void Mesh::set_translate(float translate_x, float translate_y, float translate_z)
    {
        this->translate[0] = translate_x;
        this->translate[1] = translate_y;
        this->translate[2] = translate_z;
    }

    void Mesh::set_translate_x(float value)
    {
        this->translate[0] = value;
    }

    void Mesh::set_translate_y(float value)
    {
        this->translate[1] = value;
    }

    void Mesh::set_translate_z(float value)
    {
        this->translate[2] = value;
    }

    void Mesh::get_scale(float (&_scale)[3]) const
    {
        _scale[0] = this->scale[0];
        _scale[1] = this->scale[1];
        _scale[2] = this->scale[2];
    }

    void Mesh::get_rotate(float (&_rotate)[3]) const
    {
        _rotate[0] = this->rotate[0];
        _rotate[1] = this->rotate[1];
        _rotate[2] = this->rotate[2];
    }

    void Mesh::get_translate(float (&_translate)[3]) const
    {
        _translate[0] = this->translate[0];
        _translate[1] = this->translate[1];
        _translate[2] = this->translate[2];
    }

    // void Mesh::get_scale(float* _scale)
    // {
    //     _scale[0] = this->scale[0];
    //     _scale[1] = this->scale[1];
    //     _scale[2] = this->scale[2];
    // }

    // void Mesh::get_rotate(float* rotate_x, float* rotate_y, float* rotate_z)
    // {
    //     *rotate_x = this->scale[0];
    //     *rotate_y = this->scale[1];
    //     *rotate_z = this->scale[2];
    // }

    // void Mesh::get_translate(float* _translate)
    // {
    //     _translate[0] = this->translate[0];
    //     _translate[1] = this->translate[1];
    //     _translate[2] = this->translate[2];
    // }

}