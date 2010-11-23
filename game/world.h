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
#include <map>
#include <deque>

typedef std::vector<Platform*> Platforms;
typedef std::map<std::string, Bitmap*> Imagemap;

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
	Bitmap* Get_image(const std::string& filename);
	void Add_entity(Entity* e);
	void Remove_entity(Entity* e);
	
	b2World *Get_b2world();
	int Get_script(const std::string& filename);
private:
	b2World *world;
	Player player;
	Platforms platforms;
	Bitmaps bitmaps;
	Sprites sprites;
	Imagemap images;
	Entities entities;
	Script_manager script_manager;
	b2Vec2 camera;
	bool show_bodies;
	ContactListener cl;
	bool show_console;
	ALLEGRO_FONT* font;
	ALLEGRO_USTR* console_input;
	ALLEGRO_USTR* console_stash;
	typedef std::deque<ALLEGRO_USTR*> Console_history;
	Console_history console_history;
	int console_lookup;
};

#endif
