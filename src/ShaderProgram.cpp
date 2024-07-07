#include <iostream>

#include "ShaderProgram.h"

namespace Renderer { 

    ShaderProgram::ShaderProgram(const std::string& vertex_shader_code, const std::string& fragment_shader_code)
    {
        GLuint vertex_shader_ID;
        if (!create_shader(vertex_shader_code, GL_VERTEX_SHADER, vertex_shader_ID))
        {
            std::cerr << "VERTEX SHADER compile-time error" << std::endl;
            return;
        }

        GLuint fragment_shader_ID;
        if (!create_shader(fragment_shader_code, GL_FRAGMENT_SHADER, fragment_shader_ID))
        {
            std::cerr << "FRAGMENT SHADER compile-time error" << std::endl;
            glDeleteShader(vertex_shader_ID);
            return;
        }

        shader_program_ID = glCreateProgram();
        glAttachShader(shader_program_ID, vertex_shader_ID);
        glAttachShader(shader_program_ID, fragment_shader_ID);
        glLinkProgram(shader_program_ID);

        GLint success;
        glGetProgramiv(shader_program_ID, GL_LINK_STATUS, &success);
        if (!success)
        {
            GLchar info_log[1024];
            glGetProgramInfoLog(shader_program_ID, 1024, nullptr, info_log);
            std::cerr << "ERROR::SHADER: Link-time error:\n" << info_log << std::endl;
        }
        else 
            m_isCompiled = true; 

        glDeleteShader(vertex_shader_ID);
        glDeleteShader(fragment_shader_ID);
    }

    bool ShaderProgram::create_shader(const std::string& source, const GLenum shader_type, GLuint& shaderID)
    {
        shaderID = glCreateShader(shader_type);
        const char* source_code = source.c_str();
        glShaderSource(shaderID, 1, &source_code, nullptr);
        glCompileShader(shaderID);

        // Error handling
        GLint success;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
        if (!success) 
        {
            GLchar info_log[1024];
            glGetShaderInfoLog(shaderID, 1024, nullptr, info_log);
            std::cerr << "ERROR::SHADER: Compile-time error:\n" << info_log << std::endl;
            return false;
        }
        return true;
    }

    ShaderProgram::~ShaderProgram()
    {
        glDeleteProgram(shader_program_ID);
    }

    void ShaderProgram::use() const
    {
        glUseProgram(shader_program_ID);
    }

    ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shader_program) noexcept
    {
        glDeleteProgram(shader_program_ID);
        shader_program_ID = shader_program.shader_program_ID;
        m_isCompiled = shader_program.m_isCompiled;

        shader_program.shader_program_ID = 0;
        shader_program.m_isCompiled = false;

        return *this;
    }
    ShaderProgram::ShaderProgram(ShaderProgram&& shader_program) noexcept
    {
        shader_program_ID = shader_program.shader_program_ID;
        m_isCompiled = shader_program.m_isCompiled;

        shader_program.shader_program_ID = 0;
        shader_program.m_isCompiled = false;
    }

};