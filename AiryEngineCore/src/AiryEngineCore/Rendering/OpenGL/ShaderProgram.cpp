#include "AiryEngineCore/Rendering/OpenGL/ShaderProgram.hpp"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "AiryEngineCore/Log.hpp"

namespace AiryEngine
{

    bool create_shader(const char* source, GLenum shader_type, GLuint& shader_id)
    {
        shader_id = glCreateShader(shader_type);
        glShaderSource(shader_id, 1, &source, nullptr);
        glCompileShader(shader_id);

        GLint success;
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
        if (GL_FALSE == success)
        {
            char info_log[1024];
            glGetShaderInfoLog(shader_id, 1024, nullptr, info_log);

            LOG_CRITICAL("Shader compilation error:\n{}", info_log);
            return false;
        }

        return true;
    }


    ShaderProgram::ShaderProgram(const char* vertex_shader_src, const char* fragment_shader_src)
    {
        // Compile vertex shader
        GLuint vertex_shader_id = 0;
        if (!create_shader(vertex_shader_src, GL_VERTEX_SHADER, vertex_shader_id))
        {
            LOG_CRITICAL("VERTEX SHADER: compile-time error.");
            glDeleteShader(vertex_shader_id);
            return;
        }

        // Compile fragment shader
        GLuint fragment_shader_id = 0;
        if (!create_shader(fragment_shader_src, GL_FRAGMENT_SHADER, fragment_shader_id))
        {
            LOG_CRITICAL("FRAGMENT SHADER: compile-time error.");
            glDeleteShader(fragment_shader_id);
            return;
        }

        // Create shader program
        this->id = glCreateProgram();
        glAttachShader(this->id, vertex_shader_id);
        glAttachShader(this->id, fragment_shader_id);
        glLinkProgram(this->id);

        GLint success;
        glGetProgramiv(this->id, GL_LINK_STATUS, &success);
        if (!success)
        {
            char info_log[1024];
            glGetProgramInfoLog(this->id, 1024, nullptr, info_log);
            LOG_CRITICAL("SHADER PROGRAM: Link-time error:\n{}", info_log);

            glDeleteProgram(this->id);
            this->id = 0;
            glDeleteShader(vertex_shader_id);
            glDeleteShader(fragment_shader_id);

            return;
        }
        else
            this->is_shader_compiled = true;

        glDetachShader(this->id, vertex_shader_id);
        glDetachShader(this->id, fragment_shader_id);
        glDeleteShader(vertex_shader_id);
        glDeleteShader(fragment_shader_id);
    }

    ShaderProgram::~ShaderProgram() { glDeleteProgram(this->id); }

    void ShaderProgram::bind() const { glUseProgram(this->id); }

    void ShaderProgram::unbind() { glUseProgram(0); }

    ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shaderProgram)
    {
        glDeleteProgram(this->id);
        this->id = shaderProgram.id;
        this->is_shader_compiled = shaderProgram.is_shader_compiled;

        shaderProgram.id = 0;
        shaderProgram.is_shader_compiled = false;

        return *this;
    }

    ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram)
    {
        this->id = shaderProgram.id;
        this->is_shader_compiled = shaderProgram.is_shader_compiled;

        shaderProgram.id = 0;
        shaderProgram.is_shader_compiled = false;
    }

    void ShaderProgram::set_matrix4(const char* name, const glm::mat4& matrix) const
    {
        glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void ShaderProgram::set_vec3(const char* name, const glm::vec3& vector) const
    {
        glUniform3f(glGetUniformLocation(this->id, name), vector.x, vector.y, vector.z);
    }

    void ShaderProgram::set_float(const char* name, const float value) const
    {
        glUniform1f(glGetUniformLocation(this->id, name), value);
    }
    void ShaderProgram::set_int(const char* name, const int value) const
    {
        glUniform1i(glGetUniformLocation(this->id, name), value);
    }

}
