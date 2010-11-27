#include "menu_entry.h"
#include <string>
#include <allegro5/allegro_native_dialog.h>

Menu_entry::Menu_entry():
x(0),
y(0),
w(0),
h(0),
resized(false)
{
}

Menu_entry::~Menu_entry()
{
}

void Menu_entry::Draw()
{
}

void Menu_entry::Event(ALLEGRO_EVENT& event)
{
}

void Menu_entry::Open()
{
}

void Menu_entry::Close()
{
}

void Menu_entry::Set_position(int ix, int iy)
{
	x = ix;
	y = iy;
}

void Menu_entry::Set_size(int iw, int ih)
{
	w = iw;
	h = ih;
}

ALLEGRO_PATH *Get_relative_path(const ALLEGRO_PATH* abspath)
{
	ALLEGRO_PATH *relpath = al_clone_path(abspath);
	while(std::string("data") != al_get_path_component(relpath, 0) && al_get_path_num_components(relpath)>1)
		al_remove_path_component(relpath, 0);
	if(al_get_path_num_components(relpath)<1)
	{
		al_show_native_message_box(NULL, "Bad path", "Not in data", "You must only select files that exist in the games data folder.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_path(relpath);
		return NULL;
	}

	const char *p = al_path_cstr(relpath, '/');
	if(!al_filename_exists(p))
	{
		al_show_native_message_box(NULL, "Bad path", "Not in data", "You must only select files that exist in the games data folder.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_path(relpath);
		return NULL;
	}
	return relpath;
}
