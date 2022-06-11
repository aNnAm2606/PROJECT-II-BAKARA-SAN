#include "ParticleModule.h"
#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"

ParticleModule::ParticleModule(bool startEnabled) :Module(startEnabled)
{
	//particleTexture = app->tex->Load("MyTexture");
}

ParticleModule::~ParticleModule()
{

}

bool ParticleModule::Awake()
{
	return true;
}
bool ParticleModule::Start()
{
	return true;
}
bool ParticleModule::CleanUp()
{
	particles.Clear();
	return true;
}
bool ParticleModule::PreUpdate()
{
	return true;
}
bool ParticleModule::Update(float dt)
{

	for (ListItem<Particle*>* item = particles.start; item; item = item->next)
	{
		if (item == nullptr)	continue;

		if (item->data->Update(dt) == false)
		{
			particles.Del(item);
		}
	}
	
	return true;
}
bool ParticleModule::PostUpdate()
{
	for (ListItem<Particle*>* item = particles.start; item; item = item->next)
	{

		app->render->DrawTexture(particleTexture, item->data->position.x, item->data->position.y, &(item->data->animation.GetCurrentFrame()));

	}
	return true;
}
void ParticleModule::AddParticle(const Particle& particle, int x, int y, uint delay)
{
	Particle* p = new Particle(particle);

	p->position.x = x;
	p->position.y = y;

	if(particles.Count() < MAX_ACTIVE_PARTICLES) particles.Add(p);
	
}