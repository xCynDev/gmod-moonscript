
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "moonscript.h"

#include <stdio.h>


// put whatever is on top of stack into package.loaded under name something is
// already there
void setloaded(lua_State* l, char* name) {
	int top = lua_gettop(l);
	lua_getglobal(l, "package");
	lua_getfield(l, -1, "loaded");
	lua_getfield(l, -1, name);
	if (lua_isnil(l, -1)) {
		lua_pop(l, 1);
		lua_pushvalue(l, top);
		lua_setfield(l, -2, name);
	}

	lua_settop(l, top);
}

extern int luaopen_lpeg(lua_State *l);

LUALIB_API int luaopen_moonscript(lua_State *l) {
	luaopen_lpeg(l);
	setloaded(l, "lpeg");

	if (luaL_loadbuffer(l, (const char *)moonscript_lua, moonscript_lua_len, "moonscript.lua") == 0) {
		lua_call(l, 0, 1);
		return 1;
	}
	return 0;
};

