#ifndef __STEVEN_WONDER_H__
#define __STEVEN_WONDER_H__

#include "NPC.h"

class StevenWonder : public NPC {
private:
	void FillBaseDialog();
	void FillCompletedDialog();

	size_t m_MissionBoxId;
	size_t m_UncompletedId;
	size_t m_CompletedId;
public:
	StevenWonder();
	~StevenWonder();

	void Init();
};

#endif  // __LOG_H__