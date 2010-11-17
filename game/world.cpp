#include "world.h"
#include "render_box2d.h"
#include <map>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <algorithm>

World::World()
{
	b2Vec2 gravity(0.0f, 40.0f);
	world = new b2World(gravity, true);

	player.Create_body(world);
	script_manager.Set_player(&player);
	script_manager.Set_world(this);

	world->SetContactListener(&cl);
	
	show_bodies = false;

	show_console = false;
	font = al_load_ttf_font("data/times.ttf", 12, 0);
	console_input = al_ustr_new("");
	
	Entity* entity = new Entity();
	Bitmap* entimage = new Bitmap("data/enemy.png");
	entity->Set_image(entimage);
	entity->Create_body(world);
	entity->Set_position(0, -10);
	entities.push_back(entity);
}

World::~World()
{
	delete world;
}

void World::Event(ALLEGRO_EVENT& event)
{
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

void World::Update(float dt)
{
	player.Update(dt);
	world->Step(dt, 6, 2);
	world->ClearForces();

	camera = 10*player.Get_position();
	camera.x -= 400;
	camera.y -= 300;
}

void World::Draw()
{
	for(Sprites::iterator i = sprites.begin(); i != sprites.end(); ++i)
		(*i)->Draw(Vector2(camera.x, camera.y));

	for(Entities::iterator i = entities.begin(); i!= entities.end(); ++i)
		(*i)->Draw(camera);
	
	player.Draw(camera);

	if(show_bodies)
	{
		for(b2Body* body = world->GetBodyList(); body; body = body->GetNext())
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
}

void World::Load(const char* filename)
{
	for(Platforms::iterator i = platforms.begin(); i!=platforms.end(); ++i)
	{
		delete *i;
	}
	platforms.clear();
	bitmaps.clear();
	sprites.clear();

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
			platforms.push_back(platform);
		}
		if((*i)->Get_name() == "bitmap")
		{
			std::string filename = (*i)->Get_child("filename")->Get_value();
			int id = sinxml::fromstring<int>((*i)->Get_child("id")->Get_value());
			
			Bitmap* bitmap = new Bitmap(filename);
			bitmaps.push_back(bitmap);
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
			sprites.push_back(sprite);
		}
	}

	for(Platforms::iterator i = platforms.begin(); i!=platforms.end(); ++i)
		(*i)->Create_body(*world);
}

b2World* World::Get_b2world()
{
	return world;
}

void World::Add_entity(Entity* e)
{
	Entities::iterator i = std::find(entities.begin(), entities.end(), e);
	if(i!=entities.end())
		return;
	entities.push_back(e);
}

void World::Remove_entity(Entity* e)
{
	Entities::iterator i = std::find(entities.begin(), entities.end(), e);
	if(i!=entities.end())
		entities.erase(i);
}
