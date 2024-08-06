#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/trigonometric.hpp>

#include <memory>

#include "Renderer_OpenGL.hpp"

#include "AiryEngineCore/Camera.hpp"
#include "AiryEngineCore/Log.hpp"


namespace AiryEngine {

    GLfloat pos_norm_uv[] = {
        //    position             normal              UV                  index

        // FRONT
        -1.0f, -1.f, -1.f,    -1.f,  0.f,  0.f,     0.f, 0.f,              // 0
        -1.0f,  1.f, -1.f,    -1.f,  0.f,  0.f,     1.f, 0.f,              // 1
        -1.0f,  1.f,  1.f,    -1.f,  0.f,  0.f,     1.f, 1.f,              // 2
        -1.0f, -1.f,  1.f,    -1.f,  0.f,  0.f,     0.f, 1.f,              // 3

        // BACK                                  
         1.0f, -1.f, -1.f,     1.f,  0.f,  0.f,     1.f, 0.f,              // 4
         1.0f,  1.f, -1.f,     1.f,  0.f,  0.f,     0.f, 0.f,              // 5
         1.0f,  1.f,  1.f,     1.f,  0.f,  0.f,     0.f, 1.f,              // 6
         1.0f, -1.f,  1.f,     1.f,  0.f,  0.f,     1.f, 1.f,              // 7

        // RIGHT
        -1.0f,  1.f, -1.f,     0.f,  1.f,  0.f,     0.f, 0.f,              // 8
         1.0f,  1.f, -1.f,     0.f,  1.f,  0.f,     1.f, 0.f,              // 9
         1.0f,  1.f,  1.f,     0.f,  1.f,  0.f,     1.f, 1.f,              // 10
        -1.0f,  1.f,  1.f,     0.f,  1.f,  0.f,     0.f, 1.f,              // 11

        // LEFT
        -1.0f, -1.f, -1.f,     0.f, -1.f,  0.f,     1.f, 0.f,              // 12
         1.0f, -1.f, -1.f,     0.f, -1.f,  0.f,     0.f, 0.f,              // 13
         1.0f, -1.f,  1.f,     0.f, -1.f,  0.f,     0.f, 1.f,              // 14
        -1.0f, -1.f,  1.f,     0.f, -1.f,  0.f,     1.f, 1.f,              // 15

        // TOP
        -1.0f, -1.f,  1.f,     0.f,  0.f,  1.f,     0.f, 0.f,              // 16
        -1.0f,  1.f,  1.f,     0.f,  0.f,  1.f,     1.f, 0.f,              // 17
         1.0f,  1.f,  1.f,     0.f,  0.f,  1.f,     1.f, 1.f,              // 18
         1.0f, -1.f,  1.f,     0.f,  0.f,  1.f,     0.f, 1.f,              // 19

         // BOTTOM
         -1.0f, -1.f, -1.f,    0.f,  0.f, -1.f,     0.f, 1.f,              // 20
         -1.0f,  1.f, -1.f,    0.f,  0.f, -1.f,     1.f, 1.f,              // 21
          1.0f,  1.f, -1.f,    0.f,  0.f, -1.f,     1.f, 0.f,              // 22
          1.0f, -1.f, -1.f,    0.f,  0.f, -1.f,     0.f, 0.f,              // 23
    };

    GLint indices[] = {
         0,  1,  2,  2,  3,  0, // front
         4,  5,  6,  6,  7,  4, // back
         8,  9, 10, 10, 11,  8, // right
        12, 13, 14, 14, 15, 12, // left
        16, 17, 18, 18, 19, 16, // top
        20, 21, 22, 22, 23, 20  // bottom
    };

    float scale[3] = { 1.0f, 1.0f, 1.0f };
    float rotate = 0.0f;
    float translate[3] = { 0.0f, 0.0f, 0.0f };

    float background_color[4] = {0.33f, 0.33f, 0.33f, 0.f};

    std::array<glm::vec3, 6> cubes_positions = {
        glm::vec3(-2.f, -2.f, -4.f),
        glm::vec3(-5.f,  0.f,  3.f),
        glm::vec3(-8.f,  0.f,  3.f),
        glm::vec3( 2.f,  1.f, -2.f),
        glm::vec3( 4.f, -3.f,  3.f),
        glm::vec3( 1.f, -7.f, -1.f),
    };

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

