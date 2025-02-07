#include "game_application.hpp"

#include <imgui/imgui.h>
#include <AiryEngineCore/Input.hpp>
#include <AiryEngineCore/ResourceManager.hpp>

#include <AiryEngineCore/Rendering/OpenGL/Model3D.hpp>

#include <iostream>



GameApplication::GameApplication(std::shared_ptr<AiryEngine::ResourceManager> _resource_manager) : AiryEngine::Application(_resource_manager)
{
    // set_executable_path(executable_path);
    // std::cout << "GameApplication constructor started" << std::endl;
}
// adar

void GameApplication::on_start(std::shared_ptr<AiryEngine::ResourceManager> _resource_manager)
{
    this->renderer = std::make_shared<AiryEngine::Renderer>(_resource_manager);

    this->game_round = std::make_shared<GameRound>(_resource_manager);
    this->game_object_renderer = std::make_shared<GameObjectRenderer>(this->renderer, this->camera, _resource_manager);
}

void GameApplication::on_update()
{
    _handle_events(); 

    _update_light_source_state();

    _detect_collisions();
}

void GameApplication::_handle_events()
{
    glm::vec3 movement_delta{ 0, 0, 0 };
    glm::vec3 rotation_delta{ 0, 0, 0 };

    // Go Forward
    if (AiryEngine::Input::IsKeyPressed(AiryEngine::KeyCode::KEY_W))
    {
        movement_delta.x += 0.05f;
    }

    // Go Back
    if (AiryEngine::Input::IsKeyPressed(AiryEngine::KeyCode::KEY_S))
    {
        movement_delta.x -= 0.05f;
    }

    // Go Left
    if (AiryEngine::Input::IsKeyPressed(AiryEngine::KeyCode::KEY_A))
    {
        movement_delta.y += 0.05f;
    }

    // Go Right
    if (AiryEngine::Input::IsKeyPressed(AiryEngine::KeyCode::KEY_D))
    {
        movement_delta.y -= 0.05f;
    }

    // Go Up
    if (AiryEngine::Input::IsKeyPressed(AiryEngine::KeyCode::KEY_SPACE))
    {
        movement_delta.z += 0.05f;
    }

    // Go Down
    if (AiryEngine::Input::IsKeyPressed(AiryEngine::KeyCode::KEY_LEFT_SHIFT))
    {
        movement_delta.z -= 0.05f;
    }

    // Rotation Up
    if (AiryEngine::Input::IsKeyPressed(AiryEngine::KeyCode::KEY_UP))
    {
        rotation_delta.y -= 0.5f;
    }

    // Rotation Down
    if (AiryEngine::Input::IsKeyPressed(AiryEngine::KeyCode::KEY_DOWN))
    {
        rotation_delta.y += 0.5f;
    }

    // Rotation Left
    if (AiryEngine::Input::IsKeyPressed(AiryEngine::KeyCode::KEY_LEFT))
    {
        rotation_delta.z -= 0.5f;
    }

    // Rotation Right
    if (AiryEngine::Input::IsKeyPressed(AiryEngine::KeyCode::KEY_RIGHT))
    {
        rotation_delta.z += 0.5f;
    }

    // Rotation 1
    if (AiryEngine::Input::IsKeyPressed(AiryEngine::KeyCode::KEY_P))
    {
        rotation_delta.x += 0.5f;
    }

    // Rotation 2
    if (AiryEngine::Input::IsKeyPressed(AiryEngine::KeyCode::KEY_O))
    {
        rotation_delta.x -= 0.5f;
    }


    if (AiryEngine::Input::IsMouseButtonPressed(AiryEngine::MouseButtonCode::MOUSE_BUTTON_RIGHT))
    {
        glm::vec2 current_cursor_position = get_current_cursor_position();

        if (AiryEngine::Input::IsMouseButtonPressed(AiryEngine::MouseButtonCode::MOUSE_BUTTON_LEFT))
        {
            camera->move_right(static_cast<float>(current_cursor_position.x - this->initial_mouse_pos_x) / 100.f );
            // camera.move_up(static_cast<float>(this->initial_mouse_pos_y - current_cursor_position.y) / 100.f );
            camera->move_up(static_cast<float>(current_cursor_position.y - this->initial_mouse_pos_y) / 100.f );
        }
        else
        {
            // rotation_delta.z += static_cast<float>(this->initial_mouse_pos_x - current_cursor_position.x) / 5.f;
            // rotation_delta.y -= static_cast<float>(this->initial_mouse_pos_y - current_cursor_position.y) / 5.f;
            rotation_delta.y += static_cast<float>(this->initial_mouse_pos_x - current_cursor_position.x) / 5.f;
            rotation_delta.x -= static_cast<float>(this->initial_mouse_pos_y - current_cursor_position.y) / 5.f;
        }

        this->initial_mouse_pos_x = current_cursor_position.x;
        this->initial_mouse_pos_y = current_cursor_position.y;
    }

    camera->add_movement_and_rotation(movement_delta, rotation_delta);  
}


