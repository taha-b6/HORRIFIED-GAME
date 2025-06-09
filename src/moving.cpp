#include "moving.hpp"
#include <stdexcept>
#include <iostream>
//========================================================================================================================//
using namespace std;
//========================================================================================================================//
Hero *moving::last = nullptr;
//======================================================================================
void moving::set_places(std::map<std::string, place> & p){
    places=p;
}

//============================================================================================
moving::moving(Hero *first, Hero *seccend, Monster *dera, Monster *invisible_man)
{
    first_hero = first;
    seccend_hero = seccend;
    deracula = dera;
    invisible_man = invisible_man;
}
//========================================================================================================================//
void moving::set_new_location(Hero *h, std::string place_name, bool f = false)
{
    place &themp = places[h->get_hero_place()];
    if (!f)
    {
        bool succesful = false;
        for (auto &p : themp.near_place)
        {
            if (place_name == p)
            {
                succesful = true;
                try
                {
                    get_place(p).put_in_place(h);
                    cout << "do you like move villager if yes enter one\n";
                    int a;
                    cin >> a;
                    if (a == 1)
                    {

                        place::put_villager_in_place(h, themp, p);
                    }
                    else
                    {
                        return;
                    }
                }
                catch (runtime_error &e)
                {
                    cerr << e.what() << endl;
                    throw;
                }
            }
        }
        if (!succesful)
        {
            throw runtime_error("place not found");
        }
    }
    if (f)
    {
        moving::get_place(h->get_hero_place()).delete_hero(h);
        try
        {
            themp.put_in_place(h);
        }
        catch (...)
        {
        }
    }
}
//========================================================================================================================//
void moving::set_new_location(std::string place_name)
{
    if (places.find(place_name) != places.end())
    {
        places[place_name].go_to_near_place(invisible_man);
    }
    else
    {
        throw invalid_argument("place was not found");
    }
}
//========================================================================================================================//
void moving::set_new_location(int a = 0)
{
    if (a == 0)
    {
        places[deracula->get_monster_place()].go_to_near_place(deracula);
        places[invisible_man->get_monster_place()].go_to_near_place(invisible_man);
    }
    else
    {
        places[first_hero->get_hero_place()].go_to_near_place(first_hero);
        places[first_hero->get_hero_place()].go_to_near_place(first_hero);
        places[seccend_hero->get_hero_place()].go_to_near_place(first_hero);
        places[seccend_hero->get_hero_place()].go_to_near_place(first_hero);
    }
}
//========================================================================================================================//
void moving::set_new_lacation_for_villager(Hero *h, string place_of_hero, string place_name = "")
{
    place &themp = places[place_of_hero];
    if (place_name != "")
    {
        place::put_villager_in_place(h, themp, place_name);
    }
    if (place_name == "")
    {
        place::put_villager_in_place(h, themp, place_name);
    }
}
//********************************************************************//
void moving::set_location_for_villagers(Villager v, std::string n)
{
    try
    {
        places[n].put_vilager(v);
    }
    catch (runtime_error &e)
    {
        cerr << e.what() << endl;
    }
}

//========================================================================================================================//
place &moving::get_place(std::string place_name)
{
    return places[place_name];
}
//========================================================================================================================//
bool moving::each_tabot_distroy()
{
    bool can = false;
    for (auto &p : places)
    {
        can = p.second.get_tabot();
    }
    return can;
}
//========================================================================================================================//
void moving::kill_inviseble_man()
{
    invisible_man = nullptr;
}
//========================================================================================================================//
void moving::kill_deracula()
{
    deracula = nullptr;
}
//========================================================================================================================//
place &moving::get_near_place(std::string n)
{
    vector<string> p = places[n].get_p();
    cout << "near place is\n";
    for (auto &pl : p)
    {
        cout << pl << endl;
    }
    cout << "which place you like \n";
    string pla;
    cin >> pla;
    return places[pla];
}
//**********************************************************//
void moving::set_last_hero(Hero *h)
{
    last = h;
}
//**********************************************************************************//
void moving::set_location_deracula(std::string place_name = "")
{
    try
    {
        if (place_name == "")
        {
            get_place(last->get_hero_place()).put_in_place(deracula);
        }
        if (place_name != "")
        {
            get_place(place_name).put_in_place(deracula, true);
        }
    }
    catch (runtime_error &e)
    {
        cout << e.what() << endl;
    }
}
//*********************************************************************************//
string moving::get_place_whit_max_item()
{
    string pl;
    int max = 0;
    for (auto &p : places)
    {
        if (p.second.get_num_of_items() > max)
        {
            max = p.second.get_num_of_items();
            pl = p.first;
        }
    }
    return pl;
}
//===============================================================================
void moving::set_location_invisible_man()
{
    try
    {
        get_place(invisible_man->get_monster_place()).delete_monster(invisible_man);
        places[get_place_whit_max_item()].put_in_place(invisible_man, true);
        places[get_place_whit_max_item()].erase_item();
    }
    catch (runtime_error &e)
    {
        cerr << e.what() << endl;
    }
}
//==========================================================================================
void moving::set_new_location(std::string name, int a)
{
    if (name == "deracula")
    {
        if (a == 1)
        {

            for (auto &p : places[deracula->get_monster_place()].near_place)
            {
                if (!get_place(p).hero_in_place.empty())
                {
                    get_place(p).go_to_near_place(deracula);
                    return;
                }
            }
            string p = places[deracula->get_monster_place()].near_place.back();
            get_place(p).go_to_near_place(deracula);
        }
        if (a == 2)
        {
            for (auto &p : places[deracula->get_monster_place()].near_place)
            {
                for (auto &pl : get_place(p).near_place)
                {
                    if (!get_place(pl).hero_in_place.empty())
                    {
                        get_place(pl).go_to_near_place(deracula);
                        return;
                    }
                }
            }
            string p = places[deracula->get_monster_place()].near_place.back();
            get_place(p).go_to_near_place(deracula);
        }
    }
    if (name == "invisible_man")
    {
        if (a == 1)
        {

            for (auto &p : places[deracula->get_monster_place()].near_place)
            {
                if (!get_place(p).villager_in_place.empty())
                {
                    get_place(p).go_to_near_place(deracula);
                    return;
                }
            }
            string p = places[deracula->get_monster_place()].near_place.back();
            get_place(p).go_to_near_place(deracula);
        }
        if (a == 2)
        {
            for (auto &p : places[deracula->get_monster_place()].near_place)
            {
                for (auto &pl : get_place(p).near_place)
                {
                    if (!get_place(pl).villager_in_place.empty())
                    {
                        get_place(pl).go_to_near_place(deracula);
                        return;
                    }
                }
            }
            string p = places[deracula->get_monster_place()].near_place.back();
            get_place(p).go_to_near_place(deracula);
        }
    }
}

//================================================================================================]
void moving::special_power_invi()
{
    string n = places[invisible_man->get_monster_place()].has_villager();
    if (n != "" && n != invisible_man->get_monster_place())
    {
        try
        {
            places[n].put_in_place(invisible_man, true);
            return;
        }
        catch (runtime_error &e)
        {
            cout << e.what() << endl;
        }
    }
    if (n == "")
    {
        cout << "place which have villager dont fount\n";
    }
    if (n == invisible_man->get_monster_place())
    {
        return;
    }
}
//========================================================================
void moving::special_power_der()
{
    places[deracula->get_monster_place()].put_hero(last);
}
