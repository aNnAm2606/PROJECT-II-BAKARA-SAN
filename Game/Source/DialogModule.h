#ifndef __DIALOG_MODULE_H__
#define __DIALOG_MODULE_H__

#include "Module.h"

class Dialog;

class DialogModule : public Module
{
public:

	DialogModule(bool startEnabled);

	// Destructor
	virtual ~DialogModule();

	// Called before render is available
	bool Awake(pugi::xml_node& config);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	bool IsDialogActive() { return m_IsDialogActive; }

	void StartDialog(Dialog* dialog);
private:
	Dialog* m_ActiveDialog;

	bool m_IsDialogActive;
};

#endif // __LOGOSCREEN_H__