#include "coin.hpp"


Coin::Coin(const std::string& model_name,
    const std::string& model_filename,
    const std::string& model_path_to_file,
    std::shared_ptr<AiryEngine::ResourceManager> resource_manager) : GameObject(model_name, 
                                                                                model_filename, 
                                                                                model_path_to_file,
                                                                                resource_manager)
{
    set_model_start_offset(glm::vec3(0, 0.305f, 0));

    set_model_start_scale(glm::vec3(0.300f, 0.300f, 0.300f));

    set_model_start_rotate(glm::vec3(0, 90, 0));

    set_colliding_cube_start_offset(glm::vec3(0, 0.410f, 0));

    set_colliding_cube_start_scale(glm::vec3(0.360f, 0.360f, 0.360f));
}