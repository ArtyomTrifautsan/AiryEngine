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
