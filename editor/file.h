#ifndef file_h
#define file_h

#include "menu_entry.h"
#include "platform.h"
#include "inputbox.h"
#include "button.h"
#include "bitmap.h"
#include "sprite.h"
#include <allegro5/allegro_font.h>

class File: public Menu_entry
{
public:
	File(ALLEGRO_FONT* font);
	virtual ~File();
	virtual void Draw();
	virtual void Event(ALLEGRO_EVENT& event);
	virtual void Open();
	virtual void Close();

	void Load(const char* filename);
public:
	Platforms* platforms;
	Bitmaps* bitmaps;
	Sprites* sprites;
private:
	ALLEGRO_FONT* font;
	Inputbox inputbox;
	Button savebutton;
	Button loadbutton;
	ALLEGRO_PATH *datapath;
	bool open;
};

#endif
