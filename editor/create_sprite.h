#ifndef create_sprite_h
#define create_sprite_h

#include "menu_entry.h"
#include "sprite.h"
#include <allegro5/allegro_font.h>
#include "inputbox.h"
#include "button.h"
#include "thumbnail_list.h"

class Create_sprite: public Menu_entry
{
public:
	Create_sprite(Bitmaps& bitmaps, Sprites& sprites, Vector2& camera, ALLEGRO_FONT* font);
	virtual ~Create_sprite();
	virtual void Draw();
	virtual void Event(ALLEGRO_EVENT& event);
	virtual void Open();
	virtual void Close();
private:
	Bitmaps* bitmaps;
	Sprites* sprites;
	Vector2* camera;
	Sprite* sprite;
	ALLEGRO_FONT* font;
	Vector2 nearest;
	Vector2 mouse;
	int selected;
	Inputbox inputbox;
	Button loadbutton;
	bool open;
	Thumbnail_list thumbnail_list;
};

#endif
