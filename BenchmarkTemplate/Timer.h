#pragma once
#include <chrono>
#include <thread>

class Timer
{
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> mStartTimePoint;
	long long mDuration = 0;
	double mDurationMillisec = 0;
public:
	Timer();
	~Timer();

	void stop();
	double durationMillisec();
	long long duration();
};