#include "lua_entity.h"
#include "entity.h"
#include "lua_world.h"
#include "world.h"

#include <iostream>

#define PLAYER_STRING "entity"

//Userdata handlers

Entity* check_entity (lua_State *L, int index)
{
	Lua_entity** pi;
	Entity* im;
	luaL_checktype(L, index, LUA_TUSERDATA);

	pi = (Lua_entity**)luaL_checkudata(L, index, PLAYER_STRING);
	if (*pi == NULL)
		luaL_typerror(L, index, PLAYER_STRING);
	if ((*pi)->entity == NULL)
	{
		luaL_argerror (L, index, "invalid entity");
	}
	return (*pi)->entity;
}

Lua_entity *push_entity (lua_State *L, Entity* im)
{
	Lua_entity **pi = (Lua_entity**)lua_newuserdata(L, sizeof(Lua_entity*));
	*pi = new Lua_entity(im);
	luaL_getmetatable(L, PLAYER_STRING);
	lua_setmetatable(L, -2);
	return *pi;
}

// Methods

static int entity_new(lua_State *L)
{
	push_entity(L, new Entity);
	return 1;
}

static int entity_delete(lua_State *L)
{
	Entity* entity = check_entity(L, 1);
	lua_getglobal(L, "world");
	World* world = check_world(L, -1);
	world->Remove_entity(entity);
	lua_pop(L, 1);
	delete entity;
	Lua_entity** pi = (Lua_entity**)luaL_checkudata(L, 1, PLAYER_STRING);
	(*pi)->entity = NULL;
	return 1;
}

static int entity_create_body(lua_State *L)
{
	Entity* entity = check_entity(L, 1);
	lua_getglobal(L, "world");
	World* world = check_world(L, -1);
	entity->Create_body(world->Get_b2world());
	world->Add_entity(entity);
	lua_pop(L, 1);
	return 0;
}

static int entity_destroy_body(lua_State *L)
{
	Entity* entity = check_entity(L, 1);
	entity->Destroy_body();
	lua_getglobal(L, "world");
	World* world = check_world(L, -1);
	world->Remove_entity(entity);
	lua_pop(L, 1);
	return 0;
}

static int entity_set_position(lua_State *L)
{
	Entity* entity = check_entity(L, 1);
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	entity->Set_position(x, y);
	return 0;
}

static int entity_get_position(lua_State *L)
{
	Entity* entity = check_entity(L, 1);
	b2Vec2 p = entity->Get_position();
	lua_pushnumber(L, p.x);
	lua_pushnumber(L, p.y);
	return 2;
}

static int entity_set_linear_velocity(lua_State *L)
{
	Entity* entity = check_entity(L, 1);
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	entity->Set_linear_velocity(b2Vec2(x, y));
	return 0;
}

static int entity_get_linear_velocity(lua_State *L)
{
	Entity* entity = check_entity(L, 1);
	b2Vec2 p = entity->Get_linear_velocity();
	lua_pushnumber(L, p.x);
	lua_pushnumber(L, p.y);
	return 2;
}

static int entity_set_image(lua_State *L)
{
	Entity* entity = check_entity(L, 1);
	const char* filename = luaL_checkstring(L, 2);
	lua_getglobal(L, "world");
	World* world = check_world(L, -1);
	Bitmap* image = world->Get_image(filename);
	lua_pop(L, 1);
	entity->Set_image(image);
	return 0;
}

static const luaL_reg entity_methods[] = {
	{"get_position", entity_get_position},
	{"set_position", entity_set_position},
	{"get_linear_velocity", entity_get_linear_velocity},
	{"set_linear_velocity", entity_set_linear_velocity},
	{"new", entity_new},
	{"delete", entity_delete},
	{"create_body", entity_create_body},
	{"destroy_body", entity_destroy_body},
	{"set_image", entity_set_image},
	{0,0}
};

// Meta

static int entity_tostring (lua_State *L)
{
	lua_pushfstring(L, "entity: %p", lua_touserdata(L, 1));
	return 1;
}

static int entity_gc (lua_State *L)
{
	Lua_entity** pi = (Lua_entity**)luaL_checkudata(L, 1, PLAYER_STRING);
/*	Entity* entity = (*pi)->entity;
	lua_getglobal(L, "world");
	World* world = check_world(L, -1);
	world->Remove_entity(entity);
	lua_pop(L, 1);
	delete entity;
*/	delete *pi;
	return 0;
}

static const luaL_reg entity_meta[] = {
	{"__gc",       entity_gc},
	{"__tostring", entity_tostring},
	{0, 0}
};

// Register

int register_entity (lua_State *L)
{
	lua_newtable (L);
	luaL_register(L, NULL, entity_methods);  /* create methods table,
												add it to the globals */

	luaL_newmetatable(L, PLAYER_STRING);        /* create metatable for Image,
										 add it to the Lua registry */
	luaL_register(L, 0, entity_meta);  /* fill metatable */
	lua_pushliteral(L, "__index");
	lua_pushvalue(L, -3);               /* dup methods table*/
	lua_rawset(L, -3);                  /* metatable.__index = methods */
	lua_pushliteral(L, "__metatable");
	lua_pushvalue(L, -3);               /* dup methods table*/
	lua_rawset(L, -3);                  /* hide metatable:
										 metatable.__metatable = methods */
	lua_pop(L, 1);                      /* drop metatable */

	lua_setfield(L, -2, PLAYER_STRING);

	return 0;                           /* return methods on the stack */
}
