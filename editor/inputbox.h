#ifndef inputbox_h
#define inputbox_h

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

class Inputbox
{
public:
	Inputbox();
	virtual ~Inputbox();
	void Set_font(ALLEGRO_FONT* font);
	void Set_text(const char* t);
	ALLEGRO_USTR* Get_text();
	virtual void Draw();
	virtual void Event(ALLEGRO_EVENT& event);
	void Set_position(int x, int y);
	void Set_size(int w, int h);
public:
	int x;
	int y;
	int w;
	int h;
	ALLEGRO_USTR* text;
	ALLEGRO_FONT* font;
};

#endif
