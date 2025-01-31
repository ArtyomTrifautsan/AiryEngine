#pragma once

#include <AiryEngineCore/Application.hpp>
#include <AiryEngineCore/Renderer.hpp>

#include <AiryEngineCore/Physics/CollisionDetector.hpp>


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

    void setup_dockspace_menu();

private:
    std::shared_ptr<AiryEngine::Renderer> renderer;

    std::shared_ptr<AiryEngine::Model3D> lamp_model;
    std::shared_ptr<AiryEngine::Model3D> cube_model3D;
    std::shared_ptr<AiryEngine::Model3D> sphere_model3D;
    std::shared_ptr<AiryEngine::CubeCollidingObject> cube_1_colliding_object;
    std::shared_ptr<AiryEngine::CubeCollidingObject> cube_2_colliding_object;
    std::shared_ptr<AiryEngine::SphereCollidingObject> sphere_1_colliding_object;
    std::shared_ptr<AiryEngine::SphereCollidingObject> sphere_2_colliding_object;

    double initial_mouse_pos_x = 0.0;
    double initial_mouse_pos_y = 0.0;

    float light_source_position[3] = { 0, 0, 0 };
    float light_source_color[3] = { 1, 1, 1 };
    float ambient_factor = 0.1f;
    float diffuse_factor = 1.0f;
    float specular_factor = 0.5f;

    float camera_fov = 60.f;
    float camera_near_plane = 0.1f;
    float camera_far_plane = 100.f;

    float collision_cube_1_position[3] = { 0, 0, 0 };
    float collision_cube_2_position[3] = { 0, 0, 0 };
    float collision_sphere_1_position[3] = { -3, -3, 0 };
    float collision_sphere_2_position[3] = { -3, -3, 0 };

    void _handle_events();
    void _update_light_source_state();
    void _detect_collisions();
};

