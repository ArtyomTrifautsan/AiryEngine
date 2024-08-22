#include <iostream>
#include <memory>
#include <imgui/imgui.h>
// using std::cout;
// using std::endl;

#include <AiryEngineCore/Application.hpp>
#include <AiryEngineCore/Renderer.hpp>
#include <AiryEngineCore/Input.hpp>
#include <AiryEngineCore/ResourceManager.hpp>

#include <AiryEngineCore/Scene/Model3D.hpp>




class GameApplication : public AiryEngine::Application
{
    double m_initial_mouse_pos_x = 0.0;
    double m_initial_mouse_pos_y = 0.0;

    float camera_position[3] = { 0.0f, 0.0f, 1.0f };
    float camera_rotation[3] = { 0.0f, 0.0f, 0.0f };
    bool perspective_camera = true;
    float camera_fov = 60.f;
    float camera_near_plane = 0.1f;
    float camera_far_plane = 100.f;

    float light_source_position[3] = { 0, 0, 0 };
    float light_source_color[3] = { 1, 1, 1 };

    std::shared_ptr<AiryEngine::Renderer> renderer;
    std::shared_ptr<AiryEngine::Model3D> Egorka_model;
    std::shared_ptr<AiryEngine::Model3D> lamp_model;

public:
    GameApplication(std::shared_ptr<AiryEngine::ResourceManager> _resource_manager) : AiryEngine::Application(_resource_manager)
    {
        // set_executable_path(executable_path);
    }

    virtual void on_start(std::shared_ptr<AiryEngine::ResourceManager> _resource_manager) override
    {
        std::cout << "On_start start" << std::endl;
        this->renderer = std::make_shared<AiryEngine::Renderer>(_resource_manager);
        std::cout << "Renderer was crerated" << std::endl;

        // this->lamp_model = _resource_manager->load_model3D("lamp_model", "Lampa234.obj");
        this->lamp_model = _resource_manager->load_model3D("1", "1.obj");

        this->Egorka_model = _resource_manager->load_model3D("Egorka_model", "CartoonCity2.obj");
        std::cout << "Model 1 was crerated" << std::endl;
        Egorka_model->set_translate_x(-5);
        this->Egorka_model->set_rotate(90, 0, 0);
        Egorka_model->set_translate(0, 0, -10);

        // this->lamp_model = _resource_manager->load_model3D("lamp_model", "Lamp.obj");
        std::cout << "Model 2 was crerated" << std::endl;
    }

    virtual void on_update() override
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
                camera.move_right(static_cast<float>(current_cursor_position.x - m_initial_mouse_pos_x) / 100.f );
                camera.move_up(static_cast<float>(m_initial_mouse_pos_y - current_cursor_position.y) / 100.f );
            }
            else
            {
                rotation_delta.z += static_cast<float>(m_initial_mouse_pos_x - current_cursor_position.x) / 5.f;
                rotation_delta.y -= static_cast<float>(m_initial_mouse_pos_y - current_cursor_position.y) / 5.f;
            }

            m_initial_mouse_pos_x = current_cursor_position.x;
            m_initial_mouse_pos_y = current_cursor_position.y;
        }

        camera.add_movement_and_rotation(movement_delta, rotation_delta);   


        this->lamp_model->set_scale(0.1, 0.1, 0.1);
        this->lamp_model->set_translate(light_source_position[0], light_source_position[1], light_source_position[2]);
    }

    virtual void on_draw() override
    {
        // AiryEngine::Renderer::render_model3D(camera, this->Egorka_model);
        this->renderer->render_model3D(camera, this->Egorka_model);
        // AiryEngine::Renderer::render_model3D(camera, this->lamp_model);
        this->renderer->render_model3D(camera, this->lamp_model);
    }

    void setup_dockspace_menu()
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

    virtual void on_mouse_button_pressed(const AiryEngine::MouseButtonCode mouse_button_code, 
                                        const double x_pos, 
                                        const double y_pos, 
                                        const bool pressed) override 
    {
        m_initial_mouse_pos_x = x_pos;
        m_initial_mouse_pos_y = y_pos;


    }

    virtual void on_ui_draw() override
    {
        setup_dockspace_menu();

        camera_position[0] = camera.get_camera_position().x;
        camera_position[1] = camera.get_camera_position().y;
        camera_position[2] = camera.get_camera_position().z;

        camera_rotation[0] = camera.get_camera_rotation().x;
        camera_rotation[1] = camera.get_camera_rotation().y;
        camera_rotation[2] = camera.get_camera_rotation().z;

        camera_fov = camera.get_field_of_view();
        camera_near_plane = camera.get_near_clip_plane();
        camera_far_plane = camera.get_far_clip_plane();

        // Editor GUI
        ImGui::Begin("Editor");

        ImGui::SliderFloat3("light source position", light_source_position, -50.0f, 50.0f);
        // set_light_source_position(light_source_position);
        this->renderer->set_light_source_position(glm::vec3(light_source_position[0], light_source_position[1], light_source_position[2]));

        ImGui::ColorEdit3("light source color", light_source_color);
        // set_light_source_color(light_source_color);
        this->renderer->set_light_source_color(glm::vec3(light_source_color[0], light_source_color[1], light_source_color[2]));

        // ImGui::SliderFloat("ambiant factor", &ambiant_factor, 0.0f, 1.0f);
        // set_ambiant_factor(ambiant_factor);

        // ImGui::SliderFloat("diffuse factor", &diffuse_factor, 0.0f, 1.0f);
        // set_diffuse_factor(diffuse_factor);

        // ImGui::SliderFloat("specular factor", &specular_factor, 0.0f, 1.0f);
        // set_specular_factor(specular_factor);

        // ImGui::SliderFloat("shininess", &shininess, 1.0f, 128.0f);
        // set_shininess(shininess);

        if (ImGui::SliderFloat3("camera position", camera_position, -10.0f, 10.0f))
        {
            camera.set_position(glm::vec3(camera_position[0], camera_position[1], camera_position[2]));
        }
        if (ImGui::SliderFloat3("camera rotation", camera_rotation, 0.0f, 360.0f))
        {
            camera.set_rotation(glm::vec3(camera_rotation[0], camera_rotation[1], camera_rotation[2]));
        }
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
        if (ImGui::Checkbox("Perspective camera", &perspective_camera))
        {
            camera.set_projection_mode(perspective_camera ? AiryEngine::Camera::ProjectionMode::Perspective : AiryEngine::Camera::ProjectionMode::Orthographic);
        }

        ImGui::End();
    }   
};

int main(int argc, char const *argv[])
{
    std::cout << "main start" << std::endl;

    auto resource_manager = std::make_shared<AiryEngine::ResourceManager>(argv[0]);
    resource_manager->set_shaders_directory("Resources/Shaders");
    resource_manager->set_textures_directory("Resources/Textures");
    resource_manager->set_models_directory("Resources/Models");

    // AiryEngine::Renderer::init(resource_manager);
    
    auto game_application = std::make_unique<GameApplication>(resource_manager);
    
    int returnCode = game_application->start(1024, 768, "OurFirstGame");

    return returnCode;
}
