#ifndef CLASS-PLACE
#define CLASS-PLACE

#include <iostream>
#include <vector>
#include <string>
#include <variant>
#include <map>
#include"card.hpp"
#include"character.hpp"
#include<map>
#include<queue>

//***********************************************************************************************************************//
struct coordinate{
    int x;
    int y;
};

class place{
    friend class moving;
    friend class item;
    friend class visit_from_the_detective ;
    private:
    coordinate place_pos;
     std:: vector <item> items_list;
     std:: multimap <std:: string , place> near_place;
     std:: vector <Monster*> monster_in_place;
     std:: vector <Hero*> hero_in_place;
     //std:: vector <> villager_in_place;
public:
    place(std::string n):name(n){}
     std:: string name;
     void put_in_place(Monster*);
     void go_to_near_place(Monster*);
     void go_to_near_place(Hero*);
     void put_in_place(Hero*);
     void show_near_place();
    ~place();    
   // add other methods
}

#endif