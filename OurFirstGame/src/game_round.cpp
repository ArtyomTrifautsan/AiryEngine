#include "game_round.hpp"


#include <iostream>


GameRound::GameRound(std::shared_ptr<AiryEngine::ResourceManager> resource_manager)
{
    // std::cout << "GameRound::start start" << std::endl;

    create_car(resource_manager);

    create_roads(resource_manager);
    
    create_barriers(resource_manager);

    create_coins(resource_manager);

    this->fuel_canister = std::make_shared<FuelCanister>(
        "FuelCanisterModel",
        "Kanistra.obj",
        "FunnyRider/Canister",
        resource_manager
    );

    // std::cout << "GameRound::start finish" << std::endl;
}


void GameRound::create_car(std::shared_ptr<AiryEngine::ResourceManager> resource_manager)
{
    this->car = std::make_shared<Car>(
        "CarModel",
        "Mashina12.obj",
        "FunnyRider/SportCar",
        resource_manager
    );
}


void GameRound::create_roads(std::shared_ptr<AiryEngine::ResourceManager> resource_manager)
{
    // this->road = std::make_shared<Road>(
    //     "RoadModel",
    //     "WayOne.obj",
    //     "FunnyRider/Road",
    //     resource_manager
    // );

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
}


void GameRound::create_barriers(std::shared_ptr<AiryEngine::ResourceManager> resource_manager)
{
    // this->barrier = std::make_shared<Barrier>(
    //     "BarrierModel",
    //     "Pregrados.obj",
    //     "FunnyRider/Pregrados",
    //     resource_manager
    // );

    this->barriers = std::make_shared<std::vector<std::shared_ptr<Barrier>>>();
    std::string model_name = "BarrierModel";
    for (int i = 0; i < 5; i++)
    {
        // std::cout << "create road " << i << std::endl;
        model_name += "1";
        std::shared_ptr<Barrier> curr_barrier = std::make_shared<Barrier>(
            model_name,
            "Pregrados.obj",
            "FunnyRider/Pregrados",
            resource_manager
        );
        // std::cout << "created road " << i << std::endl;
        this->barriers->push_back(curr_barrier);
    }
}


void GameRound::create_coins(std::shared_ptr<AiryEngine::ResourceManager> resource_manager)
{
    // this->coin = std::make_shared<Coin>(
    //     "CoinModel",
    //     "Monetka12.obj",
    //     "FunnyRider/Coin",
    //     resource_manager
    // );

    this->coins = std::make_shared<std::vector<std::shared_ptr<Coin>>>();
    std::string model_name = "CoinModel";
    for (int i = 0; i < 5; i++)
    {
        // std::cout << "create road " << i << std::endl;
        model_name += "1";
        std::shared_ptr<Coin> curr_coin = std::make_shared<Coin>(
            model_name,
            "Monetka12.obj",
            "FunnyRider/Coin",
            resource_manager
        );
        // std::cout << "created road " << i << std::endl;
        this->coins->push_back(curr_coin);
    }
}


void GameRound::set_start_pos()
{
    set_car_start_pos();

    set_roads_start_pos();

    set_barriers_start_pos();

    set_coins_start_pos();
}


void GameRound::set_car_start_pos()
{
    this->car->set_position(0.277f, 0, 0);
}


void GameRound::set_roads_start_pos()
{
    // float road_offset = 4.317f * 2 - 0.1f;
    for (int i = 0; i < this->roads->size(); i++)
    {
        (*this->roads)[i]->set_position(0, 0, this->road_offset * i);
    }
}


void GameRound::set_barriers_start_pos()
{
    // float road_offset = 4.317f * 2 - 0.1f;
    for (int i = 0; i < this->barriers->size(); i++)
    {
        (*this->barriers)[i]->set_position(0, 0, this->road_offset * i + 1.0f);
    }
}


void GameRound::set_coins_start_pos()
{
    // float road_offset = 4.317f * 2 - 0.1f;
    for (int i = 0; i < this->coins->size(); i++)
    {
        (*this->coins)[i]->set_position(-2.0f, 0, this->road_offset * i + 1.0f);
    }
}


void GameRound::move_back_game_objects()
{
    move_back_roads();

    move_back_barriers();

    move_back_coins();

    move_back_fuel_canister();
}


void GameRound::move_back_roads()
{
    for (int i = 0; i < this->roads->size(); i++)
    {
        (*this->roads)[i]->set_position(0, 0, this->road_offset * i);
    }
}


void GameRound::move_back_barriers()
{

}


void GameRound::move_back_coins()
{

}


void GameRound::move_back_fuel_canister()
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