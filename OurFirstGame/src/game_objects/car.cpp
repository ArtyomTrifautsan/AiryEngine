#include "car.hpp"


#include <AiryEngineCore/Input.hpp>


#include <iostream>


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

    set_model_start_rotate(glm::vec3(0, -90, 0));

    set_colliding_cube_start_offset(glm::vec3(-0.277f, 0.277f, 0.528f));

    set_colliding_cube_start_scale(glm::vec3(0.873f, 0.497f, 1.781f));
}


void Car::update_moving_state()
{
    /*
    Так как эта функция вызывается каждый кадр, мы сдвигаем машину на покадровую скорость
    (на длину шага за один кадр - lateral_steps_per_frame)
    */
    if (this->lateral_state == 1)
    {
        lateral_move(this->lateral_steps_per_frame);

        lateral_rotate(this->lateral_rotate_per_frame);
    }
    else if (this->lateral_state == -1)
    {
        lateral_move(-this->lateral_steps_per_frame);

        lateral_rotate(-this->lateral_rotate_per_frame);
    }

    if (this->current_lateral_offset <= -this->lateral_offset)
    {
        // Закончилось движение влево

        this->current_lateral_offset = 0;
        this->lateral_state = 0;
    }

    if (this->current_lateral_offset >= this->lateral_offset)
    {
        // Закончилось движение вправо

        this->current_lateral_offset = 0;
        this->lateral_state = 0;
    }
}


void Car::lateral_move(float step)
{
    glm::vec3 pos = get_position();
    set_position(
        pos.x + step,
        pos.y,
        pos.z
    );
    this->current_lateral_offset += step;
}


void Car::lateral_rotate(float angle_step)
{
    // Поворот машины
    // std::cout << "Повороты." << std::endl;
    // std::cout << "lateral_rotate_angle: " << this->lateral_rotate_angle << std::endl;
    // std::cout << "current_lateral_rotate_angle: " << this->current_lateral_rotate_angle << std::endl;
    // std::cout << "lateral_rotate_per_frame: " << this->lateral_rotate_per_frame << std::endl;
    // std::cout << "lateral_rotate_direction: " << this->lateral_rotate_direction << std::endl;

    glm::vec3 rot = get_rotate();
    set_rotate(
        rot.x,
        rot.y + angle_step * this->lateral_rotate_direction,
        rot.z
    );
    this->current_lateral_rotate_angle += angle_step * this->lateral_rotate_direction;

    if (this->current_lateral_rotate_angle >= this->lateral_rotate_angle)
    {
        this->current_lateral_rotate_angle = this->lateral_rotate_angle;
        if (this->lateral_rotate_direction == 1)
        {
            // Меняем направление вращения
            this->lateral_rotate_direction = -1;
        }
        else if (this->lateral_rotate_direction == -1)
        {
            // Заканчиваем вращение
            this->lateral_rotate_direction = 0;
            this->current_lateral_rotate_angle = 0.0f;
        }
    }

    if (this->current_lateral_rotate_angle <= -this->lateral_rotate_angle)
    {
        this->current_lateral_rotate_angle = -this->lateral_rotate_angle;
        if (this->lateral_rotate_direction == 1)
        {
            // Меняем направление вращения
            this->lateral_rotate_direction = -1;
        }
        else if (this->lateral_rotate_direction == -1)
        {
            // Заканчиваем вращение
            this->lateral_rotate_direction = 0;
            this->current_lateral_rotate_angle = 0.0f;
        }
    }
}


void Car::handle_events()
{
    // Rotation Left
    if (AiryEngine::Input::IsKeyPressed(AiryEngine::KeyCode::KEY_LEFT))
    {
        // std::cout << "KEY_LEFT pressed" << std::endl;
        if ((this->lateral_pos_on_the_road < 1) && (this->lateral_state == 0))
        {
            this->lateral_pos_on_the_road++;
            this->lateral_state = 1;
            this->lateral_rotate_direction = 1;
        }
    }

    // Rotation Right
    if (AiryEngine::Input::IsKeyPressed(AiryEngine::KeyCode::KEY_RIGHT))
    {
        if ((this->lateral_pos_on_the_road > -1) && (this->lateral_state == 0))
        {
            this->lateral_pos_on_the_road--;
            this->lateral_state = -1;
            this->lateral_rotate_direction = 1;
        }
    }
}