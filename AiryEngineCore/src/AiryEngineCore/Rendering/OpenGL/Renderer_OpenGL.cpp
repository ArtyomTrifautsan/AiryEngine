#include "AiryEngineCore/Rendering/OpenGL/Renderer_OpenGL.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/trigonometric.hpp>

#include <memory>

#include "AiryEngineCore/Camera.hpp"
#include "AiryEngineCore/Log.hpp"
#include "AiryEngineCore/Scene/Model3D.hpp"

#include "AiryEngineCore/Rendering/OpenGL/Mesh.hpp"
#include "AiryEngineCore/Rendering/OpenGL/ShaderProgram.hpp"
#include "AiryEngineCore/Rendering/OpenGL/VertexBuffer.hpp"
#include "AiryEngineCore/Rendering/OpenGL/IndexBuffer.hpp"
#include "AiryEngineCore/Rendering/OpenGL/VertexArray.hpp"
#include "AiryEngineCore/Rendering/OpenGL/Texture2D.hpp"


namespace AiryEngine {

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

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);      // Технология рассчета прозрачности

        return true;
    }

    void Renderer_OpenGL::before_render()
    {
        set_clear_color(
            background_color[0],
            background_color[1],
            background_color[2],
            background_color[3]
        );
        clear();
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

    void Renderer_OpenGL::enable_alpha_channel()
    {
        glEnable(GL_BLEND);
        // glDisable(GL_CULL_FACE);    // Отсечение обратных поверхностей
    }

    void Renderer_OpenGL::disable_alpha_channel()
    {
        glDisable(GL_BLEND);
        // glEnable(GL_CULL_FACE);    // Отсечение обратных поверхностей
    }


    const char* Renderer_OpenGL::get_vendor_str() { return reinterpret_cast<const char*>(glGetString(GL_VENDOR)); }

    const char* Renderer_OpenGL::get_renderer_str() { return reinterpret_cast<const char*>(glGetString(GL_RENDERER)); }
    
    const char* Renderer_OpenGL::get_version_str() { return reinterpret_cast<const char*>(glGetString(GL_VERSION)); }

}