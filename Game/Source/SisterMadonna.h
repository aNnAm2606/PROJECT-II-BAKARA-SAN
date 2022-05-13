#ifndef __SISTER_MADONNA_H__
#define __SISTER_MADONNA_H__

#include "NPC.h"

class SisterMadonna : public NPC {
private:
	void FillBaseDialog();
public:
	SisterMadonna();
	~SisterMadonna();

	void OnDialogButton(size_t data) override;

	void Init();
};

#endif  // __LOG_H__