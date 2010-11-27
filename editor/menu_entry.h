#ifndef menu_entry_h
#define menu_entry_h

#include <allegro5/allegro5.h>

class Menu_entry
{
public:
	Menu_entry();
	virtual ~Menu_entry();
	virtual void Draw();
	virtual void Event(ALLEGRO_EVENT& event);
	virtual void Open();
	virtual void Close();
	void Set_position(int x, int y);
	void Set_size(int w, int h);
public:
	int x;
	int y;
	int w;
	int h;
	bool resized;
};

ALLEGRO_PATH *Get_relative_path(const ALLEGRO_PATH* abspath);

#endif
