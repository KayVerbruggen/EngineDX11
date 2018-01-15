#pragma once
#include <Windows.h>

float deltaTime = 0.0f;
long countsPerSeconds = 0;
float secondsPerCount;
long prevTime = 0;
long currTime = 0;

void StartTimer()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSeconds);
	secondsPerCount = 1.0f / countsPerSeconds;
	QueryPerformanceCounter((LARGE_INTEGER*)&prevTime);
}

void UpdateTimer()
{
	currTime = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	deltaTime = (currTime - prevTime) * secondsPerCount;
}

void ResetTimer()
{
	prevTime = currTime;
}

float GetDeltaTime()
{
	return deltaTime;
}