    Renderer_OpenGL::Renderer_OpenGL(std::shared_ptr<ResourceManager> resource_manager)
    {
        // glfwMakeContextCurrent(window);

        // if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        // {
        //     LOG_CRITICAL("Failed to initialize GLAD");
        //     return;
        // }

        // LOG_INFO("OpenGL context initializited:");
        // LOG_INFO("  Vendor: {}", get_vendor_str());
        // LOG_INFO("  Renderer: {}", get_renderer_str());
        // LOG_INFO("  Version: {}", get_version_str());

        this->resource_manager = resource_manager;

        this->default_shader_program = this->resource_manager->load_shaders("default_shaders", "Resources/Shaders/default_vertex_shader.txt", "Resources/Shaders/default_fragment_shader.txt");
        if (!this->default_shader_program->is_compiled()) 
        {
            LOG_CRITICAL("Failed to compile Shader Program");
        }

        this->light_source_shader_program = this->resource_manager->load_shaders("light_source_shaders", "Resources/Shaders/light_source_vertex_shader.txt", "Resources/Shaders/light_source_fragment_shader.txt");
        if (!this->light_source_shader_program->is_compiled()) 
        {
            LOG_CRITICAL("Failed to compile Shader Program");
        }

        BufferLayout bufferLayout_vec3_vec3_vec2
        {
            ShaderDataType::Float3,
            ShaderDataType::Float3,
            ShaderDataType::Float2
        };
        this->cube_positions_vbo = std::make_unique<VertexBuffer>(pos_norm_uv, sizeof(pos_norm_uv), bufferLayout_vec3_vec3_vec2);
        this->cube_vao = std::make_unique<VertexArray>();
        this->cube_index_buffer = std::make_unique<IndexBuffer>(indices, sizeof(indices) / sizeof(GLuint));

        cube_vao->add_vertex_buffer(*this->cube_positions_vbo);
        cube_vao->set_index_buffer(*this->cube_index_buffer);

        this->dog_texture = this->resource_manager->load_texture("Resources/Textures/dog.png");
        this->dog_texture->bind(0);
    }

