#include "AiryEngineCore/Physics/CollisionDetector.hpp"

#include <glm/vec3.hpp>
#include <glm/trigonometric.hpp>
#include <glm/ext/matrix_float4x4.hpp>

#include <cmath>

// #include "AiryEngineCore/Physics/CollidingObjects/CubeCollidingObject.hpp"
// #include "AiryEngineCore/Physics/CollidingObjects/SphereCollidingObject.hpp"


namespace AiryEngine {

    bool CollisionDetector::cube_cube_collision(CubeCollidingObject first, CubeCollidingObject second)    
    {
        // Checking X axis
        if (first.anchor_point[0] > second.x_point[0]) return false;
        if (first.x_point[0] < second.anchor_point[0]) return false;

        // Checking Y axis
        if (first.anchor_point[1] > second.y_point[1]) return false;
        if (first.y_point[1] < second.anchor_point[1]) return false;

        // Checking Z axis
        if (first.anchor_point[2] < second.z_point[2]) return false;
        if (first.z_point[2] > second.anchor_point[2]) return false;

        return true;
    }


    // bool CollisionDetector::cube_sphere_collision(CubeCollidingObject cube, SphereCollidingObject sphere)
    // {
    //     float max_distance = sphere.get_radius();

    //     // Проверяем ось Х
    //     if ((sphere.anchor_point[0] + max_distance) < cube.anchor_point[0] || 
    //         (sphere.anchor_point[0] - max_distance) > cube.x_point[0])
    //     {
    //         return false;
    //     }

    //     // Вычисляем максимальное расстояние, на котором может находиться шар по оси Y
    //     int dist_x_1 = sphere.anchor_point[0] - cube.anchor_point[0];
    //     if (dist_x_1 < 0) dist_x_1 *= -1;
    //     int dist_x_2 = sphere.anchor_point[0] - cube.x_point[0];
    //     if (dist_x_2 < 0) dist_x_2 *= -1;

    //     int shorter_dist_x = dist_x_1 ? dist_x_1 < dist_x_2 : dist_x_2;
    //     max_distance = sqrt(pow(sphere.get_radius(), 2) - pow(shorter_dist_x, 2));

    //     // Проверяем ось У
    //     if ((sphere.anchor_point[1] + max_distance) < cube.anchor_point[1] || 
    //         (sphere.anchor_point[1] - max_distance) > cube.y_point[1])
    //     {
    //         return false;
    //     }

    //     // Вычисляем максимальное расстояние, на котором может находиться шар по оси Z
    //     int dist_y_1 = sphere.anchor_point[1] - cube.anchor_point[1];
    //     if (dist_y_1 < 0) dist_y_1 *= -1;
    //     int dist_y_2 = sphere.anchor_point[1] - cube.y_point[1];
    //     if (dist_y_2 < 0) dist_y_2 *= -1;

    //     int shorter_dist_y = dist_y_1 ? dist_y_1 < dist_y_2 : dist_y_2;
    //     max_distance = sqrt(pow(sphere.get_radius(), 2) - pow(shorter_dist_x, 2) - pow(shorter_dist_y, 2));

    //     // Проверяем ось Z
    //     if ((sphere.anchor_point[2] - max_distance) > cube.anchor_point[2] || 
    //         (sphere.anchor_point[2] + max_distance) < cube.z_point[2])
    //     {
    //         return false;
    //     }

    //     return true;
    // }


    bool CollisionDetector::cube_sphere_collision(CubeCollidingObject cube, SphereCollidingObject sphere)
    {
        glm::vec3 cube_center = glm::vec3(
            cube.anchor_point[0] + cube.x_point[0] / 2,
            cube.anchor_point[1] + cube.y_point[1] / 2,
            cube.anchor_point[2] + cube.z_point[2] / 2
        );

        // Сдвигаем сферу на расстояние её радиуса в сторону центр куба
        glm::vec3 destinatoin_vector = glm::normalize(cube_center - sphere.anchor_point);
        destinatoin_vector[0] *= sphere.radius / sqrt(3);
        destinatoin_vector[1] *= sphere.radius / sqrt(3);
        destinatoin_vector[2] *= sphere.radius / sqrt(3);
        glm::vec3 point = sphere.anchor_point + destinatoin_vector;

        // if point into the cube, then return true
        // Если центр сферы внутри куба, то фигуры пересекаются
        if (point[0] < cube.anchor_point[0] || point[0] > cube.x_point[0]) return false;
        if (point[1] < cube.anchor_point[1] || point[1] > cube.y_point[1]) return false;
        if (point[2] > cube.anchor_point[2] || point[2] < cube.z_point[2]) return false;

        return true;
    }


    bool CollisionDetector::sphere_sphere_collision(SphereCollidingObject first, SphereCollidingObject second)
    {
        float distance_between_spheres = sqrt(pow(first.anchor_point[0] - second.anchor_point[0], 2) + 
                                                pow(first.anchor_point[1] - second.anchor_point[1], 2) +
                                                pow(first.anchor_point[2] - second.anchor_point[2], 2));

        if (distance_between_spheres > first.get_radius() + second.get_radius())
            return false;
        
        return true;
    }

}