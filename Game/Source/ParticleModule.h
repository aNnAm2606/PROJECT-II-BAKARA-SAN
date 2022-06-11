#ifndef __PARTICLE_MODULE_H__
#define __PARTICLE_MODULE_H__

#define MAX_ACTIVE_PARTICLES 50
#include "Module.h"
#include "Particle.h"
#include "List.h"
#include "Textures.h"


class ParticleModule: public Module
{

private:
	
	List <Particle*> particles;
	int lastParticle = 0;
	SDL_Texture* particleTexture;

public:
	ParticleModule(bool startEnabled);

	// Destructor
	virtual ~ParticleModule();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();


	void AddParticle(const Particle& particle, int x, int y, uint delay);
	
	
};

#endif





