#include "create_platform.h"
#include <allegro5/allegro_primitives.h>

Create_platform::Create_platform(Platforms& iplatforms, Vector2& icamera, ALLEGRO_FONT* ifont)
:platforms(&iplatforms),
camera(&icamera),
platform(NULL),
font(ifont)
{
	w = al_get_text_width(font, "Create platform") + 4;
	h = al_get_font_line_height(font) + 4;
}

Create_platform::~Create_platform()
{
}

void Create_platform::Draw()
{
	ALLEGRO_COLOR color = al_map_rgb_f(1, 1, 1);
	ALLEGRO_COLOR back_color = al_map_rgb_f(1, .9, .9);
	al_draw_rectangle(x, y, x+w, y+h, back_color, 0);
	al_draw_text(font, color, x+w/2, y+2, ALLEGRO_ALIGN_CENTRE, "Create platform");

	if(platform)
	{
		platform->Draw(*camera, al_map_rgb_f(1, 0, 0));
		al_draw_line(nearest.x-camera->x, nearest.y-camera->y, mouse.x-camera->x, mouse.y-camera->y, color, 0);
	}
}

void Create_platform::Event(ALLEGRO_EVENT& event)
{
	if(event.type == ALLEGRO_EVENT_MOUSE_AXES)
	{
		mouse.Set(event.mouse.x, event.mouse.y);
		mouse += *camera;
	}

	if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
	{
		if(event.mouse.button == 1)
		{
			if(platform == NULL)
			{
				platform = new Platform();
			}
			nearest = mouse;
			platform->Add_collision_vertex(nearest);
		}
		if(event.mouse.button == 2)
		{
			if(platform)
			{
				if(platform->Get_vertices().size()>1)
					platforms->push_back(platform);
				else
					delete platform;
				platform = NULL;
			}
		}
	}
}

void Create_platform::Open()
{
}

void Create_platform::Close()
{
	if(platform)
	{
		delete platform;
		platform = NULL;
	}
}
