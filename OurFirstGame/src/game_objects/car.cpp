#include "car.hpp"


Car::Car(const std::string& model_name,
    const std::string& model_filename,
    const std::string& model_path_to_file,
    std::shared_ptr<AiryEngine::ResourceManager> resource_manager)
{
    this->model = resource_manager->load_model3D(model_name, model_filename, model_path_to_file);;

    this->colliding_cube = std::make_shared<AiryEngine::CubeCollidingObject>();

    this->model_start_offset = glm::vec3(10.101f, 0, 0 );
    this->model->set_translate(
        this->model_start_offset.x, 
        this->model_start_offset.y, 
        this->model_start_offset.z
    );

    this->model_start_scale = glm::vec3(1, 1, 1);
    this->model->set_scale(
        this->model_start_scale.x,
        this->model_start_scale.y,
        this->model_start_scale.z
    );

    this->model_start_rotate = glm::vec3(0, -90, 0);
    this->model->set_rotate(
        this->model_start_rotate.x,
        this->model_start_rotate.y, 
        this->model_start_rotate.z
    );

    this->colliding_cube_start_offset = glm::vec3( 0.006f, 0.282f, 0.529f );
    this->colliding_cube->set_translate(
        this->colliding_cube_start_offset.x,
        this->colliding_cube_start_offset.y,
        this->colliding_cube_start_offset.z
    );

    this->colliding_cube_start_scale = glm::vec3(0.873f, 0.497f, 1.781f);
    this->colliding_cube->set_scale(
        this->colliding_cube_start_scale.x,
        this->colliding_cube_start_scale.y,
        this->colliding_cube_start_scale.z
    );

    this->position = glm::vec3(0, 0, 0);
    this->scale = glm::vec3(0, 0, 0);
    this->rotate = glm::vec3(0, 0, 0);
    this->visible = true;
}


void Car::set_visible(bool visible)
{
    this->visible = visible;
}


void Car::set_position(glm::vec3 position)
{
    this->position = position;

    this->model->set_translate(
        this->model_start_offset.x + position.x, 
        this->model_start_offset.y + position.y, 
        this->model_start_offset.z + position.z
    );

    this->colliding_cube->set_translate(
        this->colliding_cube_start_offset.x + position.x,
        this->colliding_cube_start_offset.y + position.y,
        this->colliding_cube_start_offset.z + position.z
    );
}


void Car::set_position(float position_x, float position_y, float position_z)
{
    this->position = glm::vec3(position_x, position_y, position_z);

    this->model->set_translate(
        this->model_start_offset.x + position_x, 
        this->model_start_offset.y + position_y, 
        this->model_start_offset.z + position_z
    );

    this->colliding_cube->set_translate(
        this->colliding_cube_start_offset.x + position_x,
        this->colliding_cube_start_offset.y + position_y,
        this->colliding_cube_start_offset.z + position_z
    );
}


void Car::set_scale(glm::vec3 scale)
{
    this->scale = scale;

    this->model->set_scale(
        this->model_start_scale.x * scale.x,
        this->model_start_scale.y * scale.y,
        this->model_start_scale.z * scale.z
    );

    this->colliding_cube->set_scale(
        this->colliding_cube_start_scale.x * scale.x,
        this->colliding_cube_start_scale.y * scale.y,
        this->colliding_cube_start_scale.z * scale.z
    );
}


void Car::set_scale(float scale_x, float scale_y, float scale_z)
{
    this->scale = glm::vec3(scale_x, scale_y, scale_z);

    this->model->set_scale(
        this->model_start_scale.x * scale_x,
        this->model_start_scale.y * scale_y,
        this->model_start_scale.z * scale_z
    );

    this->colliding_cube->set_scale(
        this->colliding_cube_start_scale.x * scale_x,
        this->colliding_cube_start_scale.y * scale_y,
        this->colliding_cube_start_scale.z * scale_z
    );
}


void Car::set_rotate(glm::vec3 rotate)
{
    this->rotate = rotate;

    this->model->set_rotate(
        this->model_start_rotate.x + rotate.x,
        this->model_start_rotate.y + rotate.y,
        this->model_start_rotate.z + rotate.z
    );
}


void Car::set_rotate(float rotate_x, float rotate_y, float rotate_z)
{
    this->rotate = glm::vec3(rotate_x, rotate_y, rotate_z);

    this->model->set_rotate(
        this->model_start_rotate.x + rotate_x,
        this->model_start_rotate.y + rotate_y,
        this->model_start_rotate.z + rotate_z
    );
}