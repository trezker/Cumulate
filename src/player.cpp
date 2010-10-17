#include "player.h"
#include <iostream>
#include "render_box2d.h"

Player::Player():
	jetpack(false),
	image(al_load_bitmap("data/char.png")),
	move_left(false),
	move_right(false),
	jump(false),
	body(NULL)
{
}

void Player::Create_body(b2World* world)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = true;
	bodyDef.position.Set(0.0f, -4.0f);
	body = world->CreateBody(&bodyDef);
	b2CircleShape shape;
	shape.m_radius = 1.2;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 20.0f;
	fixtureDef.friction = 1.0f;
	fixtureDef.restitution = 0.1f;
	body->CreateFixture(&fixtureDef);
}

void Player::Set_position(float x, float y)
{
	body->SetTransform(b2Vec2(x, y), 0);
}

b2Vec2 Player::Get_position()
{
	return body->GetPosition();
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
	if(move_left || move_right)
		body->SetFixedRotation(false);
	else
	{
		body->SetAngularVelocity(0);
		body->SetFixedRotation(true);
	}
}

void Player::Update(float dt)
{
	float max_speed = 10;
	b2Vec2 v = body->GetLinearVelocity();

	if(move_left)
	{
		float mdiff = max_speed + v.x;
		v.x -= mdiff*10*dt;
	}
	if(move_right)
	{
		float mdiff = max_speed - v.x;
		v.x += mdiff*10*dt;
	}
	b2ContactEdge* contactedge = body->GetContactList();
	b2Vec2 contact_normal(0, 0);
	int contacts = 0;
	bool touching_ground = false;
	while(contactedge)
	{
		if(contactedge->contact->IsTouching() && contactedge->contact->IsEnabled())
		{
			touching_ground = true;
			contact_normal += contactedge->contact->GetManifold()->localNormal;
			contacts ++;
		}
		contactedge = contactedge->next;
	}
	contact_normal.x = contact_normal.x/contacts;
	contact_normal.y = contact_normal.y/contacts;

	//Jumping
	if(jump && touching_ground)
	{
		jump = false;
		v += 15*contact_normal;
	}

	//Thrust
	if(jetpack)
	{
		v.y -= 180*dt;
	}

	body->SetLinearVelocity(v);
}

void Player::Draw(b2Vec2 camera)
{
	b2Vec2 p = 10*body->GetPosition()-camera;
	al_draw_bitmap(image, p.x-al_get_bitmap_width(image)/2, p.y-al_get_bitmap_height(image)/2, 0);
	Draw_body(body, camera);
}
