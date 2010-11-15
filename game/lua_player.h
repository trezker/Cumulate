#ifndef lua_player_h
#define lua_player_h

extern "C" {
#include <lua5.1/lua.h>
#include <lua5.1/lualib.h>
#include <lua5.1/lauxlib.h>
}

class Player;

class Lua_player
{
public:
	Lua_player(Player* p):player(p){}
	Player* player;
};

int register_player (lua_State* L);
Lua_player *push_player (lua_State *L, Player* im);

#endif
