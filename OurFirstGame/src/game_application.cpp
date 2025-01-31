#include "game_application.hpp"

#include <memory>
#include <imgui/imgui.h>
// using std::cout;
// using std::endl;

// #include <AiryEngineCore/Application.hpp>
// #include <AiryEngineCore/Renderer.hpp>
#include <AiryEngineCore/Input.hpp>
#include <AiryEngineCore/ResourceManager.hpp>

#include <AiryEngineCore/Scene/Model3D.hpp>

// #include <AiryEngineCore/Physics/CollisionDetector.hpp>


GameApplication::GameApplication(std::shared_ptr<AiryEngine::ResourceManager> _resource_manager) : AiryEngine::Application(_resource_manager)
{
    // set_executable_path(executable_path);
    // std::cout << "GameApplication constructor started" << std::endl;
}


void GameApplication::on_start(std::shared_ptr<AiryEngine::ResourceManager> _resource_manager)
{
    // std::cout << "on_start started" << std::endl;
    this->renderer = std::make_shared<AiryEngine::Renderer>(_resource_manager);

    this->lamp_model = _resource_manager->load_model3D("Lamp", "Lampa234.obj");
    this->lamp_model->set_rotate(90, 0, 0);
    this->lamp_model->set_translate_y(-1);

    this->cube_model3D = create_collision_cube_model("Cube1", "Cube.obj");
    this->sphere_model3D = create_collision_cube_model("sphere", "sphere.obj");
    // this->cube_model3D->set_translate(3, -3, 0);

    this->cube_1_colliding_object = std::make_shared<AiryEngine::CubeCollidingObject>();
    this->collision_cube_1_position[0] = -3;

    this->cube_2_colliding_object = std::make_shared<AiryEngine::CubeCollidingObject>();

    this->sphere_1_colliding_object = std::make_shared<AiryEngine::SphereCollidingObject>();
    this->collision_sphere_1_position[0] = 3;

    this->sphere_2_colliding_object = std::make_shared<AiryEngine::SphereCollidingObject>();
    this->collision_sphere_2_position[0] = 6;
    // std::cout << "on_start finished" << std::endl;
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
        movement_delta.y -= 0.05f;
    }

    // Go Right
    if (AiryEngine::Input::IsKeyPressed(AiryEngine::KeyCode::KEY_D))
    {
        movement_delta.y += 0.05f;
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
            camera.move_right(static_cast<float>(current_cursor_position.x - this->initial_mouse_pos_x) / 100.f );
            camera.move_up(static_cast<float>(this->initial_mouse_pos_y - current_cursor_position.y) / 100.f );
        }
        else
        {
            rotation_delta.z += static_cast<float>(this->initial_mouse_pos_x - current_cursor_position.x) / 5.f;
            rotation_delta.y -= static_cast<float>(this->initial_mouse_pos_y - current_cursor_position.y) / 5.f;
        }

        this->initial_mouse_pos_x = current_cursor_position.x;
        this->initial_mouse_pos_y = current_cursor_position.y;
    }

    camera.add_movement_and_rotation(movement_delta, rotation_delta);  
}


void GameApplication::_update_light_source_state()
{
    this->lamp_model->set_scale(0.1, 0.1, 0.1);
    this->lamp_model->set_translate(light_source_position[0], light_source_position[1], light_source_position[2]);
}


