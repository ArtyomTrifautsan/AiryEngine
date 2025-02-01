#include "game_round.hpp"


#include <iostream>


void GameRound::start(std::shared_ptr<AiryEngine::ResourceManager> resource_manager)
{
    // std::cout << "GameRound::start start" << std::endl;

    this->colliding_cube_model3D = resource_manager->create_collision_cube_model("Cube1", "Cube.obj", "CubeCollideModel");
    this->colliding_sphere_model3D = resource_manager->create_collision_cube_model("sphere", "sphere.obj", "SphereCollideModel");

    create_car(resource_manager);
    create_road(resource_manager);
    create_barrier(resource_manager);
    create_coin(resource_manager);
    create_fuel_canister(resource_manager);

    // std::cout << "GameRound::start finish" << std::endl;
}


void GameRound::create_car(std::shared_ptr<AiryEngine::ResourceManager> resource_manager)
{
    // std::cout << "GameRound::create_car start" << std::endl;
    this->car_model = resource_manager->load_model3D("CarModel", "SportCar.obj", "FunnyRider/SportCar");
    this->car_colliding_cube = std::make_shared<AiryEngine::CubeCollidingObject>();

    this->car_model->set_rotate(0, -90, 0);

    this->car_model_start_offset = glm::vec3(10.101f, 0, 0 );
    this->car_colliding_cube_start_offset = glm::vec3( 0.006f, 0.282f, 0.529f );
    this->car_colliding_cube_start_scale = glm::vec3(0.873f, 0.497f, 1.781f);
    this->car_model->set_translate(
        this->car_model_start_offset.x, 
        this->car_model_start_offset.y, 
        this->car_model_start_offset.z
    );
    this->car_colliding_cube->set_translate(
        this->car_colliding_cube_start_offset.x,
        this->car_colliding_cube_start_offset.y,
        this->car_colliding_cube_start_offset.z
    );
    this->car_colliding_cube->set_scale(
        this->car_colliding_cube_start_scale.x,
        this->car_colliding_cube_start_scale.y,
        this->car_colliding_cube_start_scale.z
    );

    // std::cout << "GameRound::create_car finish" << std::endl;
}


void GameRound::create_road(std::shared_ptr<AiryEngine::ResourceManager> resource_manager)
{
    this->road_model = resource_manager->load_model3D("RoadModel", "WayOne.obj", "FunnyRider/Road");
    this->road_colliding_cube = std::make_shared<AiryEngine::CubeCollidingObject>();

    this->road_model_start_offset = glm::vec3(0, -0.302f, 0);
    this->road_model_start_scale = glm::vec3(0.708f, 0.708f, 0.708f);
    this->road_colliding_cube_start_offset = glm::vec3(0, -0.620f, -0.753f);
    this->road_colliding_cube_start_scale = glm::vec3(3.569f, 0.395f, 4.317f);
    this->road_model->set_translate(
        this->road_model_start_offset.x, 
        this->road_model_start_offset.y, 
        this->road_model_start_offset.z
    );
    this->road_model->set_scale(
        this->road_model_start_scale.x,
        this->road_model_start_scale.y,
        this->road_model_start_scale.z
    );
    this->road_colliding_cube->set_translate(
        this->road_colliding_cube_start_offset.x,
        this->road_colliding_cube_start_offset.y,
        this->road_colliding_cube_start_offset.z
    );
    this->road_colliding_cube->set_scale(
        this->road_colliding_cube_start_scale.x,
        this->road_colliding_cube_start_scale.y,
        this->road_colliding_cube_start_scale.z
    );
}


void GameRound::create_barrier(std::shared_ptr<AiryEngine::ResourceManager> resource_manager)
{
    this->barrier_model = resource_manager->load_model3D("BarrierModel", "Pregrados.obj", "FunnyRider/Pregrados");
    this->barrier_colliding_cube = std::make_shared<AiryEngine::CubeCollidingObject>();

    this->barrier_model_start_offset = glm::vec3(0, -0.503f, 0);
    this->barrier_model_start_scale = glm::vec3(0.270f, 0.270f, 0.270f);
    this->barrier_colliding_cube_start_offset = glm::vec3(0, 0.202f, 0);
    this->barrier_colliding_cube_start_scale = glm::vec3(0.849f, 0.446f, 0.246f);
    this->barrier_model->set_translate(
        this->barrier_model_start_offset.x, 
        this->barrier_model_start_offset.y, 
        this->barrier_model_start_offset.z
    );
    this->barrier_model->set_scale(
        this->barrier_model_start_scale.x,
        this->barrier_model_start_scale.y,
        this->barrier_model_start_scale.z
    );
    this->barrier_colliding_cube->set_translate(
        this->barrier_colliding_cube_start_offset.x,
        this->barrier_colliding_cube_start_offset.y,
        this->barrier_colliding_cube_start_offset.z
    );
    this->barrier_colliding_cube->set_scale(
        this->barrier_colliding_cube_start_scale.x,
        this->barrier_colliding_cube_start_scale.y,
        this->barrier_colliding_cube_start_scale.z
    );
}


