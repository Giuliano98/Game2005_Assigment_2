#pragma once
#ifndef __PARTICLE__
#define __PARTICLE__
#include <SDL_stdinc.h>

#include "DisplayObject.h"

class Particle final : public DisplayObject
{
public:
	Particle();
	~Particle();

	// Life Cycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void yAxisUpdate();

	void setStart(bool check);
	bool getStart();
	void setTouchGround(bool touch);
	void setYi(float y);

private:

	float dt_y, dt_x = 0.016;
	// particle's variables
	const float DEG_TO_RADIANS = (double)M_PI / (double)180.0;
	float time_y, time_x = 0.0f;
	float v = 95.0f;
	float d = 485.0f;
	float g = 9.8f;
	float xi = 0.0f;
	float xf = 0.0f;
	float yi;
	float yf;
	float y;
	float launchAng = 15.901f;
	float Vx = 0.0f; 
	float Vy = 0.0f; 

	bool touchGround = false;

	bool startFlag = false;
};

#endif /* defined (__PARTICLE__) */