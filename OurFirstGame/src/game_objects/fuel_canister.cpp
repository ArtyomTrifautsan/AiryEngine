#include "fuel_canister.hpp"


FuelCanister::FuelCanister(const std::string& model_name,
    const std::string& model_filename,
    const std::string& model_path_to_file,
    std::shared_ptr<AiryEngine::ResourceManager> resource_manager) : GameObject(model_name, 
                                                                                model_filename, 
                                                                                model_path_to_file,
                                                                                resource_manager)
{
    set_model_start_offset(glm::vec3(0, 0.202, 0));

    set_model_start_scale(glm::vec3(0.120f, 0.120f, 0.120f));

    set_model_start_rotate(glm::vec3(0, 0, 0));

    set_colliding_cube_start_offset(glm::vec3(0, 0.404f, 0));

    set_colliding_cube_start_scale(glm::vec3(0.320f, 0.537f, 0.321f));
}