#include "Particle.h"

#include "Game.h"
#include "TextureManager.h"

Particle::Particle()
{
	TextureManager::Instance().load("../Assets/textures/OW_LootBox.png", "particle");

	auto size = TextureManager::Instance().getTextureSize("particle");
	setWidth(size.x);
	setHeight(size.y);
	
}

Particle::~Particle()
{
}

void Particle::draw()
{
	TextureManager::Instance().draw("particle",
		getTransform()->position.x, getTransform()->position.y, 0, 255, false);
}

void Particle::update()
{

	if (startFlag)	// check if user start the movement
	{
		// move according if the particle is in the ground, ramp or air
		if (touchGround)
		{
			// update init pos if it's first time in ground
			firstTimeGround();
			// move in ground
			moveInGround();
		}
		else if (touchRamp)
		{
			// update init pos if it's first time in ramp
			firstTimeRamp();
			// move in ramp
			moveInRamp();
		}
		else
		{
			// move in air
			moveInAir();
		}
		
		// make a new pos coordinates
		x = xf + xi;
		y = yf + yi;
		// update new position to the particle
		this->getTransform()->position = glm::vec2(x,y);
		
	}
	else
	{
		updateNewInitPos();
	}
}

void Particle::clean()
{
}

void Particle::moveInGround()	// move in X by resting the V0 with a desacceleration for fricction
{
	time_Ground += dt;		// get the currect time since the particule is in the ground
	xf = vel_Ground * time_Ground - 0.5f * accel_FloorFric * pow(time_Ground, 2); // cal new pos in X 
	currentVel_Ground = vel_Ground - accel_FloorFric * pow(time_Ground, 2);	// cal currect velocity in X
	xf *= P30_M1; // it's 30 pix = 1 m

	if (currentVel_Ground < 0)		// if my vel in X is negative. Stop moving
	{
		xi = 0;
		xf = this->getTransform()->position.x;
	}

	yf = 0;		// my Y does not change in the ground
}

void Particle::moveInRamp()
{
	time_Ramp += dt;	// get the current time since the particule is in the ramp
	rampDis = 0.5 * accel_Ramp * pow(time_Ramp, 2);	// cal the distance in the ramp traveled in time

	xf = cos(angle * DEG_TO_RADIANS) * rampDis;	// move in X by the cos(theta) * distance_traveled
	yf = sin(angle * DEG_TO_RADIANS) * rampDis;	// move in Y by the sin(theta) * distance_traveled

	// it's 30 pix = 1 m
	xf *= P30_M1;
	yf *= P30_M1;
}

void Particle::moveInAir()	// particle is falling
{
	time_y += dt;	// get time since the particle start falling
	yf =  0.5 * g * pow(time_y, 2); // move in Y, falling
	yf *= P30_M1; // it's 30 pix = 1 m
	xf = 0; // it doesnt change in X
}

void Particle::updateNewInitPos()
{
	xi = this->getTransform()->position.x;
	yi = this->getTransform()->position.y;
}

void Particle::firstTimeGround()
{
	if (ground_FT)
	{
		updateNewInitPos();
		ground_FT = false;
	}
}

void Particle::firstTimeRamp()
{
	if (ramp_FT)
	{
		updateNewInitPos();
		ramp_FT = false;
	}
}

void Particle::setStart(bool check)
{
	startFlag = check;
}

bool Particle::getStart()
{
	return startFlag;
}

void Particle::setTouchGround(bool touch)
{
	touchGround = touch;
}

void Particle::setTouchRamp(bool touch)
{
	touchRamp = touch;
}

void Particle::setYi(float y)
{
	yi = y;
}

void Particle::setXi(float x)
{
	xi = x;
}

void Particle::setAngle(float ang)
{
	angle = ang;
}

void Particle::setVelGround(float vel)
{
	vel_Ground = vel;
}

void Particle::setGrav(float grav)
{
	g = grav;
}

void Particle::setAccelFloorFric(float a_Fric)
{
	accel_FloorFric = a_Fric;
}

void Particle::setAccelRamp(float accel)
{
	accel_Ramp = accel;
}
