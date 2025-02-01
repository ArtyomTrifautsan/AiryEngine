#pragma once

#include <string>
#include <vector>
#include <memory>
#include <map>


namespace AiryEngine {

    class ShaderProgram;
    class Texture2D;
    class Model3D;
    class Mesh;
    struct Material;

    class ResourceManager
    {
    public:
        ResourceManager(const std::string& executable_path);
        //~ResourceManager();
        void set_executable_path(const std::string& executable_path);

        //ResourceManager(const ResourceManager&) = delete;
        //ResourceManager& operator=(const ResourceManager&) = delete;
        //ResourceManager& operator=(ResourceManager&&) = delete;
        //ResourceManager(ResourceManager&&) = delete;

        std::shared_ptr<ShaderProgram> load_shaders(const std::string& shader_name, const std::string& vertex_path, const std::string& fragment_path);
        std::shared_ptr<ShaderProgram> get_shader_program(const std::string& shader_name);

        std::shared_ptr<Texture2D> load_texture2D(const std::string& texture_name, const std::string& texture_path);
        std::shared_ptr<Texture2D> load_texture2D_by_full_path(const std::string& texture_name, const std::string& texture_full_path);
        std::shared_ptr<Texture2D> get_texture2D(const std::string& texture_name);

        std::shared_ptr<Model3D> load_model3D(const std::string& model_name, const std::string& model_path, const std::string& model_dir_path);
        std::shared_ptr<Model3D> get_model3D(const std::string& model_name);

        void set_shaders_directory(const std::string& path);
        void set_textures_directory(const std::string& path);
        void set_models_directory(const std::string& path);

        typedef std::map<const std::string, std::shared_ptr<ShaderProgram>> ShaderProgramsMap;
        ShaderProgramsMap shader_programs;
        ShaderProgramsMap loaded_shaders;
        typedef std::map<const std::string, std::shared_ptr<Texture2D>> Texture2DMap;
        Texture2DMap textures;
        Texture2DMap loaded_textures;
        typedef std::map<const std::string, std::shared_ptr<Model3D>> Model3DMap;
        Model3DMap models;
        Model3DMap loaded_models;

    private:
        std::string get_file_string(const std::string& relative_file_path);
        std::string get_directory_path(const std::string& path_to_file);
        std::string change_symbol(std::string& str, const char& src_symbol, const std::string& new_symbol);
        void load_OBJ(const std::string& full_path_to_model, std::vector<std::shared_ptr<Mesh>>& meshes, const std::string& model_name);

        std::shared_ptr<std::map<std::string, std::shared_ptr<Material>>> load_MTL(const std::string& full_path_to_model, const std::string& model_name);
        std::vector<std::string> split_string(std::string& str, const std::string separator);

        std::string path_to_executable;

        std::string shaders_directory;
        std::string textures_directory;
        std::string models_directory;
    };

}