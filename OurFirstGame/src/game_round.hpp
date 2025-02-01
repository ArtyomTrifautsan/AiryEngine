#pragma once

// Файлы движка
#include <AiryEngineCore/Physics/CollisionDetector.hpp>

#include <AiryEngineCore/Rendering/OpenGL/Model3D.hpp>

#include <AiryEngineCore/ResourceManager.hpp>
#include <AiryEngineCore/Renderer.hpp>
#include "AiryEngineCore/Camera.hpp"

// Системные библиотеки
#include <memory>
#include <string>


class GameRound {
public:
    // GameRound();
    // ~GameRound();

    void start(std::shared_ptr<AiryEngine::ResourceManager> resource_manager);
    void on_update();

    void render_game_objects(std::shared_ptr<AiryEngine::Renderer> renderer, AiryEngine::Camera& camera);

    void set_visible_colliding_objects(bool visible_colliding_objects);
    bool get_visible_colliding_objects() const { return this->visible_colliding_objects; }

    void set_translate_car(glm::vec3 model_translate, glm::vec3 colliding_cube_translate);
    void set_scale_car(glm::vec3 model_scale, glm::vec3 colliding_cube_scale);
    void set_translate_road(glm::vec3 translate, glm::vec3 colliding_cube_translate);
    void set_scale_road(glm::vec3 model_scale, glm::vec3 colliding_cube_scale);
    void set_translate_barrier(glm::vec3 translate, glm::vec3 colliding_cube_translate);
    void set_scale_barrier(glm::vec3 model_scale, glm::vec3 colliding_cube_scale);
    void set_translate_coin(glm::vec3 translate, glm::vec3 colliding_cube_translate);
    void set_scale_coin(glm::vec3 model_scale, glm::vec3 colliding_cube_scale);
    void set_translate_fuel_canister(glm::vec3 translate, glm::vec3 colliding_cube_translate);
    void set_scale_fuel_canister(glm::vec3 model_scale, glm::vec3 colliding_cube_scale);

    void set_visible_car(bool visible_car);
    void set_visible_road(bool visible_road);
    void set_visible_barrier(bool visible_barrier);
    void set_visible_coin(bool visible_coin);
    void set_visible_fuel_canister(bool visible_fuel_canister);

    bool get_visible_car() const { return this->visible_car; }
    bool get_visible_road() const { return this->visible_road; }
    bool get_visible_barrier() const { return this->visible_barrier; }
    bool get_visible_coin() const { return this->visible_coin; }
    bool get_visible_fuel_canister() const { return this->visible_fuel_canister; }

private:
    void create_car(std::shared_ptr<AiryEngine::ResourceManager> resource_manager);
    void create_road(std::shared_ptr<AiryEngine::ResourceManager> resource_manager);
    void create_barrier(std::shared_ptr<AiryEngine::ResourceManager> resource_manager);
    void create_coin(std::shared_ptr<AiryEngine::ResourceManager> resource_manager);
    void create_fuel_canister(std::shared_ptr<AiryEngine::ResourceManager> resource_manager);

    void render_car(std::shared_ptr<AiryEngine::Renderer> renderer, AiryEngine::Camera& camera);
    void render_road(std::shared_ptr<AiryEngine::Renderer> renderer, AiryEngine::Camera& camera);
    void render_barrier(std::shared_ptr<AiryEngine::Renderer> renderer, AiryEngine::Camera& camera);
    void render_coin(std::shared_ptr<AiryEngine::Renderer> renderer, AiryEngine::Camera& camera);
    void render_fuel_canister(std::shared_ptr<AiryEngine::Renderer> renderer, AiryEngine::Camera& camera);


    std::shared_ptr<AiryEngine::Model3D> colliding_cube_model3D;
    std::shared_ptr<AiryEngine::Model3D> colliding_sphere_model3D;

    std::shared_ptr<AiryEngine::Model3D> car_model;
    std::shared_ptr<AiryEngine::CubeCollidingObject> car_colliding_cube;
    glm::vec3 car_model_start_offset;
    glm::vec3 car_model_start_scale;
    glm::vec3 car_colliding_cube_start_offset;
    glm::vec3 car_colliding_cube_start_scale;
    bool visible_car = true;

    std::shared_ptr<AiryEngine::Model3D> road_model;
    std::shared_ptr<AiryEngine::CubeCollidingObject> road_colliding_cube;
    glm::vec3 road_model_start_offset;
    glm::vec3 road_model_start_scale;
    glm::vec3 road_colliding_cube_start_offset;
    glm::vec3 road_colliding_cube_start_scale;
    bool visible_road = true;

    std::shared_ptr<AiryEngine::Model3D> barrier_model;
    std::shared_ptr<AiryEngine::CubeCollidingObject> barrier_colliding_cube;
    glm::vec3 barrier_model_start_offset;
    glm::vec3 barrier_model_start_scale;
    glm::vec3 barrier_colliding_cube_start_offset;
    glm::vec3 barrier_colliding_cube_start_scale;
    bool visible_barrier = true;

    std::shared_ptr<AiryEngine::Model3D> coin_model;
    std::shared_ptr<AiryEngine::CubeCollidingObject> coin_colliding_cube;
    glm::vec3 coin_model_start_offset;
    glm::vec3 coin_model_start_scale;
    glm::vec3 coin_colliding_cube_start_offset;
    glm::vec3 coin_colliding_cube_start_scale;
    bool visible_coin = true;

    std::shared_ptr<AiryEngine::Model3D> fuel_canister_model;
    std::shared_ptr<AiryEngine::CubeCollidingObject> fuel_canister_colliding_cube;
    glm::vec3 fuel_canister_model_start_offset;
    glm::vec3 fuel_canister_model_start_scale;
    glm::vec3 fuel_canister_colliding_cube_start_offset;
    glm::vec3 fuel_canister_colliding_cube_start_scale;
    bool visible_fuel_canister = true;

    bool visible_colliding_objects = true;
};