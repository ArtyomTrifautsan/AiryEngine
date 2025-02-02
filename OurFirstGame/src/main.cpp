// Системные библиотеки
#include <iostream>


// Файлы движка
#include <AiryEngineCore/ResourceManager.hpp>


// Файлы игры
#include "game_application.hpp"


int main(int argc, char const *argv[])
{
    // std::cout << "main start" << std::endl;

    auto resource_manager = std::make_shared<AiryEngine::ResourceManager>(argv[0]);
    resource_manager->set_shaders_directory("Resources/Shaders");
    resource_manager->set_textures_directory("Resources/Textures");
    resource_manager->set_models_directory("Resources/Models");

    // AiryEngine::Renderer::init(resource_manager);
    
    auto game_application = std::make_unique<GameApplication>(resource_manager);
    
    int returnCode = game_application->start(1024, 768, "OurFirstGame");

    return returnCode;
}
