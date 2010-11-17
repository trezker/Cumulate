#ifndef world_h
#define world_h

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include "player.h"
#include "platform.h"
#include "bitmap.h"
#include "sprite.h"
#include "script_manager.h"
#include <sinxml/sinxml.h>
#include "contactlistener.h"
#include "entity.h"

typedef std::vector<Platform*> Platforms;

class b2World;

class World
{
public:
	World();
	~World();
	
	void Event(ALLEGRO_EVENT& event);
	void Update(float dt);
	void Draw();
	
	void Load(const char* filename);
	void Add_entity(Entity* e);
	void Remove_entity(Entity* e);
	
	b2World *Get_b2world();
private:
	b2World *world;
	Player player;
	Platforms platforms;
	Bitmaps bitmaps;
	Sprites sprites;
	Entities entities;
	Script_manager script_manager;
	b2Vec2 camera;
	bool show_bodies;
	ContactListener cl;
	bool show_console;
	ALLEGRO_FONT* font;
	ALLEGRO_USTR* console_input;
};

#endif
