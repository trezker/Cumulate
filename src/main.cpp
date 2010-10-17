#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include "player.h"
#include "platform.h"
#include "contactlistener.h"

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

	b2Vec2 gravity(0.0f, 40.0f);
	b2World world(gravity, true);

	Player player;
	player.Create_body(&world);

	Platform platform;
	platform.Add_collision_vertex(b2Vec2(-130, -40));
	platform.Add_collision_vertex(b2Vec2(-110, -20));
	platform.Add_collision_vertex(b2Vec2(-90, -40));
	platform.Add_collision_vertex(b2Vec2(-70, -20));
	platform.Add_collision_vertex(b2Vec2(-30, -20));
	platform.Add_collision_vertex(b2Vec2(30, -20));
	platform.Add_collision_vertex(b2Vec2(50, -30));
	platform.Add_collision_vertex(b2Vec2(70, -50));
	platform.Add_collision_vertex(b2Vec2(90, -80));
	platform.Add_collision_vertex(b2Vec2(110, -120));
	platform.Add_collision_vertex(b2Vec2(130, -170));
	platform.Create_body(world);

	ContactListener cl;
	world.SetContactListener(&cl);

	float acctime = 0;
	float32 timeStep = 1.0f / 60.0f;
	
	b2Vec2 camera(0.0f, 0.0f);

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

		acctime += dt;
		while(acctime>timeStep)
		{
			player.Update(timeStep);

			acctime-=timeStep;
			world.Step(timeStep, 6, 2);
			world.ClearForces();

			camera = 10*player.Get_position();
			camera.x -= 400;
			camera.y -= 300;
		}


		platform.Draw(camera);
		player.Draw(camera);
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));

		al_rest(0.001);
	}

	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
}
