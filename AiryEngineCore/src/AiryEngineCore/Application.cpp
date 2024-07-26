#include "AiryEngineCore/Application.hpp"

#include <iostream>
using std::cout;
using std::endl;

#include <GLFW/glfw3.h>
#include <glm/trigonometric.hpp>
#include <imgui/imgui.h>

#include "AiryEngineCore/Camera.hpp"
#include "AiryEngineCore/Window.hpp"
#include "AiryEngineCore/Log.hpp"
#include "AiryEngineCore/Input.hpp"

#include "AiryEngineCore/Rendering/OpenGL/Renderer_OpenGL.hpp"
#include "AiryEngineCore/Rendering/OpenGL/ShaderProgram.hpp"
#include "AiryEngineCore/Rendering/OpenGL/VertexBuffer.hpp"
#include "AiryEngineCore/Rendering/OpenGL/IndexBuffer.hpp"
#include "AiryEngineCore/Rendering/OpenGL/VertexArray.hpp"
#include "AiryEngineCore/Modules/UIModule.hpp"

namespace AiryEngine {

    GLfloat positions_colors2[] = {
        0.0f, -0.5f, -0.5f,     1.0f, 1.0f, 0.0f,
        0.0f,  0.5f, -0.5f,     0.0f, 1.0f, 1.0f,
        0.0f, -0.5f,  0.5f,     1.0f, 0.0f, 1.0f,
        0.0f,  0.5f,  0.5f,     1.0f, 0.0f, 0.0f,
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

    Application::Application() 
    {
        LOG_INFO("Starting Application");
    }

    Application::~Application() 
    {
        LOG_INFO("Closing Application");
    }

    int Application::start(unsigned int window_width, unsigned int window_height, const char* title)
    {
        this->window = std::make_unique<Window>(title, window_width, window_height);

        this->eventDispatcher.add_event_listener<EventMouseMoved>(
            [](EventMouseMoved& event)
            {
                //LOG_INFO("[MouseMoved] Mouse moved to {0}x{1}", event.x, event.y);
            }
        );

        this->eventDispatcher.add_event_listener<EventWindowResize>(
            [](EventWindowResize& event)
            {
                //LOG_INFO("[WindowResize] Changed window size to {0}x{1}", event.width, event.height);
            }
        );

        this->eventDispatcher.add_event_listener<EventWindowClose>(
            [&](EventWindowClose& event)
            {
                LOG_INFO("[WindowClose]");
                this->closeWindow = true;
            }
        );

        this->eventDispatcher.add_event_listener<EventMouseButtonPressed>(
            [&](EventMouseButtonPressed& event)
            {
                LOG_INFO("[Mouse button pressed] {0}, at ({1}, {2})", static_cast<char>(event.mouse_button_code), event.x_pos, event.y_pos); 
                Input::PressMouseButton(event.mouse_button_code); 
                on_mouse_button_pressed(event.mouse_button_code, event.x_pos, event.y_pos, true);
            }
        );

        this->eventDispatcher.add_event_listener<EventMouseButtonReleased>(
            [&](EventMouseButtonReleased& event)
            {
                LOG_INFO("[Mouse button released] {0}, at ({1}, {2})", static_cast<char>(event.mouse_button_code), event.x_pos, event.y_pos); 
                Input::ReleaseMouseButton(event.mouse_button_code);
                on_mouse_button_pressed(event.mouse_button_code, event.x_pos, event.y_pos, false);
            }
        );

        this->eventDispatcher.add_event_listener<EventKeyPressed>(
            [&](EventKeyPressed& event)
            {
                if (event.key_code <= KeyCode::KEY_Z)
                {
                    if (event.repeated)
                        LOG_INFO("[Key pressed] {} repeated", static_cast<char>(event.key_code));
                    else
                        LOG_INFO("[Key pressed] {}", static_cast<char>(event.key_code));
                }
                
                Input::PressKey(event.key_code);
            }
        );

        this->eventDispatcher.add_event_listener<EventKeyReleased>(
            [&](EventKeyReleased& event)
            {
                if (event.key_code <= KeyCode::KEY_Z)
                    LOG_INFO("[Key released] {}", static_cast<char>(event.key_code));
                Input::ReleaseKey(event.key_code);
            }
        );

        this->window->set_enevt_callback(
            [&](BaseEvent& event)
            {
                this->eventDispatcher.dispatch(event);
            }
        );


        //------------------------------------------------------------//
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
        //------------------------------------------------------------//

        while (!this->closeWindow)
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

            
            camera.set_projection_mode(perspective_camera ? Camera::ProjectionMode::Perspective : Camera::ProjectionMode::Orthographic);
            shaderProgram->set_matrix4("view_projection_matrix", camera.get_projection_matrix() * camera.get_view_matrix());

            Renderer_OpenGL::draw(*vao);


            //------------------------------------------------------------//
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
            //------------------------------------------------------------//
            on_ui_draw();

            UIModule::on_window_draw_end();


            this->window->on_update();
            on_update();
        }

        return 0;
    }

    glm::vec2 Application::get_current_cursor_position() const
    {
        return this->window->get_current_cursor_position();
    }

}