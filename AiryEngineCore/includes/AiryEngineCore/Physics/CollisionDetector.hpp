#pragma once

#include "AiryEngineCore/Physics/CollidingObjects/CubeCollidingObject.hpp"
#include "AiryEngineCore/Physics/CollidingObjects/SphereCollidingObject.hpp"


namespace AiryEngine {

    // class CubeCollidingObject;
    // class SphereCollidingObject;

    class CollisionDetector
    {
    public:
        static bool cube_cube_collision(CubeCollidingObject first, CubeCollidingObject second);
        static bool cube_sphere_collision(CubeCollidingObject cube, SphereCollidingObject sphere);
        static bool sphere_sphere_collision(SphereCollidingObject first, SphereCollidingObject second);
    
    private:

    };

}