void GameRound::create_coin(std::shared_ptr<AiryEngine::ResourceManager> resource_manager)
{
    this->coin_model = resource_manager->load_model3D("CoinModel", "Monetka.obj", "FunnyRider/Coin");
    this->coin_colliding_cube = std::make_shared<AiryEngine::CubeCollidingObject>();

    this->coin_model->set_rotate(0, 90, 0);

    this->coin_model_start_offset = glm::vec3(-2.821f, 0.302f, 0);
    this->coin_model_start_scale = glm::vec3(0.300f, 0.300f, 0.300f);
    this->coin_colliding_cube_start_offset = glm::vec3(-0.025f, 0.400f, 0);
    this->coin_colliding_cube_start_scale = glm::vec3(00.360f, 0.360f, 0.360f);
    this->coin_model->set_translate(
        this->coin_model_start_offset.x, 
        this->coin_model_start_offset.y, 
        this->coin_model_start_offset.z
    );
    this->coin_model->set_scale(
        this->coin_model_start_scale.x,
        this->coin_model_start_scale.y,
        this->coin_model_start_scale.z
    );
    this->coin_colliding_cube->set_translate(
        this->coin_colliding_cube_start_offset.x,
        this->coin_colliding_cube_start_offset.y,
        this->coin_colliding_cube_start_offset.z
    );
    this->coin_colliding_cube->set_scale(
        this->coin_colliding_cube_start_scale.x,
        this->coin_colliding_cube_start_scale.y,
        this->coin_colliding_cube_start_scale.z
    );
}


void GameRound::create_fuel_canister(std::shared_ptr<AiryEngine::ResourceManager> resource_manager)
{
    this->fuel_canister_model = resource_manager->load_model3D("FuelCanisterModel", "Kanistra.obj", "FunnyRider/Canister");
    this->fuel_canister_colliding_cube = std::make_shared<AiryEngine::CubeCollidingObject>();

    this->fuel_canister_model_start_offset = glm::vec3(0, 0.202, 0);
    this->fuel_canister_model_start_scale = glm::vec3(0.120f, 0.120f, 0.120f);
    this->fuel_canister_colliding_cube_start_offset = glm::vec3(0, 0.404, 0);
    this->fuel_canister_colliding_cube_start_scale = glm::vec3(0.320f, 0.537f, 0.321f);
    this->fuel_canister_model->set_translate(
        this->fuel_canister_model_start_offset.x, 
        this->fuel_canister_model_start_offset.y, 
        this->fuel_canister_model_start_offset.z
    );
    this->fuel_canister_model->set_scale(
        this->fuel_canister_model_start_scale.x,
        this->fuel_canister_model_start_scale.y,
        this->fuel_canister_model_start_scale.z
    );
    this->fuel_canister_colliding_cube->set_translate(
        this->fuel_canister_colliding_cube_start_offset.x,
        this->fuel_canister_colliding_cube_start_offset.y,
        this->fuel_canister_colliding_cube_start_offset.z
    );
    this->fuel_canister_colliding_cube->set_scale(
        this->fuel_canister_colliding_cube_start_scale.x,
        this->fuel_canister_colliding_cube_start_scale.y,
        this->fuel_canister_colliding_cube_start_scale.z
    );
}



void GameRound::render_game_objects(std::shared_ptr<AiryEngine::Renderer> renderer, AiryEngine::Camera& camera)
{
    // std::cout << "GameRound::render_game_objects start" << std::endl;
    render_car(renderer, camera);
    render_road(renderer, camera);
    render_barrier(renderer, camera);
    render_coin(renderer, camera);
    render_fuel_canister(renderer, camera);
    // std::cout << "GameRound::render_game_objects finish" << std::endl;
}


