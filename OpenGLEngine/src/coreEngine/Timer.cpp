#include <chrono>
#include <iostream>
#include "Timer.h"

#pragma region Public API

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
	m_LogFPS = false;
}

float Timer::GetElapsedTime()
{
	float currentTime = GetTime();
	m_ElapsedTime = currentTime - m_LastFrameTime;
	m_LastFrameTime = currentTime;

	return m_ElapsedTime;
}


void Timer::LogFPS(bool value)
{
	m_LogFPS = value;
}

void Timer::Update()
{
	if (m_LogFPS)
		PrintFPS();
}

#pragma endregion


#pragma region Private API

float Timer::GetTime()
{
	auto currentTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> time = currentTime - m_StartedTime;

	return time.count();
}

void Timer::PrintFPS()
{
	std::cout << 1.0f / m_ElapsedTime << " FPS." << std::endl;
}

#pragma endregion



