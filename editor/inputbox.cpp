#include "inputbox.h"

Inputbox::Inputbox():
x(0),
y(0),
w(0),
h(0),
font(NULL)
{
	text = al_ustr_new("");
}

Inputbox::~Inputbox()
{
	al_ustr_free(text);
}

void Inputbox::Set_font(ALLEGRO_FONT* ifont)
{
	font = ifont;
}

void Inputbox::Set_text(const char* t)
{
	al_ustr_assign_cstr(text, t);
}

ALLEGRO_USTR* Inputbox::Get_text()
{
	return text;
}

void Inputbox::Draw()
{
	ALLEGRO_COLOR color = al_map_rgb_f(1, 1, 1);
	al_draw_text(font, color, x, y, 0, al_cstr(text)) ;
}

void Inputbox::Event(ALLEGRO_EVENT& event)
{
	if(event.type == ALLEGRO_EVENT_KEY_DOWN || event.type == ALLEGRO_EVENT_KEY_REPEAT)
	{
		if(event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE)
		{
			int pos = al_ustr_offset(text, -1);
			al_ustr_remove_chr(text, pos);
			return;
		}
	}
	if(event.type == ALLEGRO_EVENT_KEY_DOWN)
	{
		al_ustr_append_chr(text, event.keyboard.unichar);
	}
}

void Inputbox::Set_position(int ix, int iy)
{
	x = ix;
	y = iy;
}

void Inputbox::Set_size(int iw, int ih)
{
	w = iw;
	h = ih;
}
