#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "player.h"
#include "platform.h"
#include "bitmap.h"
#include "sprite.h"
#include "contactlistener.h"
#include <sinxml/sinxml.h>
#include <map>
#include "render_box2d.h"
#include "script_manager.h"

/*
 * Scripts
 * When an object wants to use a scripted object, 
 * set a flag on that object and which object wants to use it.
 * It will then act on that flag next update.
 * A flag like this is a one time thing, 
 * */

typedef std::vector<Platform*> Platforms;

void Load(const char* filename, Platforms* platforms, Bitmaps* bitmaps, Sprites* sprites)
{
	for(Platforms::iterator i = platforms->begin(); i!=platforms->end(); ++i)
	{
		delete *i;
	}
	platforms->clear();
	bitmaps->clear();
	sprites->clear();
	
	typedef std::map<int, Bitmap*> Idbmpmap;
	Idbmpmap idbmpmap;

	sinxml::Document doc("1.0");
	if(!doc.Load_file(filename))
		return;
	sinxml::Children& mapchildren = doc.Get_root()->Get_children();
	for(sinxml::Children::iterator i = mapchildren.begin(); i != mapchildren.end(); ++i)
	{
		if((*i)->Get_name() == "platform")
		{
			Platform* platform = new Platform;
			sinxml::Children& platformchildren = (*i)->Get_children();
			for(sinxml::Children::iterator j = platformchildren.begin(); j != platformchildren.end(); ++j)
			{
				float x = sinxml::fromstring<float>((*j)->Get_child("x")->Get_value());
				float y = sinxml::fromstring<float>((*j)->Get_child("y")->Get_value());
				platform->Add_collision_vertex(Vector2(x, y));
			}
			platforms->push_back(platform);
		}
		if((*i)->Get_name() == "bitmap")
		{
			std::string filename = (*i)->Get_child("filename")->Get_value();
			int id = sinxml::fromstring<int>((*i)->Get_child("id")->Get_value());
			
			Bitmap* bitmap = new Bitmap(filename);
			bitmaps->push_back(bitmap);
			idbmpmap[id] = bitmap;
		}
	}
	for(sinxml::Children::iterator i = mapchildren.begin(); i != mapchildren.end(); ++i)
	{
		if((*i)->Get_name() == "sprite")
		{
			int id = sinxml::fromstring<int>((*i)->Get_child("id")->Get_value());
			float x = sinxml::fromstring<float>((*i)->Get_child("x")->Get_value());
			float y = sinxml::fromstring<float>((*i)->Get_child("y")->Get_value());
			Sprite* sprite = new Sprite(idbmpmap[id]);
			sprite->Set_position(Vector2(x, y));
			sprites->push_back(sprite);
		}
	}
}

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

	Script_manager script_manager;

	b2Vec2 gravity(0.0f, 40.0f);
	b2World world(gravity, true);

	Player player;
	player.Create_body(&world);

	Platforms platforms;
	Bitmaps bitmaps;
	Sprites sprites;
	if(argc==2)
	{
		Load(argv[1], &platforms, &bitmaps, &sprites);
	}
	else
	{
		Load("data/test.map", &platforms, &bitmaps, &sprites);
	}
	for(Platforms::iterator i = platforms.begin(); i!=platforms.end(); ++i)
		(*i)->Create_body(world);
	
	ContactListener cl;
	world.SetContactListener(&cl);

	float acctime = 0;
	float32 timeStep = 1.0f / 60.0f;
	
	b2Vec2 camera(0.0f, 0.0f);

	bool show_bodies = false;
	bool show_console = false;
	ALLEGRO_FONT* font = al_load_ttf_font("data/times.ttf", 12, 0);
	ALLEGRO_USTR* console_input = al_ustr_new("");


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

			if (ALLEGRO_EVENT_KEY_DOWN == event.type)
			{
				if (ALLEGRO_KEY_F9 == event.keyboard.keycode)
				{
					show_bodies = !show_bodies;
				}

				if (ALLEGRO_KEY_F12 == event.keyboard.keycode)
				{
					show_console = !show_console;
				}
			}
			if(!show_console)
			{
				player.Event(event);
			}
			else
			{
				//Input for console and call lua
				if(event.type == ALLEGRO_EVENT_KEY_DOWN || event.type == ALLEGRO_EVENT_KEY_REPEAT)
				{
					if(event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE)
					{
						int pos = al_ustr_offset(console_input, -1);
						al_ustr_remove_chr(console_input, pos);
					}
					else if(event.keyboard.keycode == ALLEGRO_KEY_ENTER
						||  event.keyboard.keycode == ALLEGRO_KEY_PAD_ENTER)
					{
						script_manager.Run_string(al_cstr(console_input));
						al_ustr_assign_cstr(console_input, "");
					}
					else
					{
						al_ustr_append_chr(console_input, event.keyboard.unichar);
					}
				}
			}
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


		for(Sprites::iterator i = sprites.begin(); i != sprites.end(); ++i)
			(*i)->Draw(Vector2(camera.x, camera.y));

		player.Draw(camera);

		if(show_bodies)
		{
			for(b2Body* body = world.GetBodyList(); body; body = body->GetNext())
			{
				Draw_body(body, camera);
			}
		}

		if(show_console)
		{
			ALLEGRO_COLOR color = al_map_rgb_f(1, 1, 1);
			al_draw_filled_rectangle(0, 10, 800, 30, al_map_rgb_f(0.1, 0.1, 0.1));
			al_draw_text(font, color, 10, 10, 0, al_cstr(console_input)) ;
		}

		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));

		al_rest(0.001);
	}

	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
}
