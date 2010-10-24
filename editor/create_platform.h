#ifndef create_platform_h
#define create_platform_h

#include "menu_entry.h"
#include "platform.h"
#include <allegro5/allegro_font.h>

class Create_platform: public Menu_entry
{
public:
	Create_platform(Platforms& platforms, Vector2& camera, ALLEGRO_FONT* font);
	virtual ~Create_platform();
	virtual void Draw();
	virtual void Event(ALLEGRO_EVENT& event);
	virtual void Open();
	virtual void Close();
private:
	Platforms* platforms;
	Vector2* camera;
	Platform* platform;
	ALLEGRO_FONT* font;
	Vector2 nearest;
	Vector2 mouse;
};

#endif
