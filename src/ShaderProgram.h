#pragma once

#include <string>

#include <glad/glad.h>

namespace Renderer { 

    class ShaderProgram {
    public:
        ShaderProgram(const std::string& vertex_shader, const std::string& fragment_shader);
        ~ShaderProgram();
        bool is_compiled() const { return m_isCompiled; }
        void use() const;

        ShaderProgram() = delete;
        ShaderProgram(ShaderProgram&) = delete;
        ShaderProgram& operator=(const ShaderProgram&) = delete;
        ShaderProgram& operator=(ShaderProgram&& shader_program) noexcept;
        ShaderProgram(ShaderProgram&& shader_program) noexcept;
    private:
        bool create_shader(const std::string& source, const GLenum shader_type, GLuint& shaderID);
        bool m_isCompiled = false;
        GLuint shader_program_ID = 0;
    };

};