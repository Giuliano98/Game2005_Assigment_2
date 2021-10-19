#pragma once
#ifndef __PARTICLE__
#define __PARTICLE__
#include <SDL_stdinc.h>

#include "DisplayObject.h"

#define P30_M1 30

class Particle final : public DisplayObject
{
public:
	Particle();
	~Particle();

	// Life Cycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void moveInGround();
	void moveInRamp();
	void moveInAir();

	void updateNewInitPos();

	void firstTimeGround();
	void firstTimeRamp();

	void setStart(bool check);
	bool getStart();
	void setTouchGround(bool touch);
	void setTouchRamp(bool touch);
	void setYi(float y);
	void setXi(float x);
	void setAngle(float ang);
	void setVelGround(float vel);
	void setGrav(float grav);
	void setAccelFloorFric(float a_Fric);
	void setAccelRamp(float accel);

private:

	const float dt = 0.016f;

	float time_Ramp = 0.0f;
	float time_Ground = 0.0f;
	float time_y = 0.0f;

	float rampDis = 0.0f;

	float g = 9.8f;
	float mass = 12.8f;
	
	float vel_Ground = 0.0f;
	float currentVel_Ground = 0.0f;

	float accel_Ramp = 0.0f;
	float accel_FloorFric = 0.0f;
	
	float angle = 0.0;

	// particle's variables
	const float DEG_TO_RADIANS = (double)M_PI / (double)180.0;
	const float RADIANS_TO_DEG = (double)180.0 / (double)M_PI;

	float xi;
	float xf = 0;
	float x;

	float yi;
	float yf = 0;
	float y;

	bool ground_FT = true;
	bool ramp_FT = true;
	bool touchRamp = false;
	bool touchGround = false;
	bool startFlag = false;
	bool updateRamp = true;
	bool updateGround = true;
};

#endif /* defined (__PARTICLE__) */