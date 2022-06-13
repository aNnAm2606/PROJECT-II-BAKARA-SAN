#include "Button.h"
#include "Render.h"
#include "App.h"
#include "Audio.h"
#include "Input.h"
#include "Fonts.h"

Button::Button()
{
}

Button::Button(SDL_Rect bounds, SDL_Texture* texture, const char* text, int font)
{
	this->texture = texture;
	this->bounds = bounds;
	this->text = text;
	this->font = font;

	canClick = true;
	drawBasic = false;
	use_font_states = false;

	state = State::NORMAL;
}

Button::~Button()
{

}

void Button::SetPosition(int x, int y)
{
	bounds.x = x;
	bounds.y = y;
}

void Button::SetFontStates(int base, int highlight, int press)
{
	font = base;
	hfont = highlight;
	pfont = press;

	use_font_states = true;
}

bool Button::Update()
{
	if (state != State::DISABLED)
	{
		// L14: TODO 3: Update the state of the GUiButton according to the mouse position
		int mouseX, mouseY;
		app->input->GetMousePosition(mouseX, mouseY);

		if ((mouseX > bounds.x ) && (mouseX < (bounds.x + bounds.w )) &&
			(mouseY > bounds.y ) && (mouseY < (bounds.y + bounds.h )))
		{
			state = State::FOCUSED;

			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
			{
				state = State::PRESSED;
			}

			// If mouse button pressed -> Generate event!
			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
			{
				clicked = true;
			}
		}
		else state = State::NORMAL;
	}

	return false;
}

bool Button::Draw()
{
	if (texture) {
		app->render->DrawTextureScaled(texture, bounds.x, bounds.y, bounds.w, bounds.h, NULL, false);
	}

	Font& fontobj = app->fonts->GetFont(font);

	if (use_font_states) {
		if (state == State::FOCUSED) {
			fontobj = app->fonts->GetFont(hfont);
		}
		else if (state == State::PRESSED) {
			fontobj = app->fonts->GetFont(pfont);
		}
	}
	
	int textXOffset = bounds.w / 2 - fontobj.char_w * text.length() / 2;
	int textYOffset = bounds.h / 2 - fontobj.char_h / 2;

	app->fonts->BlitText(bounds.x + textXOffset, bounds.y + textYOffset, font, text.c_str(), false);

	return false;
}