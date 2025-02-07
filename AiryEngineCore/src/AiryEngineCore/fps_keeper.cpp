#include "AiryEngineCore/fps_keeper.hpp"

// #include <ctime>
#include "AiryEngineCore/timer.hpp"

#include <thread>
#include <chrono>

#include <iostream>


namespace AiryEngine {
    FpsKeeper::FpsKeeper(double FPS)
    {
        this->FPS = FPS;
        this->delta_time = (double) 1 / this->FPS;
        this->start_loop_timepoint = Timer::get_current_time();

        this->current_fps = 0;
    }


    void FpsKeeper::set_fps(double FPS)
    {
        this->FPS = FPS;
        this->delta_time = 1 / this->FPS;
    }


    void FpsKeeper::keep_fps()
    {
        this->delta = Timer::get_current_time() - this->start_loop_timepoint;
        if (this->delta < this->delta_time)
        {
            this->sleep_time = (int)((this->delta_time - this->delta) * 1000);
            std::this_thread::sleep_for(std::chrono::milliseconds(this->sleep_time));

            // std::cout << "FPS: " << 1 / (Timer::get_current_time() - this->start_loop_timepoint) << std::endl;
            this->current_fps = 1 / (Timer::get_current_time() - this->start_loop_timepoint);

            this->start_loop_timepoint = Timer::get_current_time();
        }
    }
}