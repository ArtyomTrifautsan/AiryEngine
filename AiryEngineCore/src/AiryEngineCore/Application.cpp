#include <iostream>
using std::cout;
using std::endl;

#include "AiryEngineCore/Application.hpp"
#include "AiryEngineCore/Window.hpp"
#include "AiryEngineCore/Log.hpp"

namespace AiryEngine {
    Application::Application() 
    {
        LOG_INFO("Starting Application");
    }

    Application::~Application() 
    {
        LOG_INFO("Closing Application");
    }

    int Application::start(unsigned int window_width, unsigned int window_height, const char* title)
    {
        this->window = std::make_unique<Window>(title, window_width, window_height);
        this->window->set_enevt_callback(
            [](Event& event)
            {
                LOG_INFO("[EVENT] Changed size to {0}x{1}", event.width, event.height);
            }
        );

        while (true)
        {
            this->window->on_update();
            on_update();
        }

        return 0;
    }

    void Application::on_update() {}
}