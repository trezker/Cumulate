#include "platform.h"
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <cmath>

Platform::Platform()
{
	collision_loop = false;
	position.x = 0;
	position.y = 0;
}

void Platform::Draw(Vector2 camera, ALLEGRO_COLOR c)
{
	int np = collision_vertices.size();
	if(np == 0)
	{
		return;
	}
	Vector2 pn = collision_vertices[0];
	Vector2 ps, pe;
	float angle = 0;
	ps.x = cos(angle)*pn.x - sin(angle)*pn.y;
	ps.y = sin(angle)*pn.x + cos(angle)*pn.y;
	for(int i=1; i<np; ++i)
	{
		pn = collision_vertices[i];
		pe.x = cos(angle)*pn.x - sin(angle)*pn.y;
		pe.y = sin(angle)*pn.x + cos(angle)*pn.y;
		al_draw_line(ps.x - camera.x, ps.y - camera.y, pe.x - camera.x, pe.y - camera.y, c, 0);
		
		Vector2 middle = (pe+ps)/2-camera;
		float a = (pe-ps).Angle()-M_PI/2;
		al_draw_line(middle.x, middle.y, middle.x+cos(a)*5, middle.y+sin(a)*5, c, 0);
		
		ps = pe;
	}
}

void Platform::Add_collision_vertex(Vector2 v)
{
	collision_vertices.push_back(v);
	position = Vector2(0, 0);
	for(Vertices::iterator i = collision_vertices.begin(); i!=collision_vertices.end(); ++i)
		position+=*i;
	position.x = position.x/collision_vertices.size();
	position.y = position.y/collision_vertices.size();
}

void Platform::Insert_collision_vertex(Vector2 v)
{
}

void Platform::Move_collision_vertex(Vector2 v)
{
	collision_vertices[Nearest_vertex(v)] = v;
}

void Platform::Remove_collision_vertex(Vector2 v)
{
}

void Platform::Set_collision_loop(bool loop)
{
}

void Platform::Set_collision_scale(float s)
{
}

Vector2 Platform::Get_vertex(Vector2 v)
{
	return collision_vertices[Nearest_vertex(v)];
}

int Platform::Nearest_vertex(Vector2 v)
{
	Vector2 r(*collision_vertices.begin());
	int index = 0;
	int n = 0;
	for(Vertices::iterator i = collision_vertices.begin(); i!=collision_vertices.end(); ++i, ++n)
	{
		if( (r-v).Length_squared() > ((*i)-v).Length_squared() )
		{
			r = *i;
			index = n;
		}
	}
	return index;
}

Vertices& Platform::Get_vertices()
{
	return collision_vertices;
}
