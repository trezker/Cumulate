#include "platform.h"
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include "render_box2d.h"

Platform::Platform()
{
	collision_loop = false;
	collision_scale = 10;
	position.x = 0;
	position.y = 0;
	body = NULL;
}

void Platform::Draw(b2Vec2 camera)
{
	if(body)
	{
		Draw_body(body, camera);
	}
	else
	{
		int np = collision_vertices.size();
		if(np == 0)
		{
			return;
		}
		b2Vec2 pn = collision_vertices[0];
		b2Vec2 ps, pe;
		float angle = 0;
		ps.x = cos(angle)*pn.x - sin(angle)*pn.y;
		ps.y = sin(angle)*pn.x + cos(angle)*pn.y;
		for(int i=1; i<np; ++i)
		{
			pn = collision_vertices[i];
			pe.x = cos(angle)*pn.x - sin(angle)*pn.y;
			pe.y = sin(angle)*pn.x + cos(angle)*pn.y;
			al_draw_line(ps.x - camera.x, ps.y - camera.y, pe.x - camera.x, pe.y - camera.y, al_map_rgb_f(1, 0, 0), 0);
			ps = pe;
		}
	}
}

void Platform::Add_collision_vertex(b2Vec2 v)
{
	collision_vertices.push_back(v);
	position = b2Vec2(0, 0);
	for(Vertices::iterator i = collision_vertices.begin(); i!=collision_vertices.end(); ++i)
		position+=*i;
	position.x = position.x/collision_vertices.size();
	position.y = position.y/collision_vertices.size();
}

void Platform::Insert_collision_vertex(b2Vec2 v)
{
}

void Platform::Move_collision_vertex(b2Vec2 v)
{
}

void Platform::Remove_collision_vertex(b2Vec2 v)
{
}

void Platform::Set_collision_loop(bool loop)
{
}

void Platform::Set_collision_scale(float s)
{
}

void Platform::Create_body(b2World& world)
{
	if(body)
	{
		world.DestroyBody(body);
	}
	b2BodyDef bodyDef;
	bodyDef.position.Set(position.x/collision_scale, position.y/collision_scale);
	body = world.CreateBody(&bodyDef);
	body->SetUserData(&physicplatform);

	b2PolygonShape dynamicBox;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.1f;

	b2Vec2 p1 = collision_vertices[0];
	p1.x = (p1.x-position.x)/collision_scale;
	p1.y = (p1.y-position.y)/collision_scale;
	for(int i = 1; i<collision_vertices.size(); ++i)
	{
		b2Vec2 p2 = collision_vertices[i];
		p2.x = (p2.x-position.x)/collision_scale;
		p2.y = (p2.y-position.y)/collision_scale;
		dynamicBox.SetAsEdge(p1, p2);
		b2Fixture* f = body->CreateFixture(&fixtureDef);
		p1 = p2;
	}
}
