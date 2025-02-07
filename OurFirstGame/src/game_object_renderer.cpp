#include "game_object_renderer.hpp"


GameObjectRenderer::GameObjectRenderer(std::shared_ptr<AiryEngine::Renderer> renderer, 
                                        std::shared_ptr<AiryEngine::Camera> camera, 
                                        std::shared_ptr<AiryEngine::ResourceManager> resource_manager)
{
    this->renderer = renderer;
    this->camera = camera;

    this->colliding_cube_model3D = resource_manager->create_collision_cube_model("Cube1", "Cube.obj", "CubeCollideModel");
    this->colliding_sphere_model3D = resource_manager->create_collision_cube_model("sphere", "sphere.obj", "SphereCollideModel");

    this->visible_colliding_objects = true;
}


void GameObjectRenderer::render_car(std::shared_ptr<Car> car)
{
    if (!car->get_visible())
        return;

    car->update_pos_and_scale();

    renderer->render_model3D(*camera, car->get_model());

    if (!this->visible_colliding_objects)
        return;

    if (car->get_colliding_cube()->get_is_collided()) this->colliding_cube_model3D->set_diffuse_color(1.0f, 0.0f, 0.0f);
    else this->colliding_cube_model3D->set_diffuse_color(0.0f, 1.0f, 0.0f);
    glm::vec3 cube_pos = car->get_colliding_cube()->get_translate();
    this->colliding_cube_model3D->set_translate(cube_pos.x, cube_pos.y, cube_pos.z);
    glm::vec3 cube_scale = car->get_colliding_cube()->get_scale();
    this->colliding_cube_model3D->set_scale(cube_scale.x, cube_scale.y, cube_scale.z);
    renderer->render_collision_model(*camera, this->colliding_cube_model3D);
}


void GameObjectRenderer::render_road(std::shared_ptr<Road> road)
{
    if (!road->get_visible())
        return;

    road->update_pos_and_scale();

    renderer->render_model3D(*camera, road->get_model());

    if (!this->visible_colliding_objects)
        return;

    if (road->get_colliding_cube()->get_is_collided()) this->colliding_cube_model3D->set_diffuse_color(1.0f, 0.0f, 0.0f);
    else this->colliding_cube_model3D->set_diffuse_color(0.0f, 1.0f, 0.0f);
    glm::vec3 cube_pos = road->get_colliding_cube()->get_translate();
    this->colliding_cube_model3D->set_translate(cube_pos.x, cube_pos.y, cube_pos.z);
    glm::vec3 cube_scale = road->get_colliding_cube()->get_scale();
    this->colliding_cube_model3D->set_scale(cube_scale.x, cube_scale.y, cube_scale.z);
    renderer->render_collision_model(*camera, this->colliding_cube_model3D);
}


void GameObjectRenderer::render_roads(std::shared_ptr<std::vector<std::shared_ptr<Road>>> roads)
{
    for (std::shared_ptr<Road> curr_road : *roads)
    {
        render_road(curr_road);
    }
}


void GameObjectRenderer::render_barrier(std::shared_ptr<Barrier> barrier)
{
    if (!barrier->get_visible())
        return;

    barrier->update_pos_and_scale();

    renderer->render_model3D(*camera, barrier->get_model());

    if (!this->visible_colliding_objects)
        return;

    if (barrier->get_colliding_cube()->get_is_collided()) this->colliding_cube_model3D->set_diffuse_color(1.0f, 0.0f, 0.0f);
    else this->colliding_cube_model3D->set_diffuse_color(0.0f, 1.0f, 0.0f);
    glm::vec3 cube_pos = barrier->get_colliding_cube()->get_translate();
    this->colliding_cube_model3D->set_translate(cube_pos.x, cube_pos.y, cube_pos.z);
    glm::vec3 cube_scale = barrier->get_colliding_cube()->get_scale();
    this->colliding_cube_model3D->set_scale(cube_scale.x, cube_scale.y, cube_scale.z);
    renderer->render_collision_model(*camera, this->colliding_cube_model3D);
}


void GameObjectRenderer::render_coin(std::shared_ptr<Coin> coin)
{
    if (!coin->get_visible())
        return;

    coin->update_pos_and_scale();

    renderer->render_model3D(*camera, coin->get_model());

    if (!this->visible_colliding_objects)
        return;

    if (coin->get_colliding_cube()->get_is_collided()) this->colliding_cube_model3D->set_diffuse_color(1.0f, 0.0f, 0.0f);
    else this->colliding_cube_model3D->set_diffuse_color(0.0f, 1.0f, 0.0f);
    glm::vec3 cube_pos = coin->get_colliding_cube()->get_translate();
    this->colliding_cube_model3D->set_translate(cube_pos.x, cube_pos.y, cube_pos.z);
    glm::vec3 cube_scale = coin->get_colliding_cube()->get_scale();
    this->colliding_cube_model3D->set_scale(cube_scale.x, cube_scale.y, cube_scale.z);
    renderer->render_collision_model(*camera, this->colliding_cube_model3D);
}


void GameObjectRenderer::render_fuel_canister(std::shared_ptr<FuelCanister> fuel_canister)
{
    if (!fuel_canister->get_visible())
        return;

    fuel_canister->update_pos_and_scale();

    renderer->render_model3D(*camera, fuel_canister->get_model());

    if (!this->visible_colliding_objects)
        return;

    if (fuel_canister->get_colliding_cube()->get_is_collided()) this->colliding_cube_model3D->set_diffuse_color(1.0f, 0.0f, 0.0f);
    else this->colliding_cube_model3D->set_diffuse_color(0.0f, 1.0f, 0.0f);
    glm::vec3 cube_pos = fuel_canister->get_colliding_cube()->get_translate();
    this->colliding_cube_model3D->set_translate(cube_pos.x, cube_pos.y, cube_pos.z);
    glm::vec3 cube_scale = fuel_canister->get_colliding_cube()->get_scale();
    this->colliding_cube_model3D->set_scale(cube_scale.x, cube_scale.y, cube_scale.z);
    renderer->render_collision_model(*camera, this->colliding_cube_model3D);
}


void GameObjectRenderer::set_visible_colliding_objects(bool visible_colliding_objects)
{
    this->visible_colliding_objects = visible_colliding_objects;
}