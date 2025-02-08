#pragma once


namespace AiryEngine {

    class FpsKeeper
    {
    public:
        FpsKeeper();
        // static void set_fps(double FPS = 60.0);
        static double get_fps() { return m_FPS; }
        void keep_fps();

    private:
        static inline double m_FPS = 100;
        double m_delta_time;

        double m_delta;
        int m_sleep_time;
        double m_start_loop_timepoint;

        double m_current_fps;
    };

}