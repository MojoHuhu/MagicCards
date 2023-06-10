#include <iostream>

class card {
 unsigned int id;
 std::string name;
 std::string text;
 std::string lua_code;
 public :
   card (  unsigned int _id,std::string _name,std::string _text ,std::string _lua_code )  { id= _id; name = _name;text =_text ;lua_code =_lua_code;}
   std::string  get_lua_code() {return lua_code;}
   std::string  get_name() {return name;}
   unsigned int get_id(){ return id;}

};