#include "moving.hpp"
#include <stdexcept>
#include <iostream>
//========================================================================================================================//
using namespace std;
//========================================================================================================================//
Hero *moving::last = nullptr;
Hero *moving::first_hero = nullptr;
Hero *moving::seccend_hero = nullptr;
Monster *moving::invisible_man = nullptr;
Monster *moving::deracula = nullptr;
map<std::string, place *> &moving::places = *(new std::map<std::string, place *>());

//======================================================================================
void moving::set_places(std::map<std::string, place *> &p)
{
    if (p.empty()) {
        throw std::runtime_error("Error: 'places' map is empty during set_places() call.");
    }
    places = p;
}

//============================================================================================
moving::moving(Hero *first, Hero *seccend, Monster *dera, Monster *invisible_man)
{
    first_hero = first;
    seccend_hero = seccend;
    deracula = dera;
    this->invisible_man = invisible_man;
}
//========================================================================================================================//
void moving::set_new_location(Hero *h, std::string place_name, bool f)
{
    if (!h) {
        throw invalid_argument("Error: Null pointer passed for Hero in set_new_location.");
    }

    if (places.find(h->get_hero_place()) == places.end()) {
        throw runtime_error("Error: Current hero location not found in map.");
    }

    cout << "Selected place : " << place_name << endl;
    place *themp = places[h->get_hero_place()];

    if (!f) 
    {
        bool successful = false;

        for ( auto &p : themp->near_place)
        {
            if (place_name == p)
            {
                successful = true;
                try
                {
                    place* maghsad=moving::get_place(p);
                    maghsad->put_in_place(h);
                    cout << "Do you want to move a villager? Enter 1 for Yes: \n";
                    int a;
                    std::cin >> a;
                    if (a == 1)
                    {
                        cout<<endl<<"plase wait ... \n";
                        themp->put_villager_in_place( h , maghsad);
                    }
                    else
                    {
                        return;
                    }
                }
                catch (std::runtime_error &e)
                {
                    std::cerr << e.what() << std::endl;
                    throw;
                }
            }
        }

        if (!successful)
        {
            throw runtime_error("Error: The selected place is not adjacent to the current location.");
        }
    }
}
//========================================================================================================================//
void moving::set_new_location(std::string place_name)
{
    if (places.find(place_name) == places.end())
    {
        throw std::invalid_argument("Error: The place was not found in the map.");
    }

    places[place_name]->go_to_near_place(invisible_man);
}
//========================================================================================================================//
void moving::set_new_location(int a)
{
    if (a == 0)
    {
        string place;
        place = get_place(deracula->get_monster_place())->near_place.back();
        places[place]->go_to_near_place(deracula);
        place = get_place(invisible_man->get_monster_place())->near_place.back();
        places[place]->go_to_near_place(invisible_man);
        place = get_place(deracula->get_monster_place())->near_place.back();
        places[place]->go_to_near_place(deracula);
        place = get_place(invisible_man->get_monster_place())->near_place.back();
        places[place]->go_to_near_place(invisible_man);        
    }
    else
    {
        string place;
        place = get_place(first_hero->get_hero_place())->near_place.back();
        places[place]->go_to_near_place(first_hero);
        place = get_place(first_hero->get_hero_place())->near_place.back();
        places[place]->go_to_near_place(first_hero);
        place = get_place(seccend_hero->get_hero_place())->near_place.back();
        places[place]->go_to_near_place(seccend_hero);
        place = get_place(seccend_hero->get_hero_place())->near_place.back();
        places[place]->go_to_near_place(seccend_hero);
    }
}
//========================================================================================================================//
void moving::set_new_lacation_for_villager(Hero *h, string place_of_hero, string place_name)
{
    place *themp = places[place_of_hero];

        themp->put_villager_in_place(h, place_name);

}
//********************************************************************//
void moving::set_location_for_villagers(Villager *v, std::string n)
{

    try
    {
        places[n]->put_vilager(v);
    }
    catch (runtime_error &e)
    {
        cerr << e.what() << endl;
    }
}

