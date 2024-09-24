#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <stdio.h>
#include <string.h>

int main() {
  char buf[512];
  int error;
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);

  FILE *F = fopen("main.lua", "r");
  fread(buf, sizeof(char), sizeof(buf), F);

  error = luaL_loadbuffer(L, buf, strlen(buf), "file") || lua_pcall(L, 0, 0, 0);
  if (error) {
    fprintf(stderr, "%s\n", lua_tostring(L, -1));
    lua_pop(L, 1);
  }

  lua_getglobal(L, "Triple");
  lua_pushnumber(L, 7);
  lua_pcall(L, 1, 1, 0);
  int x = lua_tointeger(L, -1);
  lua_pop(L, 1);

  lua_getglobal(L, "Quadruple");
  lua_pushnumber(L, 4);
  lua_pcall(L, 1, 1, 0);
  int y = lua_tointeger(L, -1);
  lua_pop(L, 1);

  printf("Result: %d, %d\n", x, y);

  lua_close(L);
  return 0;
}