#include <iostream>
using std::cout;
using std::endl;

#include <GLFW/glfw3.h>
#include <glm/trigonometric.hpp>
#include <imgui/imgui.h>

#include "AiryEngineCore/Application.hpp"

#include "AiryEngineCore/Camera.hpp"
#include "AiryEngineCore/Window.hpp"
#include "AiryEngineCore/Log.hpp"
#include "AiryEngineCore/Input.hpp"

#include "AiryEngineCore/ResourceManaging/ResourceManager.hpp"
#include "AiryEngineCore/Rendering/OpenGL/Renderer_OpenGL.hpp"
#include "AiryEngineCore/Modules/UIModule.hpp"

namespace AiryEngine {

    float scale[3] = { 1.0f, 1.0f, 1.0f };
    float rotate = 0.0f;
    float translate[3] = { 0.0f, 0.0f, 0.0f };

    std::vector<float> pos_norm_uv = {
        //    position             normal              UV                  index

        // FRONT
        -1.0f, -1.f, -1.f,    -1.f,  0.f,  0.f,     0.f, 0.f,              // 0
        -1.0f,  1.f, -1.f,    -1.f,  0.f,  0.f,     1.f, 0.f,              // 1
        -1.0f,  1.f,  1.f,    -1.f,  0.f,  0.f,     1.f, 1.f,              // 2
        -1.0f, -1.f,  1.f,    -1.f,  0.f,  0.f,     0.f, 1.f,              // 3

        // BACK                                  
         1.0f, -1.f, -1.f,     1.f,  0.f,  0.f,     1.f, 0.f,              // 4
         1.0f,  1.f, -1.f,     1.f,  0.f,  0.f,     0.f, 0.f,              // 5
         1.0f,  1.f,  1.f,     1.f,  0.f,  0.f,     0.f, 1.f,              // 6
         1.0f, -1.f,  1.f,     1.f,  0.f,  0.f,     1.f, 1.f,              // 7

        // RIGHT
        -1.0f,  1.f, -1.f,     0.f,  1.f,  0.f,     0.f, 0.f,              // 8
         1.0f,  1.f, -1.f,     0.f,  1.f,  0.f,     1.f, 0.f,              // 9
         1.0f,  1.f,  1.f,     0.f,  1.f,  0.f,     1.f, 1.f,              // 10
        -1.0f,  1.f,  1.f,     0.f,  1.f,  0.f,     0.f, 1.f,              // 11

        // LEFT
        -1.0f, -1.f, -1.f,     0.f, -1.f,  0.f,     1.f, 0.f,              // 12
         1.0f, -1.f, -1.f,     0.f, -1.f,  0.f,     0.f, 0.f,              // 13
         1.0f, -1.f,  1.f,     0.f, -1.f,  0.f,     0.f, 1.f,              // 14
        -1.0f, -1.f,  1.f,     0.f, -1.f,  0.f,     1.f, 1.f,              // 15

        // TOP
        -1.0f, -1.f,  1.f,     0.f,  0.f,  1.f,     0.f, 0.f,              // 16
        -1.0f,  1.f,  1.f,     0.f,  0.f,  1.f,     1.f, 0.f,              // 17
         1.0f,  1.f,  1.f,     0.f,  0.f,  1.f,     1.f, 1.f,              // 18
         1.0f, -1.f,  1.f,     0.f,  0.f,  1.f,     0.f, 1.f,              // 19

         // BOTTOM
         -1.0f, -1.f, -1.f,    0.f,  0.f, -1.f,     0.f, 1.f,              // 20
         -1.0f,  1.f, -1.f,    0.f,  0.f, -1.f,     1.f, 1.f,              // 21
          1.0f,  1.f, -1.f,    0.f,  0.f, -1.f,     1.f, 0.f,              // 22
          1.0f, -1.f, -1.f,    0.f,  0.f, -1.f,     0.f, 0.f,              // 23
    };

    std::vector<unsigned int> indices {
         0,  1,  2,  2,  3,  0, // front
         4,  5,  6,  6,  7,  4, // back
         8,  9, 10, 10, 11,  8, // right
        12, 13, 14, 14, 15, 12, // left
        16, 17, 18, 18, 19, 16, // top
        20, 21, 22, 22, 23, 20  // bottom
    };

