#include "AiryEngineCore/Physics/CollidingObjects/SphereCollidingObject.hpp"


namespace AiryEngine {

    SphereCollidingObject::SphereCollidingObject()
    {

    }

    SphereCollidingObject::~SphereCollidingObject()
    {

    }

    void SphereCollidingObject::set_radius(float _radius)
    {
        this->radius = _radius;
    }

    void SphereCollidingObject::set_translate(glm::vec3 _translate)
    {
        this->translate = _translate;
    }

    void SphereCollidingObject::set_translate(float translate_x, float translate_y, float translate_z)
    {
        this->translate[0] = translate_x;
        this->translate[1] = translate_y;
        this->translate[2] = translate_z;
    }

    void SphereCollidingObject::set_is_collided(bool _is_collided)
    {
        this->is_collided = _is_collided;
    }

}