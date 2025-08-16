#pragma once
#include <glut.h>

static class Time
{
private:
	static float _timeScale;
	static float _deltaTime;
	static float _realTime;
	static float _previousTime;
	static double _passedTime;
public:
	static void updateTime();
	static void setTimeScale(float value);
	static float getTimeScale();
	static float getDeltaTime();
	static float getRealTime();
	static double getTime();
};

