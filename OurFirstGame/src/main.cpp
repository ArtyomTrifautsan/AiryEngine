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

#include <AiryEngineCore/Physics/CollisionDetector.hpp>


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

    float collision_cube_1_position[3] = { 0, 0, 0 };
    float collision_cube_2_position[3] = { 0, 0, 0 };
    float collision_sphere_1_position[3] = { -3, -3, 0 };
    float collision_sphere_2_position[3] = { -3, -3, 0 };

    float ambient_factor = 0.1f;
    float diffuse_factor = 1.0f;
    float specular_factor = 0.5f;

    std::shared_ptr<AiryEngine::Renderer> renderer;

    std::shared_ptr<AiryEngine::Model3D> house_model;
    std::shared_ptr<AiryEngine::Model3D> lamp_model;
    std::shared_ptr<AiryEngine::Model3D> tree_model;

    std::shared_ptr<AiryEngine::Model3D> collision_cube_model_1;
    std::shared_ptr<AiryEngine::CubeCollidingObject> cube_1;
    std::shared_ptr<AiryEngine::Model3D> collision_cube_model_2;
    std::shared_ptr<AiryEngine::CubeCollidingObject> cube_2;
    std::shared_ptr<AiryEngine::Model3D> collision_sphere_model_1;
    std::shared_ptr<AiryEngine::SphereCollidingObject> sphere_1;
    std::shared_ptr<AiryEngine::Model3D> collision_sphere_model_2;
    std::shared_ptr<AiryEngine::SphereCollidingObject> sphere_2;

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

        // this->tree_model = _resource_manager->load_model3D("lamp_model", "ifghh.obj");
        // std::cout << "Lamp model was loaded" << std::endl;

        this->lamp_model = _resource_manager->load_model3D("Lamp", "Lampa234.obj");
        this->lamp_model->set_rotate(90, 0, 0);
        std::cout << "Lamp model was loaded" << std::endl;
        // std::cout << "Meshes: " << this->lamp_model->get_meshes().size() << std::endl;

        this->house_model = _resource_manager->load_model3D("House", "CartoonCity2.obj");
        std::cout << "House model was loaded" << std::endl;
        // std::cout << "Meshes: " << this->house_model->get_meshes().size() << std::endl;
        this->house_model->set_translate_x(-5);
        this->house_model->set_rotate(90, 0, 0);
        this->house_model->set_translate(0, 0, -10);

        this->collision_cube_model_1 = create_collision_cube_model("Cube1", "Cube.obj");
        this->cube_1 = std::make_shared<AiryEngine::CubeCollidingObject>();
        this->collision_cube_model_1->set_translate(3, -3, 0);
        this->cube_1->set_translate(3, -3, 0);
        std::cout << "Collide cube 1 model was loaded" << std::endl;
        // std::cout << "Meshes: " << this->collision_cube_model_1->get_meshes().size() << std::endl;

        this->collision_cube_model_2 = create_collision_cube_model("Cube2", "Cube.obj");
        this->cube_2 = std::make_shared<AiryEngine::CubeCollidingObject>();
        // this->collision_cube_model_2->set_scale(0.1, 0.1, 0.1);
        std::cout << "Collide cube 2 model was loaded" << std::endl;
        // std::cout << "Meshes: " << this->collision_cube_model_2->get_meshes().size() << std::endl;

        this->collision_sphere_model_1 = create_collision_cube_model("Sphere1", "Sphere.obj");
        this->sphere_1 = std::make_shared<AiryEngine::SphereCollidingObject>();
        std::cout << "Collide sphere 1 model was loaded" << std::endl;

        this->collision_sphere_model_2 = create_collision_cube_model("Sphere2", "Sphere.obj");
        this->sphere_2 = std::make_shared<AiryEngine::SphereCollidingObject>();
        // this->collision_sphere_model_2->set_scale(0.1, 0.1, 0.1);
        std::cout << "Collide sphere 2 model was loaded" << std::endl;
        // std::cout << "Meshes: " << this->collision_sphere_model_1->get_meshes().size() << std::endl;
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

        
        // ============================COLISION DETECTION=============================
        this->cube_1->set_is_collided(false);
        this->cube_2->set_is_collided(false);
        this->sphere_1->set_is_collided(false);
        this->sphere_2->set_is_collided(false);
        
        // if (AiryEngine::CollisionDetector::cube_cube_collision(*this->cube_1, *this->cube_2))
        // {
        //     this->cube_1->set_is_collided(true);
        //     this->cube_2->set_is_collided(true);
        // }

        // if (AiryEngine::CollisionDetector::sphere_sphere_collision(*this->sphere_1, *this->sphere_2))
        // {
        //     this->sphere_1->set_is_collided(true);
        //     this->sphere_2->set_is_collided(true);
        // }

        if (AiryEngine::CollisionDetector::cube_sphere_collision(*this->cube_1, *this->sphere_1))
        {
            this->cube_1->set_is_collided(true);
            this->sphere_1->set_is_collided(true);
        }

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

        if (this->cube_1->get_is_collided()) collision_cube_model_1->set_diffuse_color(1, 0, 0);
        else collision_cube_model_1->set_diffuse_color(0, 1, 0);

        if (this->cube_2->get_is_collided()) collision_cube_model_2->set_diffuse_color(1, 0, 0);
        else collision_cube_model_2->set_diffuse_color(0, 1, 0);

        if (this->sphere_1->get_is_collided()) collision_sphere_model_1->set_diffuse_color(1, 0, 0);
        else collision_sphere_model_1->set_diffuse_color(0, 1, 0);

        if (this->sphere_2->get_is_collided()) collision_sphere_model_2->set_diffuse_color(1, 0, 0);
        else collision_sphere_model_2->set_diffuse_color(0, 1, 0);
        // ===========================================================================
    }

    virtual void on_draw() override
    {
        this->renderer->render_model3D(camera, this->lamp_model);
        this->renderer->render_model3D(camera, this->house_model);
        // this->renderer->render_model3D(camera, this->tree_model);
        this->renderer->render_collision_model(camera, this->collision_cube_model_1);
        // this->renderer->render_collision_model(camera, this->collision_cube_model_2);
        this->renderer->render_collision_model(camera, this->collision_sphere_model_1);
        // this->renderer->render_collision_model(camera, this->collision_sphere_model_2);
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

        ImGui::SliderFloat3("collision cube_1 pos", collision_cube_1_position, -10.0f, 10.0f);
        this->cube_1->set_translate(glm::vec3(collision_cube_1_position[0], collision_cube_1_position[1], collision_cube_1_position[2]));
        this->collision_cube_model_1->set_translate(collision_cube_1_position[0], collision_cube_1_position[1], collision_cube_1_position[2]);

        ImGui::SliderFloat3("collision cube_2 pos", collision_cube_2_position, -10.0f, 10.0f);
        this->cube_2->set_translate(glm::vec3(collision_cube_2_position[0], collision_cube_2_position[1], collision_cube_2_position[2]));
        this->collision_cube_model_2->set_translate(collision_cube_2_position[0], collision_cube_2_position[1], collision_cube_2_position[2]);

        ImGui::SliderFloat3("collision sphere_1 pos", collision_sphere_1_position, -10.0f, 10.0f);
        this->sphere_1->set_translate(glm::vec3(collision_sphere_1_position[0], collision_sphere_1_position[1], collision_sphere_1_position[2]));
        this->collision_sphere_model_1->set_translate(collision_sphere_1_position[0], collision_sphere_1_position[1], collision_sphere_1_position[2]);

        ImGui::SliderFloat3("collision sphere_2 pos", collision_sphere_2_position, -10.0f, 10.0f);
        this->sphere_2->set_translate(glm::vec3(collision_sphere_2_position[0], collision_sphere_2_position[1], collision_sphere_2_position[2]));
        this->collision_sphere_model_2->set_translate(collision_sphere_2_position[0], collision_sphere_2_position[1], collision_sphere_2_position[2]);

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
