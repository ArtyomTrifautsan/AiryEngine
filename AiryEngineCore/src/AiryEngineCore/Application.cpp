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

        this->eventDispatcher.add_event_listener<EventMouseMoved>(
            [](EventMouseMoved& event)
            {
                //LOG_INFO("[MouseMoved] Mouse moved to {0}x{1}", event.x, event.y);
            }
        );

        this->eventDispatcher.add_event_listener<EventWindowResize>(
            [](EventWindowResize& event)
            {
                LOG_INFO("[WindowResize] Changed window size to {0}x{1}", event.width, event.height);
            }
        );

        this->eventDispatcher.add_event_listener<EventWindowClose>(
            [&](EventWindowClose& event)
            {
                LOG_INFO("[WindowClose]");
                this->closeWindow = true;
            }
        );

        this->window->set_enevt_callback(
            [&](BaseEvent& event)
            {
                this->eventDispatcher.dispatch(event);
            }
        );

        while (!this->closeWindow)
        {
            this->window->on_update();
            on_update();
        }

        return 0;
    }

    void Application::on_update() {}
}