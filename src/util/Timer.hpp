#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>
typedef std::chrono::steady_clock::time_point TimePoint;

class Timer {
    protected:
        TimePoint startTime,
                  endTime;
        bool stopped;

    public:
        Timer();

        void start();
        void stop();

        // Time in seconds.
        // If timer is still running, return time elapsed since the start
        // Else, return duration between start and end
        float getTime() const;
};

#endif // TIMER_HPP
