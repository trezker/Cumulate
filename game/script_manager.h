#ifndef script_manager_h
#define script_manager_h

extern "C" {
#include <lua5.1/lua.h>
#include <lua5.1/lualib.h>
#include <lua5.1/lauxlib.h>
}

class Script_manager
{
public:
	Script_manager();
	~Script_manager();
	void Run_string(const char* s);
private:
	lua_State* state;
};

#endif
