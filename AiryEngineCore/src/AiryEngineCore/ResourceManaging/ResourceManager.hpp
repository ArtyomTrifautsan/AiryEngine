#pragma once

#include <string>
#include <memory>
#include <map>

#include "AiryEngineCore/Rendering/OpenGL/ShaderProgram.hpp"
#include "AiryEngineCore/Rendering/OpenGL/Texture2D.hpp"

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

        std::shared_ptr<Texture2D> load_texture(const std::string& texture_path);

        //ResourceManager(const ResourceManager&) = delete;
        //ResourceManager& operator=(const ResourceManager&) = delete;
        //ResourceManager& operator=(ResourceManager&&) = delete;
        //ResourceManager(ResourceManager&&) = delete;

        typedef std::map<const std::string, std::shared_ptr<ShaderProgram>> ShaderProgramsMap;
        ShaderProgramsMap shader_programs;
    
    private:
        std::string get_file_string(const std::string& relative_file_path);

        std::string path_to_executable;        
    };

}