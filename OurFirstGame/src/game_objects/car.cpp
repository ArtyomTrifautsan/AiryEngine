#include "car.hpp"


Car::Car(const std::string& model_name,
    const std::string& model_filename,
    const std::string& model_path_to_file,
    std::shared_ptr<AiryEngine::ResourceManager> resource_manager) : GameObject(model_name, 
                                                                                model_filename, 
                                                                                model_path_to_file,
                                                                                resource_manager)
{
    set_model_start_offset(glm::vec3(0, 0, 0 ));

    set_model_start_scale(glm::vec3(1, 1, 1));

    set_colliding_cube_start_offset(glm::vec3( -0.277f, 0.277f, 0.528f ));

    set_colliding_cube_start_scale(glm::vec3(0.873f, 0.497f, 1.781f));
}