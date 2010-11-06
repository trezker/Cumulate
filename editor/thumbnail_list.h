#ifndef thumbnail_list_h
#define thumbnail_list_h

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include "bitmap.h"

class Thumbnail_list
{
public:
	Thumbnail_list();
	virtual ~Thumbnail_list();
	int Get_selected();
	void Set_selected(int s);
	bool Get_changed();
	void Set_changed(bool c);
	void Add_thumbnail(Bitmap* t);
	void Clear();
	
	virtual void Draw();
	virtual void Event(ALLEGRO_EVENT& event);
	void Set_position(int x, int y);
	void Set_size(int w, int h);
	bool Covers_point(int x, int y);
public:
	int x;
	int y;
	int w;
	int h;
	bool pressed;
	bool changed;
	int selected;
	Bitmaps thumbnails;
};

#endif
