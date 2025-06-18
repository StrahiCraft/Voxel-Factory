#include "Time.h"

float Time::_timeScale = 1;
float Time::_deltaTime;
float Time::_realTime;
float Time::_previousTime = 0;
double Time::_passedTime = 0;

void Time::updateTime() {
	float currentTime = glutGet(GLUT_ELAPSED_TIME);

	_realTime = (float)((currentTime - _previousTime) / 1000);
	_deltaTime = _realTime * _timeScale;
	_previousTime = currentTime;

	_passedTime += _realTime;
}

void Time::setTimeScale(float value) {
	_timeScale = value;
}

float Time::getTimeScale() {
	return _timeScale;
}

float Time::getDeltaTime()
{
	return _deltaTime;
}

float Time::getRealTime()
{
	return _realTime;
}

double Time::getTime() {
	return _passedTime;
}
