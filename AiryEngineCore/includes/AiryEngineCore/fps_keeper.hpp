#pragma once


namespace AiryEngine {

    class FpsKeeper
    {
    public:
        FpsKeeper(double FPS = 60.0);
        void set_fps(double FPS);
        double get_fps() const { return this->FPS; }
        void keep_fps();

    private:
        double FPS;
        double delta_time;

        double delta;
        int sleep_time;
        double start_loop_timepoint;

        double current_fps;
    };

}