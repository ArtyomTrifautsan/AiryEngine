#pragma once

#include <glm/vec3.hpp>


namespace AiryEngine {

    class SphereCollidingObject
    {
    public:
        SphereCollidingObject();
        ~SphereCollidingObject();

        void set_is_collided(bool _is_collided);

        void set_radius(float _radius);

        void set_translate(glm::vec3 _translate);
        void set_translate(float translate_x, float translate_y, float translate_z);

        bool get_is_collided() const { return this->is_collided; }

        glm::vec3 get_anchor_point() { return this->anchor_point; }
        float get_radius() { return this->radius; }

        glm::vec3 get_translate() { return this->translate; }
    
    // private:
        bool is_collided = false;

        glm::vec3 anchor_point = glm::vec3(0, 0, 0);
        float radius = 1;

        glm::vec3 translate = glm::vec3(0, 0, 0);
    };

}