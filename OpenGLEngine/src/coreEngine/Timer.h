#pragma once

#include <chrono>

class Timer
{
private:
	std::chrono::steady_clock::time_point m_StartedTime;
	float m_LastFrameTime;
	float m_ElapsedTime;

public:
    Timer();
    ~Timer();
	void Init();
	float GetElapsedTime();
	void PrintFPS();

private:
	float GetTime();
};