void GameRound::render_car(std::shared_ptr<AiryEngine::Renderer> renderer, AiryEngine::Camera& camera)
{
    // std::cout << "GameRound::render_car start" << std::endl;
    if (!this->visible_car)
        return;

    renderer->render_model3D(camera, this->car_model);

    if (!this->visible_colliding_objects)
        return;

    if (this->car_colliding_cube->get_is_collided()) this->colliding_cube_model3D->set_diffuse_color(1.0f, 0.0f, 0.0f);
    else this->colliding_cube_model3D->set_diffuse_color(0.0f, 1.0f, 0.0f);
    glm::vec3 cube_pos = this->car_colliding_cube->get_translate();
    this->colliding_cube_model3D->set_translate(cube_pos.x, cube_pos.y, cube_pos.z);
    glm::vec3 cube_scale = this->car_colliding_cube->get_scale();
    this->colliding_cube_model3D->set_scale(cube_scale.x, cube_scale.y, cube_scale.z);
    renderer->render_collision_model(camera, this->colliding_cube_model3D);

    // std::cout << "GameRound::render_car finish" << std::endl;
}


void GameRound::render_road(std::shared_ptr<AiryEngine::Renderer> renderer, AiryEngine::Camera& camera)
{
    if (!this->visible_road)
        return;

    renderer->render_model3D(camera, this->road_model);

    if (!this->visible_colliding_objects)
        return;

    if (this->road_colliding_cube->get_is_collided()) this->colliding_cube_model3D->set_diffuse_color(1.0f, 0.0f, 0.0f);
    else this->colliding_cube_model3D->set_diffuse_color(0.0f, 1.0f, 0.0f);
    glm::vec3 cube_pos = this->road_colliding_cube->get_translate();
    this->colliding_cube_model3D->set_translate(cube_pos.x, cube_pos.y, cube_pos.z);
    glm::vec3 cube_scale = this->road_colliding_cube->get_scale();
    this->colliding_cube_model3D->set_scale(cube_scale.x, cube_scale.y, cube_scale.z);
    renderer->render_collision_model(camera, this->colliding_cube_model3D);
}


void GameRound::render_barrier(std::shared_ptr<AiryEngine::Renderer> renderer, AiryEngine::Camera& camera)
{
    if (!this->visible_barrier)
        return;

    renderer->render_model3D(camera, this->barrier_model);

    if (!this->visible_colliding_objects)
        return;

    if (this->barrier_colliding_cube->get_is_collided()) this->colliding_cube_model3D->set_diffuse_color(1.0f, 0.0f, 0.0f);
    else this->colliding_cube_model3D->set_diffuse_color(0.0f, 1.0f, 0.0f);
    glm::vec3 cube_pos = this->barrier_colliding_cube->get_translate();
    this->colliding_cube_model3D->set_translate(cube_pos.x, cube_pos.y, cube_pos.z);
    glm::vec3 cube_scale = this->barrier_colliding_cube->get_scale();
    this->colliding_cube_model3D->set_scale(cube_scale.x, cube_scale.y, cube_scale.z);
    renderer->render_collision_model(camera, this->colliding_cube_model3D);
}


void GameRound::render_coin(std::shared_ptr<AiryEngine::Renderer> renderer, AiryEngine::Camera& camera)
{
    if (!this->visible_coin)
        return;

    renderer->render_model3D(camera, this->coin_model);

    if (!this->visible_colliding_objects)
        return;

    if (this->coin_colliding_cube->get_is_collided()) this->colliding_cube_model3D->set_diffuse_color(1.0f, 0.0f, 0.0f);
    else this->colliding_cube_model3D->set_diffuse_color(0.0f, 1.0f, 0.0f);
    glm::vec3 cube_pos = this->coin_colliding_cube->get_translate();
    this->colliding_cube_model3D->set_translate(cube_pos.x, cube_pos.y, cube_pos.z);
    glm::vec3 cube_scale = this->coin_colliding_cube->get_scale();
    this->colliding_cube_model3D->set_scale(cube_scale.x, cube_scale.y, cube_scale.z);
    renderer->render_collision_model(camera, this->colliding_cube_model3D);
}


