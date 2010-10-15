#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include "player.h"

int main()
{	
	al_init();

	al_init_image_addon();

	ALLEGRO_DISPLAY *display;
	al_set_new_display_flags(ALLEGRO_WINDOWED);
	display = al_create_display(800, 600);
	
	al_install_keyboard();

	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, (ALLEGRO_EVENT_SOURCE *)display);
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	Player player;
	player.Set_position(20, al_get_display_height(display));

	float last_update = al_current_time();
	float dt;

	while(1)
	{
		float current_time = al_current_time();
		dt = current_time - last_update;
		last_update = current_time;
		
		ALLEGRO_EVENT event;
		if (al_get_next_event(event_queue, &event))
		{
			if (ALLEGRO_EVENT_DISPLAY_CLOSE == event.type ||
					ALLEGRO_EVENT_KEY_DOWN == event.type &&
					ALLEGRO_KEY_ESCAPE == event.keyboard.keycode)
			{
				break;
			}
			player.Event(event);
		}
		
		player.Update(dt);

		player.Draw();
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));

		al_rest(0.001);
	}

	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
}
