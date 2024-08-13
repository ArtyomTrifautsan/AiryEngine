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

    // void Mesh::draw(std::shared_ptr<ShaderProgram> shader_program, Camera& camera, const glm::vec3& light_source_position, const glm::vec3& light_source_color)
    // {
    //     LOG_INFO("Draw mesh function");

    //     // this->texture->bind(0); 

    //     shader_program->bind();
    //     this->vertex_array->bind();

    //     shader_program->set_matrix4("view_projection_matrix", camera.get_projection_matrix() * camera.get_view_matrix());
    //     shader_program->set_vec3("camera_position", camera.get_camera_position());
    //     shader_program->set_vec3("light_position", light_source_position);
    //     shader_program->set_vec3("light_color", light_source_color);
    //     shader_program->set_float("ambient_factor", this->ambiant_factor);
    //     shader_program->set_float("diffuse_factor", this->diffuse_factor);
    //     shader_program->set_float("specular_factor", this->specular_factor);
    //     shader_program->set_float("shininess", this->shininess);

    //     glm::mat4 scale_matrix(
    //         scale[0], 0,        0,        0,
    //         0,        scale[1], 0,        0,
    //         0,        0,        scale[2], 0,
    //         0,        0,        0,        1
    //     );
            
    //     float rotate_in_radians = glm::radians(rotate);
    //     glm::mat4 rotate_matrix(
    //          cos(rotate_in_radians), sin(rotate_in_radians), 0, 0,
    //         -sin(rotate_in_radians), cos(rotate_in_radians), 0, 0,
    //          0,                      0,                      1, 0,
    //          0,                      0,                      0, 1
    //     );

    //     glm::mat4 translate_matrix(
    //         1,            0,            0,            0,
    //         0,            1,            0,            0,
    //         0,            0,            1,            0,  
    //         translate[0], translate[1], translate[2], 1
    //     );

    //     glm::mat4 model_matrix = translate_matrix * rotate_matrix * scale_matrix;
    //     shader_program->set_matrix4("model_matrix", model_matrix);

    //     Renderer_OpenGL::draw_vertex_elements(*this->vertex_array);
        
    //     this->vertex_array->unbind();
    // }

    void Mesh::set_material(std::shared_ptr<Material> material)
    {
        this->material = material;
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