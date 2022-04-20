#ifndef __TRIANA_H__
#define __TRIANA_H__

#include "NPC.h"

class Triana : public NPC {
private:
	void FillShopDialog();
public:
	Triana();
	~Triana();

	void Init();
};

#endif  // __LOG_H__