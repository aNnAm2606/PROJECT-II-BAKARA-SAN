#ifndef __NPC_H__
#define __NPC_H__

#include "Dialog.h"

class NPC {
private:
	bool m_Interacted;
protected:
	std::vector<Dialog> m_Dialogs;
	std::vector<size_t> m_StartingNodes;
	int m_ActiveDialog;

	SDL_Texture* m_NPCTex;
	SDL_Rect m_NPCRect;

	void AddDialog(Dialog& dialog, size_t resetNode);
public:
	NPC();
	~NPC();

	virtual void Init(){}

	void Interact();

	void Update();

	bool Interacting() { return m_Interacted; }
};

#endif  // __LOG_H__