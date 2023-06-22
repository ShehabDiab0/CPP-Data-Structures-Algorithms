#include <iostream>
#include <thread>
#include <chrono>
#include "Timer.h"


Timer::Timer()
{
	mStartTimePoint = std::chrono::high_resolution_clock::now();
}

Timer::~Timer()
{
	stop();
}

void Timer::stop()
{
	auto endTimePoint = std::chrono::high_resolution_clock::now();

	auto start = std::chrono::time_point_cast<std::chrono::microseconds>(mStartTimePoint).time_since_epoch().count();
	auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

	mDuration = end - start;
	mDurationMillisec = mDuration * 0.001;

	std::cout << mDurationMillisec << "ms" << std::endl;
}

double Timer::durationMillisec()
{
	return mDurationMillisec;
}

long long Timer::duration()
{
	return mDuration;
}
