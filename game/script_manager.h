#ifndef script_manager_h
#define script_manager_h

extern "C" {
#include <lua5.1/lua.h>
#include <lua5.1/lualib.h>
#include <lua5.1/lauxlib.h>
}
#include <map>
#include <string>

class Player;
class World;

class Script_manager
{
public:
	Script_manager();
	~Script_manager();
	void Run_string(const char* s);

	void Set_player(Player* player);
	void Set_world(World* world);
	int Get_script(const std::string& filename);

	bool Push_callback(const char* c, int ref);
	void Push_number(float n);
	lua_State* Get_state();
	void Call(int args);
private:
	void Print_error();
	lua_State* state;
	typedef std::map<std::string, int> Script_references;
	Script_references script_references;
};

#endif
