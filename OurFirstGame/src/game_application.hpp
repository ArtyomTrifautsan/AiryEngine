#pragma once

// Файлы движка
#include <AiryEngineCore/Application.hpp>
#include <AiryEngineCore/Renderer.hpp>

#include <AiryEngineCore/Physics/CollisionDetector.hpp>

// Файлы игры
#include "game_round.hpp"

// Системные библиотеки
#include <memory>
#include <string>


class GameApplication : public AiryEngine::Application
{
public:
    GameApplication(std::shared_ptr<AiryEngine::ResourceManager> _resource_manager);
    virtual void on_start(std::shared_ptr<AiryEngine::ResourceManager> _resource_manager) override;
    virtual void on_update() override;
    virtual void on_draw() override;
    virtual void on_mouse_button_pressed(const AiryEngine::MouseButtonCode mouse_button_code, 
                                        const double x_pos, 
                                        const double y_pos, 
                                        const bool pressed) override;
    virtual void on_ui_draw() override;

private:
    void setup_dockspace_menu();
    void setup_light_dockspace();
    void setup_game_objects_dockspace();

    std::shared_ptr<GameRound> game_round;

    std::shared_ptr<AiryEngine::Renderer> renderer;

    std::shared_ptr<AiryEngine::Model3D> lamp_model;
    std::shared_ptr<AiryEngine::Model3D> cube_model3D;
    std::shared_ptr<AiryEngine::Model3D> sphere_model3D;
    std::shared_ptr<AiryEngine::Model3D> canister_model;
    std::shared_ptr<AiryEngine::CubeCollidingObject> cube_1_colliding_object;
    std::shared_ptr<AiryEngine::CubeCollidingObject> cube_2_colliding_object;
    std::shared_ptr<AiryEngine::SphereCollidingObject> sphere_1_colliding_object;
    std::shared_ptr<AiryEngine::SphereCollidingObject> sphere_2_colliding_object;

    double initial_mouse_pos_x = 0.0;
    double initial_mouse_pos_y = 0.0;

    bool light_source_visible = true;
    float light_source_position[3] = { 0, 17.0f, -11.0f };
    float light_source_color[3] = { 1, 1, 1 };
    float ambient_factor = 0.1f;
    float diffuse_factor = 1.0f;
    float specular_factor = 0.5f;

    float camera_fov = 60.f;
    float camera_near_plane = 0.1f;
    float camera_far_plane = 100.f;

    bool visible_colliding_objects = true;

    // float car_model_position[3] = { 0, 0, -10.025f };
    // float car_model_scale[3] = { 1, 1, 1 };
    // float car_colliding_cube_position[3] = { 0.529f, 0.282f, 0.070f };
    // float car_colliding_cube_scale[3] = { 1.781f, 0.497f, 0.873f };
    float car_model_position[3] = { 10.101f, 0, 0 };
    float car_model_scale[3] = { 1, 1, 1 };
    float car_colliding_cube_position[3] = { 0.006f, 0.282f, 0.529f };
    float car_colliding_cube_scale[3] = { 0.873f, 0.497f, 1.781f };
    bool car_visible = true;

    float road_model_position[3] = { 0, -0.302f, 0 };
    float road_model_scale[3] = { 0.708f, 0.708f, 0.708f };
    float road_colliding_cube_position[3] = { 0, -0.620f, -0.753f };
    float road_colliding_cube_scale[3] = { 3.569f, 0.395f, 4.317f };
    bool road_visible = true;

    float barrier_model_position[3] = { 0, -0.503f, 0 };
    float barrier_model_scale[3] = { 0.270f, 0.270f, 0.270f };
    float barrier_colliding_cube_position[3] = { 0, 0.202f, 0 };
    float barrier_colliding_cube_scale[3] = { 0.849f, 0.446f, 0.246f };
    bool barrier_visible = true;

    float coin_model_position[3] = { -2.821f, 0.302f, 0 };
    float coin_model_scale[3] = { 0.300f, 0.300f, 0.300f };
    float coin_colliding_cube_position[3] = { -0.025f, 0.400f, 0 };
    float coin_colliding_cube_scale[3] = { 0.360f, 0.360f, 0.360f };
    bool coin_visible = true;

    float fuel_canister_model_position[3] = { 0, 0.202, 0 };
    float fuel_canister_model_scale[3] = { 0.120f, 0.120f, 0.120f };
    float fuel_canister_colliding_cube_position[3] = { 0, 0.404, 0 };
    float fuel_canister_colliding_cube_scale[3] = { 0.320f, 0.537f, 0.321f };
    bool fuel_canister_visible = true;

    void _handle_events();
    void _update_light_source_state();
    void _detect_collisions();
};