//========================================================================================================================//
place *moving::get_place(std::string place_name)
{
    return places[place_name];
}
//========================================================================================================================//
bool moving::each_tabot_distroy() {
    for (const auto &p : places) {
        if (!p.second->get_tabot()) {
            return false; 
        }
    }
    return true; 
}
//========================================================================================================================//
void moving::kill_deracula()
{
    if (!deracula) {
        throw runtime_error("Error: Deracula pointer is null.");
    }
    delete deracula;
    deracula = nullptr;
}
//========================================================================================================================//
void moving::kill_inviseble_man()
{
    if (!invisible_man) {
        throw runtime_error("Error: Invisible man pointer is null.");
    }
    delete invisible_man;
    invisible_man = nullptr;
}
//========================================================================================================================//
place *moving::get_near_place(std::string n)
{
    vector<string> p = places[n]->get_p();
    cout << "near place is\n";
    for (auto &pl : p)
    {
        cout << pl << endl;
    }
    cout << "which place you like please enter id \n";
    int a;
    cin >> a;
    string pla=to_string_place(a);
    return places[pla];
}
//**********************************************************//
void moving::set_last_hero(Hero *h)
{
    last = h;
}
//**********************************************************************************//
void moving::set_location_deracula(std::string place_name)
{
    if (!deracula) {
        throw runtime_error("Error: Null pointer for deracula in set_location_deracula.");
    }

    if (place_name=="")
    {
        moving::get_place(last->get_hero_place())->put_in_place(deracula);
    }
    if(place_name!="")
    {
        moving::get_place(place_name)->put_in_place(deracula, true);
    }
}
//*********************************************************************************//
string moving::get_place_whit_max_item()
{
    string pl="";
    int max = 0;
    for (auto &p : places)
    {
        if (p.second->get_num_of_items() > max)
        {
            max = p.second->get_num_of_items();
            pl = p.first;
        }
    }
    return pl;
}
//===============================================================================
void moving::set_location_invisible_man()
{
    try
    {string p=get_place_whit_max_item();
        if(p!=""){
            if(invisible_man->get_monster_place()!="")
        get_place(invisible_man->get_monster_place())->delete_monster(invisible_man);
        places[p]->put_in_place(invisible_man, true);
        places[p]->erase_item();}
        else{
            cout<<"no location whit the most items found yet \n";
            return;
        }
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
            bool f= true;
            for (const auto &p : places[deracula->get_monster_place()]->near_place)
            {
                if (!moving::get_place(p)->hero_in_place.empty())
                {
                    f=false;
                    moving::get_place(p)->go_to_near_place(deracula);
                    return;
                }
            }
            if(f){
                moving::get_place(places[deracula->get_monster_place()]->near_place.back())->go_to_near_place(deracula);
            }
        }
        else if (a == 2)
        {
            bool f =true;
            for (const auto &p : places[deracula->get_monster_place()]->near_place)
            {
                for (const auto &pl : moving::get_place(p)->near_place)
                {
                    if (!moving::get_place(pl)->hero_in_place.empty())
                    {
                        f=false;
                        moving::get_place(pl)->go_to_near_place(deracula);
                        return;
                    }
                }
            }
            if(f){
                moving::get_place(places[deracula->get_monster_place()]->near_place.back())->go_to_near_place(deracula);
            }            
        }
    }
    if(name=="invisible_man"){
        if (a == 1)
        {
            bool f= true;
            for (const auto &p : places[invisible_man->get_monster_place()]->near_place)
            {
                if (!moving::get_place(p)->villager_in_place.empty())
                {
                    f=false;
                    moving::get_place(p)->go_to_near_place(invisible_man);
                    return;
                }
            }
            if(f){
                moving::get_place(places[invisible_man->get_monster_place()]->near_place.back())->go_to_near_place(invisible_man);
            }
        }
        else if (a == 2)
        {
            bool f =true;
            for (const auto &p : places[invisible_man->get_monster_place()]->near_place)
            {
                for (const auto &pl : moving::get_place(p)->near_place)
                {
                    if (!moving::get_place(pl)->villager_in_place.empty())
                    {
                        f=false;
                        moving::get_place(pl)->go_to_near_place(invisible_man);
                        return;
                    }
                }
            }
            if(f){
                moving::get_place(places[invisible_man->get_monster_place()]->near_place.back())->go_to_near_place(invisible_man);
            }            
        }        
    }
}

//================================================================================================]
void moving::special_power_invi()
{
    string n = places[invisible_man->get_monster_place()]->has_villager();
    if (n != "" && n != invisible_man->get_monster_place())
    {
        try
        {
            places[n]->put_in_place(invisible_man, true);
            return;
        }
        catch (runtime_error &e)
        {
            cerr << e.what() << endl;
        }
    }
    if (n == "")
    {
        cout << "invisible man go to near villager \n";
    }
    if (n == invisible_man->get_monster_place())
    {
        return;
    }
}
//========================================================================
void moving::special_power_der()
{
    places[deracula->get_monster_place()]->put_hero(last);
}
//===============================================================================
bool moving::hero_won()
{
    for (const auto &p : places)
    {
        if (!p.second->each_monster_kiil())
        {
            return false;
        }
    }
    return true;
}
//************************************************************************************ */
void moving::start()
{
    last=first_hero;

    if (first_hero->name == "Mayor")
    {
        places["theatre"]->go_to_near_place(first_hero);
        places["docks"]->go_to_near_place(seccend_hero);
    }
    if (first_hero->name == "Archaeologist")
    {
        places["theatre"]->go_to_near_place(seccend_hero);
        places["ducks"]->go_to_near_place(first_hero);
    }
    places["mansion"]->go_to_near_place(deracula);
    places["institute"]->go_to_near_place(invisible_man);
}
