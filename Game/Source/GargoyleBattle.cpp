#include "GargoyleBattle.h"
#include "App.h"
#include "Textures.h"
#include "Fonts.h"
#include "FadeToBlack.h"
#include "TutorialScene_4.h"
#include "BattleScene.h"

GargoyleBattle::GargoyleBattle()
{
	m_InteractDistance = 200;
}

GargoyleBattle::~GargoyleBattle()
{
}

void GargoyleBattle::OnInit()
{
	m_NPCTex = app->tex->Load("Assets/Art/Enemies/gargoyle_statue.png");
	m_NPCRect = {
		0, 0,
		256, 256
	};

	m_Position = { 500, 450 };
	m_OriginScene = app->tutorialScene_4;
}

void GargoyleBattle::OnInteract()
{
	SetBattlefield();
	m_Deactivate = true;
	app->fade->Fade(m_OriginScene, app->battleScene);
}