#include "script_manager.h"
#include <iostream>

Script_manager::Script_manager()
{
	state = luaL_newstate();
	luaL_openlibs (state);
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
	}
}
