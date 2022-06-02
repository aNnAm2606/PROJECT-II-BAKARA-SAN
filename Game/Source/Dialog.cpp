#include "Dialog.h"
#include "App.h"
#include "Render.h"
#include "Fonts.h"
#include "Input.h"
#include "NPC.h"

void Dialog::SplitText(std::string text)
{
	std::string line;
	std::string word;

	size_t textLen = text.length();

	for (size_t i = 0; i < textLen; i++) {
		if (text[i] == ' ') {
			if (line.length() + word.length() > max_chars_line) {
				texts.push_back(line);
				line = word;
				line += " ";

				word = "";
			}
			else {
				line += word;
				line += " ";

				word = "";
			}
		}
		else {
			word += text[i];
		}
	}

	if (word.length() > 0) {
		if (line.length() + word.length() > max_chars_line) {
			texts.push_back(line);
			line = word;
		}
		else {
			line += word;
		}

		texts.push_back(line);
	}
}

Dialog::Dialog() : finished(false), activeNode(NULL)
{
	posX = 0;
	posY = 0;
}

Dialog::~Dialog()
{
}

size_t Dialog::AddNode(DialogNode& node, bool reset)
{
	size_t id = nodes.size();

	nodes.push_back(node);

	if (reset) {
		node.text = "";
		node.nodes.clear();
		node.options.clear();
		node.optionsData.clear();
	}

	return id;
}

void Dialog::SetFollowNode(size_t node_origin, size_t node_index, size_t node_dest)
{
	if (ValidNode(node_origin) && ValidNode(node_dest)) {
		if (node_index >= 0 && node_index < nodes[node_origin].nodes.size()) {
			nodes[node_origin].nodes[node_index] = node_dest;
		}
	}
}

void Dialog::SetNPC(NPC* npc)
{
	parentNPC = npc;
}

bool Dialog::ValidNode(size_t node)
{
	return node >= 0 && node < nodes.size();
}

void Dialog::SetActiveNode(size_t id)
{
	if (id >= 0 && id < nodes.size()) {
		activeNode = &nodes[id];

		size_t opts = activeNode->options.size();
		SDL_Rect bounds = {
			posX,
			posY + dialogHeight,
			0,
			dialogHeight / 4
		};

		Font& fontobj = app->fonts->GetFont(dialogFont);

		buttons.clear();
		for (size_t i = 0; i < opts; i++) {
			bounds.w = fontobj.char_w * (activeNode->options[i].length() + 4);
			buttons.emplace_back(bounds, dialogImg, activeNode->options[i].c_str(), dialogFont);
			bounds.x += bounds.w;
		}

		texts.clear();
		SplitText(activeNode->text);

		int lines = texts.size();

		textXOffset = dialogWidth / 2 - (max_chars_line * char_width) / 2;
		textYOffset = dialogHeight / 2 - (lines * char_height) / 2;

		if (lines > 1) {
			textYOffset -= ((lines - 1) * char_height / 2);
		}
	}
}

void Dialog::Update()
{
	GamePad& gamepad = app->input->pads[0];
	
	if (activeNode) {
		app->render->DrawTextureScaled(dialogImg, posX, posY, dialogWidth, dialogHeight, NULL, false);

		size_t lines = texts.size();
		for (size_t i = 0; i < lines; i++) {
			app->fonts->BlitText(posX + textXOffset, posY + textYOffset + char_height * i * 2, dialogFont, texts[i].c_str(), false);
		}

		size_t optionSize = activeNode->options.size();

		for (size_t i = 0; i < optionSize; i++) {
			buttons[i].Update();
			buttons[i].Draw();
		}

		if (optionSize > 0) {
			for (size_t i = 0; i < optionSize; i++) {
				if (buttons[i].clicked) {
					if (i < activeNode->optionsData.size()) {
						parentNPC->OnDialogButton(activeNode->optionsData[i]);
					}
					SetActiveNode(activeNode->nodes[i]);
					break;
				}
			}
		}
		else {
			if (activeNode->nodes.size() > 0) {
				continueButton.Update();
				continueButton.Draw();
				if (app->input->GamepadConnected() == false)
				{
					if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || continueButton.clicked) {
						continueButton.clicked = false;
						SetActiveNode(activeNode->nodes[0]);
					}
				}
				else if (gamepad.a == true || continueButton.clicked)
				{
					continueButton.clicked = false;
					SetActiveNode(activeNode->nodes[0]);
				}
				
			}
			else {
				finishButton.Update();
				finishButton.Draw();

				if (finishButton.clicked) {
					finishButton.clicked = false;
					finished = true;
				}
			}
		}
	}
	else {
		finished = true;
	}
}

void Dialog::SetPosition(int x, int y)
{
	posX = x;
	posY = y;

	continueButton.SetPosition(x, dialogHeight + y);
	finishButton.SetPosition(x, dialogHeight + y);
}

void Dialog::SetFont(int font)
{
	dialogFont = font;

	Font& fontobj = app->fonts->GetFont(dialogFont);

	SDL_Rect bounds = {
			posX,
			posY + dialogHeight,
			fontobj.char_w * (sizeof("continue") + 4),
			dialogHeight / 4
	};

	continueButton = Button(bounds, dialogImg, "continue", dialogFont);

	bounds.w = fontobj.char_w * (sizeof("finish") + 4);
	finishButton = Button(bounds, dialogImg, "finish", dialogFont);

	char_width = fontobj.char_w;
	char_height = fontobj.char_h;

	max_chars_line = dialogWidth / char_width - char_width * 4;
}

void Dialog::SetDialogBg(SDL_Texture* dialog_bg, int width, int height)
{
	dialogImg = dialog_bg;
	dialogWidth = width;
	dialogHeight = height;
	
	SetFont(dialogFont);
}

void Dialog::ResetDialog(size_t startNode)
{
	finished = false;

	SetActiveNode(startNode);
}
