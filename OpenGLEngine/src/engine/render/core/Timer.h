#pragma once

#include <chrono>

class Timer
{
private:
	std::chrono::steady_clock::time_point m_StartedTime;
	float m_LastFrameTime;
	float m_ElapsedTime;
	bool m_LogFPS;

public:
    Timer();
    ~Timer();
	void Init();
	float GetElapsedTime();
	void LogFPS(bool value);
	void Update();

private:
	void PrintFPS();
	float GetTime();
};
