#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>
#include <iostream>
#include <iomanip>

class Timer
{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start{};
    std::chrono::time_point<std::chrono::high_resolution_clock> end{};
    std::chrono::duration<float> duration{0.0};
public:
    Timer() = default;
	Timer(Timer const &) = delete;
    Timer & operator=(Timer const &) = delete;
	Timer(Timer &&) = delete;
	Timer & operator=(Timer &&) = delete;
	~Timer() = default;

	void Start()
	{
		start = std::chrono::high_resolution_clock::now();
	}

	float Stop()
	{
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		return duration.count();
	}

	std::string YYYYMMDD_HHMMSS()
	{
		auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::stringstream dateAndTime;
		dateAndTime << std::put_time(std::localtime(& now), "%Y%m%d_%H%M%S");
		return dateAndTime.str();
	}
};



#endif // TIMER_HPP