void GameApplication::_update_light_source_state()
{
    // this->lamp_model->set_scale(0.1, 0.1, 0.1);
    // this->lamp_model->set_translate(light_source_position[0], light_source_position[1], light_source_position[2]);
}


void GameApplication::_detect_collisions()
{
    // this->cube_1_colliding_object->set_is_collided(false);
    // this->cube_2_colliding_object->set_is_collided(false);
    // this->sphere_1_colliding_object->set_is_collided(false);
    // this->sphere_2_colliding_object->set_is_collided(false);

    // if (AiryEngine::CollisionDetector::cube_cube_collision(*this->cube_1_colliding_object, *this->cube_2_colliding_object))
    // {
    //     this->cube_1_colliding_object->set_is_collided(true);
    //     this->cube_2_colliding_object->set_is_collided(true);
    // }

    // if (AiryEngine::CollisionDetector::sphere_sphere_collision(*this->sphere_1_colliding_object, *this->sphere_2_colliding_object))
    // {
    //     this->sphere_1_colliding_object->set_is_collided(true);
    //     this->sphere_2_colliding_object->set_is_collided(true);
    // }

    // if (AiryEngine::CollisionDetector::cube_sphere_collision(*this->cube_1, *this->sphere_1))
    // {
    //     this->cube_1->set_is_collided(true);
    //     this->sphere_1->set_is_collided(true);
    // }

    // if (AiryEngine::CollisionDetector::cube_sphere_collision(*this->cube_1, *this->sphere_2))
    // {
    //     this->cube_1->set_is_collided(true);
    //     this->sphere_2->set_is_collided(true);
    // }

    // if (AiryEngine::CollisionDetector::cube_sphere_collision(*this->cube_2, *this->sphere_1))
    // {
    //     this->cube_2->set_is_collided(true);
    //     this->sphere_1->set_is_collided(true);
    // }

    // if (this->cube_1_colliding_object->get_is_collided()) collision_cube_model_1->set_diffuse_color(1, 0, 0);
    // else collision_cube_model_1->set_diffuse_color(0, 1, 0);

    // if (this->cube_2->get_is_collided()) collision_cube_model_2->set_diffuse_color(1, 0, 0);
    // else collision_cube_model_2->set_diffuse_color(0, 1, 0);

    // if (this->sphere_1->get_is_collided()) collision_sphere_model_1->set_diffuse_color(1, 0, 0);
    // else collision_sphere_model_1->set_diffuse_color(0, 1, 0);

    // if (this->sphere_2->get_is_collided()) collision_sphere_model_2->set_diffuse_color(1, 0, 0);
    // else collision_sphere_model_2->set_diffuse_color(0, 1, 0);
}


void GameApplication::on_draw()
{
    // this->renderer->render_model3D(camera, this->lamp_model);

    // this->game_round->render_game_objects(this->renderer, this->camera);

    this->game_object_renderer->render_car(this->game_round->get_car());
    this->game_object_renderer->render_road(this->game_round->get_road());
    this->game_object_renderer->render_barrier(this->game_round->get_barrier());
    this->game_object_renderer->render_coin(this->game_round->get_coin());
    this->game_object_renderer->render_fuel_canister(this->game_round->get_fuel_canister());
}


