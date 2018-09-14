#include "Timer.h"

#include <sstream>

/// Namespace KD-Tree
namespace kdt
{
#pragma region Public

    /// Constructor
    /// Takes (up to) 1 boolean argument based on which
    /// the timer does or doesn't start
    Timer::Timer(const bool start = true)
        : isTimerRunning{ false }
    {
        if (start)
            Start();
    }

    /// Start the timer
    void Timer::Start(void)
    {
        if (!isTimerRunning)
        {
            isTimerRunning = true;
            startTime = std::chrono::high_resolution_clock::now();
        }
            
    }

    /// Stop the timer
    void Timer::Stop(void)
    {
        if (isTimerRunning)
        {
            endTime = std::chrono::high_resolution_clock::now();
            isTimerRunning = false;
        }
            
    }

    /// Get the time between the start and end time
    /// Note: if the timer is not stopped, method returns 0
    double Timer::GetTimePassed(void)
    {
        if (!isTimerRunning)
            return std::chrono::duration_cast
                <std::chrono::nanoseconds>
                (endTime - startTime).count();

        return 0.0;
    }

    /// Return time data as a string.
    /// Often used for displaying object information
    /// in console
    std::string Timer::ToString(void)
    {
        std::stringstream ss;

        ss << "Time passed: " << GetTimePassed();

        return ss.str();
    }

#pragma endregion

}
