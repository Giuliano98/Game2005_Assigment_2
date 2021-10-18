#include "Particle.h"

#include "Game.h"
#include "TextureManager.h"

Particle::Particle()
{
	TextureManager::Instance().load("../Assets/textures/A1_Cactus.png", "particle");

	auto size = TextureManager::Instance().getTextureSize("particle");
	setWidth(size.x);
	setHeight(size.y);

	yi = this->getTransform()->position.y;
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
	if (true)	// check if user start the movement
	{
		

		// gets the velocity in X and Y
		//Vx = cos(-launchAng * DEG_TO_RADIANS) * v;
		//Vy = sin(-launchAng * DEG_TO_RADIANS) * v;

		// finding final position after "t" seconds
		//xf = xi + Vx * t;
		//yf = yi + Vy * t + (0.5f * g * pow(t, 2));

		yAxisUpdate();

		xf = getTransform()->position.x;

		this->getTransform()->position = glm::vec2(xf,y);

		//this->getTransform()->position.y = yi + yf;

		//this->getTransform()->position.y = this->getTransform()->position.y + yf;
		//yf += getTransform()->position.y;

		// updating new position
		//this->getTransform()->position = glm::vec2(xf, yf);

		std::cout << dt_y << ", " << time_y << "/  h:" << yf << "/ y:" << this->getTransform()->position.y << std::endl;
		std::cout <<"-------------------------------" << std::endl;
	}
}

void Particle::clean()
{
}

void Particle::yAxisUpdate()
{
	time_y += dt_y;	// gets a estimate time in seconds on Y axis
		
	if (!touchGround)  // if the particle is in the air add units in Y Axis
	{
		yf =  0.5 * g * pow(time_y, 2);			
	}
	else			// set the current Y possition to the inicial position
	{				// no add units in Y bc is in the ground, set time to 0
		yi = this->getTransform()->position.y;
		yf = 0;
		time_y = 0;
	}

	// add inicial Y pos and "change" Y pos
	y = yf + yi;
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

void Particle::setYi(float y)
{
	yi = y;
}
