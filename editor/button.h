#ifndef button_h
#define button_h

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

class Button
{
public:
	Button();
	virtual ~Button();
	void Set_font(ALLEGRO_FONT* font);
	void Set_text(const char* t);
	bool Get_active();
	void Set_active(bool a);
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
	ALLEGRO_USTR* text;
	ALLEGRO_FONT* font;
	bool pressed;
	bool active;
};

#endif
