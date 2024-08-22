#pragma once

// #include "AiryEngineCore/ResourceManaging/ResourceManager.hpp"
// #include "AiryEngineCore/Rendering/OpenGL/Model3D.hpp"


struct GLFWwindow;

//class Camera;

namespace AiryEngine {

    class Model3D;
    class VertexArray;
    // class VertexBuffer;
    // class IndexBuffer;
    // class Texture2D;
    // class ShaderProgram;

    class Renderer_OpenGL
    {
    public:
        static void before_render();
        // static void render_model3D(class Camera& camera, 
        //                     std::shared_ptr<Model3D> model, 
        //                     std::shared_ptr<ShaderProgram> shader_program, 
        //                     const glm::vec3& light_source_position, 
        //                     const glm::vec3& light_source_color);
        // static void render_light_model3D(class Camera& camera, 
        //                     std::shared_ptr<Model3D> model, 
        //                     std::shared_ptr<ShaderProgram> shader_program, 
        //                     const glm::vec3& light_source_position, 
        //                     const glm::vec3& light_source_color);

        static bool init(GLFWwindow* window);  //  Нельзя убирать этот метод, он инициализирует glad в Window.cpp

        static void draw_vertex_elements(const VertexArray& vertex_array);
        static void set_clear_color(const float r, const float g, const float b, const float a);
        static void clear();
        static void set_viewport(const unsigned int width, const unsigned int height, const unsigned int left_offset = 0, const unsigned bottom_offset = 0);
        static void enable_depth_testing();
        static void disable_depth_testing();

        static const char* get_vendor_str();
        static const char* get_renderer_str();
        static const char* get_version_str();
    
    private:
        // static void render_mesh(class Camera& camera, 
        //                 std::shared_ptr<Mesh> mesh,
        //                 std::shared_ptr<ShaderProgram> shader_program, 
        //                 const glm::vec3& light_source_position, 
        //                 const glm::vec3& light_source_color);
        // static void render_light_mesh(class Camera& camera, 
        //                 std::shared_ptr<Mesh> mesh,
        //                 std::shared_ptr<ShaderProgram> shader_program, 
        //                 const glm::vec3& light_source_position, 
        //                 const glm::vec3& light_source_color);
    };

}