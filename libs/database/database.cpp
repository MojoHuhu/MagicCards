#include "database.h"
#include <iostream>
Json::Value db;
#include <filesystem>
#include <fstream>
#include <sstream>

std::string readFileIntoString(const std::string& path) 
{
    std::ifstream input_file(path);
    if (!input_file.is_open()) {
        std::cerr << "Could not open the file - '"
             << path << "'" << std::endl;
        exit(EXIT_FAILURE);
    }
    return std::string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
}



int list_files_of_luaCards() {
   std::cout<< "Create DB from /luaCards Folder!\n";  
    std::string directory_path = "luaCards";
    int i = 0;
    for (const auto & file: std::filesystem::directory_iterator(directory_path)) {
         std::cout << file.path() << std::endl;
         make_card(i++,file.path()," Fucking Lua code from Json file!",
        "/some_location/pic.jpg", readFileIntoString(file.path()).c_str() );
    }

    return 0;
}


bool read_json_db(std::string filename)
{
    std::ifstream file(filename.c_str());
    Json::Reader reader;

   if (!reader.parse(file, db)){
      /*make_card(0,"Unbelievable Ulf"," Fucking Lua code from Json file!",
        "/some_location/pic.jpg",
        "\nfunction LuaMakesAction()\n"\
        "player[1]['health'] =  player[1]['health']- math.random(0,10)\n"\
        "print('Attack from Lua!')\n"\
        "print(player[1]['health'])\n"\
        "end\n");*/

      list_files_of_luaCards();
      save_json_db(filename);
      return false;
   }
  return true;
}

void save_json_db(std::string filename)
    {
    std::ofstream file_id;
    file_id.open(filename.c_str());
    Json::StyledWriter styledWriter;
    file_id << styledWriter.write(db);

    file_id.close();
    }




bool make_card (unsigned int id ,std::string name, std::string text,std::string  pic, std::string lua_code)
{
    std::cout <<db.size();
      int now = db.size();
      db[now]["id"]= id;
      db[now]["name"] =name;
      db[now]["lua"] = lua_code;
      db[now]["pic"] = pic;
      db[now]["txt"] =text;
      return true;
}


bool search_id(unsigned int id ,std::string &name, std::string &text,std::string & pic,std::string &lua_code)
{

    for ( int i = 0; i < db.size(); i++ )
        {
         if ( db[i]["id"].asInt() == id ) 
         {
            name =db[i]["name"].asString() ;
            lua_code =db[i]["lua"].asString();
            text  =db[i]["txt"].asString();
            pic = db[i]["pic"].asString();
            return true;
         }

        }
 return false;
}