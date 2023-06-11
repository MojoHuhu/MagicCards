#include <cctype>
#include <sstream>
#include "../player/player.h"
#include "../database/database.h"
std::string run_game()
{ 
    
    
 player ply[2];
  std::stringbuf sbuf( std::ios::out ) ; // create a stringbuf
  auto oldbuf = std::cout.rdbuf( std::addressof(sbuf) ) ; // associate the stringbuf with std::cout
  

  read_json_db("CardsDB.json");        // cards database 

  ply[0].init(0);                     // Player          
  ply[1].init(1);  

  ply[0].me["name"] = "Herman";
  ply[1].me["name"] =  "Winfried";
   //create_lua_table(ply[0].me, ply[1].me);

  ply[0].push_card(0);                // indipendent card index 
  ply[1].push_card(1);        
  bool pl0=true;

 int x =1;
  while (pl0)                      //round
  {
      std::string out_text;
      if(x>0) x=0; else x=1;
      std::cout << "Player " << x <<" turn\n";
      pl0=ply[x].make_turn(ply[!x].get_attrebuts(),out_text);   // Attack 0-> 1
      std::cout << out_text <<"\n";
      
      if(ply[0].me["health"].asInt()<=0){ std::cout << ply[1].me["name"] <<" win the game!\n"; }
      if(ply[1].me["health"].asInt()<=0){ std::cout << ply[0].me["name"] <<" win the game!\n"; }
      
  }
   // std::cout << "Test  "<< sbuf.str();
   std::cout.rdbuf( oldbuf ) ; // restore cout's original buffer
 
   return std::string(sbuf.str()) ; // get a copy of the underlying string
}