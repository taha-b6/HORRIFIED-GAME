#include <iostream>
#include <vector>
#include <string>
#include <variant>
#include <map>
#include "card.hpp"
#include "place.hpp"

//========================================================================================================================//
using namespace std;
vector<item_info> bag_items::items_in_the_game = {};
vector<item_info> bag_items::items_out_the_game = {};
vector<perk_card *> bag_perks::Perk_cards={};


//========================================================================================================================//
bag_items::bag_items() {
    item_info i;

    // حذف خط i.count = 2; چون در مقداردهی بعدی مقداردهی می‌شود

    i = {"flower", "docks", "yellow", 2, 2}; items_in_the_game.push_back(i);
    i = {"tarot deck", "camp", "yellow", 3, 2}; items_in_the_game.push_back(i);
    i = {"garlic", "inn", "yellow", 2, 2}; items_in_the_game.push_back(i);
    i = {"mirrored box", "mansion", "yellow", 3, 2}; items_in_the_game.push_back(i);
    i = {"stake", "abbey", "yellow", 3, 2}; items_in_the_game.push_back(i);
    i = {"holy water", "church", "yellow", 4, 2}; items_in_the_game.push_back(i);
    i = {"crucifix", "graveyard", "yellow", 2, 2}; items_in_the_game.push_back(i);

    i = {"torch", "barn", "red", 2, 2}; items_in_the_game.push_back(i);
    i = {"silver dagger", "tower", "red", 3, 2}; items_in_the_game.push_back(i);
    i = {"vampire book", "mansion", "red", 4, 2}; items_in_the_game.push_back(i);
    i = {"explosive vial", "cave", "red", 3, 2}; items_in_the_game.push_back(i);
    i = {"axe", "barn", "red", 2, 2}; items_in_the_game.push_back(i);
    i = {"blood sample", "precinct", "red", 2, 2}; items_in_the_game.push_back(i);
    i = {"crossbow", "dungeon", "red", 4, 2}; items_in_the_game.push_back(i);
    i = {"spear", "crypt", "red", 3, 2}; items_in_the_game.push_back(i);

    i = {"mind elixir", "laboratory", "blue", 2, 2}; items_in_the_game.push_back(i);
    i = {"hypnotic charm", "institute", "blue", 3, 2}; items_in_the_game.push_back(i);
    i = {"ghost mirror", "mansion", "blue", 2, 2}; items_in_the_game.push_back(i);
    i = {"scientific journal", "institute", "blue", 4, 2}; items_in_the_game.push_back(i);
    i = {"telepathy stone", "laboratory", "blue", 2, 2}; items_in_the_game.push_back(i);
    i = {"magnetic compass", "camp", "blue", 3, 2}; items_in_the_game.push_back(i);
    i = {"dream catcher", "inn", "blue", 2, 2}; items_in_the_game.push_back(i);

    i = {"sacred scroll", "church", "yellow", 2, 2}; items_in_the_game.push_back(i);
    i = {"crystal ball", "tower", "yellow", 3, 2}; items_in_the_game.push_back(i);
    i = {"magic talisman", "cave", "yellow", 2, 2}; items_in_the_game.push_back(i);
    i = {"sun medallion", "graveyard", "yellow", 4, 2}; items_in_the_game.push_back(i);

    i = {"ancient relic", "museum", "red", 3, 2}; items_in_the_game.push_back(i);
    i = {"ritual knife", "crypt", "red", 2, 2}; items_in_the_game.push_back(i);
    i = {"soul urn", "dungeon", "red", 3, 2}; items_in_the_game.push_back(i);

    i = {"mental tonic", "hospital", "blue", 2, 2}; items_in_the_game.push_back(i);
    i = {"calming incense", "theater", "blue", 2, 2}; items_in_the_game.push_back(i);
    i = {"spirit lantern", "cemetery", "yellow", 2, 2}; items_in_the_game.push_back(i);
    i = {"protective amulet", "precinct", "blue", 3, 2}; items_in_the_game.push_back(i);
    i = {"enchanted rope", "camp", "red", 2, 2}; items_in_the_game.push_back(i);
}

