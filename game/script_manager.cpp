#include "script_manager.h"
#include "lua_world.h"
#include "lua_player.h"
#include "lua_entity.h"
#include <iostream>

Script_manager::Script_manager()
{
	state = luaL_newstate();
	luaL_openlibs (state);

	lua_newtable (state);
	register_player(state);
	register_entity(state);
	register_world(state);
	lua_setglobal (state, "cumulate");
}

Script_manager::~Script_manager()
{
	lua_close(state);
}

void Script_manager::Run_string(const char* s)
{
	int r = luaL_dostring (state, s);
	if(r)
	{
		const char *e = luaL_checkstring (state, 1);
		std::cout<<"Lua error "<< r <<": "<< e <<std::endl;
		lua_pop(state, 1);
	}
}

void Script_manager::Set_player(Player* player)
{
	push_player(state, player);
	lua_setglobal (state, "player");
}

void Script_manager::Set_world(World* world)
{
	push_world(state, world);
	lua_setglobal (state, "world");
}

int Script_manager::Get_script(const std::string& filename)
{
	Script_references::iterator i = script_references.find(filename);
	if(i != script_references.end())
		return i->second;
	int r = luaL_dofile (state, filename.c_str());
	if(r)
	{
		Print_error();
		return LUA_NOREF;
	}
	int ref = luaL_ref(state, LUA_REGISTRYINDEX);
	script_references[filename] = ref;
	return ref;
}

void Script_manager::Print_error()
{
	const char *e = luaL_checkstring (state, 1);
	std::cout<<"Lua error: "<< e <<std::endl;
	lua_pop(state, 1);
}

bool Script_manager::Push_callback(const char* c, int ref)
{
	if(ref == LUA_NOREF)
		return false;
	lua_rawgeti(state, LUA_REGISTRYINDEX, ref);
	lua_getfield (state, -1, c);
	lua_remove(state, -2);
	return true;
}

void Script_manager::Push_number(float n)
{
	lua_pushnumber(state, n);
}

lua_State* Script_manager::Get_state()
{
	return state;
}

void Script_manager::Call(int args)
{
	int r = lua_pcall(state, args, 0, 0);
	if(r)
	{
		Print_error();
	}
}
