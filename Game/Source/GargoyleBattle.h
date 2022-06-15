#ifndef __GARGOYLE_TEST_H__
#define __GARGOYLE_TEST_H__

#include "NPC.h"

class Scene;

class GargoyleBattle : public NPC {
protected:
	Scene* m_OriginScene;

	virtual void SetBattlefield() = 0;
public:
	GargoyleBattle();
	~GargoyleBattle();

	void SetOriginScene(Scene* scene) { m_OriginScene = scene; }

	void OnInit() override;
	void OnInteract() override;
};

#endif  // __LOG_H__