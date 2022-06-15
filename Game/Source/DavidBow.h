#ifndef __DAVID_BOW_H__
#define __DAVID_BOW_H__

#include "NPC.h"

class DavidBow : public NPC {
private:
	enum EDavidDialog {
		EDAVIDDIALOG_MAIN,
		EDAVIDDIALOG_COMPLETED
	};

	void FillBaseDialog();
	void FillCompletedDialog();
public:
	DavidBow();
	~DavidBow();

	void OnInit() override;
	void OnUpdate() override;

	virtual void OnDialogStart() override;
	virtual void OnDialogFinish() override;

	virtual void OnDialogButton(size_t data) override;
};

#endif  // __LOG_H__