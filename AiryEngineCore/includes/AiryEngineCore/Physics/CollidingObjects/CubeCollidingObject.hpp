#pragma once

#include <glm/vec3.hpp>

namespace AiryEngine {

    class CubeCollidingObject
    {
    public:
        CubeCollidingObject();
        // ~CubeCollidingObject();

        void set_is_collided(bool _is_collided);
        bool get_is_collided() const { return this->is_collided; }

        void set_scale(const glm::vec3& _scale);
        void set_scale(float scale_x, float scale_y, float scale_z);
        void set_translate(const glm::vec3& _translate);
        void set_translate(float translate_x, float translate_y, float translate_z);

        void move_colliding_object(float delta_move_x, float delta_move_y, float delta_move_z);
        void move_colliding_object_x(float delta_move_x);
        void move_colliding_object_y(float delta_move_y);
        void move_colliding_object_z(float delta_move_z);

        void rotate_colliding_object(float delta_angle_x, float delta_angle_y, float delta_angle_z);
        void rotate_colliding_object_x(float delta_angle_x);
        void rotate_colliding_object_y(float delta_angle_y);
        void rotate_colliding_object_z(float delta_angle_z);

        glm::vec3 get_anchor_point() const { return this->anchor_point; }

        glm::vec3 get_start_point() const { return this->start_point; }
        glm::vec3 get_end_point() const { return this->end_point; }

        glm::vec3 get_x_shifted_point() const { return this->x_shifted_point; }
        glm::vec3 get_y_shifted_point() const { return this->y_shifted_point; }
        glm::vec3 get_z_shifted_point() const { return this->z_shifted_point; }

        glm::vec3 get_x_vector() const { return this->x_vector; }
        glm::vec3 get_y_vector() const { return this->y_vector; }
        glm::vec3 get_z_vector() const { return this->z_vector; }

        glm::vec3 get_translate() { return this->translate; }
        glm::vec3 get_scale() { return this->scale; }
    
    private:
        bool is_collided;

        glm::vec3 anchor_point;

        glm::vec3 start_point;
        glm::vec3 end_point;
        glm::vec3 x_shifted_point;
        glm::vec3 y_shifted_point;
        glm::vec3 z_shifted_point;

        glm::vec3 x_vector;
        glm::vec3 y_vector;
        glm::vec3 z_vector;

        glm::vec3 translate;
        glm::vec3 scale;
        glm::vec3 rotate;

        void update_coords();
    };

}