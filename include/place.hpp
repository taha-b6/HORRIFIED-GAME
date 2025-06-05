#ifndef PLACE_HPP
#define PLACE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <variant>
#include <map>
#include "card.hpp"
#include "character.hpp"
#include <map>
#include <queue>

//***********************************************************************************************************************//
struct coordinate
{
    int x;
    int y;
};

class place
{
    friend class moving;
    friend class bag_items;    
    friend class visit_from_the_detective;

private:
    coordinate place_pos;
    static std::vector<item> items_list;
    static std::vector<place> near_place;
    std::vector<Monster *> monster_in_place;
    std::vector<Hero *> hero_in_place;
    static std:: vector <Villager> villager_in_place;
    bool tabot = false;
public:
    place(std::string n);
    std::string name;
    void put_in_place(Monster *);
    void go_to_near_place(Monster *);
    void go_to_near_place(Hero *);
    void put_in_place(Hero *);
    static void put_villager_in_place(  Hero* , place & , place&);
    static void put_villager_in_place( Hero* ,place& , std::string ="");
    static std::vector<item>get_items(int);
    void show_near_place();
    bool get_tabot();
    void destroy_tabot();
    int get_monster_in_place();
    void kill_monster(int);
    std::vector<place>get_p();

    ~place();
    // add other methods
};
#endif