void GameApplication::setup_dockspace_menu()
{
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
    static ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    window_flags |= ImGuiWindowFlags_NoBackground;

    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace", nullptr, window_flags);
    ImGui::PopStyleVar(3);

    ImGuiIO& io = ImGui::GetIO();
    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            // Disabling fullscreen would allow the window to be moved to the front of other windows,
            // which we can't undo at the moment without finer window depth/z control.
            if (ImGui::MenuItem("New Scene...", NULL))
            {

            }

            if (ImGui::MenuItem("Open Scene...", NULL))
            {

            }

            if (ImGui::MenuItem("Save Scene...", NULL))
            {

            }
            ImGui::Separator();
            if (ImGui::MenuItem("Exit", NULL))
            {
                close();
            }
            
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    ImGui::End();
}


void GameApplication::on_mouse_button_pressed(const AiryEngine::MouseButtonCode mouse_button_code, 
                                                const double x_pos, 
                                                const double y_pos, 
                                                const bool pressed)
{
    this->initial_mouse_pos_x = x_pos;
    this->initial_mouse_pos_y = y_pos;
}


void GameApplication::on_ui_draw()
{
    setup_dockspace_menu();

    camera_fov = camera->get_field_of_view();
    camera_near_plane = camera->get_near_clip_plane();
    camera_far_plane = camera->get_far_clip_plane();

    // Editor GUI
    ImGui::Begin("Editor");

    setup_game_objects_dockspace();
    ImGui::Checkbox("light source visible", &light_source_visible);
    if (light_source_visible)
        setup_light_dockspace();
    
    ImGui::Checkbox("camera dockspace visible", &camera_dockspace_visible);
    if (camera_dockspace_visible)
        setup_camera_dockspace();

    ImGui::End();
}


void GameApplication::setup_light_dockspace()
{
    ImGui::SliderFloat3("light source position", light_source_position, -50.0f, 50.0f);
    this->renderer->set_light_source_position(glm::vec3(light_source_position[0], light_source_position[1], light_source_position[2]));

    ImGui::ColorEdit3("light source color", light_source_color);
    this->renderer->set_light_source_color(glm::vec3(light_source_color[0], light_source_color[1], light_source_color[2]));

    ImGui::SliderFloat("ambient factor", &ambient_factor, 0.0f, 1.0f);
    this->renderer->set_ambient_factor(ambient_factor);

    ImGui::SliderFloat("diffuse factor", &diffuse_factor, 0.0f, 1.0f);
    this->renderer->set_diffuse_factor(diffuse_factor);

    ImGui::SliderFloat("specular factor", &specular_factor, 0.0f, 1.0f);
    this->renderer->set_specular_factor(specular_factor);

    // ImGui::SliderFloat("shininess", &shininess, 1.0f, 128.0f);
    // set_shininess(shininess);

    if (ImGui::SliderFloat("camera FOV", &camera_fov, 1.0f, 120.0f))
    {
        camera->set_field_of_view(camera_fov);
    }
    if (ImGui::SliderFloat("camera near clip plane", &camera_near_plane, 0.1f, 10.0f))
    {
        camera->set_near_clip_plane(camera_near_plane);
    }  
    if (ImGui::SliderFloat("camera far clip plane", &camera_far_plane, 1.0f, 100.0f))
    {
        camera->set_far_clip_plane(camera_far_plane);
    }
}


void GameApplication::setup_camera_dockspace()
{
    glm::vec3 cam_pos = this->camera->get_camera_position();
    camera_position[0] = cam_pos.x;
    camera_position[1] = cam_pos.y;
    camera_position[2] = cam_pos.z;
    if (ImGui::SliderFloat3("camera position", camera_position, -10.0f, 10.0f))
    {
        this->camera->set_position(glm::vec3(camera_position[0], camera_position[1], camera_position[2]));
    }

    glm::vec3 cam_rot = this->camera->get_camera_rotation();
    camera_rotation[0] = cam_rot.x;
    camera_rotation[1] = cam_rot.y;
    camera_rotation[2] = cam_rot.z;
    if (ImGui::SliderFloat3("camera rotation", camera_rotation, 0.0f, 360.0f))
    {
        this->camera->set_rotation(glm::vec3(camera_rotation[0], camera_rotation[1], camera_rotation[2]));
    }
}


