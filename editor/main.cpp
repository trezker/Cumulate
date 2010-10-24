/* Tab to open/close menu
 * Menu appears on the side, vertical layout listing the tools.
 * Click on a tool to select it.
 * 	The tool expands to show its options.
 * 	Previous tool closes.
 * 	Layout adjusts.
 * If the menu is too large, use middle button drag.
 * */
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "menu.h"
#include "platform.h"
#include "create_platform.h"
#include "edit_platform.h"
#include "file.h"
#include <iostream>

int main(int argc, const char* argv[])
{
	al_init();
	
	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_DISPLAY *display;
	al_set_new_display_flags(ALLEGRO_WINDOWED);
	display = al_create_display(800, 600);

	al_install_keyboard();
	al_install_mouse();

	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, (ALLEGRO_EVENT_SOURCE *)display);
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());

	ALLEGRO_FONT* font = al_load_ttf_font("data/times.ttf", 12, 0);

	Vector2 camera(-400, -300);
	
	Platforms platforms;
	Create_platform* create_platform = new Create_platform(platforms, camera, font);
	Edit_platform* edit_platform = new Edit_platform(platforms, camera, font);
	File* file = new File(platforms, font);
	
	Menu menu;
	menu.Add_entry(create_platform);
	menu.Add_entry(edit_platform);
	menu.Add_entry(file);

	if(argc==2)
		file->Load(argv[1]);

	while(1)
	{
		ALLEGRO_EVENT event;
		if (al_get_next_event(event_queue, &event))
		{
			if (ALLEGRO_EVENT_DISPLAY_CLOSE == event.type ||
					ALLEGRO_EVENT_KEY_DOWN == event.type &&
					ALLEGRO_KEY_ESCAPE == event.keyboard.keycode)
			{
				break;
			}
			menu.Event(event);
		}

		for(Platforms::iterator i = platforms.begin(); i != platforms.end(); ++i)
		{
			(*i)->Draw(camera, al_map_rgb_f(0, 1, 0));
		}
		
		menu.Draw();

		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));

		al_rest(0.001);
	}

	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
}
