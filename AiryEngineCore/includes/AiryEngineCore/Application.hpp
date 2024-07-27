#pragma once

#include <memory>
#include <string>

#include "AiryEngineCore/Camera.hpp"
#include "AiryEngineCore/Event.hpp"

namespace AiryEngine {

    class Application
    {
    public:
        Application();  
        virtual ~Application();

        Application(const Application&) = delete;
        Application(Application&&) = delete;
        Application& operator=(const Application&) = delete;
        Application& operator=(Application&&) = delete;

        virtual int start(unsigned int window_width, unsigned int window_height, const char* title);
        virtual void on_update() {}
        virtual void on_ui_draw() {}
        virtual void on_mouse_button_pressed(const MouseButtonCode mouse_button_code, 
                                            const double x_pos, 
                                            const double y_pos, 
                                            const bool pressed) {}

        glm::vec2 get_current_cursor_position() const;

        void set_executable_path(const std::string& executable_path);

        float camera_position[3] = { 0.0f, 0.0f, 1.0f };
        float camera_rotation[3] = { 0.0f, 0.0f, 0.0f };
        bool perspective_camera = true;
        Camera camera{glm::vec3(-5, 0, 0)};
    
    private:

        std::unique_ptr<class Window> window;
        std::unique_ptr<class ResourceManager> resource_manager;
        std::shared_ptr<class ShaderProgram> shader_program;

        EventDispatcher eventDispatcher;
        bool closeWindow = false;
        float background_color[4] = {0.33f, 0.33f, 0.33f, 0.f};

        std::string path_to_executable;
    };

}