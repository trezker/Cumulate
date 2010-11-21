#ifndef entity_h
#define entity_h
#include <allegro5/allegro5.h>
#include <Box2D/Box2D.h>
#include "bitmap.h"
#include <vector>

class Entity
{
public:
	Entity();
	~Entity();
	void Set_image(Bitmap* i);
	void Create_body(b2World* world);
	void Destroy_body();
	void Set_position(float x, float y);
	b2Vec2 Get_position();
	b2Vec2 Get_linear_velocity();
	void Set_linear_velocity(b2Vec2 v);
	void Update(float dt);
	void Draw(b2Vec2 camera);
	void Set_script_reference(int r);
	int Get_script_reference();
private:
	b2Body* body;
	Bitmap* image;
	int script_reference;
};

typedef std::vector<Entity*> Entities;

#endif
