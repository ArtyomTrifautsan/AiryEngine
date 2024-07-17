#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include <AiryEngineCore/Window.hpp>
#include <AiryEngineCore/Log.hpp>

namespace AiryEngine {

    static bool GLFW_initializated = false;

    Window::Window(std::string title, const unsigned int width, const unsigned int height):
        data({std::move(title), width, height})
    {
        int resultCode = init();

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui_ImplOpenGL3_Init();
    }

    Window::~Window()
    {
        shutdown();
    }

    int Window::init()
    {
        LOG_INFO("Creating widnow \"{0}\" size {1}x{2}", this->data.title, this->data.width, this->data.height);

        /* Initialize the library */
        if (!GLFW_initializated)
        {
            if (!glfwInit())
            {
                LOG_CRITICAL("Can't initialize GLFW!");
                return -1;
            }
            
            GLFW_initializated = true;
        }

        /* Create a windowed mode window and its OpenGL context */
        this->window = glfwCreateWindow(this->data.width, this->data.height, this->data.title.c_str(), NULL, NULL);
        if (!this->window)
        {
            LOG_CRITICAL("Can't create widnow \"{0}\" size {1}x{2}!", this->data.title, this->data.width, this->data.height);
            glfwTerminate();
            return -2;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(this->window);

        // initialize GLAD
        // This function gives access to all opengl functions
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            LOG_CRITICAL("Failed to initialize GLAD");
            return -1;
        }

        glfwSetWindowUserPointer(this->window, &this->data);

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

        return 0;
    }

    void Window::shutdown()
    {
        glfwDestroyWindow(this->window);
        glfwTerminate();
    }
    
    void Window::on_update()
    {
        // Set buffer fill color 
        glClearColor(1, 0, 0, 0);

         /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);


        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize.x = static_cast<float>(get_width());
        io.DisplaySize.y = static_cast<float>(get_height());

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


        /* Swap front and back buffers */
        glfwSwapBuffers(this->window);  

        /* Poll for and process events */
        glfwPollEvents();
    }

}
