#ifndef __ALAN_PARSONS_H__
#define __ALAN_PARSONS_H__

#include "NPC.h"

class AlanParsons : public NPC {
private:
	void FillBaseDialog();
public:
	AlanParsons();
	~AlanParsons();

	void OnInit() override;
};

#endif  // __LOG_H__