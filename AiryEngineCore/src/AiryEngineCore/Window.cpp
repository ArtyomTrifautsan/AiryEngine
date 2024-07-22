#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/mat3x3.hpp>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>

#include <AiryEngineCore/Window.hpp>
#include <AiryEngineCore/Log.hpp>
#include "AiryEngineCore/Rendering/OpenGL/ShaderProgram.hpp"
#include "AiryEngineCore/Rendering/OpenGL/VertexBuffer.hpp"
#include "AiryEngineCore/Rendering/OpenGL/IndexBuffer.hpp"
#include "AiryEngineCore/Rendering/OpenGL/VertexArray.hpp"

namespace AiryEngine {

    static bool GLFW_initializated = false;

    GLfloat positions_colors[] = {
        -0.5f, -0.5f,  0.0f,    1.0f, 1.0f, 0.0f,
         0.5f, -0.5f,  0.0f,    0.0f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.0f,    1.0f, 0.0f, 1.0f,

         0.5f,  0.5f,  0.0f,    1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.0f,    1.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.0f,    0.0f, 1.0f, 1.0f,
    };

    GLfloat positions_colors2[] = {
        -0.5f, -0.5f,  0.0f,    1.0f, 1.0f, 0.0f,
         0.5f, -0.5f,  0.0f,    0.0f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.0f,    1.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.0f,    1.0f, 0.0f, 0.0f,
    };

    GLint indices[] = {
        0, 1, 2, 3, 2, 1
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
    std::unique_ptr<IndexBuffer> index_buffer;
    std::unique_ptr<VertexBuffer> positions_colors_vbo;
    std::unique_ptr<VertexArray> vao;

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


        shaderProgram = std::make_unique<ShaderProgram>(vertex_shader_src, fragment_shader_src);
        if (!shaderProgram->is_compiled()) 
            return false;
        

        BufferLayout bufferLayout_2vec3
        {
            ShaderDataType::Float3,
            ShaderDataType::Float3,
        };

        vao = std::make_unique<VertexArray>();
        positions_colors_vbo = std::make_unique<VertexBuffer>(positions_colors2, sizeof(positions_colors2), bufferLayout_2vec3);
        index_buffer = std::make_unique<IndexBuffer>(indices, sizeof(indices) / sizeof(GLuint));

        vao->add_vertex_buffer(*positions_colors_vbo);
        vao->set_index_buffer(*index_buffer);


        glm::mat3 matrix1(4, 0, 0, 2, 8, 1, 0, 1, 0);
        glm::mat3 matrix2(4, 2, 9, 2, 0, 4, 1, 4, 2);
        glm::mat3 result_matrix = matrix1 * matrix2;

        LOG_INFO("");
        LOG_INFO("|{0:3} {1:3} {2:3}|", result_matrix[0][0], result_matrix[1][0], result_matrix[2][0]);
        LOG_INFO("|{0:3} {1:3} {2:3}|", result_matrix[0][1], result_matrix[1][1], result_matrix[2][1]);
        LOG_INFO("|{0:3} {1:3} {2:3}|", result_matrix[0][2], result_matrix[1][2], result_matrix[2][2]);
        LOG_INFO("");


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

        shaderProgram->bind();
        vao->bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(vao->get_indices_count()), GL_UNSIGNED_INT, nullptr);


        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize.x = static_cast<float>(get_width());
        io.DisplaySize.y = static_cast<float>(get_height());

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //ImGui::ShowDemoWindow();

        ImGui::Begin("Backgroun Color Window");

        ImGui::ColorEdit4("Background Color", this->background_color);

        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


        /* Swap front and back buffers */
        glfwSwapBuffers(this->window);  

        /* Poll for and process events */
        glfwPollEvents();
    }

}
