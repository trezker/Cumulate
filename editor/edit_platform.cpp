#include "edit_platform.h"
#include <allegro5/allegro_primitives.h>

Edit_platform::Edit_platform(Platforms& iplatforms, Vector2& icamera, ALLEGRO_FONT* ifont)
:platforms(&iplatforms),
camera(&icamera),
platform(NULL),
font(ifont),
holding(false)
{
	w = al_get_text_width(font, "Create platform") + 4;
	h = al_get_font_line_height(font) + 4;
}

Edit_platform::~Edit_platform()
{
}

void Edit_platform::Draw()
{
	ALLEGRO_COLOR color = al_map_rgb_f(1, 1, 1);
	ALLEGRO_COLOR back_color = al_map_rgb_f(1, .9, .9);
	al_draw_rectangle(x, y, x+w, y+h, back_color, 0);
	al_draw_text(font, color, x+w/2, y+2, ALLEGRO_ALIGN_CENTRE, "Edit platform");

	if(platform)
	{
		platform->Draw(*camera, al_map_rgb_f(1, 0, 0));
//		al_draw_line(nearest.x-camera->x, nearest.y-camera->y, mouse.x-camera->x, mouse.y-camera->y, color, 0);
	}
}

void Edit_platform::Event(ALLEGRO_EVENT& event)
{
	if(event.type == ALLEGRO_EVENT_MOUSE_AXES)
	{
		mouse.Set(event.mouse.x, event.mouse.y);
		mouse += *camera;
		if(platform && holding)
		{
			platform->Move_collision_vertex(mouse);
		}
	}

	if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
	{
		if(event.mouse.button == 1)
		{
			if(platform)
			{
				holding = true;
				platform->Move_collision_vertex(mouse);
			}
		}
	}
	if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
	{
		if(event.mouse.button == 1)
		{
			holding = false;
		}
		if(event.mouse.button == 2)
		{
			holding = false;
			float n = 10000;
			for(Platforms::iterator i = platforms->begin(); i != platforms->end(); ++i)
			{
				Vector2 p = (*i)->Get_vertex(mouse);
				if((p-mouse).Length_squared()<n)
				{
					platform = *i;
					nearest = p;
					n = (p-mouse).Length_squared();
				}
			}
		}
	}
}

void Edit_platform::Open()
{
}

void Edit_platform::Close()
{
	if(platform)
		platform = NULL;
}
