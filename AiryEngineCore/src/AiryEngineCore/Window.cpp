#include <memory>
#include <iostream>

#include <GLFW/glfw3.h>
#include <glm/mat3x3.hpp>
#include <glm/trigonometric.hpp>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>

#include "AiryEngineCore/Window.hpp"
#include "AiryEngineCore/Log.hpp"
#include "AiryEngineCore/Camera.hpp"
#include "AiryEngineCore/Modules/UIModule.hpp"
#include "AiryEngineCore/Rendering/OpenGL/Renderer_OpenGL.hpp"
#include "AiryEngineCore/Rendering/OpenGL/ShaderProgram.hpp"
#include "AiryEngineCore/Rendering/OpenGL/VertexBuffer.hpp"
#include "AiryEngineCore/Rendering/OpenGL/IndexBuffer.hpp"
#include "AiryEngineCore/Rendering/OpenGL/VertexArray.hpp"

namespace AiryEngine {

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
        R"(
            #version 460
            layout(location = 0) in vec3 vertex_position;
            layout(location = 1) in vec3 vertex_color;
            uniform mat4 model_matrix;
            uniform mat4 view_projection_matrix;
            out vec3 color;
            void main() {
                color = vertex_color;
                gl_Position = view_projection_matrix* model_matrix * vec4(vertex_position, 1.0);
            };
        )";
    
    const char* fragment_shader_src = 
        R"(
            #version 460
            in vec3 color;
            out vec4 fragment_color;
            void main() {
                fragment_color = vec4(color, 1.0);
            };
        )";

    std::unique_ptr<ShaderProgram> shaderProgram;
    std::unique_ptr<IndexBuffer> index_buffer;
    std::unique_ptr<VertexBuffer> positions_colors_vbo;
    std::unique_ptr<VertexArray> vao;
    float scale[3] = { 1.0f, 1.0f, 1.0f };
    float rotate = 0.0f;
    float translate[3] = { 0.0f, 0.0f, 0.0f };

    float camera_position[3] = { 0.0f, 0.0f, 1.0f };
    float camera_rotation[3] = { 0.0f, 0.0f, 0.0f };
    bool perspective_camera = false;
    Camera camera;

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
        Renderer_OpenGL::set_clear_color(
            this->background_color[0],
            this->background_color[1],
            this->background_color[2],
            this->background_color[3]
        );
        Renderer_OpenGL::clear();

        shaderProgram->bind();

        glm::mat4 scale_matrix(scale[0], 0,        0,        0,
                               0,        scale[1], 0,        0,
                               0,        0,        scale[2], 0,
                               0,        0,        0,        1);
        
        float rotate_in_radians = glm::radians(rotate);
        glm::mat4 rotate_matrix( cos(rotate_in_radians), sin(rotate_in_radians), 0, 0,
                                -sin(rotate_in_radians), cos(rotate_in_radians), 0, 0,
                                 0,                      0,                      1, 0,
                                 0,                      0,                      0, 1);
        
        glm::mat4 translate_matrix(1,            0,            0,            0,
                                   0,            1,            0,            0,
                                   0,            0,            1,            0, 
                                   translate[0], translate[1], translate[2], 1);

        glm::mat4 model_matrix = translate_matrix * rotate_matrix * scale_matrix; 
        shaderProgram->set_matrix4("model_matrix", model_matrix);

        camera.set_position_rotation(glm::vec3(camera_position[0], camera_position[1], camera_position[2]),
                                     glm::vec3(camera_rotation[0], camera_rotation[1], camera_rotation[2]));
        camera.set_projection_mode(perspective_camera ? Camera::ProjectionMode::Perspective : Camera::ProjectionMode::Orthographic);
        shaderProgram->set_matrix4("view_projection_matrix", camera.get_projection_matrix() * camera.get_view_matrix());

        Renderer_OpenGL::draw(*vao);

        UIModule::on_window_draw_begin();
        bool show = true;
        UIModule::ShowExampleAppDockSpace(&show);
        ImGui::ShowDemoWindow();

        ImGui::Begin("Backgroun Color Window");
        ImGui::ColorEdit4("Background Color", this->background_color);
        ImGui::SliderFloat3("scale", scale, 0.f, 2.f);
        ImGui::SliderFloat("rotate", &rotate, 0.f, 360.f);
        ImGui::SliderFloat3("translate", translate, -1.f, 1.f);

        ImGui::SliderFloat3("camera position", camera_position, -10.0f, 10.0f);
        ImGui::SliderFloat3("camera rotation", camera_rotation, 0.0f, 360.0f);
        ImGui::Checkbox("Perspective camera", &perspective_camera);
        ImGui::End();
        UIModule::on_window_draw_end();

        /* Swap front and back buffers */
        glfwSwapBuffers(this->window);  

        /* Poll for and process events */
        glfwPollEvents();
    }

}
