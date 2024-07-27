#pragma once

#include <string>
#include <functional>
#include <glm/ext/vector_float2.hpp>

#include "AiryEngineCore/Event.hpp"

struct GLFWwindow;

namespace AiryEngine {

    class Window
    {
    public:
        using EventCallbackFn = std::function<void(BaseEvent&)>;

        Window(std::string title, const unsigned int width, const unsigned int height);
        ~Window();

        Window(const Window&) = delete;
        Window(Window&&) = delete;
        Window& operator=(const Window&) = delete;
        Window& operator=(Window&&) = delete;

        void on_update();
        unsigned int get_width() const { return this->data.width; }
        unsigned int get_height() const { return this->data.height; }
        glm::vec2 get_current_cursor_position() const;
        GLFWwindow* get_GLFWwindow() { return this->window; }

        void set_enevt_callback(const EventCallbackFn& callback) { this->data.eventCallbackFn = callback; }
    
    private:
        struct WindowData
        {
            std::string title;
            unsigned int width;
            unsigned int height;
            EventCallbackFn eventCallbackFn;
        };

        int init();
        void shutdown();

        GLFWwindow* window = nullptr;
        WindowData data;
    };

}