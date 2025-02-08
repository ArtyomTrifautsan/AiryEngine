#pragma once


// Файлы движка
#include <AiryEngineCore/Physics/CollisionDetector.hpp>

#include <AiryEngineCore/Rendering/OpenGL/Model3D.hpp>

#include <AiryEngineCore/ResourceManager.hpp>

#include <AiryEngineCore/fps_keeper.hpp>

// #include "AiryEngineCore/Camera.hpp"


// Файлы игры
#include "game_object.hpp"


// Системные библиотеки
#include <memory>


class Car : public GameObject {
public:
    Car(const std::string& model_name,
        const std::string& model_path,
        const std::string& model_dir_path,
        std::shared_ptr<AiryEngine::ResourceManager> resource_manager);
    
    void handle_events();

    void update_moving_state();
    
    // bool go_right();
    // bool go_left();

private:
    void lateral_move(float step);
    void lateral_rotate(float angle_step);

    // Данные относятся  к движению машины вправо и влево
    float time_to_lateral_moving = 0.3f;    // За столько секунд машина сделает сдвиг в сторону
    int lateral_state = 0;      // 0 -- don't go, 1 -- go left, -1 -- go right
    int lateral_pos_on_the_road = 0;    // 0 -- center, 1 -- left, -1 -- right

    float lateral_offset = 2.0f;    // На столько машина сдвинется в сторону
    float current_lateral_offset = 0.0f;
    float lateral_speed = lateral_offset / time_to_lateral_moving;     // Шаг за секунду
    float lateral_steps_per_frame = lateral_speed / AiryEngine::FpsKeeper::get_fps();

    float lateral_rotate_angle = 30.0f;   // Угол поворота машины при движении вправо и влево
    float current_lateral_rotate_angle = 0.0f;
    float lateral_rotate_speed = lateral_rotate_angle / (0.5 * time_to_lateral_moving);     // Поворот за секунду
    float lateral_rotate_per_frame = lateral_rotate_speed / AiryEngine::FpsKeeper::get_fps();  // Поворот за кадр
    float lateral_rotate_direction = 0;     // 1 - в направлении поворота, -1 - обратно, 0 - не вращаемся
};



/*
steps_per_frame = Steps/Frames - ?
Steps/Seconds = lateral_speed   => Steps = lateral_speed * seconds
Frames/Seconds = FPS    => Frames = FPS * seconds
=> steps_per_frame = lateral_speed / FPS
*/