#include <iostream>
#include <string>
#include <vector>
#include <variant>
#include <algorithm>
#include "place.hpp"
#include <map>
#include <algorithm>

//========================================================================================================================//

using namespace std;

place::place(string n) : name(n)
{
    if (n == "cave" || n == "dungeon" || n == "crypt" || n == "graveyard")
    {
        tabot = true;
    }
    if(n=="cave"){
        near_place.push_back("camp");
    }
    if(n=="camp"){
        near_place.push_back("cave");
        near_place.push_back("precinct");
        near_place.push_back("mansion");
        near_place.push_back("theatre");
        near_place.push_back("inn");
    }
    if(n=="precinct"){
        near_place.push_back("camp");
        near_place.push_back("inn");
        near_place.push_back("theatre");
        near_place.push_back("mansion");
    }
    if(n=="inn"){
        near_place.push_back("precinct");
        near_place.push_back("camp");
        near_place.push_back("theatre");
        near_place.push_back("mansion");
    }
    if(n=="barn"){
        near_place.push_back("theatre");
    }
    if(n=="dungion"){
        near_place.push_back("tower");
    }
    if(n=="theatre"){
        near_place.push_back("inn");
        near_place.push_back("precinct");
        near_place.push_back("camp");
        near_place.push_back("mansion");
        near_place.push_back("tower");
        near_place.push_back("shop");
    }
    if(n=="tower"){
        near_place.push_back("theatre");
        near_place.push_back("docks");
        near_place.push_back("dungion");
    }
    if(n=="mansion"){
        near_place.push_back("abbey");
        near_place.push_back("camp");
        near_place.push_back("precinct");
        near_place.push_back("inn");
        near_place.push_back("theatre");
        near_place.push_back("shop");
        near_place.push_back("mansion");
        near_place.push_back("church");
    }
    if(n=="docks"){
        near_place.push_back("tower");
    }
    if(n=="abbey"){
        near_place.push_back("mansion");
        near_place.push_back("crypt");
    }
    if(n=="shop"){
        near_place.push_back("theatre");
        near_place.push_back("mansion");
        near_place.push_back("musium");
        near_place.push_back("church");
        near_place.push_back("laboratory");
    }
    if(n=="crypt"){
        near_place.push_back("abbey");
    }
    if(n=="musium"){
        near_place.push_back("mansion");
        near_place.push_back("shop");
        near_place.push_back("church");
    }
    if(n=="charch"){
        near_place.push_back("mansion");
        near_place.push_back("musium");
        near_place.push_back("hospital");
        near_place.push_back("graveyard");
        near_place.push_back("shop");
    }
    if(n=="laboratory"){
        near_place.push_back("shop");
        near_place.push_back( "institute");
    }
    if(n=="hospital"){
        near_place.push_back("church");
    }
    if(n=="graveyard"){
        near_place.push_back("church");
    }
    if(n=="institute"){
        near_place.push_back("laboratory");
    }
}

place::~place() {}
//========================================================================================================================//
void place::delete_monster(Monster *m)
{
    auto it = std::find(monster_in_place.begin(), monster_in_place.end(), m);
    if (it != monster_in_place.end())
    {
        monster_in_place.erase(it);
    }
}
//==============================================================
void place::delete_hero(Hero *h)
{
    auto it = std::find(hero_in_place.begin(), hero_in_place.end(), h);
    if (it != hero_in_place.end())
    {
        hero_in_place.erase(it);
    }
}

void place::put_in_place(Monster *m, bool f = false)
{
    if (monster_in_place.size() == 2)
    {
        throw runtime_error("monster was in place ");
        return;
    }
    if (monster_in_place.size() == 1 && monster_in_place.back() == m)
    {
        throw runtime_error("monster was in place ");
        return;
    }
    moving::get_place(m->get_monster_place()).delete_monster(m);
    monster_in_place.push_back(m);
    m->set_location(this->name);

}
//========================================================================================================================//
void place::put_in_place(Hero *h)
{
    if (hero_in_place.size() == 2)
    {
        throw runtime_error("monster was in place ");
        return;
    }
    if (hero_in_place.size() == 1 && hero_in_place.back() == h)
    {
        throw runtime_error("monster was in place ");
        return;
    }
    moving::get_place(h->get_hero_place()).delete_hero(h);
    hero_in_place.push_back(h);
    h->set_location(this->name);
}
//========================================================================================================================//

