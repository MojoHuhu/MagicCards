#include "player.h"
#include "../database/database.h"

#include <fstream>
#include <iostream>

void save_init_file(Json::Value &value_obj)
{
  std::ofstream file_id;
  file_id.open("init_ply.json");

  Json::StyledWriter styledWriter;
  file_id << styledWriter.write(value_obj);

  file_id.close();
}

bool read_init_file(Json::Value &value_obj)
{
  std::ifstream file("init_ply.json");
  Json::Reader reader;
  if (!reader.parse(file, value_obj))
  {
    std::cout << "create new 'init_ply.json' modify it to change the game" << std::ends;
    getchar();
    return false;
  }
  return true;
}

std::string create_lua_table(Json::Value &me, Json::Value &enemy)
{
  std::stringstream ss;
  // player
  ss << "player = {}\n"
     << std::endl;
  ss << "player[0] = {";
  for (Json::Value::const_iterator it = me.begin(); it != me.end(); ++it)
  {
    if (it->isInt())
      ss << it.key().asString() << "=" << it->asInt();
    else if (it->isDouble())
      ss << it.key().asString() << "=" << it->asDouble();
    else if (it->isString())
      ss << it.key().asString() << "= " << '"' << it->asString() << '"';

    if (std::next(it, 1) != me.end())
      ss << ", ";
  }
  ss << "}" << std::endl;
  // enamy
  ss << "player[1] = {";
  for (Json::Value::const_iterator it = enemy.begin(); it != enemy.end(); ++it)
  {
    if (it->isInt())
      ss << it.key().asString() << "=" << it->asInt();
    else if (it->isDouble())
      ss << it.key().asString() << "=" << it->asDouble();
    else if (it->isString())
      ss << it.key().asString() << "= " << '"' << it->asString() << '"';

    if (std::next(it, 1) != enemy.end())
      ss << ", ";
  }
  ss << "}\n"
     << std::endl;

  // std::cout<< ss.str();

  return ss.str();
}

player::player(/* args */)
{
  if (!read_init_file(me))
  {
    me["id"] = 0;
    me["health"] = 100;
    me["name"] = "yo";
    save_init_file(me);
  }
}

player::~player()
{
}

bool player::make_turn(Json::Value &enemy,std::string &output_txt)
{
  std::string getPlayerFunc = "function GetPlayer(n)\n"
                              "   return player[n]\n"
                              "end\n";

  for (int i = 0; i < deck.size(); i++)
    execute_card(create_lua_table(me, enemy) + getPlayerFunc + deck[i].get_lua_code(), enemy,output_txt);

  if (enemy["health"].asInt() <= 0 || enemy["health"].asInt() <= 0)
    return false;

  return true;
}

bool check_lua(lua_State *L, int r)
{
  if (r != LUA_OK)
  {
    std::cout << "[Lua] error :" << lua_tostring(L, -1);
    return false;
  }
  return true;
}

bool lua_get_player_state(lua_State *L, int index, Json::Value &ret)
{

  lua_getglobal(L, "GetPlayer");
  if (lua_isfunction(L, -1))
  {
    lua_pushinteger(L, index);
    check_lua(L, lua_pcall(L, 1, 1, 0));
  }
  else
  {
    std::cout << "no GetPlayer function !\n";
  }

  if (lua_istable(L, -1))
  {
    for (Json::Value::iterator it = ret.begin(); it != ret.end(); ++it)
    {
      std::string n = it.key().asString();

      lua_pushstring(L, n.c_str());

      lua_gettable(L, -2);
      if (lua_isinteger(L, -1))
        ret[n] = (int)lua_tointeger(L, -1);
      else if (lua_isnumber(L, -1))
        ret[n] = (double)lua_tonumber(L, -1);
      else if (lua_isstring(L, -1))
        ret[n] = lua_tostring(L, -1);
      lua_pop(L, 1);
    }
  }
  else
    std::cout << lua_tostring(L, -1);
}

void player::execute_card(std::string lua_code_from_card, Json::Value &enemy,std::string &output_txt)
{
  lua_State *L = luaL_newstate(); // create a new lua instance
  luaL_openlibs(L);               // give lua access to basic libraries

  // luaL_dofile(L, "../main.lua");                             // loads the Lua script
  if (check_lua(L, luaL_dostring(L, lua_code_from_card.c_str())))
  {

    lua_getglobal(L, "LuaMakesAction");
    if (check_lua(L, lua_pcall(L, 0, 1, 0)))
    {
      if(lua_isstring(L, -1))
       output_txt= lua_tostring(L, -1);

      lua_get_player_state(L, 0, me);
      lua_get_player_state(L, 1, enemy);
    }
  }

  lua_close(L);
}

bool player::push_card(unsigned int id)
{
  std::string name, text, pic, code;

  if (search_id(id, name, text, pic, code))
  { // found in Json
    deck.push_back(card(id, name, text, code));
    return true;
  }
  return false;
}