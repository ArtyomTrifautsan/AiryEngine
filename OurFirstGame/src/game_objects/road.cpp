#include "road.hpp"

#include <iostream>



Road::Road(const std::string& model_name,
    const std::string& model_filename,
    const std::string& model_path_to_file,
    std::shared_ptr<AiryEngine::ResourceManager> resource_manager) : GameObject(model_name, 
                                                                                model_filename, 
                                                                                model_path_to_file,
                                                                                resource_manager)
{
    set_model_start_offset(glm::vec3(0, -0.302f, 0));

    set_model_start_scale(glm::vec3(0.708f, 0.708f, 0.708f));

    set_model_start_rotate(glm::vec3(0, 0, 0));

    set_colliding_cube_start_offset(glm::vec3(0, -0.620f, -0.753f));

    set_colliding_cube_start_scale(glm::vec3(3.569f, 0.395f, 4.317f));
}
