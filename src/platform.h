#ifndef platform_h
#define platform_h
#include <Box2D/Box2D.h>
#include <deque>
#include <allegro5/allegro5.h>
#include "physic.h"


class PhysicPlatform: public Physic
{
public:
	PhysicPlatform()
	{
		oneway = true;
	}
	PhysicPlatform(bool ioneway)
	{
		oneway = ioneway;
	}
	bool oneway;
};

class Platform
{
public:
	Platform();

	void Draw(b2Vec2 camera);

	//Collision shape editing
	void Add_collision_vertex(b2Vec2 v);
	//Insert a vertex between the two closest existing vertices
	void Insert_collision_vertex(b2Vec2 v);
	//Move closest vertex to the given point
	void Move_collision_vertex(b2Vec2 v);
	//Remove closest vertex
	void Remove_collision_vertex(b2Vec2 v);
	//Set if collision shape is a closed loop
	void Set_collision_loop(bool loop);
	void Set_collision_scale(float s);
	void Create_body(b2World& world);
private:
	typedef std::deque<b2Vec2> Vertices;
	Vertices collision_vertices;
	b2Vec2 position;
	bool collision_loop;
	float collision_scale;
	PhysicPlatform physicplatform;
	b2Body* body;
};

#endif
