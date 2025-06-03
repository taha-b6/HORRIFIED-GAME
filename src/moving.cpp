#include "moving.hpp"
#include <stdexcept>
#include <iostream>
using namespace std;
moving::moving(Hero *first, Hero *seccend, Monster *dera, Monster *Invisable_man) : first_hero(first), seccend_hero(seccend)
{
    deracola = dera;
    invisable_man = Invisable_man;
}
//****************************************************************//
void moving::set_new_location(Hero *h, std::string place_name)
{
    bool successful = false;
    place &temp = places[h->get_place()];

    for (auto &p : temp.hero_in_place)
    {
        if (p == h)
        {
            successful = true;
            std::cout << "you can't go to this place\n";
            break;
        }
    }

    while (successful)
    {
        std::cout << "where would you like to go?\n";
        std::cin >> place_name;

        if (place_name == "precinct" || place_name == "mansion" || place_name == "lnn" || place_name == "camp" ||
            place_name == "theatre" || place_name == "cave" || place_name == "institute" || place_name == "crypt" ||
            place_name == "barn" || place_name == "dungeon" || place_name == "docks" || place_name == "tower" ||
            place_name == "laboratory" || place_name == "graveyard")
        {
            places[place_name].hero_in_place.push_back(h);
            h->set_location(place_name);
            return;
            break;
        }
    }
}
//********************************************************************************* //
void moving::set_new_location(std::string place_name)
{
    if (places.find(place_name) != places.end())
    {
        places[place_name].go_to_near_place(invisable_man);
    }
    else
    {
        throw invalid_argument("place was not found");
    }
}
//************************************************************************************//
void moving::set_new_location()
{
    places[deracola->get_place()].go_to_near_place(deracola);
    places[invisable_man->get_place()].go_to_near_place(invisable_man);
}
