#include <iostream>
#include <string>
#include <vector>
#include <variant>
#include <algorithm>
#include "place.hpp"
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
using namespace std;

//========================================================================================================================//

place::place(string n) : name(n)
{

    if (name == "cave")
    {
        near_place.push_back("camp");
        tabot = true;
    }
    if (name == "camp")
    {
        near_place.push_back("cave");
        near_place.push_back("precinct");
        near_place.push_back("mansion");
        near_place.push_back("theatre");
        near_place.push_back("inn");
    }
    if (name == "precinct")
    {
        near_place.push_back("camp");
        near_place.push_back("inn");
        near_place.push_back("theatre");
        near_place.push_back("mansion");
    }
    if (name == "inn")
    {
        near_place.push_back("precinct");
        near_place.push_back("camp");
        near_place.push_back("theatre");
        near_place.push_back("mansion");
    }
    if (name == "barn")
    {
        near_place.push_back("theatre");
    }
    if (name == "dungion")
    {
        tabot = true;
        near_place.push_back("tower");
    }
    if (name == "theatre")
    {
        near_place.push_back("inn");
        near_place.push_back("precinct");
        near_place.push_back("camp");
        near_place.push_back("mansion");
        near_place.push_back("tower");
        near_place.push_back("shop");
    }
    if (name == "tower")
    {
        near_place.push_back("theatre");
        near_place.push_back("docks");
        near_place.push_back("dungion");
    }
    if (name == "mansion")
    {
        near_place.push_back("abbey");
        near_place.push_back("camp");
        near_place.push_back("precinct");
        near_place.push_back("inn");
        near_place.push_back("theatre");
        near_place.push_back("shop");
        near_place.push_back("mansion");
        near_place.push_back("church");
    }
    if (name == "docks")
    {
        near_place.push_back("tower");
    }
    if (name == "abbey")
    {
        near_place.push_back("mansion");
        near_place.push_back("crypt");
    }
    if (name == "shop")
    {
        near_place.push_back("theatre");
        near_place.push_back("mansion");
        near_place.push_back("musium");
        near_place.push_back("church");
        near_place.push_back("laboratory");
    }
    if (name == "crypt")
    {
        tabot = true;
        near_place.push_back("abbey");
    }
    if (name == "musium")
    {
        near_place.push_back("mansion");
        near_place.push_back("shop");
        near_place.push_back("church");
    }
    if (name == "church")
    {
        near_place.push_back("mansion");
        near_place.push_back("musium");
        near_place.push_back("hospital");
        near_place.push_back("graveyard");
        near_place.push_back("shop");
    }
    if (name == "laboratory")
    {
        near_place.push_back("shop");
        near_place.push_back("institute");
    }
    if (name == "hospital")
    {
        near_place.push_back("church");
    }
    if (name == "graveyard")
    {
        tabot = true;
        near_place.push_back("church");
    }
    if (name == "institute")
    {
        near_place.push_back("laboratory");
    }
}

//========================================================================================================================//
void place::delete_monster(Monster *m)
{
    if (m->get_monster_place() == "")
    {
        return;
    }
    auto it = std::find(monster_in_place.begin(), monster_in_place.end(), m);
    if (it != monster_in_place.end())
    {
        monster_in_place.erase(it);
    }
}
//==============================================================
void place::delete_hero(Hero *h)
{
    if (h->get_hero_place() == "")
    {
        return;
    }
    auto it = std::find(hero_in_place.begin(), hero_in_place.end(), h);
    if (it != hero_in_place.end())
    {
        hero_in_place.erase(it);
    }
}

