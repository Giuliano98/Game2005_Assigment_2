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
private:
	// IMGUI Function
	void GUI_Function();
	std::string m_guiTitle;
	
	glm::vec2 m_mousePosition;

	Particle* m_pParticle;
	// particle's variables
	/*const float DEG_TO_RADIANS = (double)M_PI / (double)180.0;
	float t = 0.0f;
	float v = 95.0f;
	float d = 485.0f;
	float g = 9.8f;
	float xi = 0.0f;
	float xf = 0.0f;
	float yi = 0.0f;
	float yf = 0.0f;
	float launchAng = 15.901f;
	float Vx = 0.0f; 
	float Vy = 0.0f; 
	
	bool startFlag = false;*/
	
	bool m_playerFacingRight;

	Label* m_pStart;
	Label* m_pRestart;


	// UI Items
	//Button* m_pBackButton;
	//Button* m_pNextButton;
	Label* m_pInstructionsLabel;
	
};

#endif /* defined (__PLAY_SCENE__) */