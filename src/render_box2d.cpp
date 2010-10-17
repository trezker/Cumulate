#include "render_box2d.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "player.h"
#include <iostream>

void Draw_body(b2Body* body, b2Vec2 camera)
{
	float scale = 10;
	b2Vec2 position = scale*body->GetPosition() - camera;
	float32 angle = body->GetAngle();

	al_draw_pixel(position.x, position.y, al_map_rgb_f(1, 0, 0));

	for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext())
	{
		b2Shape* shape_base = f->GetShape();
		if(shape_base->GetType() == b2Shape::e_polygon)
		{
			b2PolygonShape& shape = dynamic_cast<b2PolygonShape&>(*shape_base);
			int np = shape.GetVertexCount ();
			b2Vec2 pn = scale*shape.GetVertex(np-1);
			b2Vec2 ps, pe;
			ps.x = cos(angle)*pn.x - sin(angle)*pn.y;
			ps.y = sin(angle)*pn.x + cos(angle)*pn.y;
			for(int i=0; i<np; ++i)
			{
				pn = scale*shape.GetVertex(i);
				pe.x = cos(angle)*pn.x - sin(angle)*pn.y;
				pe.y = sin(angle)*pn.x + cos(angle)*pn.y;
				al_draw_line(position.x+ps.x, position.y+ps.y, position.x+pe.x, position.y+pe.y, al_map_rgb_f(1, 0, 0), 0);
				ps = pe;
			}
		}
		if(shape_base->GetType() == b2Shape::e_circle)
		{
			b2CircleShape& shape = dynamic_cast<b2CircleShape&>(*shape_base);
			al_draw_circle(position.x, position.y, shape.m_radius * scale, al_map_rgb_f(1, 0, 0), 0);
		}
	}
}
