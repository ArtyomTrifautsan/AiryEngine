#pragma once

#include <string>
#include <memory>
#include <map>

#include "AiryEngineCore/Rendering/OpenGL/ShaderProgram.hpp"
#include "AiryEngineCore/Rendering/OpenGL/Texture2D.hpp"
#include "AiryEngineCore/Rendering/OpenGL/Model3D.hpp"

namespace AiryEngine {

    // struct Texture2D
    // {
    //     int width = 0;
    //     int height = 0;
    //     int channels = 0;
    //     unsigned char* pixels;
    // };

    class ResourceManager
    {
    public:
        ResourceManager(const std::string& executable_path);
        //~ResourceManager();
        std::shared_ptr<ShaderProgram> load_shaders(const std::string& shader_name, const std::string& vertex_path, const std::string& fragment_path);
        std::shared_ptr<ShaderProgram> get_shader_program(const std::string& shader_name);

        std::shared_ptr<Texture2D> load_texture2D(const std::string& texture_name, const std::string& texture_path);
        std::shared_ptr<Texture2D> get_texture2D(const std::string& texture_name);

        std::shared_ptr<Model3D> load_model3D(const std::string& model_name, const std::string& texture_path, std::shared_ptr<Texture2D> texture);
        std::shared_ptr<Model3D> get_model3D(const std::string& model_name);

        //ResourceManager(const ResourceManager&) = delete;
        //ResourceManager& operator=(const ResourceManager&) = delete;
        //ResourceManager& operator=(ResourceManager&&) = delete;
        //ResourceManager(ResourceManager&&) = delete;

        typedef std::map<const std::string, std::shared_ptr<ShaderProgram>> ShaderProgramsMap;
        ShaderProgramsMap shader_programs;
        typedef std::map<const std::string, std::shared_ptr<Texture2D>> Texture2DMap;
        Texture2DMap textures;
    
    private:
        std::string get_file_string(const std::string& relative_file_path);
        void load_OBJ(const std::string& full_path_to_model, 
                                    std::shared_ptr<std::vector<float>> vertices, 
                                    std::shared_ptr<std::vector<unsigned int>> indices);
        std::vector<std::string> split_string(std::string& str, const std::string separator);

        std::string path_to_executable;     
    };

}