    Renderer_OpenGL::~Renderer_OpenGL()
    {
        
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

        this->default_shader_program->bind();

        // glm::mat4 scale_matrix(scale[0], 0,        0,        0,
        //                        0,        scale[1], 0,        0,
        //                        0,        0,        scale[2], 0,
        //                        0,        0,        0,        1);
            
        // float rotate_in_radians = glm::radians(rotate);
        // glm::mat4 rotate_matrix( cos(rotate_in_radians), sin(rotate_in_radians), 0, 0,
        //                         -sin(rotate_in_radians), cos(rotate_in_radians), 0, 0,
        //                          0,                      0,                      1, 0,
        //                          0,                      0,                      0, 1);
        
        // glm::mat4 translate_matrix(1,            0,            0,            0,
        //                            0,            1,            0,            0,
        //                            0,            0,            1,            0,  
        //                            translate[0], translate[1], translate[2], 1);

        // glm::mat4 model_matrix = translate_matrix * rotate_matrix * scale_matrix; 
        // this->default_shader_program->set_matrix4("model_matrix", model_matrix);
        this->default_shader_program->set_matrix4("view_projection_matrix", camera.get_projection_matrix() * camera.get_view_matrix());
        this->default_shader_program->set_vec3("camera_position", camera.get_camera_position());
        this->default_shader_program->set_vec3("light_position", glm::vec3(this->light_source_position[0], this->light_source_position[1], this->light_source_position[2]));
        this->default_shader_program->set_vec3("light_color", glm::vec3(this->light_source_color[0], this->light_source_color[1], this->light_source_color[2]));
        this->default_shader_program->set_float("ambient_factor", this->ambiant_factor);
        this->default_shader_program->set_float("diffuse_factor", this->diffuse_factor);
        this->default_shader_program->set_float("specular_factor", this->specular_factor);
        this->default_shader_program->set_float("shininess", this->shininess);
        // draw_vertex_elements(*cube_vao);

        // Вообще для каждого объекта нужно делать свою матрицу поворота и матрицу скалирования,
        // но это временное решение
        glm::mat4 scale_matrix(scale[0], 0,        0,        0,
                               0,        scale[1], 0,        0,
                               0,        0,        scale[2], 0,
                               0,        0,        0,        1);
            
        float rotate_in_radians = glm::radians(rotate);
        glm::mat4 rotate_matrix( cos(rotate_in_radians), sin(rotate_in_radians), 0, 0,
                                -sin(rotate_in_radians), cos(rotate_in_radians), 0, 0,
                                 0,                      0,                      1, 0,
                                 0,                      0,                      0, 1);
        for (const glm::vec3& current_position : cubes_positions)
        {
            glm::mat4 translate_matrix(1,            0,            0,            0,
                                   0,            1,            0,            0,
                                   0,            0,            1,            0,  
                                   current_position[0], current_position[1], current_position[2], 1);
            glm::mat4 model_matrix = translate_matrix * rotate_matrix * scale_matrix;
            this->default_shader_program->set_matrix4("model_matrix", model_matrix);

            draw_vertex_elements(*cube_vao);
        }

        this->light_source_shader_program->bind();
        glm::mat4 light_source_model_matrix(1,            0,            0,            0,
                                   0,            1,            0,            0, 
                                   0,            0,            1,            0, 
                                   light_source_position[0], light_source_position[1], light_source_position[2], 1);
        this->light_source_shader_program->set_matrix4("model_matrix", light_source_model_matrix);
        this->light_source_shader_program->set_matrix4("view_projection_matrix", camera.get_projection_matrix() * camera.get_view_matrix());
        this->light_source_shader_program->set_vec3("light_color", glm::vec3(this->light_source_color[0], this->light_source_color[1], this->light_source_color[2]));
        draw_vertex_elements(*cube_vao);
    }

    void Renderer_OpenGL::draw_vertex_elements(const VertexArray& vertex_array)
    {
        vertex_array.bind();
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(vertex_array.get_indices_count()), GL_UNSIGNED_INT, nullptr);
    }

    void Renderer_OpenGL::set_clear_color(const float r, const float g, const float b, const float a) { glClearColor(r, g, b, a); }

    void Renderer_OpenGL::clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

    void Renderer_OpenGL::set_viewport(
        const unsigned int width, 
        const unsigned int height, 
        const unsigned int left_offset, 
        const unsigned bottom_offset
    ) { glViewport(left_offset, bottom_offset, width, height); }

    void Renderer_OpenGL::enable_depth_testing() { glEnable(GL_DEPTH_TEST); }

    void Renderer_OpenGL::disable_depth_testing() { glDisable(GL_DEPTH_TEST); }

    const char* Renderer_OpenGL::get_vendor_str() { return reinterpret_cast<const char*>(glGetString(GL_VENDOR)); }

    const char* Renderer_OpenGL::get_renderer_str() { return reinterpret_cast<const char*>(glGetString(GL_RENDERER)); }
    
    const char* Renderer_OpenGL::get_version_str() { return reinterpret_cast<const char*>(glGetString(GL_VERSION)); }

    void Renderer_OpenGL::set_light_source_position(float position[3])
    {
        this->light_source_position[0] = position[0];
        this->light_source_position[1] = position[1];
        this->light_source_position[2] = position[2];
    }
    
    void Renderer_OpenGL::set_light_source_color(float color[3])
    {
        this->light_source_color[0] = color[0];
        this->light_source_color[1] = color[1];
        this->light_source_color[2] = color[2];
    }

    void Renderer_OpenGL::set_ambiant_factor(float factor)
    {
        this->ambiant_factor = factor;
    }

    void Renderer_OpenGL::set_diffuse_factor(float factor)
    {
        this->diffuse_factor = factor;
    }

    void Renderer_OpenGL::set_specular_factor(float factor)
    {
        this->specular_factor = factor;
    }

    void Renderer_OpenGL::set_shininess(float shininess)
    {
        this->shininess = shininess;
    }

}