    std::array<glm::vec3, 6> cubes_positions = {
        glm::vec3(-2.f, -2.f, -4.f),
        glm::vec3(-5.f,  0.f,  3.f),
        glm::vec3(-8.f,  0.f,  3.f),
        glm::vec3( 2.f,  1.f, -2.f),
        glm::vec3( 4.f, -3.f,  3.f),
        glm::vec3( 1.f, -7.f, -1.f),
    };

    Application::Application(const std::string& executable_path) 
    {
        LOG_INFO("Starting Application");
        
        set_executable_path(executable_path);

        this->resource_manager = std::make_shared<ResourceManager>(this->path_to_executable);
        this->resource_manager->set_shaders_directory("Resources/Shaders");
        this->resource_manager->set_textures_directory("Resources/Textures");
        this->resource_manager->set_models_directory("Resources/Models");
    }

    Application::~Application() 
    {
        LOG_INFO("Closing Application");
    }

    int Application::start(unsigned int window_width, unsigned int window_height, const char* title)
    {
        this->window = std::make_unique<Window>(title, window_width, window_height);
        this->camera.set_viewport_size(static_cast<float>(window_width), static_cast<float>(window_height));

        // this->renderer = std::make_unique<Renderer_OpenGL>(this->resource_manager);

        this->eventDispatcher.add_event_listener<EventMouseMoved>(
            [](EventMouseMoved& event)
            {
                //LOG_INFO("[MouseMoved] Mouse moved to {0}x{1}", event.x, event.y);
            }
        );

        this->eventDispatcher.add_event_listener<EventWindowResize>(
            [&](EventWindowResize& event)
            {
                //LOG_INFO("[WindowResize] Changed window size to {0}x{1}", event.width, event.height);
                this->camera.set_viewport_size(event.width, event.height);
            }
        );

        this->eventDispatcher.add_event_listener<EventWindowClose>(
            [&](EventWindowClose& event)
            {
                LOG_INFO("[WindowClose]");
                close();
            }
        );

        this->eventDispatcher.add_event_listener<EventMouseButtonPressed>(
            [&](EventMouseButtonPressed& event)
            {
                //LOG_INFO("[Mouse button pressed] {0}, at ({1}, {2})", static_cast<char>(event.mouse_button_code), event.x_pos, event.y_pos); 
                Input::PressMouseButton(event.mouse_button_code); 
                on_mouse_button_pressed(event.mouse_button_code, event.x_pos, event.y_pos, true);
            }
        );

        this->eventDispatcher.add_event_listener<EventMouseButtonReleased>(
            [&](EventMouseButtonReleased& event)
            {
                //LOG_INFO("[Mouse button released] {0}, at ({1}, {2})", static_cast<char>(event.mouse_button_code), event.x_pos, event.y_pos); 
                Input::ReleaseMouseButton(event.mouse_button_code);
                on_mouse_button_pressed(event.mouse_button_code, event.x_pos, event.y_pos, false);
            }
        );

        this->eventDispatcher.add_event_listener<EventKeyPressed>(
            [&](EventKeyPressed& event)
            {
                if (event.key_code <= KeyCode::KEY_Z)
                {
                    if (event.repeated) {}
                        //LOG_INFO("[Key pressed] {} repeated", static_cast<char>(event.key_code));
                    else {}
                        //LOG_INFO("[Key pressed] {}", static_cast<char>(event.key_code));
                }   
                
                Input::PressKey(event.key_code);
            }
        );

        this->eventDispatcher.add_event_listener<EventKeyReleased>(
            [&](EventKeyReleased& event)
            {
                if (event.key_code <= KeyCode::KEY_Z) {}
                    //LOG_INFO("[Key released] {}", static_cast<char>(event.key_code));
                Input::ReleaseKey(event.key_code);
            }
        );

        this->window->set_enevt_callback(
            [&](BaseEvent& event)
            {
                this->eventDispatcher.dispatch(event);
            }
        );

        std::shared_ptr<ShaderProgram> default_shader_program = this->resource_manager->load_shaders("default_shaders", "default_vertex_shader.txt", "default_fragment_shader.txt");
        if (!default_shader_program->is_compiled()) 
        {
            LOG_CRITICAL("Failed to compile Default Shader Program");
        }

        std::shared_ptr<ShaderProgram> light_source_shader_program = this->resource_manager->load_shaders("light_source_shaders", "light_source_vertex_shader.txt", "light_source_fragment_shader.txt");
        if (!light_source_shader_program->is_compiled()) 
        {
            LOG_CRITICAL("Failed to compile Light Shader Program");
        }

        std::shared_ptr<Texture2D> model_texture = this->resource_manager->load_texture2D("model_texture", "dog.png");

        // Модель Егорки
        std::shared_ptr<Model3D> Egor_model = this->resource_manager->load_model3D("first_model", "1.obj", model_texture);
        Egor_model->set_translate_x(-5);
        Egor_model->set_rotate(90, 0, 0);
        Egor_model->set_translate(0, 0, -10);

        // Модель фонарика
        std::shared_ptr<std::vector<float>> pnu_ptr = std::make_shared<std::vector<float>>();
        for (int i = 0; i < pos_norm_uv.size(); i++) pnu_ptr->push_back(pos_norm_uv[i]);
        std::shared_ptr<std::vector<unsigned int>> indices_ptr = std::make_shared<std::vector<unsigned int>>();
        for (int i = 0; i < indices.size(); i++) indices_ptr->push_back(indices[i]);

        std::shared_ptr<Model3D> cube_model = create_model(pnu_ptr, indices_ptr, model_texture);
        // cube_model->set_scale(0.1, 0.1, 0.1);
        
        // std::shared_ptr<Material> light_material = std::make_shared<Material>();
        // light_material->ambient_color = glm::vec3(0, 0, 0);
        // light_material->diffuse_color = glm::vec3(this->light_source_color[0], this->light_source_color[1], this->light_source_color[2]);
        // light_material->specular_color = glm::vec3(0, 0, 0);
        // light_material->shininess = 1;

        float frame = 0.0;
        Renderer_OpenGL::enable_depth_testing();
        while (!this->closeWindow)
        {
            Renderer_OpenGL::before_render();

            glm::vec3 lsp_vec3 = glm::vec3(this->light_source_position[0], this->light_source_position[1], this->light_source_position[2]);
            glm::vec3 lsc_vec3 = glm::vec3(this->light_source_color[0], this->light_source_color[1], this->light_source_color[2]);
            Renderer_OpenGL::render_model3D(this->camera, Egor_model, default_shader_program, lsp_vec3, lsc_vec3);
            // Renderer_OpenGL::render_model3D(this->camera, cube_model, default_shader_program, lsp_vec3, lsc_vec3);
            Renderer_OpenGL::render_light_model3D(this->camera, cube_model, light_source_shader_program, lsp_vec3, lsc_vec3);

            cube_model->set_translate(this->light_source_position[0], this->light_source_position[1], this->light_source_position[2]);

            frame += 0.01;

            UIModule::on_window_draw_begin();
            on_ui_draw();
            UIModule::on_window_draw_end();

            this->window->on_update();
            on_update();
        }

        return 0;
    }

