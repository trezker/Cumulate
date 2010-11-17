#ifndef lua_entity_h
#define lua_entity_h

extern "C" {
#include <lua5.1/lua.h>
#include <lua5.1/lualib.h>
#include <lua5.1/lauxlib.h>
}

class Entity;

class Lua_entity
{
public:
	Lua_entity(Entity* p):entity(p){}
	Entity* entity;
};

int register_entity (lua_State* L);
Lua_entity *push_entity (lua_State *L, Entity* im);
Entity* check_entity (lua_State *L, int index);

#endif
