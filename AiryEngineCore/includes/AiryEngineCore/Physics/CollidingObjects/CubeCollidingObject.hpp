#pragma once

#include <glm/vec3.hpp>

namespace AiryEngine {

    class CubeCollidingObject
    {
    public:
        CubeCollidingObject();
        ~CubeCollidingObject();

        void set_is_collided(bool _is_collided);
        bool get_is_collided() const { return this->is_collided; }

        void set_scale(const glm::vec3& _scale);
        void set_scale(float scale_x, float scale_y, float scale_z);
        void set_translate(const glm::vec3& _translate);
        void set_translate(float translate_x, float translate_y, float translate_z);

        glm::vec3 get_anchor_point() const { return this->anchor_point; }
        glm::vec3 get_right() const { return this->right; }
        glm::vec3 get_up() const { return this->up; }
        glm::vec3 get_direction() const { return this->direction; }

        glm::vec3 get_translate() { return this->translate; }
        glm::vec3 get_scale() { return this->scale; }
    
    private:
        bool is_collided = false;

        glm::vec3 anchor_point = glm::vec3(-1, -1, -1);
        glm::vec3 right = glm::vec3(1, -1, -1);
        glm::vec3 up = glm::vec3(-1, 1, -1);
        glm::vec3 direction = glm::vec3(-1, -1, 1);

        glm::vec3 translate = glm::vec3(0, 0, 0);
        glm::vec3 scale = glm::vec3(1, 1, 1);

        void update_coords();
    };

}