void GameRound::render_fuel_canister(std::shared_ptr<AiryEngine::Renderer> renderer, AiryEngine::Camera& camera)
{
    if (!this->visible_fuel_canister)
        return;

    renderer->render_model3D(camera, this->fuel_canister_model);

    if (!this->visible_colliding_objects)
        return;

    if (this->fuel_canister_colliding_cube->get_is_collided()) this->colliding_cube_model3D->set_diffuse_color(1.0f, 0.0f, 0.0f);
    else this->colliding_cube_model3D->set_diffuse_color(0.0f, 1.0f, 0.0f);
    glm::vec3 cube_pos = this->fuel_canister_colliding_cube->get_translate();
    this->colliding_cube_model3D->set_translate(cube_pos.x, cube_pos.y, cube_pos.z);
    glm::vec3 cube_scale = this->fuel_canister_colliding_cube->get_scale();
    this->colliding_cube_model3D->set_scale(cube_scale.x, cube_scale.y, cube_scale.z);
    renderer->render_collision_model(camera, this->colliding_cube_model3D);
}



void GameRound::set_visible_colliding_objects(bool visible_colliding_objects)
{
    this->visible_colliding_objects = visible_colliding_objects;
}


void GameRound::set_translate_car(glm::vec3 model_translate, glm::vec3 colliding_cube_translate)
{
    this->car_model->set_translate(model_translate.x, model_translate.y, model_translate.z);
    this->car_colliding_cube->set_translate(colliding_cube_translate.x, colliding_cube_translate.y, colliding_cube_translate.z);
}


void GameRound::set_scale_car(glm::vec3 model_scale, glm::vec3 colliding_cube_scale)
{
    this->car_model->set_scale(model_scale.x, model_scale.y, model_scale.z);
    this->car_colliding_cube->set_scale(colliding_cube_scale);
}


void GameRound::set_translate_road(glm::vec3 model_translate, glm::vec3 colliding_cube_translate)
{
    this->road_model->set_translate(model_translate.x, model_translate.y, model_translate.z);
    this->road_colliding_cube->set_translate(colliding_cube_translate);
}


void GameRound::set_scale_road(glm::vec3 model_scale, glm::vec3 colliding_cube_scale)
{
    this->road_model->set_scale(model_scale.x, model_scale.y, model_scale.z);
    this->road_colliding_cube->set_scale(colliding_cube_scale);
}


void GameRound::set_translate_barrier(glm::vec3 model_translate, glm::vec3 colliding_cube_translate)
{
    this->barrier_model->set_translate(model_translate.x, model_translate.y, model_translate.z);
    this->barrier_colliding_cube->set_translate(colliding_cube_translate);
}


void GameRound::set_scale_barrier(glm::vec3 model_scale, glm::vec3 colliding_cube_scale)
{
    this->barrier_model->set_scale(model_scale.x, model_scale.y, model_scale.z);
    this->barrier_colliding_cube->set_scale(colliding_cube_scale);
}


void GameRound::set_translate_coin(glm::vec3 model_translate, glm::vec3 colliding_cube_translate)
{
    this->coin_model->set_translate(model_translate.x, model_translate.y, model_translate.z);
    this->coin_colliding_cube->set_translate(colliding_cube_translate);
}


void GameRound::set_scale_coin(glm::vec3 model_scale, glm::vec3 colliding_cube_scale)
{
    this->coin_model->set_scale(model_scale.x, model_scale.y, model_scale.z);
    this->coin_colliding_cube->set_scale(colliding_cube_scale);
}


void GameRound::set_translate_fuel_canister(glm::vec3 model_translate, glm::vec3 colliding_cube_translate)
{
    this->fuel_canister_model->set_translate(model_translate.x, model_translate.y, model_translate.z);
    this->fuel_canister_colliding_cube->set_translate(colliding_cube_translate);
}


void GameRound::set_scale_fuel_canister(glm::vec3 model_scale, glm::vec3 colliding_cube_scale)
{
    this->fuel_canister_model->set_scale(model_scale.x, model_scale.y, model_scale.z);
    this->fuel_canister_colliding_cube->set_scale(colliding_cube_scale);
}


void GameRound::set_visible_car(bool visible_car)
{
    this->visible_car = visible_car;
}


void GameRound::set_visible_road(bool visible_road)
{
    this->visible_road = visible_road;
}


void GameRound::set_visible_barrier(bool visible_barrier)
{
    this->visible_barrier = visible_barrier;
}


void GameRound::set_visible_coin(bool visible_coin)
{
    this->visible_coin = visible_coin;
}


void GameRound::set_visible_fuel_canister(bool visible_fuel_canister)
{
    this->visible_fuel_canister = visible_fuel_canister;
}

