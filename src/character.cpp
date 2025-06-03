#include <iostream>
#include <string>
#include <vector>
#include <variant>
#include <algorithm>
#include "character.hpp"
#include <map>

//***********************************************************************************************************************//

using namespace std;

//=================================================     ================================================================//
string Monster::get_place()
{
    return wher_is_monster;
}
//********************************************************************************************************//
void Hero::set_location(string place_name)
{
    wher_is_hero = place_name;
}
//============================================       ======================================================//
void Monster::set_location(string place_name)
{
    wher_is_monster = place_name;
}
void Hero::increase_action(int new_action)
{
    action += new_action;
}
//==========================================       ==================================================================//

string Hero::get_place()
{
    return wher_is_hero;
}
//============================================       =======================================================//
void Hero::increase_perk_card(perk_card *new_perk)
{
    if (find(perk_cards.cbegin(), perk_cards.cend(), new_perk) != perk_cards.cend())
    {
        for (auto &it : perk_cards)
        {
            if (it->name == new_perk->name)
            {
                it->set_count(it->get_count() + 1);
            }
        }
    }
    else
    {
        perk_cards.push_back(new_perk);
    }
}
//************************************************************//
void Hero::domp_perk(perk_card *domp)
{
    for (auto &it : perk_cards)
    {
        if (it->name == domp->name)
        {
            if (it->get_count() == 1)
            {
                auto pos = std::find(perk_cards.begin(), perk_cards.end(), *it);
                if (pos != perk_cards.end())
                {
                    perk_cards.erase(pos);
                }
            }
            if (it->get_count() > 1)
            {
                it->set_count(it->get_count() - 1);
            }
        }
    }
}
