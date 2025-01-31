#include "AiryEngineCore/Physics/CollidingObjects/SphereCollidingObject.hpp"

#include <glm/trigonometric.hpp>
#include <glm/ext/matrix_float3x3.hpp>
#include <glm/ext/matrix_float4x4.hpp>

#include <iostream>


namespace AiryEngine {

    SphereCollidingObject::SphereCollidingObject()
    {
        this->is_collided = false;
        this->radius = 1;

        this->anchor_point = glm::vec3(-1, -1, -1);

        this->x_vector = glm::vec3(2, 0, 0);
        this->y_vector = glm::vec3(0, 2, 0);
        this->z_vector = glm::vec3(0, 0, 2);

        this->translate = glm::vec3(0, 0, 0);
        this->scale = glm::vec3(1, 1, 1);

        update_coords();
    }

    SphereCollidingObject::~SphereCollidingObject()
    {

    }


    void SphereCollidingObject::update_coords()
    {
        this->start_point = this->anchor_point + this->translate;

        // std::cout << "start_point = " << "(" << this->start_point.x << ", " << this->start_point.y << ", " << this->start_point.z << ")" << std::endl;
        // std::cout << "end_point = " << "(" << this->end_point.x << ", " << this->end_point.y << ", " << this->end_point.z << ")" << std::endl;
    }


    void SphereCollidingObject::set_radius(float _radius)
    {
        this->radius = _radius;
    }
    void SphereCollidingObject::set_is_collided(bool _is_collided)
    {
        this->is_collided = _is_collided;
    }

    void SphereCollidingObject::set_scale(const glm::vec3& _scale)
    {
        this->scale = _scale;

        update_coords();
    }


    void SphereCollidingObject::set_scale(float scale_x, float scale_y, float scale_z)
    {
        if (scale_x > 0) this->scale[0] = scale_x;
        if (scale_y > 0) this->scale[1] = scale_y;
        if (scale_z > 0) this->scale[2] = scale_z;

        update_coords();
    }


    void SphereCollidingObject::set_translate(const glm::vec3& _translate)
    {
        this->translate = _translate;

        update_coords();
    }


    void SphereCollidingObject::set_translate(float translate_x, float translate_y, float translate_z)
    {
        this->translate[0] = translate_x;
        this->translate[1] = translate_y;
        this->translate[2] = translate_z;

        update_coords();
    }

}