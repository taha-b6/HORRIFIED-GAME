#include <iostream>
#include <string>
#include <vector>
#include <variant>
#include <algorithm>
#include "place.hpp"
#include <map>

//***********************************************************************************************************************//

using namespace std;

place::place(string n):name(n){
    if(n=="cave"||n=="dungeon"||n=="crypt"||n=="graveyard"){
        tabot=true;
    }
}


place::~place(){}
//=========================================        ===================================================================

void place::put_in_place(Monster *m)
{
    for (auto &mon : monster_in_place)
    {
        if (m != mon)
        {
            monster_in_place.push_back(m);
            m->set_location(this->name);
            return;
        }
    }
    throw runtime_error("monster was in place ");
}
//=========================================    =========================================================
void place::put_in_place(Hero *h)
{

    for (auto &her : hero_in_place)
    {
        if (h != her)
        {
            hero_in_place.push_back(h);
            h->set_location(this->name);
            return;
        }
    }
    throw runtime_error("hero was in place ");
}
//=====================================     ======================================================

void place::go_to_near_place(Monster *monsters)
{
    bool succsesful = false;
    do
    {
        try
        {
            put_in_place(monsters);
            cout << " new location of " << monsters->name << " is : " << this->name << endl;
            succsesful = true;
            break;
        }
        catch (runtime_error &e)
        {
        }
    } while (!succsesful);
}
//******************************************************************************//
void place::go_to_near_place(Hero *hero)
{
    bool succsesful = false;
    do
    {
        try
        {
            put_in_place(hero);
            cout << " new location of " << hero->name << " is : " << this->name << endl;
            succsesful = true;
            break;
        }
        catch (runtime_error &e)
        {
            cout << e.what() << endl;
        }
    } while (!succsesful);
}
//***********************************************************************//
void place::show_near_place()
{
    for (const auto &p : near_place)
    {
        cout << "your near place is : \n";
        cout << p.name << "\t";
    }
}
//****************************************************************************************//
void place::put_villager_in_place(Hero* h, place &origin, place &destination)
{
    //وقتی استفاده میشود که action moveباشد 
    destination.villager_in_place.insert(
        destination.villager_in_place.end(),
        origin.villager_in_place.begin(),
        origin.villager_in_place.end());
    origin.villager_in_place.clear();
    for(auto & v: destination.villager_in_place){
        v.set_place(destination.name);
        if(v.is_safe_place()){
            h->increase_perk_card(bag_perks::get_one_perk_card());
        }
    }   
}
//*********************************************************************** //
void place::put_villager_in_place(Hero* h , place& p , std::string place_name =""){
    //وقتی استفاده میشود که action guid باشد
    if(place_name!=""){
        //گذاشتن محلی در خانه قهرمان
        Villager& v= near_place.back().villager_in_place.back();
        p.villager_in_place.push_back(v);
        v.set_place(p.name);
        near_place.back().villager_in_place.pop_back();
        if(p.villager_in_place.back().is_safe_place()){
            h->increase_perk_card(bag_perks::get_one_perk_card());
        }
    }
    if(place_name==""){
        //گذاشتن محلی در خانه قهرمان در مکان های همسایه
        Villager & v =p.villager_in_place.back();
        for(auto & pl:p.near_place){
            if(pl.name==v.name_of_safe_place()){
                pl.villager_in_place.push_back(v);
                v.set_place(pl.name);
                h->increase_perk_card(bag_perks::get_one_perk_card());
                return;
            }
            cout<<"please enter name of place which do you like villager go to it\n";
            string n;
            cin>>n;
            place& plac= moving::get_place(n);
            plac.villager_in_place.push_back(v);
            v.set_place(plac.name);

        if(plac.villager_in_place.back().is_safe_place()){
            h->increase_perk_card(bag_perks::get_one_perk_card());}
        }
    }
}
//*************************************************************************//
 vector<item> place::get_items(int a){
    vector <item> temp;
    if(a>items_list.size()){
        throw invalid_argument("here dont have enogh item");
    }
    for(int i =0 ; i<a ; ++i){
        temp.push_back(items_list.back());
        items_list.pop_back();//باید برود در وکتور خارج از بازی   
    }
    return temp;
 }
 //**************************************************************************************//
 bool place::get_tabot(){
    return tabot;
 }
 //***********************************************************************************//
 void place::destroy_tabot(){
    tabot==false;
 }
 //*****************************************************************************************//
 int place::get_monster_in_place(){
    if(monster_in_place.empty()){
        return 0;
    }
    if(monster_in_place.size()==2){
        return 1;
    }
    if(Invisable_man * m = dynamic_cast<Invisable_man*>(monster_in_place.back())){
        return 2;
    }
    if(Deracola* d = dynamic_cast<Deracola*> (monster_in_place.back())){
        return 3;
    }
 }
 //***************************************************************************//
 void place::kill_monster(int a) {
    bool found = false;

    for (auto it = monster_in_place.begin(); it != monster_in_place.end(); ++it) {
        if (a == 1) { 
            if (dynamic_cast<Invisable_man*>(*it)) {
                monster_in_place.erase(it);
                std::cout << "Invisible man removed from place.\n";
                found = true;
                break;
            }
        } else if (a == 2) { 
            if (dynamic_cast<Deracola*>(*it)) {
                monster_in_place.erase(it);
                std::cout << "Deracola removed from place.\n";
                found = true;
                break;
            }
        }
    }
    if (!found) {
        std::cout << "Monster not found in place.\n";
    }
}
//**********************************************************************//
std::vector<place> place::get_p(){
    return near_place;
}