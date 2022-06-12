#include "Ability.h"
#include "App.h"
#include "Textures.h"
#include "Render.h"

Ability::Ability(Character* character) : p_Character(character), p_FrameCount(0)
{
	
}

Ability::~Ability()
{
}

void Ability::Update()
{
	p_FrameCount++;
	p_Animation.Update();
}

void Ability::Render(iPoint position)
{
	//app->render->DrawTexture(p_Texture, )
}