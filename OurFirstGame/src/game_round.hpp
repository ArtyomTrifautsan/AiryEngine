/*

Класс GameRound занимается игровой логикой:
1) Взаимодейтсвие игровых объектов;
2) Поведение отдельных объектов;

Класс GameRound НЕ занимается:
1) Отрисовкой игровых объектов

*/


#pragma once

// Файлы движка
#include <AiryEngineCore/Physics/CollisionDetector.hpp>

#include <AiryEngineCore/Rendering/OpenGL/Model3D.hpp>

#include <AiryEngineCore/ResourceManager.hpp>
#include <AiryEngineCore/Renderer.hpp>
#include "AiryEngineCore/Camera.hpp"


// Файлы игры
#include "game_objects/car.hpp"
#include "game_objects/road.hpp"
#include "game_objects/barrier.hpp"
#include "game_objects/coin.hpp"
#include "game_objects/fuel_canister.hpp"


// Системные библиотеки
#include <memory>
#include <string>
#include <vector>

// Нужны для таймера
#include <chrono>
#include <thread>


class GameRound {
public:
    GameRound(std::shared_ptr<AiryEngine::ResourceManager> resource_manager);

    void set_start_pos();

    void update_game_round();

    void check_barrier_collision();
    void check_coins_collision();
    void check_fuel_canister_collision();

    std::shared_ptr<Car> get_car() const { return this->car; }
    // std::shared_ptr<Road> get_road() const { return this->road; }
    std::shared_ptr<std::vector<std::shared_ptr<Road>>> get_roads() const { return this->roads; }

    // std::shared_ptr<Barrier> get_barrier() const { return this->barrier; }
    std::shared_ptr<std::vector<std::shared_ptr<Barrier>>> get_barriers() const { return this->barriers; }

    // std::shared_ptr<Coin> get_coin() const { return this->coin; }
    std::shared_ptr<std::vector<std::shared_ptr<Coin>>> get_coins() const { return this->coins; }
    std::shared_ptr<FuelCanister> get_fuel_canister() const { return this->fuel_canister; }

private:
    void move_back_game_objects();
    void rotate_coins_and_fuel_canister();
    void drive_car();

    void create_car(std::shared_ptr<AiryEngine::ResourceManager> resource_manager);
    void create_roads(std::shared_ptr<AiryEngine::ResourceManager> resource_manager);
    void create_barriers(std::shared_ptr<AiryEngine::ResourceManager> resource_manager);
    void create_coins(std::shared_ptr<AiryEngine::ResourceManager> resource_manager);
    void create_fuel_canister(std::shared_ptr<AiryEngine::ResourceManager> resource_manager);

    void set_car_start_pos();
    void set_roads_start_pos();
    void set_barriers_start_pos();
    void set_coins_start_pos();
    void set_fuel_canister_pos();

    void move_back_roads();
    void move_back_barriers();
    void move_back_coins();
    void move_back_fuel_canister();

    std::shared_ptr<Car> car;
    // std::shared_ptr<Road> road;
    int number_of_roads = 10;
    std::shared_ptr<std::vector<std::shared_ptr<Road>>> roads;

    // std::shared_ptr<Barrier> barrier;
    int number_of_barriers = 10;
    std::shared_ptr<std::vector<std::shared_ptr<Barrier>>> barriers;

    // std::shared_ptr<Coin> coin;
    int number_of_coins = 10;
    std::shared_ptr<std::vector<std::shared_ptr<Coin>>> coins;

    std::shared_ptr<FuelCanister> fuel_canister;

    float road_offset = 4.317f * 2 - 0.1f;
    float game_objects_step = 0.1f;

    float rotate_delta_angle = 1.0f;
};