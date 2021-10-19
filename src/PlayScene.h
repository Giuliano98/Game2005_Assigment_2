#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Plane.h"
#include "Player.h"
#include "Button.h"
#include "Game.h"
#include "Label.h"
#include "Particle.h"

#define P30_M1 30

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

	bool isGround();
	bool isRamp();
private:
	// IMGUI Function
	void GUI_Function();
	std::string m_guiTitle;
	
	glm::vec2 m_mousePosition;
	

	//const float DEG_TO_RADIANS = (double)M_PI / (double)180.0;
	const float RADIANS_TO_DEG = (double)180.0 / (double)M_PI;
	const float DEG_TO_RADIANS = (double)M_PI / (double)180.0;

	Particle* m_pParticle;

	glm::vec2 m_rampPos = {50.0f, 200.0f};

	float m_rampRise = 3.0f;
	float m_rampRun = 4.0f;
	float m_rampAng = atan(m_rampRise/m_rampRun) * RADIANS_TO_DEG;

	float Gravity = 9.8f;
	float uFric_Floor = 0.42f;

	glm::vec4 m_myRamp = {m_rampPos.x, m_rampPos.y,	// Start pos
		m_rampPos.x + m_rampRun*P30_M1,		   // Final pos in X
		m_rampPos.y + m_rampRise*P30_M1};	  // Final pos in y

	glm::vec4 m_myFloor = { m_rampPos.x, m_myRamp.w, 
		800.0f - m_rampPos.x,
		m_rampPos.y + m_rampRise*P30_M1
	};
	


	bool m_playerFacingRight;

	Label* m_pStart;
	Label* m_pRestart;


	// UI Items
	//Button* m_pBackButton;
	//Button* m_pNextButton;
	Label* m_pInstructionsLabel;
	
};

#endif /* defined (__PLAY_SCENE__) */