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
        bool is_compiled() const { return is_shader_compiled; }
        void set_matrix4(const char* name, const glm::mat4& matrix) const;
        void set_vec3(const char* name, const glm::vec3& vector) const;
        void set_float(const char* name, const float value) const;
        void set_int(const char* name, const int value) const;

    private:
        unsigned int id = 0;
        bool is_shader_compiled = false;
    };

}