#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/trigonometric.hpp>

#include <memory>

#include "Renderer_OpenGL.hpp"

#include "AiryEngineCore/Camera.hpp"
#include "AiryEngineCore/Log.hpp"

// #define STB_IMAGE_IMPLEMENTATION
// #define STBI_ONLY_PNG
// #include "AiryEngineCore/ResourceManaging/stb_image.h"

namespace AiryEngine {





    //================================================================================//
    void generate_circle(unsigned char* data,
                         const unsigned int width,
                         const unsigned int height,
                         const unsigned int center_x,
                         const unsigned int center_y,
                         const unsigned int radius,
                         const unsigned char color_r,
                         const unsigned char color_g,
                         const unsigned char color_b)
    {
        for (unsigned int x = 0; x < width; ++x)
        {
            for (unsigned int y = 0; y < height; ++y)
            {
                if ((x - center_x) * (x - center_x) + (y - center_y) * (y - center_y) < radius * radius)
                {
                    data[3 * (x + width * y) + 0] = color_r;
                    data[3 * (x + width * y) + 1] = color_g;
                    data[3 * (x + width * y) + 2] = color_b;
                }
            }
        }
    }

    void generate_smile_texture(unsigned char* data,
                                const unsigned int width,
                                const unsigned int height)
    {
        // background
        for (unsigned int x = 0; x < width; ++x)
        {
            for (unsigned int y = 0; y < height; ++y)
            {
                data[3 * (x + width * y) + 0] = 200;
                data[3 * (x + width * y) + 1] = 191;
                data[3 * (x + width * y) + 2] = 231;
            }
        }

        // face
        generate_circle(data, width, height, width * 0.5, height * 0.5, width * 0.4, 255, 255, 0);

        // smile
        generate_circle(data, width, height, width * 0.5, height * 0.4, width * 0.2, 0, 0, 0);
        generate_circle(data, width, height, width * 0.5, height * 0.45, width * 0.2, 255, 255, 0);

        // eyes
        generate_circle(data, width, height, width * 0.35, height * 0.6, width * 0.07, 255, 0, 255);
        generate_circle(data, width, height, width * 0.65, height * 0.6, width * 0.07, 0, 0, 255);
    }
    //================================================================================//


    GLfloat positions_colors2[] = {
         1.0f, -0.5f, -0.5f,     1.0f, 1.0f, 0.0f,   1.0f, 0.0f,
         1.0f,  0.5f, -0.5f,     0.0f, 1.0f, 1.0f,   0.0f, 0.0f,
         1.0f, -0.5f,  0.5f,     1.0f, 0.0f, 1.0f,   1.0f, 1.0f,
         1.0f,  0.5f,  0.5f,     1.0f, 0.0f, 0.0f,   0.0f, 1.0f,

        -1.0f, -0.5f, -0.5f,     1.0f, 1.0f, 0.0f,   1.0f, 0.0f,
        -1.0f,  0.5f, -0.5f,     0.0f, 1.0f, 1.0f,   0.0f, 0.0f,
        -1.0f, -0.5f,  0.5f,     1.0f, 0.0f, 1.0f,   1.0f, 1.0f,
        -1.0f,  0.5f,  0.5f,     1.0f, 0.0f, 0.0f,   0.0f, 1.0f
    };

    // GLint indices[] = {
    //     0, 1, 2, 3, 2, 1
    // };

    // GLfloat positions_colors2[] = {
    //      0.0f, -0.5f, -0.5f,     1.0f, 1.0f, 0.0f,
    //      0.0f,  0.5f, -0.5f,     0.0f, 1.0f, 1.0f,
    //      0.0f, -0.5f,  0.5f,     1.0f, 0.0f, 1.0f,
    //      0.0f,  0.5f,  0.5f,     1.0f, 0.0f, 0.0f,

    //     -1.0f, -0.5f, -0.5f,     1.0f, 1.0f, 0.0f,
    //     -1.0f,  0.5f, -0.5f,     0.0f, 1.0f, 1.0f,
    //     -1.0f, -0.5f,  0.5f,     1.0f, 0.0f, 1.0f,
    //     -1.0f,  0.5f,  0.5f,     1.0f, 0.0f, 0.0f,
    // };

    GLint indices[] = {
        0, 1, 2, 3, 2, 1,
        4, 5, 6, 7, 6, 5,
        4, 0, 2, 4, 6, 2,
        5, 1, 3, 5, 7, 3,
        7, 3, 2, 7, 6, 2,
        4, 0, 1, 4, 5, 1
    };

    float scale[3] = { 1.0f, 1.0f, 1.0f };
    float rotate = 0.0f;
    float translate[3] = { 0.0f, 0.0f, 0.0f };

    float background_color[4] = {0.33f, 0.33f, 0.33f, 0.f};

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

        this->shader_program = this->resource_manager->load_shaders("DefaultShaders", "Resources/Shaders/vertex_shader.txt", "Resources/Shaders/fragment_shader.txt");
        if (!shader_program->is_compiled()) 
        {
            LOG_CRITICAL("Failed to compile Shader Program");
        }

        BufferLayout bufferLayout_vec3_vec3_vec2
        {
            ShaderDataType::Float3,
            ShaderDataType::Float3,
            ShaderDataType::Float2
        };
        this->positions_colors_vbo = std::make_unique<VertexBuffer>(positions_colors2, sizeof(positions_colors2), bufferLayout_vec3_vec3_vec2);
        this->vao = std::make_unique<VertexArray>();
        this->index_buffer = std::make_unique<IndexBuffer>(indices, sizeof(indices) / sizeof(GLuint));

        vao->add_vertex_buffer(*positions_colors_vbo);
        vao->set_index_buffer(*index_buffer);

        this->dog_texture = this->resource_manager->load_texture("Resources/Textures/dog.png");
        // const unsigned int width = 1000;
        // const unsigned int height = 1000;
        // const unsigned int channels = 3;
        // auto* pixels = new unsigned char[width * height * channels];  
        // generate_smile_texture(pixels, width, height);
        // this->dog_texture = std::make_shared<Texture2D>(pixels, width, height, channels);
        this->dog_texture->bind(0);





        // this->dog_texture = this->resource_manager->load_texture("Resources/Textures/dog.png");
        // glCreateTextures(GL_TEXTURE_2D, 1, &this->texture_handle); 
        // glTextureStorage2D(this->texture_handle, 1, GL_RGB8, dog_texture.width, dog_texture.height);
        // glTextureSubImage2D(this->texture_handle, 0, 0, 0, dog_texture.width, dog_texture.height, GL_RGBA, GL_UNSIGNED_BYTE, dog_texture.pixels);

        // glCreateTextures(GL_TEXTURE_2D, 1, &this->texture_handle); 
        // glTextureStorage2D(this->texture_handle, 1, GL_RGB8, width, height);
        // glTextureSubImage2D(this->texture_handle, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);

        // glTextureParameteri(this->texture_handle, GL_TEXTURE_WRAP_S, GL_REPEAT);
        // glTextureParameteri(this->texture_handle, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // glTextureParameteri(this->texture_handle, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        // glTextureParameteri(this->texture_handle, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // glBindTextureUnit(0, texture_handle);
    }

    Renderer_OpenGL::~Renderer_OpenGL()
    {
        // glDeleteTextures(1, &this->texture_handle);
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

}