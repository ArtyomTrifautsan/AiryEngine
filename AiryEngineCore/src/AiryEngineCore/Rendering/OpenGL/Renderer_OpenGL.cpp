#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Renderer_OpenGL.hpp"
#include "AiryEngineCore/Log.hpp"
#include "VertexArray.hpp"

namespace AiryEngine {

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

    void Renderer_OpenGL::draw(const VertexArray& vertex_array)
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