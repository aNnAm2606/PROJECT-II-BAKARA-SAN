#include "GargoyleTest.h"
#include "App.h"
#include "Textures.h"
#include "Fonts.h"
#include "FadeToBlack.h"
#include "TutorialScene_4.h"
#include "BattleScene.h"

GargoyleTest::GargoyleTest()
{
	m_InteractDistance = 350;
}

GargoyleTest::~GargoyleTest()
{
}

void GargoyleTest::Init()
{
	m_NPCTex = app->tex->Load("Assets/Art/Enemies/gargoyle_statue.png");
	m_NPCRect = {
		0, 0,
		256, 256
	};

	m_Position = { 500, 450 };
}

void GargoyleTest::OnInteract()
{
	app->fade->Fade(app->tutorialScene_4, app->battleScene);
}
