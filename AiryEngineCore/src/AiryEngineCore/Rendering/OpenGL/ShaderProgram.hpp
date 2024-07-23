#pragma once

#include <glm/mat4x4.hpp>

namespace AiryEngine {

    class ShaderProgram
    {
    public:
        ShaderProgram(const char* vertex_shader_src, const char* fragment_shader_src);
        ShaderProgram(ShaderProgram&&);
        ShaderProgram& operator=(ShaderProgram&&);
        ~ShaderProgram();

        ShaderProgram() = delete;
        ShaderProgram(const ShaderProgram&) = delete;
        ShaderProgram& operator=(const ShaderProgram&) = delete;

        void bind() const;
        static void unbind();
        bool is_compiled() const { return isCompiled; }
        void set_matrix4(const char* name, const glm::mat4& matrix) const;

    private:
        unsigned int id = 0;
        bool isCompiled = false;
    };

}