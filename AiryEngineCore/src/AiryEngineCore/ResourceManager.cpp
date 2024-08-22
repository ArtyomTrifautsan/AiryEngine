#include "AiryEngineCore/ResourceManager.hpp"

#include <sstream>
#include <fstream>
#include <iostream>

#include <string>
#include <memory>
#include <map>
#include <algorithm>
//#include <glad/glad.h>

#include "AiryEngineCore/Log.hpp"
#include "AiryEngineCore/Scene/Model3D.hpp"
#include "AiryEngineCore/Rendering/OpenGL/Mesh.hpp"
#include "AiryEngineCore/Rendering/OpenGL/ShaderProgram.hpp"
#include "AiryEngineCore/Rendering/OpenGL/Texture2D.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace AiryEngine {

    ResourceManager::ResourceManager(const std::string& executable_path)
    {
        // this->path_to_executable = executable_path;
        set_executable_path(executable_path);

        this->shaders_directory = "";
        this->textures_directory = "";
        this->models_directory = "";
    }

    std::string ResourceManager::get_file_string(const std::string& relative_file_path)
    {
        std::ifstream f;
        f.open(this->path_to_executable + "/" + relative_file_path.c_str(), std::ios::in | std::ios::binary);
        if (!f.is_open())
        {
            LOG_CRITICAL("Failed to open file: {}", relative_file_path);
            LOG_CRITICAL("Failed to open file: {}", this->path_to_executable + "/" + relative_file_path.c_str());
            //std::cerr << "Failed to open file: " << relativeFilePath << std::endl;
            return std::string{};
        }

        std::stringstream buffer;
        buffer << f.rdbuf();
        return buffer.str();
    }

    std::shared_ptr<ShaderProgram> ResourceManager::load_shaders(const std::string& shader_name, const std::string& vertex_path, const std::string& fragment_path)
    {
        std::string vertex_string = get_file_string(std::string(this->shaders_directory + "/" + vertex_path));
        if (vertex_string.empty())
        {
            LOG_CRITICAL("No vertex shader, Path: {}", vertex_path);
            //std::cerr << "No vertex shader!" << std::endl;
            return nullptr;
        }

        std::string fragment_string = get_file_string(std::string(this->shaders_directory + "/" + fragment_path));
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

    std::shared_ptr<Texture2D> ResourceManager::load_texture2D(const std::string& texture_name, const std::string& texture_path)
    {
        if (this->loaded_textures.count(texture_path))
            return this->loaded_textures[texture_path];

        int width = 0;
        int height = 0;
        int channels = 0;
        unsigned char* pixels = nullptr;

        stbi_set_flip_vertically_on_load(true);
        pixels = stbi_load(std::string(this->path_to_executable + "/" + this->textures_directory + "/" + texture_path).c_str(), &width, &height, &channels, 0);

        if (nullptr == pixels)
        {
            LOG_CRITICAL("Can't load texture: {}", texture_path);
        }
        // LOG_INFO("Created image: {}", texture_path);
        // LOG_INFO("  width: {}", width);
        // LOG_INFO("  height: {}", height);
        // LOG_INFO("  channels: {}", channels);
        
        std::shared_ptr<Texture2D> new_texture = std::make_shared<Texture2D>(pixels, width, height, channels);
        this->loaded_textures[texture_path] = new_texture;
        this->textures[texture_name] = new_texture;

        //std::shared_ptr<Texture2D>& new_texture = this->textures.emplace(texture_name, std::make_shared<Texture2D>(pixels, width, height, channels)).first->second;

        return new_texture;
    }

    std::shared_ptr<Texture2D> ResourceManager::get_texture2D(const std::string& texture_name)
    {
        Texture2DMap::const_iterator it = this->textures.find(texture_name);
        if (it != this->textures.end())
        {
            return it->second;
        }
        LOG_CRITICAL("Can't find the texture: {}", texture_name);
        //std::cerr << "Can't find the shader program: " << shaderName << std::endl;
        return nullptr;
    }

    std::shared_ptr<Model3D> ResourceManager::load_model3D(const std::string& model_name, const std::string& model_path)
    {
        if (this->loaded_models.count(model_path))
            return this->loaded_models[model_path];

        std::shared_ptr<Model3D> new_model = std::make_shared<Model3D>(); 
        std::vector<std::shared_ptr<Mesh>> meshes;

        // std::shared_ptr<std::vector<float>> vertices = std::make_shared<std::vector<float>>(); 
        // std::shared_ptr<std::vector<unsigned int>> indices = std::make_shared<std::vector<unsigned int>>();
        std::shared_ptr<Material> temp_material = std::make_shared<Material>();
        load_OBJ(std::string(this->path_to_executable + "/" + this->models_directory + "/" + model_path), meshes);
        //std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(vertices, indices, temp_material, texture);

        new_model->add_meshes(meshes);
        this->models[model_name] = new_model;
        this->loaded_models[model_path] = new_model;
        return new_model;
    }

    std::shared_ptr<Model3D> ResourceManager::get_model3D(const std::string& model_name)
    {
        Model3DMap::const_iterator it = this->models.find(model_name);
        if (it != this->models.end())
        {
            return it->second;
        }
        LOG_CRITICAL("Can't find the model: {}", model_name);
        //std::cerr << "Can't find the shader program: " << shaderName << std::endl;
        return nullptr;
    }

    void ResourceManager::load_OBJ(const std::string& full_path_to_model, std::vector<std::shared_ptr<Mesh>>& meshes)
    {
        // LOG_INFO("load_OBJ method was runned");

        std::shared_ptr<std::vector<float>> vertices = std::make_shared<std::vector<float>>(); 
        std::shared_ptr<std::vector<unsigned int>> indices = std::make_shared<std::vector<unsigned int>>();

        std::vector<std::vector<float>> vertex_coords;
        std::vector<std::vector<float>> normals;
        std::vector<std::vector<float>> texture_coords;

        std::shared_ptr<std::map<std::string, std::shared_ptr<Material>>> materials;

        std::string line;
        std::vector<std::string> line_vector;
        int mesh_count = 0;
        // std::shared_ptr<Mesh> new_mesh;
        std::shared_ptr<Material> mesh_material;

        std::ifstream file(full_path_to_model); // окрываем файл для чтения
        if (file.is_open())
        {
            // LOG_INFO("3D model loading: File opened: {}", full_path_to_model);

            int i = 0;
            while (std::getline(file, line))
            {
                //std::cout << i++ <<": " << line << std::endl;
                line_vector = split_string(line, " ");

                if (line_vector[0] == "mtllib")
                {
                    // LOG_INFO("Loading material file: {}", line_vector[1]);

                    std::string path_to_directory = get_directory_path(full_path_to_model);
                    materials = load_MTL(std::string(path_to_directory + "/" + line_vector[1]));
                }

                else if (line_vector[0] == "usemtl")
                {
                    // LOG_INFO("Using material: {}", line_vector[1]);

                    if (mesh_count)
                    {
                        std::shared_ptr<Mesh> new_mesh = std::make_shared<Mesh>(
                            vertices,
                            indices,
                            mesh_material
                        );
                        meshes.push_back(new_mesh);

                        // Нужно обяхательно обнулить все вершины и индексы
                        vertices = std::make_shared<std::vector<float>>();
                        indices = std::make_shared<std::vector<unsigned int>>();
                    }

                    mesh_material = (*materials)[line_vector[1]];
                    //new_mesh->set_material((*materials)[line_vector[1]]);
                    mesh_count++;
                }

                else if (line_vector[0] == "v")
                {
                    // LOG_INFO("Vertex: ({0}, {1}, {2})", line_vector[1], line_vector[2], line_vector[3]);
                    vertex_coords.push_back({std::stof(line_vector[1]), std::stof(line_vector[2]), std::stof(line_vector[3])});
                }

                else if (line_vector[0] == "vn")
                {
                    // LOG_INFO("Vertex normal: ({0}, {1}, {2})", line_vector[1], line_vector[2], line_vector[3]);
                    normals.push_back({std::stof(line_vector[1]), std::stof(line_vector[2]), std::stof(line_vector[3])});
                }

                else if (line_vector[0] == "vt")
                {
                    // LOG_INFO("Vertex texture: ({0}, {1})", line_vector[1], line_vector[2]);
                    texture_coords.push_back({std::stof(line_vector[1]), std::stof(line_vector[2])});
                }

                else if (line_vector[0] == "f")
                {
                    // LOG_INFO("Poligon data");

                    for (int i = 1; i <= 3; i++)
                    {
                        std::vector<std::string> _vertex = split_string(line_vector[i], "/");
                        // LOG_INFO("  Vertex {3} data: {0}/{1}/{2}", _vertex[0], _vertex[1], _vertex[2], i);
                        // LOG_INFO("  Vertex {3} pos: {0}/{1}/{2}", 
                        //             vertex_coords[static_cast<unsigned int>(std::stoul(_vertex[0]) - 1)][0], 
                        //             vertex_coords[static_cast<unsigned int>(std::stoul(_vertex[0]) - 1)][1], 
                        //             vertex_coords[static_cast<unsigned int>(std::stoul(_vertex[0]) - 1)][2], i);
                        vertices->push_back(vertex_coords[static_cast<unsigned int>(std::stoul(_vertex[0]) - 1)][0]);
                        vertices->push_back(vertex_coords[static_cast<unsigned int>(std::stoul(_vertex[0]) - 1)][1]);
                        vertices->push_back(vertex_coords[static_cast<unsigned int>(std::stoul(_vertex[0]) - 1)][2]);
                        
                        // LOG_INFO("  Vertex {3} normals: {0}/{1}/{2}", 
                        //             normals[static_cast<unsigned int>(std::stoul(_vertex[2]) - 1)][0], 
                        //             normals[static_cast<unsigned int>(std::stoul(_vertex[2]) - 1)][1], 
                        //             normals[static_cast<unsigned int>(std::stoul(_vertex[2]) - 1)][2], i);
                        vertices->push_back(vertex_coords[static_cast<unsigned int>(std::stoul(_vertex[2]) - 1)][0]);
                        vertices->push_back(vertex_coords[static_cast<unsigned int>(std::stoul(_vertex[2]) - 1)][1]);
                        vertices->push_back(vertex_coords[static_cast<unsigned int>(std::stoul(_vertex[2]) - 1)][2]);   
                        
                        // LOG_INFO("  Vertex {2} texture coords: {0}/{1}", 
                        //             texture_coords[static_cast<unsigned int>(std::stoul(_vertex[1]) - 1)][0], 
                        //             texture_coords[static_cast<unsigned int>(std::stoul(_vertex[1]) - 1)][1], i);
                        vertices->push_back(vertex_coords[static_cast<unsigned int>(std::stoul(_vertex[1]) - 1)][0]);
                        vertices->push_back(vertex_coords[static_cast<unsigned int>(std::stoul(_vertex[1]) - 1)][1]);

                        indices->push_back(static_cast<unsigned int>(indices->size()));
                    }
                }
            }

            if (mesh_count)
            {
                std::shared_ptr<Mesh> new_mesh = std::make_shared<Mesh>(
                    vertices,
                    indices,
                    mesh_material
                );
                meshes.push_back(new_mesh);

                // Нужно обяхательно обнулить все вершины и индексы
                vertices = std::make_shared<std::vector<float>>();
                indices = std::make_shared<std::vector<unsigned int>>();

                mesh_count++;
            }
        } 
        else 
        {
            LOG_CRITICAL("Can't open the file with 3D model: {}", full_path_to_model);
        }

        // LOG_INFO("load_OBJ method end");
        file.close();     // закрываем файл
    }

    std::shared_ptr<std::map<std::string, std::shared_ptr<Material>>> ResourceManager::load_MTL(const std::string& full_path_to_model)
    {
        // LOG_INFO("load_MTL method start");

        // Если не поставить эту настройку, при парсинге все float значения округляются до целых
        //std::setlocale(LC_ALL, "POSIX");  

        std::string line;
        std::vector<std::string> line_vector;
        int material_count = 0;
        std::shared_ptr<std::map<std::string, std::shared_ptr<Material>>> materials = std::make_shared<std::map<std::string, std::shared_ptr<Material>>>();
        std::shared_ptr<Material> new_material;
        unsigned int r, g, b;       // Нужно для загрузки цветов 

        std::ifstream file(full_path_to_model); // окрываем файл для чтения
        if (file.is_open())
        {
            // LOG_INFO("Open file with material");
            while (std::getline(file, line))
            {
                line_vector = split_string(line, " ");
                // LOG_INFO("line_vector, length={}", line_vector.size());
                if (!line_vector.size())
                    continue;

                if (line_vector[0] == "newmtl")
                {
                    // LOG_INFO("Create material: {}", line_vector[1]);

                    if (material_count)
                        materials->emplace(new_material->name, new_material);
                        //materials[new_material->name] = new_material;
                        //materials->push_back(new_material);
                    
                    new_material = std::make_shared<Material>();
                    new_material->name = line_vector[1];

                    material_count++;
                }

                else if (line_vector[0] == "Ns")
                {
                    // LOG_INFO("shininess: {}", line_vector[1]);

                    new_material->shininess = static_cast<unsigned int>(std::stoul(line_vector[1]));
                }

                else if (line_vector[0] == "Ka")
                {
                    // LOG_INFO("Ambient color: ({0}, {1}, {2})", line_vector[1], line_vector[2], line_vector[3]);
                    float r;
                    std::istringstream(line_vector[1]) >> r;
                    // std::cout << "r=" << r << std::endl;
                    
                    float g;
                    std::istringstream(line_vector[2]) >> g;
                    // std::cout << "g=" << g << std::endl;

                    float b;
                    std::istringstream(line_vector[3]) >> b;
                    // std::cout << "b=" << b << std::endl;

                    new_material->ambient_color = glm::vec3(r, g, b);
                }

                else if (line_vector[0] == "Kd")
                {
                    // LOG_INFO("Diffuse color: ({0}, {1}, {2})", line_vector[1], line_vector[2], line_vector[3]);

                    float r;
                    std::istringstream(line_vector[1]) >> r;
                    // std::cout << "r=" << r << std::endl;
                    
                    float g;
                    std::istringstream(line_vector[2]) >> g;
                    // std::cout << "g=" << g << std::endl;

                    float b;
                    std::istringstream(line_vector[3]) >> b;
                    // std::cout << "b=" << b << std::endl;

                    // LOG_INFO("Diffuse color+: ({0}, {1}, {2})", r, g, b);
                    new_material->diffuse_color = glm::vec3(r, g, b);
                }

                else if (line_vector[0] == "Ks")
                {
                    // LOG_INFO("Specular color: ({0}, {1}, {2})", line_vector[1], line_vector[2], line_vector[3]);

                    float r;
                    std::istringstream(line_vector[1]) >> r;
                    // std::cout << "r=" << r << std::endl;
                    
                    float g;
                    std::istringstream(line_vector[2]) >> g;
                    // std::cout << "g=" << g << std::endl;

                    float b;
                    std::istringstream(line_vector[3]) >> b;
                    // std::cout << "b=" << b << std::endl;

                    new_material->specular_color = glm::vec3(r, g, b);
                }

                else if (line_vector[0] == "map_Kd")
                {
                    // LOG_INFO("Map kd file: {}", line_vector[1]);
                }
            }

            if (material_count)
            {
                materials->emplace(new_material->name, new_material);
                material_count++;
            }
        }

        else 
        {
            LOG_CRITICAL("Can't open the file with model materials: {}", full_path_to_model);
        }

        file.close();     // закрываем файл
        // LOG_INFO("load_MTL method end");
        return materials;
    }

    std::vector<std::string> ResourceManager::split_string(std::string& str, const std::string separator)
    {
        std::vector<std::string> output_vector;
        int str_len = str.size();
        int sep_len = separator.size();

        if (str_len < sep_len)
        {

        }

        std::string word = "";
        for (int i = 0; i < str_len; i++)
        {   
            std::string checking_part_of_string;
            // Если оставшаяся часть строки меньше чем сепаратор
            if (sep_len > str_len - i + 1)
            {
                sep_len = str_len - i + 1;
                for (int j = 0; j < sep_len; j++)
                    checking_part_of_string += str[i+j];

                word += checking_part_of_string;
                output_vector.push_back(word);
                break;
            }

            for (int j = 0; j < sep_len; j++)
                checking_part_of_string += str[i+j];
            
            if (checking_part_of_string == separator)
            {
                if (word != "")
                {
                    output_vector.push_back(word);
                    word = "";
                }
            }
            else
            {
                word += str[i];
            }
        }

        // Также нужно добавить последнее слово после сепаратора
        if (word != "")
        {
            output_vector.push_back(word);
            word = "";
        }

        return output_vector;
    }

    std::string ResourceManager::get_directory_path(const std::string& path_to_file)
    {
        std::string directory_path = "";
        int index = path_to_file.find_last_of("/");
        for (int i = 0; i < index; i++)
            directory_path += path_to_file[i];
        
        return directory_path;
    }

    std::string ResourceManager::change_symbol(std::string& str, const char& src_symbol, const std::string& new_symbol)
    {
        std::string new_str = "";

        for (int i = 0; i < str.length(); i++)
        {
            if (str[i] == src_symbol)
                new_str += new_symbol;
            else
                new_str += str[i];
        }

        return new_str;
    }

    void ResourceManager::set_executable_path(const std::string& executable_path)
    {
        size_t found = executable_path.find_last_of("/\\");
        this->path_to_executable = executable_path.substr(0, found);
    }

    void ResourceManager::set_shaders_directory(const std::string& path)
    {
        this->shaders_directory = path;
    }

    void ResourceManager::set_textures_directory(const std::string& path)
    {
        this->textures_directory = path;
    }

    void ResourceManager::set_models_directory(const std::string& path)
    {
        this->models_directory = path;
    }
}