void GameApplication::_detect_collisions()
{
    this->cube_1_colliding_object->set_is_collided(false);
    this->cube_2_colliding_object->set_is_collided(false);
    this->sphere_1_colliding_object->set_is_collided(false);
    this->sphere_2_colliding_object->set_is_collided(false);

    if (AiryEngine::CollisionDetector::cube_cube_collision(*this->cube_1_colliding_object, *this->cube_2_colliding_object))
    {
        this->cube_1_colliding_object->set_is_collided(true);
        this->cube_2_colliding_object->set_is_collided(true);
    }

    if (AiryEngine::CollisionDetector::sphere_sphere_collision(*this->sphere_1_colliding_object, *this->sphere_2_colliding_object))
    {
        this->sphere_1_colliding_object->set_is_collided(true);
        this->sphere_2_colliding_object->set_is_collided(true);
    }

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
    this->renderer->render_model3D(camera, this->lamp_model);

    // Рендерим куб нужного цвета и в нужном месте
    // Я использую одну модель для отрисовки двух кубов. Просто перед каждым рендерингом 
    // я перекрашиваю ее в красный или зеленый цвет и перемещаю в место физической модели
    //куба
    if (this->cube_1_colliding_object->get_is_collided()) this->cube_model3D->set_diffuse_color(1.0f, 0.0f, 0.0f);
    else this->cube_model3D->set_diffuse_color(0.0f, 1.0f, 0.0f);
    glm::vec3 cube_1_pos = this->cube_1_colliding_object->get_translate();
    this->cube_model3D->set_translate(cube_1_pos.x, cube_1_pos.y, cube_1_pos.z);
    this->renderer->render_collision_model(camera, this->cube_model3D);

    if (this->cube_2_colliding_object->get_is_collided()) this->cube_model3D->set_diffuse_color(1.0f, 0.0f, 0.0f);
    else this->cube_model3D->set_diffuse_color(0.0f, 1.0f, 0.0f);
    glm::vec3 cube_2_pos = this->cube_2_colliding_object->get_translate();
    this->cube_model3D->set_translate(cube_2_pos.x, cube_2_pos.y, cube_2_pos.z);
    this->renderer->render_collision_model(camera, this->cube_model3D);

    if (this->sphere_1_colliding_object->get_is_collided()) this->sphere_model3D->set_diffuse_color(1.0f, 0.0f, 0.0f);
    else this->sphere_model3D->set_diffuse_color(0.0f, 1.0f, 0.0f);
    glm::vec3 sphere_1_pos = this->sphere_1_colliding_object->get_translate();
    this->sphere_model3D->set_translate(sphere_1_pos.x, sphere_1_pos.y + 3, sphere_1_pos.z);
    this->renderer->render_collision_model(camera, this->sphere_model3D);

    if (this->sphere_2_colliding_object->get_is_collided()) this->sphere_model3D->set_diffuse_color(1.0f, 0.0f, 0.0f);
    else this->sphere_model3D->set_diffuse_color(0.0f, 1.0f, 0.0f);
    glm::vec3 sphere_2_pos = this->sphere_2_colliding_object->get_translate();
    this->sphere_model3D->set_translate(sphere_2_pos.x, sphere_2_pos.y + 3, sphere_2_pos.z);
    this->renderer->render_collision_model(camera, this->sphere_model3D);

    // this->renderer->render_collision_model(camera, this->collision_cube_model_2);
    // this->renderer->render_collision_model(camera, this->collision_sphere_model_1);
    // this->renderer->render_collision_model(camera, this->collision_sphere_model_2);
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

    camera_fov = camera.get_field_of_view();
    camera_near_plane = camera.get_near_clip_plane();
    camera_far_plane = camera.get_far_clip_plane();

    // Editor GUI
    ImGui::Begin("Editor");

    ImGui::SliderFloat3("cube_1 pos", collision_cube_1_position, -10.0f, 10.0f);
    this->cube_1_colliding_object->set_translate(glm::vec3(collision_cube_1_position[0], collision_cube_1_position[1], collision_cube_1_position[2]));
    // this->collision_cube_model_1->set_translate(collision_cube_1_position[0], collision_cube_1_position[1], collision_cube_1_position[2]);

    ImGui::SliderFloat3("cube_2 pos", collision_cube_2_position, -10.0f, 10.0f);
    this->cube_2_colliding_object->set_translate(glm::vec3(collision_cube_2_position[0], collision_cube_2_position[1], collision_cube_2_position[2]));
    // this->collision_cube_model_2->set_translate(collision_cube_2_position[0], collision_cube_2_position[1], collision_cube_2_position[2]);

    ImGui::SliderFloat3("collision sphere_1 pos", collision_sphere_1_position, -10.0f, 10.0f);
    this->sphere_1_colliding_object->set_translate(glm::vec3(collision_sphere_1_position[0], collision_sphere_1_position[1], collision_sphere_1_position[2]));
    // this->collision_sphere_model_1->set_translate(collision_sphere_1_position[0], collision_sphere_1_position[1], collision_sphere_1_position[2]);

    ImGui::SliderFloat3("collision sphere_2 pos", collision_sphere_2_position, -10.0f, 10.0f);
    this->sphere_2_colliding_object->set_translate(glm::vec3(collision_sphere_2_position[0], collision_sphere_2_position[1], collision_sphere_2_position[2]));
    // this->collision_sphere_model_2->set_translate(collision_sphere_2_position[0], collision_sphere_2_position[1], collision_sphere_2_position[2]);

    ImGui::SliderFloat3("light source position", light_source_position, -50.0f, 50.0f);
    // set_light_source_position(light_source_position);
    this->renderer->set_light_source_position(glm::vec3(light_source_position[0], light_source_position[1], light_source_position[2]));

    ImGui::ColorEdit3("light source color", light_source_color);
    // set_light_source_color(light_source_color);
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
        camera.set_field_of_view(camera_fov);
    }  
    if (ImGui::SliderFloat("camera near clip plane", &camera_near_plane, 0.1f, 10.0f))
    {
        camera.set_near_clip_plane(camera_near_plane);
    }  
    if (ImGui::SliderFloat("camera far clip plane", &camera_far_plane, 1.0f, 100.0f))
    {
        camera.set_far_clip_plane(camera_far_plane);
    }

    ImGui::End();
}