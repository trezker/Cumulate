#include "entity.h"
#include <iostream>
extern "C" {
#include <lua5.1/lua.h>
#include <lua5.1/lualib.h>
#include <lua5.1/lauxlib.h>
}

Entity::Entity()
:body(NULL)
,image(NULL)
,script_reference(LUA_NOREF)
{
}

Entity::~Entity()
{
	if(body)
	{
		body->GetWorld()->DestroyBody(body);
	}
}

void Entity::Set_image(Bitmap* i)
{
	image = i;
}

void Entity::Create_body(b2World* world)
{
	Destroy_body();
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

void Entity::Destroy_body()
{
	if(body)
	{
		body->GetWorld()->DestroyBody(body);
	}
}

void Entity::Set_position(float x, float y)
{
	body->SetTransform(b2Vec2(x, y), 0);
}

b2Vec2 Entity::Get_position()
{
	return body->GetPosition();
}

b2Vec2 Entity::Get_linear_velocity()
{
	return body->GetLinearVelocity();
}

void Entity::Set_linear_velocity(b2Vec2 v)
{
	body->SetLinearVelocity(v);
}

void Entity::Set_angular_velocity(float v)
{
	body->SetAngularVelocity(v);
}

void Entity::Set_fixed_rotation(bool t)
{
	body->SetFixedRotation(t);
}

void Entity::Update(float dt)
{
}

void Entity::Draw(b2Vec2 camera)
{
	if(!image)
		return;
	b2Vec2 p = 10*body->GetPosition()-camera;
	image->Draw(p.x-image->Get_width()/2, p.y-image->Get_height()/2);
}

void Entity::Set_script_reference(int r)
{
	script_reference = r;
}

int Entity::Get_script_reference()
{
	return script_reference;
}
