#include <sstream>
#include <fstream>
#include <iostream>

#include <string>
#include <memory>
#include <map>

#include "ResourceManager.hpp"

#include "AiryEngineCore/Log.hpp"
#include "AiryEngineCore/Rendering/OpenGL/ShaderProgram.hpp"

namespace AiryEngine {

    ResourceManager::ResourceManager(const std::string& executable_path)
    {
        this->path_to_executable = executable_path;
    }

    std::string ResourceManager::get_file_string(const std::string& relative_file_path)
    {
        std::ifstream f;
        f.open(this->path_to_executable + "/" + relative_file_path.c_str(), std::ios::in | std::ios::binary);
        if (!f.is_open())
        {
            LOG_CRITICAL("Failed to open file: {}", relative_file_path);
            //std::cerr << "Failed to open file: " << relativeFilePath << std::endl;
            return std::string{};
        }

        std::stringstream buffer;
        buffer << f.rdbuf();
        return buffer.str();
    }

    std::shared_ptr<ShaderProgram> ResourceManager::load_shaders(const std::string& shader_name, const std::string& vertex_path, const std::string& fragment_path)
    {
        std::string vertex_string = get_file_string(vertex_path);
        if (vertex_string.empty())
        {
            LOG_CRITICAL("No vertex shader, Path: {}", vertex_path);
            //std::cerr << "No vertex shader!" << std::endl;
            return nullptr;
        }

        std::string fragment_string = get_file_string(fragment_path);
        if (fragment_string.empty())
        {
            LOG_CRITICAL("No fragment shader. Path: {}", fragment_path);
            //std::cerr << "No  shader!" << std::endl;
            return nullptr;
        }

        std::shared_ptr<ShaderProgram>& new_shader = this->shader_programs.emplace(shader_name, std::make_shared<ShaderProgram>(vertex_string.c_str(), fragment_string.c_str())).first->second;
        //std::shared_ptr<ShaderProgram> new_shader = std::make_shared<ShaderProgram>(vertex_string.c_str(), fragment_string.c_str());
        if (new_shader->is_compiled())
        {
            return new_shader;
        }

        LOG_CRITICAL("Can't load shader program. Vertex shader: {0}, fragment shader: {1}", vertex_path, fragment_path);
        // std::cerr << "Can't load shader program:\n"
        //     << "Vertex: " << vertexPath << "\n"
        //     << "Fragment: " << fragmentPath << std::endl;

        return nullptr;
    }

    std::shared_ptr<ShaderProgram> ResourceManager::get_shader_program(const std::string& shader_name)
    {
        ShaderProgramsMap::const_iterator it = this->shader_programs.find(shader_name);
        if (it != this->shader_programs.end())
        {
            return it->second;
        }
        LOG_CRITICAL("Can't find the shader program: {}", shader_name);
        //std::cerr << "Can't find the shader program: " << shaderName << std::endl;
        return nullptr;
    }
}