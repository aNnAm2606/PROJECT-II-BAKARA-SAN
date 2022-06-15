#ifndef __GARGOYLE_TEST_H__
#define __GARGOYLE_TEST_H__

#include "NPC.h"

class Scene;

class GargoyleBattle : public NPC {
private:
	Scene* m_OriginScene;
public:
	GargoyleBattle();
	~GargoyleBattle();

	void SetOriginScene(Scene* scene) { m_OriginScene = scene; }

	void Init() override;
	void OnInteract() override;

	virtual void SetBattlefield() = 0;
};

#endif  // __LOG_H__