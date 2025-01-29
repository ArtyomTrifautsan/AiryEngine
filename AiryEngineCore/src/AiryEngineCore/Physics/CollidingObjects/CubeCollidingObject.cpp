#include "AiryEngineCore/Physics/CollidingObjects/CubeCollidingObject.hpp"

#include <glm/trigonometric.hpp>
#include <glm/ext/matrix_float3x3.hpp>
#include <glm/ext/matrix_float4x4.hpp>


namespace AiryEngine {

    CubeCollidingObject::CubeCollidingObject()
    {

    }

    CubeCollidingObject::~CubeCollidingObject()
    {

    }

    void CubeCollidingObject::update_coords()
    {
        this->anchor_point = glm::vec3(-1, -1, 1);
        this->x_point = glm::vec3(1, -1, 1);
        this->y_point = glm::vec3(-1, 1, 1);
        this->z_point = glm::vec3(-1, -1, -1);

        glm::mat3 scale_matrix(
            this->scale[0], 0,        0,
            0,        this->scale[1], 0,
            0,        0,        this->scale[2]
        );

        this->anchor_point = scale_matrix * this->anchor_point;
        this->x_point = scale_matrix * this->x_point;
        this->y_point = scale_matrix * this->y_point;
        this->z_point = scale_matrix * this->z_point;

        this->anchor_point = this->anchor_point + this->translate;
        this->x_point = this->x_point + this->translate;
        this->y_point = this->y_point + this->translate;
        this->z_point = this->z_point + this->translate;
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

}