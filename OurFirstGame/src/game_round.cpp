#include "game_round.hpp"


#include <iostream>


GameRound::GameRound(std::shared_ptr<AiryEngine::ResourceManager> resource_manager)
{
    // std::cout << "GameRound::start start" << std::endl;

    this->car = std::make_shared<Car>(
        "CarModel",
        "Mashina12.obj",
        "FunnyRider/SportCar",
        resource_manager
    );

    this->road = std::make_shared<Road>(
        "RoadModel",
        "WayOne.obj",
        "FunnyRider/Road",
        resource_manager
    );

    this->roads = std::make_shared<std::vector<std::shared_ptr<Road>>>();
    std::string model_name = "RoadModel";
    for (int i = 0; i < 5; i++)
    {
        // std::cout << "create road " << i << std::endl;
        model_name += "1";
        std::shared_ptr<Road> curr_road = std::make_shared<Road>(
            model_name,
            "WayOne.obj",
            "FunnyRider/Road",
            resource_manager
        );
        // std::cout << "created road " << i << std::endl;
        this->roads->push_back(curr_road);
    }

    this->barrier = std::make_shared<Barrier>(
        "BarrierModel",
        "Pregrados.obj",
        "FunnyRider/Pregrados",
        resource_manager
    );

    this->coin = std::make_shared<Coin>(
        "CoinModel",
        "Monetka12.obj",
        "FunnyRider/Coin",
        resource_manager
    );

    this->fuel_canister = std::make_shared<FuelCanister>(
        "FuelCanisterModel",
        "Kanistra.obj",
        "FunnyRider/Canister",
        resource_manager
    );

    // std::cout << "GameRound::start finish" << std::endl;
}


void GameRound::set_start_pos()
{
    this->car->set_position(0.277f, 0, 0);

    float road_offset = 4.317f * 2 - 0.1f;
    for (int i = 0; i < this->roads->size(); i++)
    {
        (*this->roads)[i]->set_position(0, 0, road_offset * i);
    }
}


void GameRound::move_back_game_objects()
{

}


void GameRound::check_barrier_collision()
{

}


void GameRound::check_coins_collision()
{

}


void GameRound::check_fuel_canister_collision()
{

}