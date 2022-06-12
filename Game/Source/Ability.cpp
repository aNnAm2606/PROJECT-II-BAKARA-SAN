#include "Ability.h"
#include "App.h"
#include "Render.h"

Ability::Ability(Character* character) : p_Character(character), p_FrameCount(0), p_StartFrame(0)
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