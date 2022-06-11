#include "App.h"
#include "Particle.h"

Particle::Particle()
{

}
Particle::~Particle()
{

}
bool Particle::Update(float dt)
{
	bool ret = true;

	timePassed += dt / 1000;
	if (timePassed >= lifeTime) ret = false;

	return ret;
}