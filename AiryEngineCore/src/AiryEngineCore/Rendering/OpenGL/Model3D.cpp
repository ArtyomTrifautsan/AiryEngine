#include "AiryEngineCore/Rendering/OpenGL/Model3D.hpp"

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

    void Model3D::set_material(std::shared_ptr<Material> material)
    {
        for (std::shared_ptr<Mesh> current_mesh : this->meshes)
            current_mesh->set_material(material);
    }

    void Model3D::set_diffuse_color(float r, float g, float b)
    {
        for (std::shared_ptr<Mesh> current_mesh : this->meshes)
            current_mesh->set_diffuse_color(r, g, b);
    }

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

    void Model3D::move_model(float delta_move_x, float delta_move_y, float delta_move_z)
    {
        this->translate[0] = this->translate[0] + delta_move_x;
        this->translate[1] = this->translate[1] + delta_move_y;
        this->translate[2] = this->translate[2] + delta_move_z;

        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->set_translate(this->translate[0], this->translate[1], this->translate[2]);
    }

    // void Model3D::move_model_x(float delta_move_x);
    // void Model3D::move_model_y(float delta_move_y);
    // void Model3D::move_model_z(float delta_move_z);

    void Model3D::rotate_model(float delta_angle_x, float delta_angle_y, float delta_angle_z)
    {
        this->rotate[0] = this->rotate[0] + delta_angle_x;
        this->rotate[1] = this->rotate[1] + delta_angle_y;
        this->rotate[2] = this->rotate[2] + delta_angle_z;

        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->set_rotate(this->rotate[0], this->rotate[1], this->rotate[2]);
    }

    // void Model3D::rotate_x(float delta_angle_x);
    // void Model3D::rotate_y(float delta_angle_y);
    // void Model3D::rotate_z(float delta_angle_z);
}