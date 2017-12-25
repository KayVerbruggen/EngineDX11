#pragma once

class GameTimer
{
public:
	GameTimer();

	// delta time in seconds
	float DeltaTime();

	void Reset();		// Call before handling messages
	void Tick();		// Call to update the timer every frame

private:
	double m_secondsPerCount = 0.0;
	double m_deltaTime = -1.0;

	__int64 m_baseTime = 0;
	__int64 m_pausedTime = 0;
	__int64 m_stopTime = 0;
	__int64 m_prevTime = 0;
	__int64 m_currTime = 0;

	bool m_stopped = false;
};