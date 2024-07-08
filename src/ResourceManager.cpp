#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include "ResourceManager.h"
#include "ShaderProgram.h"

ResourceManager::ResourceManager(const std::string& path_to_executable)
{
    size_t found = path_to_executable.find_last_of("/\\");
    std::string executable_path = path_to_executable.substr(0, found);
}

std::string ResourceManager::get_file_string(const std::string& relative_file_path) const
{
    std::ifstream file;
    file.open(executable_path + "/" + relative_file_path.c_str(), std::ios::in | std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file: " << relative_file_path << std::endl;
        return std::string{};
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::load_shaders(const std::string& shader_name, const std::string& vertex_path, const std::string& fragment_path)
{
    std::string vertex_string = get_file_string(vertex_path);
    if (vertex_string.empty())
    {
        std::cerr << "No vertex shader!" << std::endl;
        return nullptr;
    }

    std::string fragment_string = get_file_string(fragment_path);
    if (fragment_string.empty())
    {
        std::cerr << "No fragment shader!" << std::endl;
        return nullptr;
    }

    std::shared_ptr<Renderer::ShaderProgram>& new_shader = shader_programs.emplace(shader_name, std::make_shared<Renderer::ShaderProgram>(vertex_string, fragment_string)).first->second;
    if (new_shader->is_compiled())
        return new_shader;
    
    std::cerr << "Can't load shader program:\n"
        << "Vertex:" << vertex_path << "\n"
        << "Fragment" << fragment_path << std::endl;
    
    return nullptr;
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::get_shader_program(const std::string& shader_name)
{
    ShaderProgramMap::const_iterator it = shader_programs.find(shader_name);
    if (it != shader_programs.end())
        return it->second;
    
    std::cerr << "Can't find the shader program: " << shader_name << std::endl;
    return nullptr;
}