#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/trigonometric.hpp>

#include "Renderer_OpenGL.hpp"

#include "AiryEngineCore/Camera.hpp"
#include "AiryEngineCore/Log.hpp"

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

    float scale[3] = { 1.0f, 1.0f, 1.0f };
    float rotate = 0.0f;
    float translate[3] = { 0.0f, 0.0f, 0.0f };

    float background_color[4] = {0.33f, 0.33f, 0.33f, 0.f};

    Renderer_OpenGL::Renderer_OpenGL(GLFWwindow* window, std::shared_ptr<ResourceManager> resource_manager)
    {
        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        {
            LOG_CRITICAL("Failed to initialize GLAD");
            return;
        }

        // LOG_INFO("OpenGL context initializited:");
        // LOG_INFO("  Vendor: {}", get_vendor_str());
        // LOG_INFO("  Renderer: {}", get_renderer_str());
        // LOG_INFO("  Version: {}", get_version_str());

        this->resource_manager = resource_manager;

        this->shader_program = this->resource_manager->load_shaders("DefaultShaders", "Resources/Shaders/vertex_shader.txt", "Resources/Shaders/fragment_shader.txt");
        if (!shader_program->is_compiled()) 
        {
            LOG_CRITICAL("Failed to compile Shader Program");
        }

        BufferLayout bufferLayout_2vec3
        {
            ShaderDataType::Float3,
            ShaderDataType::Float3,
        };
        this->positions_colors_vbo = std::make_unique<VertexBuffer>(positions_colors2, sizeof(positions_colors2), bufferLayout_2vec3);
        this->vao = std::make_unique<VertexArray>();
        this->index_buffer = std::make_unique<IndexBuffer>(indices, sizeof(indices) / sizeof(GLuint));

        vao->add_vertex_buffer(*positions_colors_vbo);
        vao->set_index_buffer(*index_buffer);
    }

    void Renderer_OpenGL::rendering(Camera& camera, bool perspective_camera)
    {
        set_clear_color(
            background_color[0],
            background_color[1],
            background_color[2],
            background_color[3]
        );
        clear();

        this->shader_program->bind();

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
        this->shader_program->set_matrix4("model_matrix", model_matrix);

        camera.set_projection_mode(perspective_camera ? Camera::ProjectionMode::Perspective : Camera::ProjectionMode::Orthographic);
        this->shader_program->set_matrix4("view_projection_matrix", camera.get_projection_matrix() * camera.get_view_matrix());

        draw_vertex_elements(*vao);
    }

    bool Renderer_OpenGL::init(GLFWwindow* window)
    {
        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        {
            LOG_CRITICAL("Failed to initialize GLAD");
            return false;
        }

        LOG_INFO("OpenGL context initializited:");
        LOG_INFO("  Vendor: {}", get_vendor_str());
        LOG_INFO("  Renderer: {}", get_renderer_str());
        LOG_INFO("  Version: {}", get_version_str());

        return true;
    }

    void Renderer_OpenGL::draw_vertex_elements(const VertexArray& vertex_array)
    {
        vertex_array.bind();
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(vertex_array.get_indices_count()), GL_UNSIGNED_INT, nullptr);
    }

    void Renderer_OpenGL::set_clear_color(const float r, const float g, const float b, const float a) { glClearColor(r, g, b, a); }

    void Renderer_OpenGL::clear() { glClear(GL_COLOR_BUFFER_BIT); }

    void Renderer_OpenGL::set_viewport(
        const unsigned int width, 
        const unsigned int height, 
        const unsigned int left_offset, 
        const unsigned bottom_offset
    ) { glViewport(left_offset, bottom_offset, width, height); }

    const char* Renderer_OpenGL::get_vendor_str() { return reinterpret_cast<const char*>(glGetString(GL_VENDOR)); }

    const char* Renderer_OpenGL::get_renderer_str() { return reinterpret_cast<const char*>(glGetString(GL_RENDERER)); }
    
    const char* Renderer_OpenGL::get_version_str() { return reinterpret_cast<const char*>(glGetString(GL_VERSION)); }

}