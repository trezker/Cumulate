#ifndef lua_world_h
#define lua_world_h

extern "C" {
#include <lua5.1/lua.h>
#include <lua5.1/lualib.h>
#include <lua5.1/lauxlib.h>
}

class World;

class Lua_world
{
public:
	Lua_world(World* p):world(p){}
	World* world;
};

int register_world (lua_State* L);
Lua_world *push_world (lua_State *L, World* im);
World* check_world (lua_State *L, int index);

#endif
