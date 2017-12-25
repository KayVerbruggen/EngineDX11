#include "GameTimer.h"
#include <Windows.h>

GameTimer::GameTimer()
{
	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	m_secondsPerCount = 1.0 / (double)countsPerSec;
}

void GameTimer::Tick()
{
	if (m_stopped)
	{
		m_deltaTime = 0.0;
		return;
	}
	// Get the time this frame.
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	m_currTime = currTime;

	// Time difference between this frame and the previous.
	m_deltaTime = (m_currTime - m_prevTime)*m_secondsPerCount;
	// Prepare for next frame.
	m_prevTime = m_currTime;
	
	// Make sure it is not negative.
	if (m_deltaTime < 0.0)
	{
		m_deltaTime = 0.0;
	}
}

void GameTimer::Reset()
{
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	m_baseTime = currTime;
	m_prevTime = currTime;
	m_stopTime = 0;
	m_stopped = false;
}

float GameTimer::DeltaTime()
{
	return (float)m_deltaTime;
}