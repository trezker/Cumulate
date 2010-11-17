#include "lua_world.h"
#include "world.h"

#include <iostream>

#define PLAYER_STRING "world"

//Userdata handlers

World* check_world (lua_State *L, int index)
{
	Lua_world** pi;
	World* im;
	luaL_checktype(L, index, LUA_TUSERDATA);

	pi = (Lua_world**)luaL_checkudata(L, index, PLAYER_STRING);
	if (*pi == NULL)
		luaL_typerror(L, index, PLAYER_STRING);
	return (*pi)->world;
}

Lua_world *push_world (lua_State *L, World* im)
{
	Lua_world **pi = (Lua_world**)lua_newuserdata(L, sizeof(Lua_world*));
	*pi = new Lua_world(im);
	luaL_getmetatable(L, PLAYER_STRING);
	lua_setmetatable(L, -2);
	return *pi;
}

// Methods

static int world_create_entity(lua_State *L)
{
	World* world = check_world(L, 1);
//	float x = luaL_checknumber(L, 2);
//	float y = luaL_checknumber(L, 3);
//	world->Set_position(x, y);
	return 0;
}

static int world_destroy_entity(lua_State *L)
{
	World* world = check_world(L, 1);
//	b2Vec2 p = world->Get_position();
//	lua_pushnumber(L, p.x);
//	lua_pushnumber(L, p.y);
	return 0;
}

static const luaL_reg world_methods[] = {
	{"create_entity", world_create_entity},
	{"destroy_entity", world_destroy_entity},
	{0,0}
};

// Meta

static int static_model_tostring (lua_State *L)
{
	lua_pushfstring(L, "world: %p", lua_touserdata(L, 1));
	return 1;
}

static const luaL_reg world_meta[] = {
	{"__tostring", static_model_tostring},
	{0, 0}
};

// Register

int register_world (lua_State *L)
{
	lua_newtable (L);
	luaL_register(L, NULL, world_methods);  /* create methods table,
												add it to the globals */

	luaL_newmetatable(L, PLAYER_STRING);        /* create metatable for Image,
										 add it to the Lua registry */
	luaL_register(L, 0, world_meta);  /* fill metatable */
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
