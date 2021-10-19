#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"

PlayScene::PlayScene()
{
	PlayScene::start();
	TextureManager::Instance().load("../Assets/textures/A1_background.png", "bg");

	auto size = TextureManager::Instance().getTextureSize("bg");
	setWidth(size.x);
	setHeight(size.y);
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	TextureManager::Instance().draw("bg",
		getTransform()->position.x, getTransform()->position.y, 0, 0, false);
	drawDisplayList();
	

	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 255, 0, 0, 255);
	SDL_RenderDrawLine(Renderer::Instance().getRenderer(),
		m_myRamp.x, m_myRamp.y, 
		m_myRamp.z, m_myRamp.w);

	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 255, 0, 0, 255);
	SDL_RenderDrawLine(Renderer::Instance().getRenderer(),
		m_myFloor.x, m_myFloor.y, 
		m_myFloor.z, m_myFloor.w);


	// ----------------------------
	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();

	// update partible var
	m_pParticle->setAngle(m_rampAng);
	m_pParticle->setGrav(Gravity);
	m_pParticle->setAccelRamp(Gravity * sin(m_rampAng * DEG_TO_RADIANS));
	m_pParticle->setVelGround(sqrt(Gravity * m_rampRise * 2));
	m_pParticle->setAccelFloorFric(Gravity * uFric_Floor);
	
	// tells the particle if it's in the ramp or ground
	m_pParticle->setTouchRamp(isRamp());
	m_pParticle->setTouchGround(isGround());

	// update ramp and ground
	m_myRamp = {m_rampPos.x, m_rampPos.y,	// Start pos
		m_rampPos.x + m_rampRun*P30_M1,		   // Final pos in X
		m_rampPos.y + m_rampRise*P30_M1};	  // Final pos in y

	m_myFloor = { m_rampPos.x, m_myRamp.w, 
		800.0f - m_rampPos.x,
		m_rampPos.y + m_rampRise*P30_M1
	};

	if (!m_pParticle->getStart())
	{
		m_pParticle->getTransform()->position = glm::vec2(m_rampPos.x, m_rampPos.y - 70);
	}

}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();
	

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance().quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance().changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance().changeSceneState(END_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_R))
	{
		// Restart the particule 
		
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
	{
		// check if the user pressed "S" for starting the simulation
		m_pParticle->setStart(true);
		//startFlag = true;
	}
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";
	

	m_pParticle = new Particle();
	addChild(m_pParticle);
	//m_pParticle->getTransform()->position = glm::vec2(m_rampPos.x, m_rampPos.y - 100);
	m_pParticle->setXi(m_rampPos.x);
	m_pParticle->setYi(m_rampPos.y - 70);



	/* Labels */
	m_pStart = new Label("Press (S) to start the motion", "Consolas", 20
		, SDL_Color({ 255, 0, 0, 255 }), glm::vec2(476.0f, 30.0f));
	addChild(m_pStart);

	m_pRestart = new Label("Press (R) to Restart the level motion", "Consolas", 20
		, SDL_Color({ 255, 0, 0, 255 }), glm::vec2(520.0f, 60.0f));
	addChild(m_pRestart);
	
	m_pInstructionsLabel = new Label("Press (`) to toggle Debug View", "Consolas", 20
		, SDL_Color({ 255, 0, 0, 255 }), glm::vec2(483.0f, 90.0f));
	addChild(m_pInstructionsLabel);

	ImGuiWindowFrame::Instance().setGUIFunction(std::bind(&PlayScene::GUI_Function, this));
}

bool PlayScene::isGround()
{
	return CollisionManager::lineRectCheck(
		{m_myFloor.x,m_myFloor.y}, {m_myFloor.z, m_myFloor.w}, 
		m_pParticle->getTransform()->position, m_pParticle->getWidth(), m_pParticle->getHeight()
	);
}

bool PlayScene::isRamp()
{
	return CollisionManager::lineRectCheck(
		{m_myRamp.x,m_myRamp.y}, {m_myRamp.z, m_myRamp.w}, 
		m_pParticle->getTransform()->position, m_pParticle->getWidth(), m_pParticle->getHeight()
	);
}

void PlayScene::GUI_Function()
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Assignment 1", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove);

	ImGui::SliderFloat("m_rampPos X", &m_rampPos.x, 0.0f, 800.0f, "%.1f,");
	ImGui::SliderFloat("m_rampPos Y", &m_rampPos.y, 0.0f, 600.0f, "%.1f,");

	/*
	ImGui::SliderFloat("IniPos X", &m_pParticle->getTransform()->position.x, 0.0f, 800.0f, "%.1f,");
	ImGui::SliderFloat("IniPos Y", &m_pParticle->getTransform()->position.y, 0.0f, 600.0f, "%.1f,");
	
	ImGui::Separator();
	ImGui::SliderFloat("Velocity", &v, 0.f, 100.0f, "%.1f,");
	ImGui::SliderFloat("Launch Angle", &launchAng, 0.0f, 90.0f, "%.1f,");

	ImGui::Separator();
	ImGui::SliderFloat("Gravity", &g, -5.0f, 20.0f, "%.1f,");
	ImGui::SliderFloat("Distance", &d, 0.0f, 600, "%.1f,");

	ImGui::Separator();
	ImGui::SliderFloat("Time", &t, -10.f, 100.0f, "%.1f,");*/
	
	// ------------------------------------
	ImGui::End();
}
