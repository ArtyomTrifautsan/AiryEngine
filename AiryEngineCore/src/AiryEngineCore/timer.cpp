#include "AiryEngineCore/timer.hpp"

// #include <ctime>
#include <GLFW/glfw3.h>


namespace AiryEngine {
    double Timer::get_current_time()
    {
        return glfwGetTime();
    }
}