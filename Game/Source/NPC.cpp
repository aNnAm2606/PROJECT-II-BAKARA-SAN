#include "NPC.h"

void NPC::AddDialog(Dialog& dialog, size_t resetNode)
{
	m_Dialogs.push_back(dialog);
	m_StartingNodes.push_back(resetNode);
}

NPC::NPC()
{
	m_ActiveDialog = -1;
	m_Interacted = false;
}

NPC::~NPC()
{
}

void NPC::Interact()
{
	m_Interacted = true;
	m_Dialogs[m_ActiveDialog].ResetDialog(m_StartingNodes[m_ActiveDialog]);
}

void NPC::Update()
{
	if (m_Interacted) {
		if (m_ActiveDialog >= 0) {
			m_Dialogs[m_ActiveDialog].Update();

			if (m_Dialogs[m_ActiveDialog].Finished()) {
				m_Interacted = false;

				m_Dialogs[m_ActiveDialog].ResetDialog(m_StartingNodes[m_ActiveDialog]);
			}
		}
	}
}