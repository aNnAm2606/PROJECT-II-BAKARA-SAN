#include "DialogModule.h"
#include "Dialog.h"

#include "Log.h"

DialogModule::DialogModule(bool startEnabled) : Module(startEnabled)
{
	name.Create("DialogModule");
}

// Destructor
DialogModule::~DialogModule()
{}

// Called before render is available
bool DialogModule::Awake(pugi::xml_node& config)
{
	LOG("Loading DialogModule");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool DialogModule::Start()
{
	m_IsDialogActive = false;

	return true;
}

// Called each loop iteration
bool DialogModule::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool DialogModule::Update(float dt)
{
	if (m_IsDialogActive) {
		m_ActiveDialog->Update();

		if (m_ActiveDialog->Finished()) {
			m_IsDialogActive = false;
		}
	}

	return true;
}

// Called each loop iteration
bool DialogModule::PostUpdate()
{
	bool ret = true;

	return ret;
}

// Called before quitting
bool DialogModule::CleanUp()
{
	LOG("Freeing DialogModule");

	return true;
}

void DialogModule::StartDialog(Dialog* dialog)
{
	m_IsDialogActive = true;

	m_ActiveDialog = dialog;
}
