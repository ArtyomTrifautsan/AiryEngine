#pragma once

#include <memory>
#include <string>

#include "AiryEngineCore/Camera.hpp"
#include "AiryEngineCore/Event.hpp"

namespace AiryEngine {

    class Application
    {
    public:
        //Application();
        Application(const std::string& executable_path);  
        virtual ~Application();
        // void init(const std::string& executable_path);
        void set_executable_path(const std::string& executable_path);

        Application(const Application&) = delete;
        Application(Application&&) = delete;
        Application& operator=(const Application&) = delete;
        Application& operator=(Application&&) = delete;

        virtual int start(unsigned int window_width, unsigned int window_height, const char* title);
        void close();
        virtual void on_update() {}
        virtual void on_ui_draw() {}
        virtual void on_mouse_button_pressed(const MouseButtonCode mouse_button_code, 
                                            const double x_pos, 
                                            const double y_pos, 
                                            const bool pressed) {}
        
        void set_light_source_position(float light_source_position[3]);     // Temporary solution
        void set_light_source_color(float light_source_color[3]);       // Temporary solution
        void set_ambiant_factor(float factor);       // Temporary solution
        void set_diffuse_factor(float factor);       // Temporary solution
        void set_specular_factor(float factor);       // Temporary solution
        void set_shininess(float shininess);       // Temporary solution

        glm::vec2 get_current_cursor_position() const;

        Camera camera{glm::vec3(-5.f, 0.f, 0.f)};

        float light_source_position[3] = { 0.f, 3.f, 0.f };     // Temporary solution
        float light_source_color[3] = { 1.f, 1.f, 1.f };        // Temporary solution
        float ambiant_factor = 0.1f;        // Temporary solution
        float diffuse_factor = 1.0f;        // Temporary solution
        float specular_factor = 0.5f;        // Temporary solution
        float shininess = 32.0f;        // Temporary solution

    private:
        std::unique_ptr<class Window> window;
        std::unique_ptr<class Renderer_OpenGL> renderer;
        std::shared_ptr<class ResourceManager> resource_manager;

        EventDispatcher eventDispatcher;
        bool closeWindow = false;
        float background_color[4] = {0.33f, 0.33f, 0.33f, 0.f};

        std::string path_to_executable;
    };

}