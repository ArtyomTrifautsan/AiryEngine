#pragma once 

// Файлы движка
#include <AiryEngineCore/Physics/CollisionDetector.hpp>

#include <AiryEngineCore/Rendering/OpenGL/Model3D.hpp>

#include <AiryEngineCore/ResourceManager.hpp>
#include <AiryEngineCore/Renderer.hpp>
#include "AiryEngineCore/Camera.hpp"


// Файлы игры
// #include "game_round.hpp"
#include "game_objects/car.hpp"
#include "game_objects/road.hpp"
#include "game_objects/barrier.hpp"
#include "game_objects/coin.hpp"
#include "game_objects/fuel_canister.hpp"


// Системные библиотеки
#include <memory>
#include <string>


class GameObjectRenderer {
public:
    GameObjectRenderer(std::shared_ptr<AiryEngine::Renderer> renderer, 
                        std::shared_ptr<AiryEngine::Camera> camera, 
                        std::shared_ptr<AiryEngine::ResourceManager> resource_manager);

    void set_visible_colliding_objects(bool visible_colliding_objects);
    bool get_visible_colliding_objects() const { return this->visible_colliding_objects; }

    void render_car(std::shared_ptr<Car> car);

    void render_road(std::shared_ptr<Road> road);
    void render_roads(std::shared_ptr<std::vector<std::shared_ptr<Road>>> roads);

    void render_barrier(std::shared_ptr<Barrier> barrier);
    void render_barriers(std::shared_ptr<std::vector<std::shared_ptr<Barrier>>> barriers);

    void render_coin(std::shared_ptr<Coin> coin);
    void render_coins(std::shared_ptr<std::vector<std::shared_ptr<Coin>>> coins);

    void render_fuel_canister(std::shared_ptr<FuelCanister> fuel_canister);

private:
    std::shared_ptr<AiryEngine::Renderer> renderer;
    std::shared_ptr<AiryEngine::Camera> camera;

    std::shared_ptr<AiryEngine::Model3D> colliding_cube_model3D;
    std::shared_ptr<AiryEngine::Model3D> colliding_sphere_model3D;

    bool visible_colliding_objects;
};