void place::put_in_place(Monster *m, bool f)
{
    if (monster_in_place.size() == 2)
    {
        throw runtime_error("monster was in place ");
        return;
    }
    if (monster_in_place.size() == 1 && monster_in_place.back()->m_name == m->m_name)
    {
        throw runtime_error("monster was in place ");
        return;
    }
    if (m->get_monster_place() != "")
    {
        moving::get_place(m->get_monster_place())->delete_monster(m);
    }
    monster_in_place.push_back(m);
    m->set_location(this->name);
    cout <<endl<<"------------------"<< "  new location of : " << m->m_name << " is " << this->name <<"------------------"<< endl;
}
//========================================================================================================================//
void place::put_in_place(Hero *h)
{
    if (hero_in_place.size() == 2)
    {
        throw runtime_error("Hero was in place ");
    }
    if (hero_in_place.size() == 1 && hero_in_place.back()->name == h->name)
    {
        throw runtime_error("Hero was in place ");
    }
    if (h->get_hero_place() != "")
    {
        moving::get_place(h->get_hero_place())->delete_hero(h);
    }
    if (h->get_hero_place() != "")
    {
        moving::get_place(h->get_hero_place())->delete_hero(h);
    }
    hero_in_place.push_back(h);
    h->set_location(this->name);
    cout <<endl<<"------------------"<< "  new location of : " << h->name << " is : " << this->name<<"------------------" << endl;
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
        cerr << e.what() << endl;
    }
}
//========================================================================================================================//
void place::go_to_near_place(Hero *hero)
{
    try
    {
        put_in_place(hero);
    }
    catch (runtime_error &e)
    {
        cerr << e.what() << endl;
    }
}
//========================================================================================================================//
vector<string> place::show_near_place()
{
    vector<string> temp;
    for (const auto &p : near_place)
    {
        temp.push_back(p);
    }
    return temp;
}
//========================================================================================================================//
void place::put_villager_in_place(Hero *h, place *destination)
{
    // وقتی استفاده میشود که action moveباشد
    if (!this->villager_in_place.empty())
    {
        destination->villager_in_place.insert(
            destination->villager_in_place.end(),
            this->villager_in_place.begin(),
            this->villager_in_place.end());
        this->villager_in_place.clear();

        for (auto &v : destination->villager_in_place)
        {
            v->set_place(destination->name);
            if (v->is_safe_place())
            {
                h->increase_perk_card(bag_perks::get_one_perk_card());
            }
        }
    }
    else
    {
        cout << "here dont have villager !!! \n";
    }
}
//========================================================================================================================//
void place::put_villager_in_place(Hero *h, std::string place_name)
{
    place *pm = moving::get_place(h->get_hero_place());
    // وقتی استفاده میشود که action guid باشد
    if (place_name != "")
    {
        bool f = false;
        for (auto &l : pm->near_place)
        {

            // گذاشتن محلی در خانه قهرمان
            if (!moving::get_place(l)->villager_in_place.empty())
            {
                f = true;
                Villager *v = moving::get_place(l)->villager_in_place.back();
                if (v->name_place() != "")
                {
                    moving::get_place(v->name_place())->villager_raft(v);
                }
                pm->villager_in_place.push_back(v);
                v->set_place(pm->name);
                if (pm->villager_in_place.back()->is_safe_place())
                {
                    h->increase_perk_card(bag_perks::get_one_perk_card());
                }
            }
            if (f)
            {
                break;
            }
        }
        if (!f)
        {
            cerr << "near place has not villager\n";
        }
    }

    if (place_name == "")
    {
        // گذاشتن محلی در خانه قهرمان در مکان های همسایه
        if (!pm->villager_in_place.empty())
        {
            Villager *v = pm->villager_in_place.back();
            for (auto &pl : pm->near_place)
            {
                if (pl == v->name_of_safe_place())
                {
                    moving::get_place(v->name_place())->villager_raft(v);
                    moving::get_place(pl)->villager_in_place.push_back(v);
                    v->set_place(pl);
                    h->increase_perk_card(bag_perks::get_one_perk_card());
                    return;
                }
                cout << "please enter name of place which do you like villager go to it\n";
                int n;
                cin >> n;
                string p = to_string_place(n);
                if (p != "")
                {
                    place *plac = moving::get_place(p);
                    moving::get_place(v->name_place())->villager_raft(v);
                    plac->villager_in_place.push_back(v);
                    v->set_place(plac->name);

                    if (plac->villager_in_place.back()->is_safe_place())
                    {
                        h->increase_perk_card(bag_perks::get_one_perk_card());
                    }
                }
            }
        }
        else
        {
            cerr << "your place hasnt villager\n";
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
        items_list.pop_back();
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
    return 0;
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
                delete *it;

                it = monster_in_place.erase(it);
                cout << "Invisible man removed from place. and it is kill\n";
                found = true;
                break;
            }
        }
        else if (a == 2)
        {
            if (dynamic_cast<Deracula *>(*it))
            {
                delete *it;
                it = monster_in_place.erase(it);
                cout << "Deracula removed from place. and it is kill\n";
                found = true;
                break;
            }
        }
    }
    if (!found)
    {
        cout << "Monster not found in place.\n";
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
    if (!items_list.empty())
    {
        for (auto &i : items_list)
        {
            bag_items::icraese_item_out_the_game(i);
        }
        items_list.clear();
    }
}
//==============================================================================================//
int place::get_num_of_items()
{
    return items_list.size();
}
//=============================================================================//
void place::put_vilager(Villager *v)
{
    if (v->name_place() != "")
        moving::get_place(v->name_place())->villager_raft(v);
    villager_in_place.push_back(v);
    v->set_place(this->name);
    cout <<endl<<"------------------"<< " location of : " << v->name << " is : " << this->name <<"------------------"<< endl;
}
//======================================================================
vector<string> place::show_villager_monster()
{
    vector<string> result;

    if (villager_in_place.empty() && monster_in_place.empty())
    {
        result.push_back("No creature found in this place");
        return result;
    }

    for (const auto &v : villager_in_place)
    {
        if (v->name != "")
            result.push_back(v->name);
    }

    for (const auto &m : monster_in_place)
    {
        if (m && !m->m_name.empty())
            result.push_back(m->m_name);
    }

    if (result.empty())
        result.push_back("No creature found in this place");

    return result;
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
        if (!moving::get_place(p)->villager_in_place.empty())
        {
            return p;
        }
    }
    for (const auto &p : near_place)
    {
        for (const auto &a : moving::get_place(p)->near_place)
        {
            if (!moving::get_place(a)->near_place.empty())
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
    if (hero_in_place.empty())
    {
        if (!villager_in_place.empty())
        {
            {
                cout << villager_in_place.back()->name << "is killed" << endl;
                villager_in_place.pop_back();
                return true;
            }
        }
    }
    return false;
}
//=======================================================================
void place::put_hero(Hero *h)
{
    moving::get_place(h->get_hero_place())->delete_hero(h);
    hero_in_place.push_back(h);
    h->set_location(this->name);
    cout << "new location for " << h->name << " is " << this->name << endl;
}
//=====================================================================================
bool place::can_deracola()
{
    if (!hero_in_place.empty())
    {

        return true;
    }
    return false;
}
//==========================================================================================
Hero *place::get_hero_in_place()
{
    if (!hero_in_place.empty())
        return hero_in_place.back();
    else
    {
        return nullptr;
    }
}
//===================================================
bool place::each_monster_kiil()
{
    return monster_in_place.empty();
}
//======================================================================================
place::~place()
{
    for (auto &h : hero_in_place)
    {
        delete h;
    }
    for (auto &m : monster_in_place)
    {
        delete m;
    }
}
//==========================================================================
void place::villager_raft(Villager *v)
{
    if (v->name_place() == "")
    {
        return;
    }

    for (auto it = villager_in_place.begin(); it != villager_in_place.end(); ++it)
    {
        if ((*it)->name == v->name)
        {
            villager_in_place.erase(it);
            break;
        }
    }
}
Villager *place::get_one_villager()
{
    if (!villager_in_place.empty())
    {
        return villager_in_place.back();
    }
    else
    {
        return nullptr;
    }
}
