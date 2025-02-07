#include "barrier.hpp"


Barrier::Barrier(const std::string& model_name,
    const std::string& model_filename,
    const std::string& model_path_to_file,
    std::shared_ptr<AiryEngine::ResourceManager> resource_manager) : GameObject(model_name, 
                                                                                model_filename, 
                                                                                model_path_to_file,
                                                                                resource_manager)
{
    // this->model = resource_manager->load_model3D(model_name, model_filename, model_path_to_file);;
    // this->colliding_cube = std::make_shared<AiryEngine::CubeCollidingObject>();

    set_model_start_offset(glm::vec3(0, -0.503f, 0));
    // this->model_start_offset = glm::vec3(0, -0.503f, 0);
    // this->model->set_translate(
    //     this->model_start_offset.x, 
    //     this->model_start_offset.y, 
    //     this->model_start_offset.z
    // );

    set_model_start_scale(glm::vec3(0.270f, 0.270f, 0.270f));
    // this->model_start_scale = glm::vec3(0.270f, 0.270f, 0.270f);
    // this->model->set_scale(
    //     this->model_start_scale.x,
    //     this->model_start_scale.y,
    //     this->model_start_scale.z
    // );

    set_model_start_rotate(glm::vec3(0, 0, 0));
    // this->model_start_rotate = glm::vec3(0, 0, 0);
    // this->model->set_rotate(
    //     this->model_start_rotate.x,
    //     this->model_start_rotate.y, 
    //     this->model_start_rotate.z
    // );

    set_colliding_cube_start_offset(glm::vec3(0, 0.202f, 0));
    // this->colliding_cube_start_offset = glm::vec3(0, 0.202f, 0);
    // this->colliding_cube->set_translate(
    //     this->colliding_cube_start_offset.x,
    //     this->colliding_cube_start_offset.y,
    //     this->colliding_cube_start_offset.z
    // );

    set_colliding_cube_start_scale(glm::vec3(0.849f, 0.446f, 0.246f));
    // this->colliding_cube_start_scale = glm::vec3(0.849f, 0.446f, 0.246f);
    // this->colliding_cube->set_scale(
    //     this->colliding_cube_start_scale.x,
    //     this->colliding_cube_start_scale.y,
    //     this->colliding_cube_start_scale.z
    // );

    // this->position = glm::vec3(0, 0, 0);
    // this->scale = glm::vec3(0, 0, 0);
    // this->rotate = glm::vec3(0, 0, 0);
    // this->visible = true;
}
