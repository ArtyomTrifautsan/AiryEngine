#pragma once


// Файлы движка
#include <AiryEngineCore/Physics/CollisionDetector.hpp>

#include <AiryEngineCore/Rendering/OpenGL/Model3D.hpp>

#include <AiryEngineCore/ResourceManager.hpp>


// Системные библиотеки
#include <memory>


class GameObject {
public:
    GameObject(const std::string& model_name,
        const std::string& model_path,
        const std::string& model_dir_path,
        std::shared_ptr<AiryEngine::ResourceManager> resource_manager);

    std::shared_ptr<AiryEngine::Model3D> get_model() const { return this->model; }
    std::shared_ptr<AiryEngine::CubeCollidingObject> get_colliding_cube() const { return this->colliding_cube; }

    void update_pos_and_scale();
    
    void set_visible(bool visible);
    bool get_visible() const { return this->visible; }

    void set_position(glm::vec3 position);      // Позиции выставляются относительно start_offset
    void set_position(float position_x, float position_y, float position_z);
    glm::vec3 get_position() const { return this->position; }

    void set_scale(glm::vec3 scale);      // Масштабирование выставляется относительно start_scale
    void set_scale(float scale_x, float scale_y, float scale_z);
    glm::vec3 get_scale() const { return this->scale; }

    void set_rotate(glm::vec3 rotate);
    void set_rotate(float rotate_x, float rotate_y, float rotate_z);
    glm::vec3 get_rotate() const { return this->rotate; }

    void set_model_start_offset(glm::vec3 model_start_offset);
    void set_model_start_scale(glm::vec3 model_start_scale);
    void set_model_start_rotate(glm::vec3 model_start_rotate);
    void set_colliding_cube_start_offset(glm::vec3 colliding_cube_start_offset);
    void set_colliding_cube_start_scale(glm::vec3 colliding_cube_start_scale);

protected:
    std::shared_ptr<AiryEngine::Model3D> model;
    std::shared_ptr<AiryEngine::CubeCollidingObject> colliding_cube;

    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotate;

    glm::vec3 model_start_offset;
    glm::vec3 model_start_scale;
    glm::vec3 model_start_rotate;
    glm::vec3 colliding_cube_start_offset;
    glm::vec3 colliding_cube_start_scale;

    bool visible;
};