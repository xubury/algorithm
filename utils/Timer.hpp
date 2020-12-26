#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <ctime>

class WallTimer {
   private:
    typedef std::chrono::high_resolution_clock TimerClock;
    typedef std::chrono::time_point<TimerClock> TimerTimePoint;
    typedef std::chrono::duration<double, std::milli> TimeDurationMS;

    TimerTimePoint m_start;

   public:
    WallTimer();
    void Reset();

    std::size_t GetElapsedMS() const;
    float GetElapsedSec() const;
};

inline WallTimer::WallTimer() { Reset(); }

inline void WallTimer::Reset() { m_start = TimerClock::now(); }

inline std::size_t WallTimer::GetElapsedMS() const {
    TimeDurationMS ms = TimerClock::now() - m_start;
    m_start.time_since_epoch();
    return ms.count();
}

inline float WallTimer::GetElapsedSec() const {
    return static_cast<float>(GetElapsedMS()) / 1000.0f;
}

#endif /* TIMER_H */
