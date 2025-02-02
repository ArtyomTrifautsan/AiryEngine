#pragma once

// Файлы движка
#include <AiryEngineCore/Application.hpp>
#include <AiryEngineCore/Renderer.hpp>

#include <AiryEngineCore/Physics/CollisionDetector.hpp>

// Файлы игры
#include "game_round.hpp"
#include "game_object_renderer.hpp"

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
    void setup_camera_dockspace();
    void setup_game_objects_dockspace();

    std::shared_ptr<GameRound> game_round;
    std::shared_ptr<GameObjectRenderer> game_object_renderer;

    std::shared_ptr<AiryEngine::Renderer> renderer;

    double initial_mouse_pos_x = 0.0;
    double initial_mouse_pos_y = 0.0;

    bool camera_dockspace_visible = true;
    float camera_position[3] = { 0, 2, 0 };
    float camera_rotation[3] = { 25, 0, 0 };

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

    float car_model_position[3] = { 0, 0, 0 };
    float car_model_scale[3] = { 1, 1, 1 };
    float car_colliding_cube_position[3] = { 0, 0, 0 };
    float car_colliding_cube_scale[3] = { 1, 1, 1 };
    bool car_visible = true;

    float road_model_position[3] = { 0, 0, 0 };
    float road_model_scale[3] = { 1, 1, 1 };
    float road_colliding_cube_position[3] = { 0, 0, 0 };
    float road_colliding_cube_scale[3] = { 1, 1, 1 };
    bool road_visible = true;

    float barrier_model_position[3] = { 0, 0, 0 };
    float barrier_model_scale[3] = { 1, 1, 1 };
    float barrier_colliding_cube_position[3] = { 0, 0, 0 };
    float barrier_colliding_cube_scale[3] = { 1, 1, 1 };
    bool barrier_visible = true;

    float coin_model_position[3] = { 0, 0, 0 };
    float coin_model_scale[3] = { 1, 1, 1 };
    float coin_colliding_cube_position[3] = { 0, 0, 0 };
    float coin_colliding_cube_scale[3] = { 1, 1, 1 };
    float coin_model_rotate[3] = { 0, 0, 0 };
    bool coin_visible = true;

    float fuel_canister_model_position[3] = { 0, 0, 0 };
    float fuel_canister_model_scale[3] = { 1, 1, 1 };
    float fuel_canister_colliding_cube_position[3] = { 0, 0, 0 };
    float fuel_canister_colliding_cube_scale[3] = { 1, 1, 1 };
    float fuel_canister_model_rotate[3] = { 0, 0, 0 };
    bool fuel_canister_visible = true;

    void _handle_events();
    void _update_light_source_state();
    void _detect_collisions();
};

