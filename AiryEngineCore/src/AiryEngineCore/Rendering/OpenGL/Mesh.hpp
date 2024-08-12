#pragma once

#include <string>
#include <vector>
#include <memory>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include "AiryEngineCore/Rendering/OpenGL/Texture2D.hpp"

namespace AiryEngine {

    class Camera;
    class ShaderProgram;
    class BufferLayout;
    class VertexArray;
    class VertexBuffer;
    class IndexBuffer;

    struct VertexData 
    {
        std::vector<float> Position;
        std::vector<float> Normal;
        std::vector<float> TexCoords;

        VertexData(std::vector<float> _pos, std::vector<float> _normal, std::vector<float> texture_coords)
        {
            Position = _pos;
            Normal = _normal;
            TexCoords = texture_coords;
        }
    };


    struct TextureData
    {
        unsigned int id;
        std::string type;
    };


    class Mesh 
    {
    public:
        Mesh(std::shared_ptr<std::vector<float>> vertices, 
                std::shared_ptr<std::vector<unsigned int>> indices, 
                std::shared_ptr<TextureData> texture_data,
                std::shared_ptr<Texture2D> texture);
        
        void draw(std::shared_ptr<ShaderProgram> shader_program, Camera& camera, const glm::vec3& light_source_position, const glm::vec3& light_source_color);

        std::shared_ptr<std::vector<VertexData>> get_vertices();
        std::shared_ptr<std::vector<unsigned int>> get_indices();
        std::shared_ptr<TextureData> get_texture_data();
        std::shared_ptr<Texture2D> get_texture() const { return this->texture; }
        std::shared_ptr<VertexArray> get_vertex_array() const { return this->vertex_array; }
        void get_scale(float _scale[3]) const;
        float get_rotate() const;
        void get_translate(float _translate[3]) const;

        float get_ambiant_factor() const { return this->ambiant_factor; }   // Temporary solution
        float get_diffuse_factor() const { return this->diffuse_factor; }   // Temporary solution
        float get_specular_factor() const { return this->specular_factor; }     //Temporary solution
        float get_shininess() const { return this->shininess; }     // Temporary solution

        void set_scale(float scale_x, float scale_y, float scale_z);
        void set_rotate(float angle);
        void set_translate(float translate_x, float translate_y, float translate_z);
        void set_translate_x(float value);
        void set_translate_y(float value);
        void set_translate_z(float value);
    
    private:
        std::shared_ptr<std::vector<float>> vertices;
        std::shared_ptr<std::vector<unsigned int>> indices;
        std::shared_ptr<TextureData> texture_data;
        std::shared_ptr<Texture2D> texture;

        std::shared_ptr<VertexArray> vertex_array;
        std::shared_ptr<VertexBuffer> vertex_buffer;
        std::shared_ptr<IndexBuffer> index_buffer;

        float scale[3] = { 1.0f, 1.0f, 1.0f };
        float rotate = 90.0f;
        float translate[3] = { 0.0f, 0.0f, 0.0f };

        float ambiant_factor = 0.1f;        // Temporary solution
        float diffuse_factor = 1.0f;        // Temporary solution
        float specular_factor = 0.5f;        // Temporary solution
        float shininess = 32.0f;        // Temporary solution

        void setup_render_data_mesh();
}; 

}