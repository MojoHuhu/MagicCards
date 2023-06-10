#include <iostream>
#include <string>
#include <vector>
#include "../card/card.h"
#include "../third-party/jsoncpp/include/json/json.h"
// include Lua headers
extern "C" {
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
};




std::string create_lua_table(Json::Value & me, Json::Value & enemy);

void save_init_file(  Json::Value &value_obj);
bool read_init_file(Json::Value & value_obj);

class player
{
private:
    /* data */
    std::vector<card> deck;
public:
    Json::Value me;
    player(/* args */);
    ~player();
    
    void init(unsigned int i){me["id"] = i;} 

    Json::Value & get_attrebuts(){return me;}

    bool make_turn(Json::Value & enemy);

    void execute_card(std::string lua_code_from_card, Json::Value & enemy );

    bool push_card(unsigned int id);

};


