#include "App.h"
#include "Particle.h"

Particle::Particle()
{
	animation.PushBack({ 520,20,80, 90 });
	animation.PushBack({ 640, 20,80,90 });
	animation.loop = true;
	animation.speed = 0.1f;

	
}
Particle::~Particle()
{

}
bool Particle::Update(float dt)
{
	bool ret = true;
	animation.Update();
	timePassed += dt / 1000;
	if (timePassed >= lifeTime) ret = false;

	return ret;
}