#ifndef __STEVEN_WONDER_H__
#define __STEVEN_WONDER_H__

#include "NPC.h"

class StevenWonder : public NPC {
private:
	enum EStevenDialog {
		ESTEVENDIALOG_MAIN,
		ESTEVENDIALOG_COMPLETED
	};

	void FillBaseDialog();
	void FillCompletedDialog();

	size_t m_MissionBoxId;
	size_t m_UncompletedId;
	size_t m_CompletedId;

	bool m_GiveCat;
public:
	StevenWonder();
	~StevenWonder();

	void OnInit() override;
	void OnUpdate() override;

	virtual void OnDialogStart() override;
	virtual void OnDialogFinish() override;

	virtual void OnDialogButton(size_t data) override;

};

#endif  // __LOG_H__