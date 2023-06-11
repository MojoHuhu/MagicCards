
#include <iostream>
#include "libs/player/player.h"
#include "libs/database/database.h"

player ply[2];




int main()
{
  
  read_json_db("CardsDB.json");        // cards database 

  ply[0].init(0);                     // Player          
  ply[1].init(1);  

  ply[0].me["name"] = "Herman";
  ply[1].me["name"] =  "Winfried";
   //create_lua_table(ply[0].me, ply[1].me);

  ply[0].push_card(0);                // indipendent card index 
  ply[1].push_card(1);        
  bool pl1=true,pl0=true;


 int x =1;
  while (pl1 && pl0)                      //round
  {
      std::string out_text;
      if(x>0) x=0; else x=1;
      std::cout << "Player " << x <<" turn\n";
      pl0=ply[x].make_turn(ply[!x].get_attrebuts(),out_text);   // Attack 0-> 1
      //std::cout << out_text;
      if(ply[0].me["health"].asInt()<=0){ std::cout << ply[1].me["name"] <<" win the game!\n"; return 0;}
      if(ply[1].me["health"].asInt()<=0){ std::cout << ply[0].me["name"] <<" win the game!\n"; return 0;}
      
  }

 

   return 0; 
}