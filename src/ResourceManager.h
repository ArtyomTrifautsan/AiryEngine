#pragma once

#include <string>
#include <map>
#include <memory>

namespace Renderer
{
    class ShaderProgram;
}

class ResourceManager
{
public:
    ResourceManager(const std::string& executable_path);
    ~ResourceManager() = default;

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;
    ResourceManager(ResourceManager&&) = delete;

    std::shared_ptr<Renderer::ShaderProgram> load_shaders(const std::string& shader_name, const std::string& vertex_path, const std::string& fragment_path);
    std::shared_ptr<Renderer::ShaderProgram> get_shader_program(const std::string& shader_name);

private:
    std::string get_file_string(const std::string& relative_file_path) const;

    typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramMap;
    ShaderProgramMap shader_programs;
    std::string executable_path;
};