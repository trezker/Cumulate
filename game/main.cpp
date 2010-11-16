#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "world.h"

/*
 * Scripts
 * When an object wants to use a scripted object, 
 * set a flag on that object and which object wants to use it.
 * It will then act on that flag next update.
 * A flag like this is a one time thing, 
 * */


int main(int argc, const char* argv[])
{
	al_init();

	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_DISPLAY *display;
	al_set_new_display_flags(ALLEGRO_WINDOWED);
	display = al_create_display(800, 600);
	
	al_install_keyboard();

	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, (ALLEGRO_EVENT_SOURCE *)display);
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	World world;
	if(argc==2)
	{
		world.Load(argv[1]);
	}
	else
	{
		world.Load("data/test.map");
	}

	float acctime = 0;
	float32 timeStep = 1.0f / 60.0f;
	
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
			world.Event(event);
		}

		acctime += dt;
		while(acctime>timeStep)
		{
			world.Update(timeStep);

			acctime-=timeStep;
		}

		world.Draw();

		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));

		al_rest(0.001);
	}

	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
}