void GameApplication::setup_game_objects_dockspace()
{
    ImGui::Checkbox("visible colliding objects", &visible_colliding_objects);
    this->game_object_renderer->set_visible_colliding_objects(visible_colliding_objects);

    ImGui::Checkbox("car visible", &car_visible);
    this->game_round->get_car()->set_visible(car_visible);

    if (car_visible)
    {
        ImGui::SliderFloat3("car pos", car_model_position, -20.0f, 20.0f);
        this->game_round->get_car()->set_position(
            car_model_position[0], 
            car_model_position[1], 
            car_model_position[2]
        );

        ImGui::SliderFloat3("car scale", car_model_scale, 0.0f, 10.0f);
        this->game_round->get_car()->set_scale(
            car_model_scale[0], 
            car_model_scale[1], 
            car_model_scale[2]
        );

        // ImGui::SliderFloat3("car model pos", car_model_position, -5.0f, 5.0f);
        // this->game_round->get_car()->get_model()->set_translate(car_model_position[0], car_model_position[1], car_model_position[2]);
        // ImGui::SliderFloat3("car model scale", car_model_scale, 0.0f, 5.0f);
        // this->game_round->get_car()->get_model()->set_scale(car_model_scale[0], car_model_scale[1], car_model_scale[2]);
        // ImGui::SliderFloat3("car cube pos", car_colliding_cube_position, -5.0f, 5.0f);
        // this->game_round->get_car()->get_colliding_cube()->set_translate(car_colliding_cube_position[0], car_colliding_cube_position[1], car_colliding_cube_position[2]);
        // ImGui::SliderFloat3("car cube scale", car_colliding_cube_scale, 0.0f, 5.0f);
        // this->game_round->get_car()->get_colliding_cube()->set_scale(car_colliding_cube_scale[0], car_colliding_cube_scale[1], car_colliding_cube_scale[2]);
    }

    ImGui::Checkbox("Road visible", &road_visible);
    this->game_round->get_road()->set_visible(road_visible);

    if (road_visible)
    {
        ImGui::SliderFloat3("road pos", road_model_position, -20.0f, 20.0f);
        this->game_round->get_road()->set_position(
            road_model_position[0], 
            road_model_position[1], 
            road_model_position[2]
        );

        ImGui::SliderFloat3("road scale", road_model_scale, -2.0f, 2.0f);
        this->game_round->get_road()->set_scale(
            road_model_scale[0], 
            road_model_scale[1], 
            road_model_scale[2]
        );

        // ImGui::SliderFloat3("road model pos", road_model_position, -5.0f, 5.0f);
        // this->game_round->get_road()->get_model()->set_translate(road_model_position[0], road_model_position[1], road_model_position[2]);
        // ImGui::SliderFloat3("road model scale", road_model_scale, 0.0f, 5.0f);
        // this->game_round->get_road()->get_model()->set_scale(road_model_scale[0], road_model_scale[1], road_model_scale[2]);
        // ImGui::SliderFloat3("road cube pos", road_colliding_cube_position, -5.0f, 5.0f);
        // this->game_round->get_road()->get_colliding_cube()->set_translate(road_colliding_cube_position[0], road_colliding_cube_position[1], road_colliding_cube_position[2]);
        // ImGui::SliderFloat3("road cube scale", road_colliding_cube_scale, 0.0f, 5.0f);
        // this->game_round->get_road()->get_colliding_cube()->set_scale(road_colliding_cube_scale[0], road_colliding_cube_scale[1], road_colliding_cube_scale[2]);
    }

    ImGui::Checkbox("barrier visible", &barrier_visible);
    this->game_round->get_barrier()->set_visible(barrier_visible);

    if (barrier_visible)
    {
        ImGui::SliderFloat3("barrier pos", barrier_model_position, -20.0f, 20.0f);
        this->game_round->get_barrier()->set_position(
            barrier_model_position[0], 
            barrier_model_position[1], 
            barrier_model_position[2]
        );

        ImGui::SliderFloat3("barrier scale", barrier_model_scale, -20.0f, 20.0f);
        this->game_round->get_barrier()->set_scale(
            barrier_model_scale[0], 
            barrier_model_scale[1], 
            barrier_model_scale[2]
        );

        // ImGui::SliderFloat3("barrier model pos", barrier_model_position, -5.0f, 5.0f);
        // this->game_round->get_barrier()->get_model()->set_translate(barrier_model_position[0], barrier_model_position[1], barrier_model_position[2]);
        // ImGui::SliderFloat3("barrier model scale", barrier_model_scale, 0.0f, 5.0f);
        // this->game_round->get_barrier()->get_model()->set_scale(barrier_model_scale[0], barrier_model_scale[1], barrier_model_scale[2]);
        // ImGui::SliderFloat3("barrier cube pos", barrier_colliding_cube_position, -5.0f, 5.0f);
        // this->game_round->get_barrier()->get_colliding_cube()->set_translate(barrier_colliding_cube_position[0], barrier_colliding_cube_position[1], barrier_colliding_cube_position[2]);
        // ImGui::SliderFloat3("barrier cube scale", barrier_colliding_cube_scale, 0.0f, 5.0f);
        // this->game_round->get_barrier()->get_colliding_cube()->set_scale(barrier_colliding_cube_scale[0], barrier_colliding_cube_scale[1], barrier_colliding_cube_scale[2]);
    }


    ImGui::Checkbox("coin visible", &coin_visible);
    this->game_round->get_coin()->set_visible(coin_visible);

    if (coin_visible)
    {
        ImGui::SliderFloat3("coin pos", coin_model_position, -20.0f, 20.0f);
        this->game_round->get_coin()->set_position(
            coin_model_position[0], 
            coin_model_position[1], 
            coin_model_position[2]
        );

        ImGui::SliderFloat3("coin scale", coin_model_scale, -20.0f, 20.0f);
        this->game_round->get_coin()->set_scale(
            coin_model_scale[0], 
            coin_model_scale[1], 
            coin_model_scale[2]
        );

        ImGui::SliderFloat3("coin rotate", coin_model_rotate, -180.0f, 180.0f);
        this->game_round->get_coin()->set_rotate(
            coin_model_rotate[0], 
            coin_model_rotate[1], 
            coin_model_rotate[2]
        );

        // ImGui::SliderFloat3("coin model pos", coin_model_position, -5.0f, 5.0f);
        // this->game_round->get_coin()->get_model()->set_translate(coin_model_position[0], coin_model_position[1], coin_model_position[2]);
        // ImGui::SliderFloat3("coin model scale", coin_model_scale, 0.0f, 5.0f);
        // this->game_round->get_coin()->get_model()->set_scale(coin_model_scale[0], coin_model_scale[1], coin_model_scale[2]);
        // ImGui::SliderFloat3("coin cube pos", coin_colliding_cube_position, -5.0f, 5.0f);
        // this->game_round->get_coin()->get_colliding_cube()->set_translate(coin_colliding_cube_position[0], coin_colliding_cube_position[1], coin_colliding_cube_position[2]);
        // ImGui::SliderFloat3("coin cube scale", coin_colliding_cube_scale, 0.0f, 5.0f);
        // this->game_round->get_coin()->get_colliding_cube()->set_scale(coin_colliding_cube_scale[0], coin_colliding_cube_scale[1], coin_colliding_cube_scale[2]);
    }


    ImGui::Checkbox("fuel_canister visible", &fuel_canister_visible);
    this->game_round->get_fuel_canister()->set_visible(fuel_canister_visible);

    if (fuel_canister_visible)
    {
        ImGui::SliderFloat3("fuel_canister pos", fuel_canister_model_position, -20.0f, 20.0f);
        this->game_round->get_fuel_canister()->set_position(
            fuel_canister_model_position[0], 
            fuel_canister_model_position[1], 
            fuel_canister_model_position[2]
        );

        ImGui::SliderFloat3("fuel_canister scale", fuel_canister_model_scale, -20.0f, 20.0f);
        this->game_round->get_fuel_canister()->set_scale(
            fuel_canister_model_scale[0],
            fuel_canister_model_scale[1],
            fuel_canister_model_scale[2]
        );

        ImGui::SliderFloat3("fuel_canister_model_rotate rotate", fuel_canister_model_rotate, -180.0f, 180.0f);
        this->game_round->get_fuel_canister()->set_rotate(
            fuel_canister_model_rotate[0], 
            fuel_canister_model_rotate[1], 
            fuel_canister_model_rotate[2]
        );
    }
}