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
#include "create_sprite.h"
#include "edit_sprite.h"
#include <iostream>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

int main(int argc, const char* argv[])
{
	al_init();
	
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();
	al_init_primitives_addon();

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
	Bitmaps bitmaps;
	Sprites sprites;
	
	File* file = new File(font);
	file->platforms = &platforms;
	file->bitmaps = &bitmaps;
	file->sprites = &sprites;
	
	Menu menu;
	menu.Add_entry(new Create_platform(platforms, camera, font));
	menu.Add_entry(new Edit_platform(platforms, camera, font));
	menu.Add_entry(file);
	menu.Add_entry(new Create_sprite(bitmaps, sprites, camera, font));
	menu.Add_entry(new Edit_sprite(sprites, camera, font));

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
			if(ALLEGRO_EVENT_MOUSE_AXES)
			{
				ALLEGRO_MOUSE_STATE mstate;
				al_get_mouse_state(&mstate);
				if(al_mouse_button_down(&mstate, 3))
				{
					camera.x -= event.mouse.dx;
					camera.y -= event.mouse.dy;
				}
			}
			menu.Event(event);
		}

		for(Sprites::iterator i = sprites.begin(); i != sprites.end(); ++i)
		{
			(*i)->Draw(camera);
		}
		for(Platforms::iterator i = platforms.begin(); i != platforms.end(); ++i)
		{
			(*i)->Draw(camera, al_map_rgb_f(0, 1, 0));
		}
		
		al_draw_line(0, -camera.y, 800, -camera.y, al_map_rgba_f(0, 1, 0, 0.5), 0);
		al_draw_line(-camera.x, 0, -camera.x, 600, al_map_rgba_f(0, 0, 1, 0.5), 0);
		
		menu.Draw();

		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));

		al_rest(0.001);
	}

	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
}
