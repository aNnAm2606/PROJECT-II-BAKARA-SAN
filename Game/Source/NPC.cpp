#include "NPC.h"
#include "App.h"
#include "Render.h"
#include "DialogModule.h"
#include "PlayerModule.h"
#include "Input.h"
#include "Defs.h"

void NPC::AddDialog(Dialog& dialog, size_t resetNode)
{
	m_Dialogs.push_back(dialog);
	m_StartingNodes.push_back(resetNode);
}

NPC::NPC()
{
	m_ActiveDialog = -1;
	m_Interacting = false;
	m_InteractDistance = 90.0f;
	m_Active = true;
	m_Deactivate = false;
}

NPC::~NPC()
{
}

void NPC::Interact()
{
	if (m_Interacting) return;

	if (m_ActiveDialog >= 0 && m_ActiveDialog < m_Dialogs.size()) {
		m_Interacting = true;
		m_Dialogs[m_ActiveDialog].ResetDialog(m_StartingNodes[m_ActiveDialog]);

		app->dialog->StartDialog(&m_Dialogs[m_ActiveDialog]);
	}

	OnInteract();
}

void NPC::Update()
{
	if (!m_Active) return;
	GamePad& gamepad = app->input->pads[0];

	if (m_Interacting) {
		if (!app->dialog->IsDialogActive()) {
			m_Interacting = false;
		}
	}
	else {
		if (app->input->GamepadConnected() == false)
		{
			if (app->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN) {
				int x, y;
				app->playerModule->GetPosition(x, y);

				float distance = DISTANCE_F(m_Position.x, m_Position.y, x, y);

				if (distance < m_InteractDistance) {
					Interact();
				}
			}
		}
		else
		{
			if (gamepad.a == true) {
				int x, y;
				app->playerModule->GetPosition(x, y);

				float distance = DISTANCE_F(m_Position.x, m_Position.y, x, y);

				if (distance < m_InteractDistance) {
					Interact();
				}
			}
		}
	}

	OnUpdate();
}

void NPC::Render()
{
	if (!m_Active) return;

	app->render->DrawTexture(m_NPCTex, m_Position.x, m_Position.y, &m_NPCRect);
}