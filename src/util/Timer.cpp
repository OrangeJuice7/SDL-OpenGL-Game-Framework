#include "Timer.hpp"

TimePoint getCurrentTime() {
    return std::chrono::steady_clock::now();
}

Timer::Timer() {
    start();
}

void Timer::start() {
    startTime = getCurrentTime();
    stopped = false;
}
void Timer::stop() {
    endTime = getCurrentTime();
    stopped = true;
}

float Timer::getTime() const {
    TimePoint end = stopped ? endTime : getCurrentTime();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - startTime).count() * .001f;
}