//=============================================================================================================//
perk_card* bag_perks::get_one_perk_card(){
    if (Perk_cards.empty())
        return nullptr;

    perk_card* original = Perk_cards.back();

    int count = original->get_count() - 1;
    original->set_count(count);

    if (count == 0)
    {
        Perk_cards.pop_back();
        delete original;
        return nullptr;  // کارت حذف شده، پس nullptr باز می‌گردد
    }

    perk_card* copy = original->clone();
    copy->set_count(1);

    return copy;
}
//========================================================================================================================//
void bag_perks::constract_perk_cart(){
    perk_card* p = new visit_from_the_detective(3);
    Perk_cards.push_back(p);
    p = new break_of_dawn(3);
    Perk_cards.push_back(p);
    p = new overstock(4);
    Perk_cards.push_back(p);
    p = new late_into_the_night(4);
    Perk_cards.push_back(p);
    p = new repel(3);
    Perk_cards.push_back(p);
    p = new hurry(3);
    Perk_cards.push_back(p);
}
//========================================================================================================================//
void bag_items::put_Itme_IN_Place(int a){
    while (a > 0)
    {
        if (items_in_the_game.empty())
        {
            if (items_out_the_game.empty())
                break;

            std::string n = items_out_the_game.back().location;

            auto it = moving::get_place(n);

            item newItem(items_out_the_game.back().power, items_out_the_game.back().color , items_out_the_game.back().name);
            it.items_list.push_back(newItem);
            a -= 1;
            items_out_the_game.back().count -= 1;

            if (items_out_the_game.back().count == 0)
            {
                items_out_the_game.pop_back();
            }
        }
        else
        {
            std::string n = items_in_the_game.back().location;

            auto it = moving::get_place(n);

            item newItem(items_in_the_game.back().power, items_in_the_game.back().color, items_in_the_game.back().name );
            it.items_list.push_back(newItem);
            a -= 1;
            items_in_the_game.back().count -= 1;

            if (items_in_the_game.back().count == 0)
            {
                items_in_the_game.pop_back();
            }
        }
    }
}
//=======================================================================================
item::item(int p, std::string c , std::string n): power(p) , color(c) , name(n){
}
//==================================================================================================
void bag_items::icraese_item_out_the_game(item i){
    for(auto & it: items_out_the_game){
        if(i.name==it.name ){
            ++it.count;
            return;
        }
    }
    item_info l;
    l.name = i.name;
    l.color = i.get_coler();
    l.count = 1;
    l.power = i.get_power();
    items_out_the_game.push_back(l);
}
//========================================================================================================================//
string item::get_coler() const{
    return color;
}
//========================================================================================================================//
int item::get_power() const{
    return power;
}
//========================================================================================================================//
void visit_from_the_detective::play_perk(Monster *monster , bool&){
    std::string name;
    bool success = false;

    while (!success)
    {
        std::cout << "\t ----------- Name the place where you want the invisible man to be : ---------- \n";
        std::cin >> name;

        try
        {
            moving::set_new_location(name);
            success = true;
        }
        catch (std::invalid_argument &e)
        {
            std::cerr << e.what() << std::endl;
            std::cerr << "Please try again with a valid place name.\n";
        }
    }
}
//========================================================================================================================//
void repel::play_perk(Monster *deracula, Monster *inviseble_man , bool& f){
    moving::set_new_location();
}
//========================================================================================================================//
void break_of_dawn::play_perk(bool&  f){
    f = true;
    bag_items::put_Itme_IN_Place(2);
}
//========================================================================================================================//
void overstock::play_perk(bool& f){
    bag_items::put_Itme_IN_Place(2);
}
//========================================================================================================================//
void late_into_the_night::play_perk(Hero *hero , bool&f){
    hero->increase_action(2);
}
//========================================================================================================================//
void hurry::play_perk(Hero *archaeologist, Hero *mayor , bool&f){
    moving::set_new_location(1);
}
//========================================================================================================================//
void perk_card::set_count(int new_count){
    count = new_count;
}
//========================================================================================================================//
int &perk_card::get_count(){
    return count;
}
//========================================================================================================================//
