#pragma once

#include "AiryEngineCore/ResourceManaging/ResourceManager.hpp"

#include "AiryEngineCore/Rendering/OpenGL/ShaderProgram.hpp"
#include "AiryEngineCore/Rendering/OpenGL/VertexBuffer.hpp"
#include "AiryEngineCore/Rendering/OpenGL/IndexBuffer.hpp"
#include "AiryEngineCore/Rendering/OpenGL/VertexArray.hpp"
#include "AiryEngineCore/Rendering/OpenGL/Texture2D.hpp"

struct GLFWwindow;

//class Camera;

namespace AiryEngine {

    class VertexArray;

    class Renderer_OpenGL
    {
    public:
        Renderer_OpenGL(std::shared_ptr<ResourceManager> resource_manager);
        ~Renderer_OpenGL();
        void rendering(class Camera& camera, bool perspective_camera);

        static bool init(GLFWwindow* window);  //  Нельзя убирать этот метод, он инициализирует glad в Window.cpp

        static void draw_vertex_elements(const VertexArray& vertex_array);
        void set_clear_color(const float r, const float g, const float b, const float a);
        static void clear();
        static void set_viewport(const unsigned int width, const unsigned int height, const unsigned int left_offset = 0, const unsigned bottom_offset = 0);
        static void enable_depth_testing();
        static void disable_depth_testing();

        void set_light_source_position(float light_source_position[3]);     // Temporary solution
        void set_light_source_color(float light_source_color[3]);       // Temporary solution
        void set_ambiant_factor(float factor);       // Temporary solution
        void set_diffuse_factor(float factor);       // Temporary solution
        void set_specular_factor(float factor);       // Temporary solution
        void set_shininess(float shininess);       // Temporary solution

        static const char* get_vendor_str();
        static const char* get_renderer_str();
        static const char* get_version_str();
    
    private:
        GLFWwindow* window;
        std::shared_ptr<ResourceManager> resource_manager;
        std::shared_ptr<ShaderProgram> default_shader_program;
        std::shared_ptr<ShaderProgram> light_source_shader_program;
        std::unique_ptr<VertexArray> cube_vao;
        std::unique_ptr<IndexBuffer> cube_index_buffer;
        std::unique_ptr<VertexBuffer> cube_positions_vbo;

        float light_source_position[3] = { 1.f, 0.f, 0.f };     // Temporary solution
        float light_source_color[3] = { 1.f, 1.f, 1.f };        // Temporary solution
        float ambiant_factor = 0.1f;        // Temporary solution
        float diffuse_factor = 1.0f;        // Temporary solution
        float specular_factor = 0.5f;        // Temporary solution
        float shininess = 32.0f;        // Temporary solution

        std::shared_ptr<Texture2D> dog_texture;
    };

}