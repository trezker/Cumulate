#ifndef menu_h
#define menu_h

#include <allegro5/allegro5.h>
#include <vector>

class Menu_entry;

class Menu
{
public:
	Menu();
	~Menu();
	void Add_entry(Menu_entry* entry);
	void Update_layout();
	void Draw();
	void Event(ALLEGRO_EVENT& event);
private:
	typedef std::vector<Menu_entry*> Entries;
	Entries entries;
	int w;
	int h;
	Menu_entry* active;
};

#endif
