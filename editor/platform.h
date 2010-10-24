#ifndef platform_h
#define platform_h

#include <deque>
#include <allegro5/allegro5.h>
#include "vector2.h"
#include <vector>

typedef std::deque<Vector2> Vertices;

class Platform
{
public:
	Platform();

	void Draw(Vector2 camera, ALLEGRO_COLOR c);

	//Collision shape editing
	void Add_collision_vertex(Vector2 v);
	//Insert a vertex between the two closest existing vertices
	void Insert_collision_vertex(Vector2 v);
	//Move closest vertex to the given point
	void Move_collision_vertex(Vector2 v);
	//Remove closest vertex
	void Remove_collision_vertex(Vector2 v);
	//Set if collision shape is a closed loop
	void Set_collision_loop(bool loop);
	void Set_collision_scale(float s);
	Vector2 Get_vertex(Vector2 v);
	int Nearest_vertex(Vector2 v);
	Vertices& Get_vertices();
private:
	Vertices collision_vertices;
	Vector2 position;
	bool collision_loop;
};

typedef std::vector<Platform*> Platforms;

#endif
