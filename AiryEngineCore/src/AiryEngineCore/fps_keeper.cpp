#include "AiryEngineCore/fps_keeper.hpp"

// #include <ctime>
#include "AiryEngineCore/timer.hpp"

#include <thread>
#include <chrono>

#include <iostream>


namespace AiryEngine {
    FpsKeeper::FpsKeeper()
    {
        // m_FPS = FPS;
        m_delta_time = (double) 1 / m_FPS;
        m_start_loop_timepoint = Timer::get_current_time();

        m_current_fps = 0;
    }


    // voidFpsKeeper::set_fps(double FPS)
    // {
    //     this->::m_FPS = FPS;
    //     this->::m_delta_time = (double) 1 / m_FPS;
    //     this->::m_start_loop_timepoint = Timer::get_current_time();

    //     this->::m_current_fps = 0;
    // }


    void FpsKeeper::keep_fps()
    {
        this->m_delta = Timer::get_current_time() - this->m_start_loop_timepoint;
        if (this->m_delta < this->m_delta_time)
        {
            this->m_sleep_time = (int)((this->m_delta_time - this->m_delta) * 1000);
            std::this_thread::sleep_for(std::chrono::milliseconds(this->m_sleep_time));

            // std::cout << "FPS: " << 1 / (Timer::get_current_time() - m_start_loop_timepoint) << std::endl;
            this->m_current_fps = 1 / (Timer::get_current_time() - this->m_start_loop_timepoint);

            this->m_start_loop_timepoint = Timer::get_current_time();
        }
    }
}