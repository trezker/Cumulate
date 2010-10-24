#include "menu.h"
#include "menu_entry.h"
#include <allegro5/allegro_primitives.h>

Menu::Menu():
w(0),
h(0),
active(NULL)
{
}

Menu::~Menu()
{
	for(Entries::iterator i = entries.begin(); i != entries.end(); ++i)
	{
		delete *i;
	}
}

void Menu::Add_entry(Menu_entry* entry)
{
	entries.push_back(entry);
	Update_layout();
}

void Menu::Update_layout()
{
	int y = 1;
	w = 0;
	h = 0;
	for(Entries::iterator i = entries.begin(); i != entries.end(); ++i)
	{
		(*i)->y = y;
		(*i)->x = 1;
		y += (*i)->h;
		w = w>(*i)->w?w:(*i)->w;
		h += (*i)->h;
	}
	for(Entries::iterator i = entries.begin(); i != entries.end(); ++i)
	{
		(*i)->w = w;
	}
	w += 2;
}

void Menu::Draw()
{
	for(Entries::iterator i = entries.begin(); i != entries.end(); ++i)
	{
		(*i)->Draw();
	}
}

void Menu::Event(ALLEGRO_EVENT& event)
{
	if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
	{
		if(event.mouse.x < w)
			return;
	}
	if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
	{
		//If on menu but outside active entry, open other entry.
		if(event.mouse.x < w)// && event.mouse.y < h)
		{
			for(Entries::iterator i = entries.begin(); i != entries.end(); ++i)
			{
				int ey = (*i)->y;
				int eh = (*i)->h;
				if(event.mouse.y < ey + eh && event.mouse.y > ey )
				{
					if(*i == active)
						break;
					if(active) 
						active->Close();
					active = *i;
					active->Open();
					Update_layout();
					return;
				}
			}
		}
	}
	
	if(active)
	{
		active->Event(event);
	}
}
