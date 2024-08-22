#include "AiryEngineCore/Window.hpp"

#include <memory>
#include <iostream>

#include <GLFW/glfw3.h>

#include "AiryEngineCore/Log.hpp"
#include "AiryEngineCore/Modules/UIModule.hpp"
#include "AiryEngineCore/Rendering/OpenGL/Renderer_OpenGL.hpp"

namespace AiryEngine {

    Window::Window(std::string title, const unsigned int width, const unsigned int height):
        data({std::move(title), width, height})
    {
        int resultCode = init();
    }

    Window::~Window()
    {
        shutdown();
    }

    int Window::init()
    {
        LOG_INFO("Creating widnow \"{0}\" size {1}x{2}", this->data.title, this->data.width, this->data.height);

        glfwSetErrorCallback([](int error_code, const char* description)
            {
                LOG_CRITICAL("GLFW error: {}", description);
            }
        );

        /* Initialize the library */
        if (!glfwInit())
        {
            LOG_CRITICAL("Can't initialize GLFW!");
            return -1;
        }

        /* Create a windowed mode window and its OpenGL context */
        this->window = glfwCreateWindow(this->data.width, this->data.height, this->data.title.c_str(), NULL, NULL);
        if (!this->window)
        {
            LOG_CRITICAL("Can't create widnow \"{0}\" size {1}x{2}!", this->data.title, this->data.width, this->data.height);
            return -2;
        }

        if (!Renderer_OpenGL::init(window))
        {
            LOG_CRITICAL("Failed to initialize OpenGL renderer");
            return -3;
        }

        glfwSetWindowUserPointer(this->window, &this->data);

        glfwSetKeyCallback(this->window, [](GLFWwindow* pWindow, int key, int scancode, int action, int mods)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));
                switch (action)
                {
                    case GLFW_PRESS:
                    {
                        EventKeyPressed event(static_cast<KeyCode>(key), false);
                        data.eventCallbackFn(event);
                        break;
                    }
                    
                    case GLFW_RELEASE:
                    {
                        EventKeyReleased event(static_cast<KeyCode>(key));
                        data.eventCallbackFn(event);
                        break;
                    }
                    
                    case GLFW_REPEAT:
                    {
                        EventKeyPressed event(static_cast<KeyCode>(key), true);
                        data.eventCallbackFn(event);
                        break;
                    }
                }
            }
        );

        glfwSetMouseButtonCallback(this->window, [](GLFWwindow* pWindow, 
            int button, int action, int mods)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));
                double x_pos;
                double y_pos;
                glfwGetCursorPos(pWindow, &x_pos, &y_pos);
                switch (action)
                {
                    case GLFW_PRESS:
                    {
                        EventMouseButtonPressed event(static_cast<MouseButtonCode>(button), x_pos, y_pos);
                        data.eventCallbackFn(event);
                        break;
                    }
                    
                    case GLFW_RELEASE:
                    {
                        EventMouseButtonReleased event(static_cast<MouseButtonCode>(button), x_pos, y_pos);
                        data.eventCallbackFn(event);
                        break;
                    }
                }
            }
        );

        glfwSetWindowSizeCallback(this->window, 
            [](GLFWwindow* pWindow, int width, int height)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));
                data.width = width;
                data.height = height;

                EventWindowResize event(width, height);
                data.eventCallbackFn(event);
            }
        );

        glfwSetCursorPosCallback(this->window,
            [](GLFWwindow* pWindow, double x, double y)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));

                EventMouseMoved event(x, y);
                data.eventCallbackFn(event);
            }
        );

        glfwSetWindowCloseCallback(this->window,
            [](GLFWwindow* pWindow)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));

                EventWindowClose event;
                data.eventCallbackFn(event);
            }
        );

        glfwSetFramebufferSizeCallback(this->window,
            [](GLFWwindow* pWindow, int width, int height)
            {
                Renderer_OpenGL::set_viewport(width, height);
            }
        );

        UIModule::on_window_create(window);

        return 0;
    }

    void Window::shutdown()
    {
        UIModule::on_window_close();

        glfwDestroyWindow(this->window);
        glfwTerminate();
    }
    
    void Window::on_update()
    {
        /* Swap front and back buffers */
        glfwSwapBuffers(this->window);  

        /* Poll for and process events */
        glfwPollEvents();
    }

    glm::vec2 Window::get_current_cursor_position() const
    {
        double x_pos;
        double y_pos;
        glfwGetCursorPos(this->window, &x_pos, &y_pos);
        return {x_pos, y_pos};
    }

}
