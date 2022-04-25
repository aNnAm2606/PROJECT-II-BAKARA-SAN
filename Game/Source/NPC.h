#ifndef __NPC_H__
#define __NPC_H__

#include "Dialog.h"

class NPC {
private:
	bool m_Interacting;
protected:
	float m_InteractDistance;

	std::vector<Dialog> m_Dialogs;
	std::vector<size_t> m_StartingNodes;
	int m_ActiveDialog;

	SDL_Texture* m_NPCTex;
	SDL_Rect m_NPCRect;

	iPoint m_Position;

	void AddDialog(Dialog& dialog, size_t resetNode);
public:
	NPC();
	~NPC();

	virtual void Init(){}

	void Interact();

	void Update();
	void Render();

	bool Interacting() { return m_Interacting; }
};

#endif  // __LOG_H__