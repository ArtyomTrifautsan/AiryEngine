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


class GameRound {
public:
    GameRound(std::shared_ptr<AiryEngine::ResourceManager> resource_manager);

    std::shared_ptr<Car> get_car() const { return this->car; }
    std::shared_ptr<Road> get_road() const { return this->road; }
    std::shared_ptr<Barrier> get_barrier() const { return this->barrier; }
    std::shared_ptr<Coin> get_coin() const { return this->coin; }
    std::shared_ptr<FuelCanister> get_fuel_canister() const { return this->fuel_canister; }

private:
    std::shared_ptr<Car> car;
    std::shared_ptr<Road> road;
    std::shared_ptr<Barrier> barrier;
    std::shared_ptr<Coin> coin;
    std::shared_ptr<FuelCanister> fuel_canister;
};