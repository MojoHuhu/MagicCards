--   player[0] is allways the on turn !

--    player[0] = {health=22, id=1, name= "Winfried"}
--    player[1] = {health=20, id=0, name= "Herman"}

--    add more values in init_ply.json and modify them in your cards 
--    to add new cards delete CardsDB.json    

cardname = "Magic Powder"


function LuaMakesAction()
    output ="Attack from Lua!\n"
    print("Attack from Lua!")
    player[1].health = player[1].health - math.random(1,10)
    print( player[0]['name'].."(".. player[0]['health']..")" .." hits "..  player[1]['name'] .."(".. player[1]['health']..")".." with " ..cardname )
    return output ..player[0]['name'].."(".. player[0]['health']..")" .." hits "..  player[1]['name'] .."(".. player[1]['health']..")".." with " ..cardname 
end