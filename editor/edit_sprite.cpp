#include "edit_sprite.h"
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <algorithm>

Edit_sprite::Edit_sprite(Sprites& isprites, Vector2& icamera, ALLEGRO_FONT* ifont)
:sprites(&isprites)
,camera(&icamera)
,sprite(NULL)
,font(ifont)
,open(false)
,holding(false)
{
	w = al_get_text_width(font, "Edit sprite") + 4;
	h = al_get_font_line_height(font) + 4;
}

Edit_sprite::~Edit_sprite()
{
}

void Edit_sprite::Draw()
{
	ALLEGRO_COLOR color = al_map_rgb_f(1, 1, 1);
	ALLEGRO_COLOR back_color = al_map_rgb_f(1, .9, .9);
	al_draw_rectangle(x, y, x+w, y+h, back_color, 0);
	al_draw_text(font, color, x+w/2, y+2, ALLEGRO_ALIGN_CENTRE, "Edit sprite");

	if(open)
	{
		if(sprite)
		{
			//Draw selection rect
			Vector2 p = sprite->Get_position() - (*camera);
			Vector2 s = sprite->Get_size();
			al_draw_rectangle(p.x, p.y, p.x+s.x, p.y+s.y, color, 0);
		}
	}
}

void Edit_sprite::Event(ALLEGRO_EVENT& event)
{
	if(event.type == ALLEGRO_EVENT_MOUSE_AXES)
	{
		mouse.Set(event.mouse.x, event.mouse.y);
		ALLEGRO_KEYBOARD_STATE keystate;
		al_get_keyboard_state(&keystate);
		if(al_key_down(&keystate, ALLEGRO_KEY_RSHIFT)
		|| al_key_down(&keystate, ALLEGRO_KEY_LSHIFT))
		{
			mouse.x -= int(mouse.x)%10;
			mouse.y -= int(mouse.y)%10;
		}
		mouse += *camera;
		if(sprite && holding)
			sprite->Set_position(mouse + hold_offset);
	}

	if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
	{
		if(event.mouse.button == 1)
		{
			if(sprite)
			{
				holding = true;
				hold_offset = sprite->Get_position() - mouse;
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
			float nearest = 10000;
			for(Sprites::iterator i = sprites->begin(); i != sprites->end(); ++i)
			{
				Vector2 center = (*i)->Get_position() + (*i)->Get_size()/2;
				float d = (mouse-center).Length_squared();
				if(d<nearest)
				{
					nearest = d;
					sprite = *i;
				}
			}
		}
	}
	if(event.type == ALLEGRO_EVENT_KEY_DOWN)
	{
		if(sprite)
		{
			if(event.keyboard.keycode == ALLEGRO_KEY_DELETE)
			{
				sprites->erase(std::find(sprites->begin(), sprites->end(), sprite));
				sprite = NULL;
			}
			if(sprite)
			{
				if(event.keyboard.keycode == ALLEGRO_KEY_UP)
				{
					sprite->Set_position(sprite->Get_position()+Vector2(0, -1));
				}
				if(event.keyboard.keycode == ALLEGRO_KEY_DOWN)
				{
					sprite->Set_position(sprite->Get_position()+Vector2(0, 1));
				}
				if(event.keyboard.keycode == ALLEGRO_KEY_LEFT)
				{
					sprite->Set_position(sprite->Get_position()+Vector2(-1, 0));
				}
				if(event.keyboard.keycode == ALLEGRO_KEY_RIGHT)
				{
					sprite->Set_position(sprite->Get_position()+Vector2(1, 0));
				}
			}
		}
	}
}

void Edit_sprite::Open()
{
	open = true;
}

void Edit_sprite::Close()
{
	open = false;
	sprite = NULL;
}
