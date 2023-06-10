#include <fstream>
#include "../third-party/jsoncpp/include/json/json.h"

bool read_json_db(std::string filename);
bool make_card (unsigned int id ,std::string name, std::string text,std::string  pic,std::string lua_code);
bool search_id(unsigned int id ,std::string &name, std::string &text,std::string & pic,std::string &lua_code);
void save_json_db(std::string filename);