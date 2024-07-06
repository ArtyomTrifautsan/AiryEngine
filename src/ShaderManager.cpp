#include <iostream>

#include "ShaderManager.h"

namespace Renderer { 

    ShaderManager::ShaderManager(const std::string& vertex_shader_code, const std::string& fragment_shader_code)
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

    bool ShaderManager::create_shader(const std::string& source, const GLenum shader_type, GLuint& shaderID)
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

    ShaderManager::~ShaderManager()
    {
        glDeleteProgram(shader_program_ID);
    }

    void ShaderManager::use() const
    {
        glUseProgram(shader_program_ID);
    }

    ShaderManager& ShaderManager::operator=(ShaderManager&& shader_manager) noexcept
    {
        glDeleteProgram(shader_program_ID);
        shader_program_ID = shader_manager.shader_program_ID;
        m_isCompiled = shader_manager.m_isCompiled;

        shader_manager.shader_program_ID = 0;
        shader_manager.m_isCompiled = false;

        return *this;
    }
    ShaderManager::ShaderManager(ShaderManager&& shader_manager) noexcept
    {
        shader_program_ID = shader_manager.shader_program_ID;
        m_isCompiled = shader_manager.m_isCompiled;

        shader_manager.shader_program_ID = 0;
        shader_manager.m_isCompiled = false;
    }

};