    std::shared_ptr<Model3D> Application::create_model(std::shared_ptr<std::vector<float>> vertices, 
                                    std::shared_ptr<std::vector<unsigned int>> indices, 
                                    std::shared_ptr<Texture2D> texture)
    {
        std::shared_ptr<Material> temp_material = std::make_shared<Material>();
        
        std::shared_ptr<Model3D> model = std::make_shared<Model3D>();

        std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(vertices, indices, temp_material);
        model->add_mesh(mesh);

        return model;
    }

    glm::vec2 Application::get_current_cursor_position() const
    {
        return this->window->get_current_cursor_position();
    }

    void Application::set_executable_path(const std::string& executable_path)
    {
        size_t found = executable_path.find_last_of("/\\");
        this->path_to_executable = executable_path.substr(0, found);
    }

    void Application::close()
    {
        this->closeWindow = true;
    }

    void Application::set_light_source_position(float position[3])
    {
        this->light_source_position[0] = position[0];
        this->light_source_position[1] = position[1];
        this->light_source_position[2] = position[2];
    }
    
    void Application::set_light_source_color(float color[3])
    {
        this->light_source_color[0] = color[0];
        this->light_source_color[1] = color[1];
        this->light_source_color[2] = color[2];
    }

    void Application::set_ambiant_factor(float factor)
    {
        this->ambiant_factor = factor;
    }

    void Application::set_diffuse_factor(float factor)
    {
        this->diffuse_factor = factor;
    }

    void Application::set_specular_factor(float factor)
    {
        this->specular_factor = factor;
    }

    void Application::set_shininess(float shininess)
    {
        this->shininess = shininess;
    }

}