#include "player.h"
#include <iostream>

Player::Player():
    jetpack(false)
{
	image = al_load_bitmap("data/char.png");
	x = 0;
	y = 0;
	move_left = false;
	move_right = false;
	jump = false;
}

void Player::Set_position(float ix, float iy)
{
	x = ix;
	y = iy - al_get_bitmap_height(image);
}

void Player::Event(ALLEGRO_EVENT& event)
{
	if(ALLEGRO_EVENT_KEY_DOWN == event.type)
	{
		if(ALLEGRO_KEY_LEFT == event.keyboard.keycode)
		{
			move_left = true;
		}
		if(ALLEGRO_KEY_RIGHT == event.keyboard.keycode)
		{
			move_right = true;
		}
        if(ALLEGRO_KEY_LCTRL == event.keyboard.keycode)
        {
            jetpack = true;
            jump = false;
        }
        else if(ALLEGRO_KEY_UP == event.keyboard.keycode)
		{
			jump = true;
		}
	}
	if(ALLEGRO_EVENT_KEY_UP == event.type)
	{
		if(ALLEGRO_KEY_LEFT == event.keyboard.keycode)
		{
			move_left = false;
		}
		if(ALLEGRO_KEY_RIGHT == event.keyboard.keycode)
		{
			move_right = false;
		}
        if(ALLEGRO_KEY_LCTRL == event.keyboard.keycode)
        {
            jetpack = false;
        }
		if(ALLEGRO_KEY_UP == event.keyboard.keycode)
		{
			jump = false;
		}
	}
}

void Player::Update(float dt)
{
	//Accellerating
	float max_speed = 100;
	if(move_left)
	{
		float mdiff = max_speed + xs;
		xs -= mdiff*10*dt;
	}
	if(move_right)
	{
		float mdiff = max_speed - xs;
		xs += mdiff*10*dt;
	}
	
	//Jumping
	bool touching_ground = y>=600-al_get_bitmap_height(image); //Placeholder
	if(jump && touching_ground)
	{
		jump = false;
		ys -= 250;
	}

	//Stopping
	if(!(move_right || move_left))
	{
		xs -= 10*xs*dt;
	}
	
	//Gravity
	if(!touching_ground)
	{
		ys += 1000*dt;
	}

    //Thrust
    if(jetpack)
    {
        ys -= 3000*dt;
    }
	
	x += xs*dt;
	y += ys*dt;

	touching_ground = y>=600-al_get_bitmap_height(image); //Placeholder
	if(touching_ground)
	{
		ys = 0;
		y = 600 - al_get_bitmap_height(image);
	}
}

void Player::Draw()
{
	al_draw_bitmap(image, x, y, 0);
}
