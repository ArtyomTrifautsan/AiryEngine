#include "AiryEngineCore/Scene/Model3D.hpp"

#include "AiryEngineCore/Rendering/OpenGL/Mesh.hpp"
#include "AiryEngineCore/Rendering/OpenGL/ShaderProgram.hpp"


namespace AiryEngine {

    Model3D::Model3D(std::vector<std::shared_ptr<Mesh>> _meshes)
    {
        add_meshes(_meshes);
    }

    void Model3D::add_mesh(std::shared_ptr<Mesh> _mesh)
    {
        this->meshes.push_back(_mesh);
    }

    void Model3D::add_meshes(std::vector<std::shared_ptr<Mesh>> _meshes)
    {
        for (std::shared_ptr<Mesh> current_mesh : _meshes) 
            add_mesh(current_mesh);
    }

    // void Model3D::draw(std::shared_ptr<ShaderProgram> shader_program, Camera& camera, const glm::vec3& light_source_position, const glm::vec3& light_source_color)
    // {
    //     for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
    //         current_mesh->draw(shader_program, camera, light_source_position, light_source_color);
    // }

    void Model3D::set_scale(float scale_x, float scale_y, float scale_z)
    {
        if (scale_x > 0) this->scale[0] = scale_x;
        if (scale_y > 0) this->scale[1] = scale_y;
        if (scale_z > 0) this->scale[2] = scale_z;

        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->set_scale(scale_x, scale_y, scale_z);
    }

    void Model3D::set_rotate(float angle_x, float angle_y, float angle_z)
    {
        this->rotate[0] = angle_x;
        this->rotate[1] = angle_y;
        this->rotate[2] = angle_z;
        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->set_rotate(angle_x, angle_y, angle_z);
    }

    void Model3D::set_translate(float translate_x, float translate_y, float translate_z)
    {
        this->translate[0] = translate_x;
        this->translate[1] = translate_y;
        this->translate[2] = translate_z;

        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->set_translate(translate_x, translate_y, translate_z);
    }

    void Model3D::set_translate_x(float value)
    {
        this->translate[0] = value;
        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->set_translate_x(value);
    }

    void Model3D::set_translate_y(float value)
    {
        this->translate[1] = value;
        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->set_translate_y(value);
    }

    void Model3D::set_translate_z(float value)
    {
        this->translate[2] = value;
        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->set_translate_z(value);
    }

}