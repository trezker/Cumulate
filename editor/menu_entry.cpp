#include "menu_entry.h"

Menu_entry::Menu_entry():
x(0),
y(0),
w(0),
h(0),
resized(false)
{
}

Menu_entry::~Menu_entry()
{
}

void Menu_entry::Draw()
{
}

void Menu_entry::Event(ALLEGRO_EVENT& event)
{
}

void Menu_entry::Open()
{
}

void Menu_entry::Close()
{
}

void Menu_entry::Set_position(int ix, int iy)
{
	x = ix;
	y = iy;
}

void Menu_entry::Set_size(int iw, int ih)
{
	w = iw;
	h = ih;
}
