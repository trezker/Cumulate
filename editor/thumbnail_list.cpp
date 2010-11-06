#include "thumbnail_list.h"
#include <allegro5/allegro_primitives.h>

Thumbnail_list::Thumbnail_list():
x(0),
y(0),
w(0),
h(0),
pressed(false),
changed(false),
selected(0)
{
}

Thumbnail_list::~Thumbnail_list()
{
}

bool Thumbnail_list::Get_changed()
{
	return changed;
}

void Thumbnail_list::Set_changed(bool c)
{
	changed = c;
}

int Thumbnail_list::Get_selected()
{
	return selected;
}

void Thumbnail_list::Set_selected(int s)
{
	selected = s;
}

void Thumbnail_list::Add_thumbnail(Bitmap* t)
{
	thumbnails.push_back(t);
}

void Thumbnail_list::Draw()
{
	ALLEGRO_COLOR color = al_map_rgb_f(1, 1, 1);
	ALLEGRO_COLOR back_color = al_map_rgb_f(1, .9, .9);
	al_draw_rectangle(x, y, x+w, y+h, back_color, 0);
	al_draw_rectangle(x, y+selected*30, x+w, y+selected*30+30, color, 0);
	int ty = y;
	for(Bitmaps::iterator i = thumbnails.begin(); i != thumbnails.end(); ++i)
	{
		(*i)->Draw(x, ty);
		ty+=30;
	}
}

void Thumbnail_list::Clear()
{
	thumbnails.clear();
	selected = 0;
}

void Thumbnail_list::Event(ALLEGRO_EVENT& event)
{
	if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && Covers_point(event.mouse.x, event.mouse.y))
	{
		pressed = true;
	}
	if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
	{
		pressed = false;
		if(Covers_point(event.mouse.x, event.mouse.y))
		{
			int newsel = (event.mouse.y-y)/30;
			if(newsel < 0 || newsel >= thumbnails.size())
				newsel = selected;
			if(selected != newsel)
				changed = true;
			selected = newsel;
		}
	}
}

void Thumbnail_list::Set_position(int ix, int iy)
{
	x = ix;
	y = iy;
}

void Thumbnail_list::Set_size(int iw, int ih)
{
	w = iw;
	h = ih;
}

bool Thumbnail_list::Covers_point(int ix, int iy)
{
	if(ix > x && ix < x+w && iy > y && iy < y+h)
	{
		return true;
	}
	return false;
}
