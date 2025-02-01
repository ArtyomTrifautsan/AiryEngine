#pragma once

#include <string>
#include <vector>
#include <memory>


namespace AiryEngine {

    struct Material;
    class Mesh;

    class Model3D
    {
    public:
        Model3D(std::vector<std::shared_ptr<Mesh>> meshes = {});

        // void draw(std::shared_ptr<ShaderProgram> shader_program, Camera& camera, const glm::vec3& light_source_position, const glm::vec3& light_source_color);

        void add_mesh(std::shared_ptr<Mesh> mesh);
        void add_meshes(std::vector<std::shared_ptr<Mesh>> meshes);

        std::vector<std::shared_ptr<Mesh>> get_meshes() const {return this->meshes; }

        void set_material(std::shared_ptr<Material> material);
        void set_diffuse_color(float r, float g, float b);
        void set_scale(float scale_x, float scale_y, float scale_z);
        void set_rotate(float angle_x, float angle_y, float angle_z);

        void set_translate(float translate_x, float translate_y, float translate_z);
        void set_translate_x(float value);
        void set_translate_y(float value);
        void set_translate_z(float value);

        void move_model(float delta_move_x, float delta_move_y, float delta_move_z);
        void move_model_x(float delta_move_x);
        void move_model_y(float delta_move_y);
        void move_model_z(float delta_move_z);

        void rotate_model(float delta_angle_x, float delta_angle_y, float delta_angle_z);
        void rotate_model_x(float delta_angle_x);
        void rotate_model_y(float delta_angle_y);
        void rotate_model_z(float delta_angle_z);

    private:
        std::vector<std::shared_ptr<Mesh>> meshes;

        float scale[3] = { 1.0f, 1.0f, 1.0f };
        float rotate[3] = { 0.0f, 0.0f, 0.0f };
        float translate[3] = { 0.0f, 0.0f, 0.0f };
    };
    
}
