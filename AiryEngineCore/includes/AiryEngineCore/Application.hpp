#pragma once

#include <memory>

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

        float camera_position[3] = { 0.0f, 0.0f, 1.0f };
        float camera_rotation[3] = { 0.0f, 0.0f, 0.0f };
        bool perspective_camera = false;
        Camera camera;
    
    private:
        std::unique_ptr<class Window> window;

        EventDispatcher eventDispatcher;
        bool closeWindow = false;
        float background_color[4] = {0.33f, 0.33f, 0.33f, 0.f};
    };

}