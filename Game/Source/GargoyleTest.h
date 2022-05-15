#ifndef __GARGOYLE_TEST_H__
#define __GARGOYLE_TEST_H__

#include "NPC.h"

class Scene;

class GargoyleTest : public NPC {
private:
	Scene* m_OriginScene;
public:
	GargoyleTest();
	~GargoyleTest();

	void SetOriginScene(Scene* scene) { m_OriginScene = scene; }

	void Init();

	void OnInteract();
};

#endif  // __LOG_H__