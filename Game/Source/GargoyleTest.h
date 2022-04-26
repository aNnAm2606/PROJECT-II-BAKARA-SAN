#ifndef __GARGOYLE_TEST_H__
#define __GARGOYLE_TEST_H__

#include "NPC.h"

class GargoyleTest : public NPC {
private:
	
public:
	GargoyleTest();
	~GargoyleTest();

	void Init();

	void OnInteract();
};

#endif  // __LOG_H__