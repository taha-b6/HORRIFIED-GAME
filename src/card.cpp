#include <iostream>
#include <vector>
#include <string>
#include <variant>
#include <map>
#include "card.hpp"
#include "place.hpp"

using namespace std;

perk_card* bag_perks::get_one_perk_card(){
    perk_card* p = Perk_cards.back();
    Perk_cards.pop_back();
    return p;
}
void constract_perk_cart(std::vector<card> c);//باید با newکردن کارت درست کنی

void bag_items::put_Itme_IN_Place(std::map<std::string, place> &places, int a)
{
    while(a>0)
    {
        if (items_in_the_game.empty())
        {
            if (items_out_the_game.empty())
                break;

            std::string n = items_out_the_game.back().name;

            auto it = places.find(n);
            if (it != places.end())
            {
                item newItem(items_out_the_game.back().power ,items_out_the_game.back().color);
                it->second.items_list.push_back(newItem);
                a-=1;
                items_out_the_game.back().count-=1;

                if (items_out_the_game.back().count == 0)
                {
                    items_in_the_game.push_back(items_out_the_game.back());
                    items_out_the_game.pop_back();
                }
            }
        }
        else 
        {
            std::string n = items_in_the_game.back().name;

            auto it = places.find(n);
            if (it != places.end())
            {
                item newItem(items_in_the_game.back().power , items_in_the_game.back().color);
                it->second.items_list.push_back(newItem);
                a-=1;
                items_in_the_game.back().count-=1;

                if (items_in_the_game.back().count == 0)
                {
                    items_out_the_game.push_back(items_in_the_game.back());
                    items_in_the_game.pop_back();
                }
            }
        }
    }
}
//***************************************************************************//
string item:: get_coler()const{
    return color;
}
//************** *********************************************//
int item::get_power()const{
    return power;
}
//***********************************************************************************************//
void visit_from_the_detective::play_perk(Monster *monster)
{
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

//*********************************************************************************************//

void repel::play_perk(Monster *deracola, Monster *inviseble_man)
{ // برای حرکت دادن هیولا ها دو خانه
    moving::set_new_location();
}
void break_of_dawn::play_perk(map<string, place> &places)
{
    bag_items::put_Itme_IN_Place(places, 2);
}
//***************************************************************************************//

void overstock::play_perk(map<string, place> &places)
{
    bag_items::put_Itme_IN_Place(places, 2);
}

//********************************************************************************//

void late_into_the_night::play_perk(Hero *hero)
{
    hero->increase_action(2);
}
//********************************************************************//
void hurry::play_perk(Hero *archaeologist, Hero *mayor)
{
    //برای حرکت دادن هر دو قهرمان دو حانه
    moving::set_new_location(1);
}
//*********************************************************** //
void perk_card::set_count(int new_count)
{
    count = new_count;
}
int &perk_card::get_count()
{
    return count;
}
