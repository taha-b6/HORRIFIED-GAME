#ifndef CLASS-PLACE
#define CLASS-PLACE

#include <iostream>
#include <vector>
#include <string>
#include <variant>
#include <map>

//***********************************************************************************************************************//

struct coordinate{
    int x;
    int y;
};

class place{
private:
    coordinate place_pos;
    std:: multimap <std:: string , double> near_place;
    std:: vector <std:: variant <class Hero , class Monster , class Villager>> in_this_place;
    std:: vector <class item> items_list;
public:
    std:: string name;
    place();
    ~place();    
   // add other methods



};


#endif