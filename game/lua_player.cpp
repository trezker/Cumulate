#include "lua_player.h"
#include "player.h"

#include <iostream>

#define PLAYER_STRING "player"

//Userdata handlers

Player* check_player (lua_State *L, int index)
{
	Lua_player** pi;
	Player* im;
	luaL_checktype(L, index, LUA_TUSERDATA);

	pi = (Lua_player**)luaL_checkudata(L, index, PLAYER_STRING);
	if (*pi == NULL)
		luaL_typerror(L, index, PLAYER_STRING);
	return (*pi)->player;
}

Lua_player *push_player (lua_State *L, Player* im)
{
	Lua_player **pi = (Lua_player**)lua_newuserdata(L, sizeof(Lua_player*));
	*pi = new Lua_player(im);
	luaL_getmetatable(L, PLAYER_STRING);
	lua_setmetatable(L, -2);
	return *pi;
}

// Methods

static int player_set_position(lua_State *L)
{
	Player* player = check_player(L, 1);
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	player->Set_position(x, y);
	return 0;
}

static int player_get_position(lua_State *L)
{
	Player* player = check_player(L, 1);
	b2Vec2 p = player->Get_position();
	lua_pushnumber(L, p.x);
	lua_pushnumber(L, p.y);
	return 2;
}

static const luaL_reg player_methods[] = {
	{"get_position", player_get_position},
	{"set_position", player_set_position},
	{0,0}
};

// Meta

static int static_model_tostring (lua_State *L)
{
	lua_pushfstring(L, "player: %p", lua_touserdata(L, 1));
	return 1;
}

static const luaL_reg player_meta[] = {
	{"__tostring", static_model_tostring},
	{0, 0}
};

// Register

int register_player (lua_State *L)
{
	std::cout<<"1"<<std::endl;
	lua_newtable (L);
	luaL_register(L, NULL, player_methods);  /* create methods table,
												add it to the globals */

	std::cout<<"1"<<std::endl;
	luaL_newmetatable(L, PLAYER_STRING);        /* create metatable for Image,
										 add it to the Lua registry */
	luaL_register(L, 0, player_meta);  /* fill metatable */
	lua_pushliteral(L, "__index");
	lua_pushvalue(L, -3);               /* dup methods table*/
	lua_rawset(L, -3);                  /* metatable.__index = methods */
	lua_pushliteral(L, "__metatable");
	lua_pushvalue(L, -3);               /* dup methods table*/
	lua_rawset(L, -3);                  /* hide metatable:
										 metatable.__metatable = methods */
	lua_pop(L, 1);                      /* drop metatable */
	std::cout<<"1"<<std::endl;

	lua_setfield(L, -2, PLAYER_STRING);

	std::cout<<"1"<<std::endl;
	return 0;                           /* return methods on the stack */
}