void place::go_to_near_place(Monster *monsters)
{
        try
        {
            put_in_place(monsters);
        }
        catch (runtime_error &e)
        {
            cerr<<e.what()<<endl;
        }
}
//========================================================================================================================//
void place::go_to_near_place(Hero *hero)
{

        try
        {
            put_in_place(hero);
            cout << " new location of " << hero->name << " is : " << this->name << endl;
        }
        catch (runtime_error &e)
        {
            cout << e.what() << endl;
        }

}
//========================================================================================================================//
void place::show_near_place()
{
    for (const auto &p : near_place)
    {
        cout << "your near place is : \n";
        cout << p << "\t";
    }
}
//========================================================================================================================//
void place::put_villager_in_place(Hero *h, place &origin, place &destination)
{
    // وقتی استفاده میشود که action moveباشد
    destination.villager_in_place.insert(
        destination.villager_in_place.end(),
        origin.villager_in_place.begin(),
        origin.villager_in_place.end());
    origin.villager_in_place.clear();
    for (auto &v : destination.villager_in_place)
    {
        v.set_place(destination.name);
        if (v.is_safe_place())
        {
            h->increase_perk_card(bag_perks::get_one_perk_card());
        }
    }
}
//========================================================================================================================//
void place::put_villager_in_place(Hero *h, place &p, std::string place_name = "")
{
    // وقتی استفاده میشود که action guid باشد
    if (place_name != "")
    {
        // گذاشتن محلی در خانه قهرمان
        Villager &v = moving::get_place( near_place.back()).villager_in_place.back();
        p.villager_in_place.push_back(v);
        v.set_place(p.name);
        moving::get_place( near_place.back()).villager_in_place.pop_back();
        if (p.villager_in_place.back().is_safe_place())
        {
            h->increase_perk_card(bag_perks::get_one_perk_card());
        }
    }
    if (place_name == "")
    {
        // گذاشتن محلی در خانه قهرمان در مکان های همسایه
        Villager &v = p.villager_in_place.back();
        for (auto &pl : p.near_place)
        {
            if (pl == v.name_of_safe_place())
            {
                moving::get_place(pl).villager_in_place.push_back(v);
                v.set_place(pl);
                h->increase_perk_card(bag_perks::get_one_perk_card());
                return;
            }
            cout << "please enter name of place which do you like villager go to it\n";
            string n;
            cin >> n;
            place &plac = moving::get_place(n);
            plac.villager_in_place.push_back(v);
            v.set_place(plac.name);

            if (plac.villager_in_place.back().is_safe_place())
            {
                h->increase_perk_card(bag_perks::get_one_perk_card());
            }
        }
    }
}
//========================================================================================================================//
vector<item> place::get_items(int a)
{
    vector<item> temp;
    if (a > items_list.size())
    {
        throw invalid_argument("here dont have enogh item");
    }
    for (int i = 0; i < a; ++i)
    {
        temp.push_back(items_list.back());
        bag_items::icraese_item_out_the_game(items_list.back());
        items_list.pop_back(); // باید برود در وکتور خارج از بازی
    }
    return temp;
}
//========================================================================================================================//
bool place::get_tabot()
{
    return tabot;
}
//========================================================================================================================//
void place::destroy_tabot()
{
    tabot == false;
}
//========================================================================================================================//
int place::get_monster_in_place()
{
    if (monster_in_place.empty())
    {
        return 0;
    }
    if (monster_in_place.size() == 2)
    {
        return 1;
    }
    if (Invisible_man *m = dynamic_cast<Invisible_man *>(monster_in_place.back()))
    {
        return 2;
    }
    if (Deracula *d = dynamic_cast<Deracula *>(monster_in_place.back()))
    {
        return 3;
    }
}
//========================================================================================================================//
void place::kill_monster(int a)
{
    bool found = false;

    for (auto it = monster_in_place.begin(); it != monster_in_place.end(); ++it)
    {
        if (a == 1)
        {
            if (dynamic_cast<Invisible_man *>(*it))
            {
                delete * it;

                it= monster_in_place.erase(it);
                std::cout << "Invisible man removed from place.\n";
                found = true;
                break;
            }
        }
        else if (a == 2)
        {
            if (dynamic_cast<Deracula *>(*it))
            {
                delete * it;
                 it=monster_in_place.erase(it);
                std::cout << "Deracula removed from place.\n";
                found = true;
                break;
            }
        }
    }
    if (!found)
    {
        std::cout << "Monster not found in place.\n";
    }
}
//========================================================================================================================//
vector<string> place::get_p()
{
    return near_place;
}
//========================================================================================================================//
void place::erase_item()
{
    items_list.clear();
}
//==============================================================================================//
int place::get_num_of_items()
{
    return items_list.size();
}
//=============================================================================//
void place::put_vilager(Villager v)
{
    villager_in_place.push_back(v);
    v.set_place(this->name);
}
//======================================================================
vector<string> place::show_villager_monster(){
    vector<string> temp;
    for(auto const & v :villager_in_place ){
        temp.push_back(v.name);
    }
    for(auto & const m : monster_in_place){
        temp.push_back(m->m_name);
    }
    return temp;
}

//**************************************************************************//
string place::has_villager()
{
    if (!villager_in_place.empty())
    {
        return this->name;
    }
    for (const auto &p : near_place)
    {
        if (!moving::get_place(p).villager_in_place.empty())
        {
            return p;
        }
    }
    for (const auto &p : near_place)
    {
        for (const auto &a : moving::get_place(p).near_place)
        {
            if (!moving::get_place(a).near_place.empty())
            {
                return a;
            }
        }
    }
    return "";
}
//==================================================================================
bool place::can_invisible_man()
{
    if (hero_in_place.empty() && !villager_in_place.empty())
    {
        cout << villager_in_place.back().name << "is killed" << endl;
        villager_in_place.pop_back();
        return true;
    }
    return false;
}
//=======================================================================
void place::put_hero(Hero* h){
    moving::get_place(h->get_hero_place()).delete_hero(h);
    hero_in_place.push_back(h);
    h->set_location(this->name);
}
//=====================================================================================
bool place::can_deracola(){
    if(!hero_in_place.empty()){

        return true;
    }
    return false;
}
//==========================================================================================
 Hero* place::get_hero_in_place(){
    return hero_in_place.back();
}
//===================================================
bool place::each_monster_kiil(){
    if(monster_in_place.size()==0){
        return true;
    }
    return false;
}
//======================================================================================
place:: ~place(){
    for(auto & h : hero_in_place ){
        delete h;
    }
    for(auto & m : monster_in_place){
        delete m;
    }
}

