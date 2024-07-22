#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>

#include <AiryEngineCore/Window.hpp>
#include <AiryEngineCore/Log.hpp>
#include "AiryEngineCore/Rendering/OpenGL/ShaderProgram.hpp"
#include "AiryEngineCore/Rendering/OpenGL/VertexBuffer.hpp"
#include "AiryEngineCore/Rendering/OpenGL/VertexArray.hpp"

namespace AiryEngine {

    static bool GLFW_initializated = false;


    const int vertex_row = 20;
    const int vertex_column = 20;
    const int vertex_count = vertex_row * vertex_column * 6;
    GLfloat points[vertex_count * 3];
    GLfloat colors[vertex_count * 3];
    

    // GLfloat points[] = {
    //     0.0f, 0.5f, 0.0f,
    //     0.5f, 0.0f, 0.0f,
    //     -0.5f, 0.0f, 0.0f,
    //     -0.5f, 0.0f, 0.0f,
    //     0.5f, 0.0f, 0.0f,
    //     0.0f, -0.5f, 0.0f,
    // };

    // GLfloat colors[] = {
    //     1.0f, 0.0f, 0.0f,
    //     0.0f, 1.0f, 0.0f,
    //     0.0f, 0.0f, 1.0f,
    //     0.0f, 0.0f, 1.0f,
    //     0.0f, 1.0f, 0.0f,
    //     1.0f, 0.0f, 0.0f,
    // };

    GLfloat positions_colors[] = {
        0.0f, 0.5f, 0.0f,       1.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 1.0f,
    };

    const char* vertex_shader_src = 
        "#version 460\n"
        "layout(location = 0) in vec3 vertex_position;"
        "layout(location = 1) in vec3 vertex_color;"
        "out vec3 color;"
        "void main() {"
        "   color = vertex_color;"
        "   gl_Position = vec4(vertex_position, 1.0);"
        "};";
    
    const char* fragment_shader_src = 
        "#version 460\n"
        "in vec3 color;"
        "out vec4 fragment_color;"
        "void main() {"
        "   fragment_color = vec4(color, 1.0);"
        "};";

    std::unique_ptr<ShaderProgram> shaderProgram;
    std::unique_ptr<VertexBuffer> points_vbo;
    std::unique_ptr<VertexBuffer> colors_vbo;
    std::unique_ptr<VertexArray> vao_2buffers;

    std::unique_ptr<VertexBuffer> positions_colors_vbo;
    std::unique_ptr<VertexArray> vao_1buffer;

    Window::Window(std::string title, const unsigned int width, const unsigned int height):
        data({std::move(title), width, height})
    {
        int resultCode = init();

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui_ImplOpenGL3_Init();
        ImGui_ImplGlfw_InitForOpenGL(this->window, true);
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

        //LOG_INFO("Renderer: {}", glGetString(GL_RENDERER));
        //LOG_INFO("OpenGL version: {}", glGetString(GL_VERSION));

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

        glfwSetFramebufferSizeCallback(this->window,
            [](GLFWwindow* pWindow, int width, int height)
            {
                glViewport(0, 0, width, height);
            }
        );


        const int triangle_side_length = 15;
        bool is_up = true;
        int x_offset = 100, y_offset = 100;
        int devider = 1000; 

        int count = 0;
        for (int r = 0; r < vertex_row; r++)
        {
            for (int c = 0; c < vertex_column; c++)
            {
                if (is_up)
                {
                    points[count] = (float)x_offset / (float)devider;
                    points[count + 1] = (float)y_offset / (float)devider;
                    points[count + 2] = 0.0f;
                    colors[count] = 1.0f;
                    colors[count + 1] = 0.0f;
                    colors[count + 2] = 0.0f;
                    
                    points[count] = (float)(x_offset + c * triangle_side_length) / (float)devider;
                    points[count + 1] = (float)y_offset / (float)devider;
                    points[count + 2] = 0.0f;
                    colors[count] = 0.0f;
                    colors[count + 1] = 0.0f;
                    colors[count + 2] = 1.0f;

                    points[count] = (float)x_offset / (float)devider;
                    points[count + 1] = (float)(y_offset + r * triangle_side_length) / (float)devider;
                    points[count + 2] = 0.0f;
                    colors[count] = 0.0f;
                    colors[count + 1] = 0.0f;
                    colors[count + 2] = 1.0f;
                }
                else
                {
                    points[count] = (float)(x_offset + c * triangle_side_length) / (float)devider;
                    points[count + 1] = (float)(y_offset + r * triangle_side_length) / (float)devider;
                    points[count + 2] = 0.0f;
                    colors[count] = 1.0f;
                    colors[count + 1] = 0.0f;
                    colors[count + 2] = 0.0f;
                    
                    points[count] = (float)(x_offset + c * triangle_side_length) / (float)devider;
                    points[count + 1] = (float)y_offset / (float)devider;
                    points[count + 2] = 0.0f;
                    colors[count] = 0.0f;
                    colors[count + 1] = 0.0f;
                    colors[count + 2] = 1.0f;

                    points[count] = (float)x_offset / (float)devider;
                    points[count + 1] = (float)(y_offset + r * triangle_side_length) / (float)devider;
                    points[count + 2] = 0.0f;
                    colors[count] = 0.0f;
                    colors[count + 1] = 0.0f;
                    colors[count + 2] = 1.0f;
                }

                count += 3;
            }
        }


        shaderProgram = std::make_unique<ShaderProgram>(vertex_shader_src, fragment_shader_src);
        if (!shaderProgram->is_compiled()) 
            return false;

        BufferLayout bufferLayout_1vec3
        {
            ShaderDataType::Float3
        };

        vao_2buffers = std::make_unique<VertexArray>();
        points_vbo = std::make_unique<VertexBuffer>(points, sizeof(points), bufferLayout_1vec3);
        colors_vbo = std::make_unique<VertexBuffer>(colors, sizeof(colors), bufferLayout_1vec3);

        vao_2buffers->add_buffer(*points_vbo);
        vao_2buffers->add_buffer(*colors_vbo);


        BufferLayout bufferLayout_2vec3
        {
            ShaderDataType::Float3,
            ShaderDataType::Float3,
        };

        vao_1buffer = std::make_unique<VertexArray>();
        positions_colors_vbo = std::make_unique<VertexBuffer>(positions_colors, sizeof(positions_colors), bufferLayout_2vec3);

        vao_1buffer->add_buffer(*positions_colors_vbo);

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
        glClearColor(
            this->background_color[0],
            this->background_color[1],
            this->background_color[2],
            this->background_color[3]
        );

         /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // shaderProgram->bind();
        // vao_1buffer->bind();
        // glDrawArrays(GL_TRIANGLES, 0, 3);


        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize.x = static_cast<float>(get_width());
        io.DisplaySize.y = static_cast<float>(get_height());

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //ImGui::ShowDemoWindow();

        ImGui::Begin("Backgroun Color Window");

        ImGui::ColorEdit4("Background Color", this->background_color);

        static bool use_2_buffers = true;
        ImGui::Checkbox("2 Buffers", &use_2_buffers);
        if (use_2_buffers)
        {
            shaderProgram->bind();
            vao_2buffers->bind();
            glDrawArrays(GL_TRIANGLES, 0, vertex_count * 3);
        }
        else
        {
            shaderProgram->bind();
            vao_1buffer->bind();
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }

        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


        /* Swap front and back buffers */
        glfwSwapBuffers(this->window);  

        /* Poll for and process events */
        glfwPollEvents();
    }

}
