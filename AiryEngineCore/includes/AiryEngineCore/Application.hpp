#pragma once

#include <memory>
#include <string>

#include "AiryEngineCore/Camera.hpp"
#include "AiryEngineCore/Event.hpp"

namespace AiryEngine {

    class Model3D;
    class Texture2D;
    class ResourceManager;

    class Application
    {
    public:
        //Application(const std::string& executable_path);
        Application(std::shared_ptr<ResourceManager> _resource_manager);  
        virtual ~Application();
        void set_executable_path(const std::string& executable_path);

        Application(const Application&) = delete;
        Application(Application&&) = delete;
        Application& operator=(const Application&) = delete;
        Application& operator=(Application&&) = delete;

        virtual int start(unsigned int window_width, unsigned int window_height, const char* title);
        void close();

        virtual void on_start(std::shared_ptr<ResourceManager> _resource_manager) {}
        virtual void on_draw() {}
        virtual void on_update() {}
        virtual void on_ui_draw() {}
        virtual void on_mouse_button_pressed(const MouseButtonCode mouse_button_code, 
                                            const double x_pos, 
                                            const double y_pos, 
                                            const bool pressed) {}
        
        // void set_light_source_position(float light_source_position[3]);     // Temporary solution
        // void set_light_source_color(float light_source_color[3]);       // Temporary solution
        // void set_ambiant_factor(float factor);       // Temporary solution
        // void set_diffuse_factor(float factor);       // Temporary solution
        // void set_specular_factor(float factor);       // Temporary solution
        // void set_shininess(float shininess);       // Temporary solution

        std::shared_ptr<Model3D> create_collision_cube_model(const std::string& model_name, const std::string& model_path, const std::string& model_dir_path);

        glm::vec2 get_current_cursor_position() const;

        Camera camera{glm::vec3(0.f, 0.f, -5.f)};

        // float light_source_position[3] = { 0.f, 3.f, 0.f };     // Temporary solution
        // float light_source_color[3] = { 1.f, 1.f, 1.f };        // Temporary solution
        // float ambiant_factor = 0.1f;        // Temporary solution
        // float diffuse_factor = 1.0f;        // Temporary solution
        // float specular_factor = 0.5f;        // Temporary solution
        // float shininess = 32.0f;        // Temporary solution

    private:
        std::unique_ptr<class Window> window;
        std::shared_ptr<class ResourceManager> resource_manager;

        EventDispatcher eventDispatcher;
        bool closeWindow = false;
        float background_color[4] = {0.33f, 0.33f, 0.33f, 0.f};

        std::vector<std::shared_ptr<Model3D>> models;

        std::string path_to_executable;
    };

}