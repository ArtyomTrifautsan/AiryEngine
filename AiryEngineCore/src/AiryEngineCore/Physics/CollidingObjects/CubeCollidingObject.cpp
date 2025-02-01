#include "AiryEngineCore/Physics/CollidingObjects/CubeCollidingObject.hpp"

#include <glm/trigonometric.hpp>
#include <glm/ext/matrix_float3x3.hpp>
#include <glm/ext/matrix_float4x4.hpp>

#include <iostream>
#include <memory>


namespace AiryEngine {

    CubeCollidingObject::CubeCollidingObject()
    {
        this->is_collided = false;

        this->anchor_point = glm::vec3(-1, -1, -1); 

        this->x_vector = glm::vec3(2, 0, 0);
        this->y_vector = glm::vec3(0, 2, 0);
        this->z_vector = glm::vec3(0, 0, 2);

        this->translate = glm::vec3(0, 0, 0);
        this->scale = glm::vec3(1, 1, 1);

        update_coords();
    }

    // CubeCollidingObject::~CubeCollidingObject()
    // {

    // }

    void CubeCollidingObject::update_coords()
    {
        this->start_point = this->anchor_point + this->translate;

        glm::mat3 scale_matrix(
            this->scale[0], 0,              0,
            0,              this->scale[1], 0,
            0,              0,              this->scale[2]
        );

        this->x_shifted_point = this->start_point + scale_matrix * this->x_vector;
        this->y_shifted_point = this->start_point + scale_matrix * this->y_vector;
        this->z_shifted_point = this->start_point + scale_matrix * this->z_vector;

        this->end_point = this->start_point + scale_matrix * (this->x_vector + this->y_vector + this->z_vector);

        // std::cout << "start_point = " << "(" << this->start_point.x << ", " << this->start_point.y << ", " << this->start_point.z << ")" << std::endl;
        // std::cout << "end_point = " << "(" << this->end_point.x << ", " << this->end_point.y << ", " << this->end_point.z << ")" << std::endl;
    }


    void CubeCollidingObject::set_scale(const glm::vec3& _scale)
    {
        this->scale = _scale;

        update_coords();
    }


    void CubeCollidingObject::set_scale(float scale_x, float scale_y, float scale_z)
    {
        if (scale_x > 0) this->scale[0] = scale_x;
        if (scale_y > 0) this->scale[1] = scale_y;
        if (scale_z > 0) this->scale[2] = scale_z;

        update_coords();
    }


    void CubeCollidingObject::set_translate(const glm::vec3& _translate)
    {
        this->translate = _translate;

        update_coords();
    }


    void CubeCollidingObject::set_translate(float translate_x, float translate_y, float translate_z)
    {
        this->translate[0] = translate_x;
        this->translate[1] = translate_y;
        this->translate[2] = translate_z;

        update_coords();
    }


    void CubeCollidingObject::set_is_collided(bool _is_collided)
    {
        this->is_collided = _is_collided;
    }

    void CubeCollidingObject::move_colliding_object(float delta_move_x, float delta_move_y, float delta_move_z)
    {
        this->translate[0] = this->translate[0] + delta_move_x;
        this->translate[1] = this->translate[1] + delta_move_y;
        this->translate[2] = this->translate[2] + delta_move_z;
    }

    // void CubeCollidingObject::move_colliding_object_x(float delta_move_x);
    // void CubeCollidingObject::move_colliding_object_y(float delta_move_y);
    // void CubeCollidingObject::move_colliding_object_z(float delta_move_z);

    void CubeCollidingObject::rotate_colliding_object(float delta_angle_x, float delta_angle_y, float delta_angle_z)
    {
        this->rotate[0] = this->rotate[0] + delta_angle_x;
        this->rotate[1] = this->rotate[1] + delta_angle_y;
        this->rotate[2] = this->rotate[2] + delta_angle_z;
    }

    // void CubeCollidingObject::rotate_x(float delta_angle_x);
    // void CubeCollidingObject::rotate_y(float delta_angle_y);
    // void CubeCollidingObject::rotate_z(float delta_angle_z);

}