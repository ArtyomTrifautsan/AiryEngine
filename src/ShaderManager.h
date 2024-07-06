#pragma once

#include <string>

#include <glad/glad.h>

namespace Renderer { 

    class ShaderManager {
    public:
        ShaderManager(const std::string& vertex_shader, const std::string& fragment_shader);
        ~ShaderManager();
        bool is_compiled() const { return m_isCompiled; }
        void use() const;

        ShaderManager() = delete;
        ShaderManager(ShaderManager&) = delete;
        ShaderManager& operator=(const ShaderManager&) = delete;
        ShaderManager& operator=(ShaderManager&& shader_manager) noexcept;
        ShaderManager(ShaderManager&& shader_shader_managerprogram) noexcept;
    private:
        bool create_shader(const std::string& source, const GLenum shader_type, GLuint& shaderID);
        bool m_isCompiled = false;
        GLuint shader_program_ID = 0;
    };

};