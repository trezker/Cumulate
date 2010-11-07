#ifndef edit_sprite_h
#define edit_sprite_h

#include "menu_entry.h"
#include "sprite.h"
#include <allegro5/allegro_font.h>
#include "inputbox.h"
#include "button.h"
#include "thumbnail_list.h"

class Edit_sprite: public Menu_entry
{
public:
	Edit_sprite(Sprites& sprites, Vector2& camera, ALLEGRO_FONT* font);
	virtual ~Edit_sprite();
	virtual void Draw();
	virtual void Event(ALLEGRO_EVENT& event);
	virtual void Open();
	virtual void Close();
private:
	Sprites* sprites;
	Vector2* camera;
	Sprite* sprite;
	ALLEGRO_FONT* font;
	Vector2 nearest;
	Vector2 mouse;
	bool open;
	bool holding;
	Vector2 hold_offset;
};

#endif
