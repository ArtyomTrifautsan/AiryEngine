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

    extern float scale[];
    extern float rotate;
    extern float translate[];

    Application::Application(const std::string& executable_path) 
    {
        LOG_INFO("Starting Application");
        
        set_executable_path(executable_path);

        this->resource_manager = std::make_shared<ResourceManager>(this->path_to_executable);
    }

    Application::~Application() 
    {
        LOG_INFO("Closing Application");
    }

    int Application::start(unsigned int window_width, unsigned int window_height, const char* title)
    {
        this->window = std::make_unique<Window>(title, window_width, window_height);
        this->camera.set_viewport_size(static_cast<float>(window_width), static_cast<float>(window_height));

        this->renderer = std::make_unique<Renderer_OpenGL>(this->resource_manager);

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

        Renderer_OpenGL::enable_depth_testing();
        while (!this->closeWindow)
        {
            this->renderer->rendering(this->camera, true);

            UIModule::on_window_draw_begin();
            on_ui_draw();
            UIModule::on_window_draw_end();


            this->window->on_update();
            on_update();
        }

        return 0;
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
        this->renderer->set_light_source_position(position);
    }
    
    void Application::set_light_source_color(float color[3])
    {
        this->renderer->set_light_source_color(color);
    }

    void Application::set_ambiant_factor(float factor)
    {
        this->renderer->set_ambiant_factor(factor);
    }

    void Application::set_diffuse_factor(float factor)
    {
        this->renderer->set_diffuse_factor(factor);
    }

    void Application::set_specular_factor(float factor)
    {
        this->renderer->set_specular_factor(factor);
    }

    void Application::set_shininess(float shininess)
    {
        this->renderer->set_shininess(shininess);
    }

}