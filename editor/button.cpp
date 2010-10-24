#include "button.h"
#include <allegro5/allegro_primitives.h>

Button::Button():
x(0),
y(0),
w(0),
h(0),
font(NULL),
pressed(false),
active(false)
{
	text = al_ustr_new("");
}

Button::~Button()
{
	al_ustr_free(text);
}

void Button::Set_font(ALLEGRO_FONT* ifont)
{
	font = ifont;
}

void Button::Set_text(const char* t)
{
	al_ustr_assign_cstr(text, t);
}

bool Button::Get_active()
{
	return active;
}

void Button::Set_active(bool a)
{
	active = a;
}

void Button::Draw()
{
	ALLEGRO_COLOR color = al_map_rgb_f(1, 1, 1);
	ALLEGRO_COLOR back_color = al_map_rgb_f(1, .9, .9);
	al_draw_rectangle(x, y, x+w, y+h, back_color, 0);
	al_draw_text(font, color, x, y, 0, al_cstr(text));
}

void Button::Event(ALLEGRO_EVENT& event)
{
	if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && Covers_point(event.mouse.x, event.mouse.y))
	{
		pressed = true;
	}
	if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
	{
		pressed = false;
		if(Covers_point(event.mouse.x, event.mouse.y))
			active = true;
	}
}

void Button::Set_position(int ix, int iy)
{
	x = ix;
	y = iy;
}

void Button::Set_size(int iw, int ih)
{
	w = iw;
	h = ih;
}

bool Button::Covers_point(int ix, int iy)
{
	if(ix > x && ix < x+w && iy > y && iy < y+h)
	{
		return true;
	}
	return false;
}
