#ifndef file_h
#define file_h

#include "menu_entry.h"
#include "platform.h"
#include "inputbox.h"
#include "button.h"
#include <allegro5/allegro_font.h>

class File: public Menu_entry
{
public:
	File(Platforms& platforms, ALLEGRO_FONT* font);
	virtual ~File();
	virtual void Draw();
	virtual void Event(ALLEGRO_EVENT& event);
	virtual void Open();
	virtual void Close();

	void Load(const char* filename);
private:
	Platforms* platforms;
	ALLEGRO_FONT* font;
	Inputbox inputbox;
	Button savebutton;
	Button loadbutton;
	bool open;
};

#endif
