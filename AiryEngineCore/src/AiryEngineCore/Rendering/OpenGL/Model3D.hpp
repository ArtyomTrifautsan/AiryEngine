#pragma once

#include <string>
#include <vector>
#include <memory>

#include "AiryEngineCore/Rendering/OpenGL/Mesh.hpp"

//#include <assimp/scene.h>

namespace AiryEngine {

    class Model3D
    {
        public:
            Model3D(std::vector<std::shared_ptr<Mesh>> meshes = {});

            void draw(std::shared_ptr<ShaderProgram> shader_program, Camera& camera, const glm::vec3& light_source_position, const glm::vec3& light_source_color);

            void add_mesh(std::shared_ptr<Mesh> mesh);
            void add_meshes(std::vector<std::shared_ptr<Mesh>> meshes);

            std::vector<std::shared_ptr<Mesh>> get_meshes() const {return this->meshes; }

            void set_scale(float scale_x, float scale_y, float scale_z);
            void set_rotate(float angle);
            void set_translate(float translate_x, float translate_y, float translate_z);
            void set_translate_x(float value);
            void set_translate_y(float value);
            void set_translate_z(float value);

        private:
            std::vector<std::shared_ptr<Mesh>> meshes;

            float scale[3] = { 1.0f, 1.0f, 1.0f };
            float rotate = 0.0f;
            float translate[3] = { 0.0f, 0.0f, 0.0f };
    };
    
}
