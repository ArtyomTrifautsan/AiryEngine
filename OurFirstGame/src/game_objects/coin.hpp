#pragma once


// Файлы движка
#include <AiryEngineCore/Physics/CollisionDetector.hpp>

#include <AiryEngineCore/Rendering/OpenGL/Model3D.hpp>

#include <AiryEngineCore/ResourceManager.hpp>


// Файлы игры
#include "game_object.hpp"


// Системные библиотеки
#include <memory>


class Coin : public GameObject {
public:
    Coin(const std::string& model_name,
        const std::string& model_path,
        const std::string& model_dir_path,
        std::shared_ptr<AiryEngine::ResourceManager> resource_manager);

private:
};