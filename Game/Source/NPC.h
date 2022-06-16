#ifndef __NPC_H__
#define __NPC_H__

#include "Dialog.h"

class NPC {
private:
	bool m_Interacting;
protected:
	float m_InteractDistance;

	SDL_Texture* m_NPCTex;
	SDL_Rect m_NPCRect;

	SDL_Texture* m_EButton;

	iPoint m_Position;
	uint m_NPCFX = NULL;
    uint QuestCompleted_fx = NULL;
	bool m_fx = false;
	// Dialogs
	std::vector<Dialog> m_Dialogs;
	std::vector<size_t> m_StartingNodes;

	int m_ActiveDialog;

	bool m_Active;
	bool m_Deactivate;

	void AddDialog(Dialog& dialog, size_t resetNode);
public:
	NPC();
	~NPC();

	void SetPosition(int x, int y) { m_Position = { x,y }; }

	void Init();
	virtual void OnInit(){}

	void Interact();

	virtual void OnInteract(){}

	virtual void OnDialogStart(){}
	virtual void OnDialogButton(size_t data){}
	virtual void OnDialogFinish(){}

	void Update();

	virtual void OnUpdate(){}

	void Render();

	bool Interacting() { return m_Interacting; }
};

#endif  // __LOG_H__