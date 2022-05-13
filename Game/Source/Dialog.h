#pragma once
#include <iostream>
#include <vector>
#include "DialogNode.h"
#include "Button.h"

class SDL_Texture;
class NPC;

class Dialog
{
private:
	// All nodes
	std::vector<DialogNode> nodes;
	
	// Active node
	DialogNode* activeNode;

	// Active buttons
	std::vector<std::string> texts;
	std::vector<Button> buttons;

	Button continueButton;
	Button finishButton;

	// Dialog position
	int posX, posY;
	int max_chars_line;

	// Text offsetting
	int char_width;
	int char_height;
	int textXOffset, textYOffset;

	// Dialog fong
	int dialogFont;

	// Dialog bg image
	SDL_Texture* dialogImg;
	int dialogWidth, dialogHeight;

	// NPC to which this dialog belongs
	NPC* parentNPC;

	// Whether the dialog has finished or not
	bool finished;

	// Split the given text with max_chars_line and add them to texts list
	void SplitText(std::string text);
public:
	Dialog();
	~Dialog();

	// Add a node and return its ID
	size_t AddNode(DialogNode& node, bool reset=true);

	// Set follow node
	void SetFollowNode(size_t node_origin, size_t node_index, size_t node_dest);

	// Set NPC
	void SetNPC(NPC* npc);

	// Valid node
	bool ValidNode(size_t node);

	// Set a node ID as active
	void SetActiveNode(size_t id);

	// Update dialog
	void Update();

	// Return if the dialog has finished
	bool Finished() { return finished; }

	// Set position of dialog
	void SetPosition(int x, int y);

	// Set the dialog font
	void SetFont(int font);

	// Set the dialog background image
	void SetDialogBg(SDL_Texture* dialog_bg, int width, int height);

	// Reset dialog
	void ResetDialog(size_t startNode);
};