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
	void Set_position(float x, float y);
	b2Vec2 Get_position();
	void Update(float dt);
	void Draw(b2Vec2 camera);
private:
	b2Body* body;
	Bitmap* image;
};

typedef std::vector<Entity*> Entities;

#endif