#pragma once

#include <chrono>
#include <string>

/// Namespace KD-Tree
namespace kdt
{
    class Timer
    {
    private:
#pragma region Private members

        std::chrono::high_resolution_clock::time_point startTime;
        std::chrono::high_resolution_clock::time_point endTime;

        bool isTimerRunning;

#pragma endregion

    public:
#pragma region Constructors

        Timer(const bool);

#pragma endregion

#pragma region Public timer methods

        void Start(void);
        void Stop(void);

        double GetTimePassed(void);

#pragma endregion

#pragma region Print methods

        std::string ToString(void);

#pragma endregion
    };
}
