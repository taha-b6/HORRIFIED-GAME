#ifndef SAVE_LOAD_HPP

#define SAVE_LOAD_HPP
#include <iostream>
#include <string>
#include <vector>
#include <variant>
#include <ctime>
#include <iomanip>
#include <map>
#include <set>
#include <sstream>
#include <algorithm>
#include "item.hpp"
#include "perk.hpp"
#include "monster_card.hpp"
#include "character.hpp"
#include "moving.hpp"
#include "place.hpp"
#include <filesystem>
#include <cstdio>
class Hero;
struct LoadedGameData {
    string hero_name;
    int troll_level;
    vector<item_info> item_in_bag_game;
    vector<item_info> item_in_bag_out_game;
    vector<item_info> item_in_places;
    vector<item_info> items_for_mayor;
    vector<item_info> items_for_archo;
    vector<item_info> special_items_for_mayor;
    vector<item_info> special_items_for_archo;
    map<string, int> perk_in_bag;
    map<string, int> perk_for_mayor;
    map<string, int> perk_for_archogolist;
    vector<string> monster_cards;
    multimap<string, string> vilager_location;
    std::string mayor_location;
    std::string arch_location;
    std::string deracula_location;
    std::string invi_location;
};
class save_load
{
private:
    Hero *first;
    Hero *seccend;
    moving mov;
    std::vector<Villager *> vil;
    Monster *deracula = nullptr;
    Monster *invisble_man = nullptr;
    int troll_level;
    bag_of_monster_card monster_bag;
    public:
    save_load(){}
    save_load(Hero*, Hero*, Monster*, Monster*, bag_of_monster_card&, int & );
    void set_info(Hero*, Hero*, Monster*, Monster*, bag_of_monster_card&, int &);
    void save(std::string hero_name,std::string file_name);
    LoadedGameData load_from_file(std::string);
    void load( LoadedGameData& );
};
#endif