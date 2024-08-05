#pragma once

struct GLFWwindow;

namespace AiryEngine {

    class UIModule
    {
    public:
        static void on_window_create(GLFWwindow* window);
        static void on_window_close();
        static void on_window_draw_begin();
        static void on_window_draw_end();

    };

}