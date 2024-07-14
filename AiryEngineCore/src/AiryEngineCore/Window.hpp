#pragma once

#include <string>

struct GLFWwindow;

namespace AiryEngine {

    class Window
    {
    public:
        Window(std::string title, const unsigned int width, const unsigned int height);
        ~Window();

        Window(const Window&) = delete;
        Window(Window&&) = delete;
        Window& operator=(const Window&) = delete;
        Window& operator=(Window&&) = delete;

        void on_update();
        unsigned int get_width() const { return this->width; }
        unsigned int get_height() const { return this->height; }
    
    private:
        int init();
        void shutdown();

        GLFWwindow* window;
        std::string title;
        unsigned int width;
        unsigned int height;
    };

}