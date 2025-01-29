#pragma once

#include <glm/vec3.hpp>

#include <memory>

namespace AiryEngine
{

    class ShaderProgram;
    class ResourceManager;
    class Model3D;
    class Mesh;

    class Renderer
    {
    public:
        Renderer(std::shared_ptr<class ResourceManager> resource_manager);
        // ~Renderer();

        void render_model3D(class Camera& camera, std::shared_ptr<Model3D> model);
        void render_collision_model(class Camera& camera, std::shared_ptr<Model3D> model);
        void render_light_model(class Camera& camera, std::shared_ptr<Model3D> model);

        glm::vec3 get_light_source_position() { return light_source_position; }
        glm::vec3 get_light_source_color() { return light_source_color; }

        void set_light_source_position(glm::vec3 _light_source_position) { light_source_position = _light_source_position; }
        void set_light_source_color(glm::vec3 _light_source_color) { light_source_color = _light_source_color; }

        void set_ambient_factor(float factor); 
        void set_diffuse_factor(float factor);  
        void set_specular_factor(float factor); 

    private:
        std::shared_ptr<ShaderProgram> default_shader_program;
        std::shared_ptr<ShaderProgram> light_source_shader_program;
        std::shared_ptr<ShaderProgram> collision_shader_program;

        glm::vec3 light_source_position = { 0.f, 3.f, 0.f };
        glm::vec3 light_source_color = { 1.f, 1.f, 1.f };

        float ambient_factor = 0.1f;
        float diffuse_factor = 1.0f;
        float specular_factor = 0.5f;

        void render_mesh(class Camera& camera, std::shared_ptr<Mesh> mesh);
        void render_collision_mesh(class Camera& camera, std::shared_ptr<Mesh> mesh);
        void render_light_mesh(class Camera& camera, std::shared_ptr<Mesh> mesh);
    };

}
