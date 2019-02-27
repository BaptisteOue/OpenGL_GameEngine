#include <chrono>
#include <iostream>
#include "Timer.h"

Timer::Timer()
{
}

Timer::~Timer()
{
}

void Timer::Init()
{
	m_StartedTime = std::chrono::high_resolution_clock::now();
	m_ElapsedTime = 0;
	m_LastFrameTime = 0;
}

float Timer::GetElapsedTime()
{
	float currentTime = GetTime();
	m_ElapsedTime = currentTime - m_LastFrameTime;
	m_LastFrameTime = currentTime;

	return m_ElapsedTime;	
}

void Timer::PrintFPS()
{
	std::cout << 1.0f / m_ElapsedTime << " FPS." << std::endl;
}

float Timer::GetTime()
{
	auto currentTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> time = currentTime - m_StartedTime;

	return time.count();
}
