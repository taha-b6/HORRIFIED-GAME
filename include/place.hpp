#ifndef PLACE_HPP
#define PLACE_HPP
//========================================================================================================================//
#include <iostream>
#include <vector>
#include <string>
#include <variant>
#include <map>
#include "card.hpp"
#include "character.hpp"
#include <map>
#include <queue>

//========================================================================================================================//
struct coordinate{
    int x;
    int y;
};
//========================================================================================================================//
class place{
    
    friend class moving;
    friend class bag_items;    
    friend class visit_from_the_detective;

private:
    coordinate place_pos;
    static std::vector<item> items_list;
    static std::vector<std::string> near_place;
    std::vector<Monster *> monster_in_place;
    std::vector<Hero *> hero_in_place;
    static std:: vector <Villager> villager_in_place;
    bool tabot = false;
public:
    place(std::string n);
    std::string name;
    void put_in_place(Monster * , bool=false);
    void go_to_near_place(Monster *);
    void go_to_near_place(Hero *);
    void put_in_place(Hero *);
    static void put_villager_in_place(  Hero* , place & , place&);
    static void put_villager_in_place( Hero* ,place& , std::string ="");
    void put_vilager(Villager);
    static std::vector<item>get_items(int);
    void show_near_place();
    bool get_tabot();
    void destroy_tabot();
    int get_monster_in_place();
    void kill_monster(int);
    void erase_item();
    int get_num_of_items();
    std::vector<std::string>get_p();
    std::string has_villager();
    void delete_monster(Monster *);
    void delete_hero(Hero *);
    bool can_invisible_man();
    void put_hero(Hero*);
    bool can_deracola();
    std::vector<std::string> show_villager_monster();
     Hero* get_hero_in_place();
     bool each_monster_kiil();
     ~place();

};
//========================================================================================================================//
#endif
