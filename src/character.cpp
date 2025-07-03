#include <iostream>
#include <string>
#include <vector>
#include <variant>
#include <algorithm>
#include "character.hpp"
#include <map>

//========================================================================================================================//

using namespace std;
//========================================================================================================================//
actions which_action(int a)
{
    switch (a)
    {
    case 0:
        return Move;
    case 1:
        return Guide;
    case 2:
        return Pickup;
    case 3:
        return Advance;
    case 4:
        return Defeat;
    case 5:
        return Special_Action;
    default:
        return Move;
    }
}

//========================================================================================================================//
int which_perk_card(perk_card *c)
{
    if (dynamic_cast<visit_from_the_detective *>(c))
    {
        return 1;
    }
    else if (dynamic_cast<break_of_dawn *>(c))
    {
        return 2;
    }
    else if (dynamic_cast<overstock *>(c))
    {
        return 3;
    }
    else if (dynamic_cast<late_into_the_night *>(c))
    {
        return 4;
    }
    else if (dynamic_cast<repel *>(c))
    {
        return 5;
    }
    else if (dynamic_cast<hurry *>(c))
    {
        return 6;
    }
    else
    {
        return 0;
    }
}
//========================================================================================================================//
void do_perk(Hero *h, bool &f)
{
    int a;
    while (1)
    {
        if (h->perk_cards.empty())
        {
            return;
        }
        perk_card *p = h->perk_cards.back();
        switch (which_perk_card(p))
        {
        case 1:
        {
            visit_from_the_detective *v = dynamic_cast<visit_from_the_detective *>(p);
            cout << "perk card is ;" << v->name << endl;
            v->play_perk(moving::get_invisible_man(), f);
            break;
        }
        case 2:
        {
            break_of_dawn *b = dynamic_cast<break_of_dawn *>(p);
            cout << "perk card is ;" << b->name << endl;
            b->play_perk(f);
            break;
        }
        case 3:
        {
            overstock *o = dynamic_cast<overstock *>(p);
            cout << "perk card is ;" << o->name << endl;
            o->play_perk(f);
            break;
        }
        case 4:
        {
            late_into_the_night *l = dynamic_cast<late_into_the_night *>(p);
            cout << "perk card is ;" << l->name << endl;
            l->play_perk(h, f);
            break;
        }
        case 5:
        {

            repel *r = dynamic_cast<repel *>(p);
            cout << "perk card is ;" << r->name << endl;
            r->play_perk(moving::get_deracula(), moving::get_invisible_man(), f);
            break;
        }
        case 6:
        {

            hurry *h = dynamic_cast<hurry *>(p);
            cout << "perk card is ;" << h->name << endl;
            h->play_perk(moving::get_first_hero(), moving::get_seccend_hero(), f);
            break;
        }
        default:
            break;
        }
        delete p;
        p = nullptr;
        h->perk_cards.pop_back();
        cout << "do you like play eater perk_card enter one\n";
        cin >> a;
        if (a != 1)
        {
            break;
        }
        if (a == 1)
        {
            continue;
        }
    }
}
//============================================================================================//
/*
string to_string_place(int p)
{
    switch (p)
    {
    case 0:
        return "precinct";
    case 1:
        return "mansion";
    case 2:
        return "inn";
    case 3:
        return "camp";
    case 4:
        return "theatre";
    case 5:
        return "cave";
    case 6:
        return "institute";
    case 7:
        return "crypt";
    case 8:
        return "barn";
    case 9:
        return "dungion";
    case 10:
        return "docks";
    case 11:
        return "tower";
    case 12:
        return "laboratory";
    case 13:
        return "graveyard";
    case 14:
        return "hospital";
    case 15:
        return "abbey";
    case 17:
        return "church";
    case 18:
        return "musium";
    case 19:
        return "shop";
    default:
        return "";
    }
}
*/
string to_string_place(int p)
{
    switch (p)
    {
    case 0:
        return "precinct";
    case 1:
        return "mansion";
    case 2:
        return "musium";
    case 3:
        return "inn";
    case 4:
        return "camp";
    case 5:
        return "theatre";
    case 6:
        return "cave";
    case 7:
        return "institute";
    case 8:
        return "crypt";
    case 9:
        return "barn";
    case 10:
        return "dungion";
    case 11:
        return "docks";
    case 12:
        return "tower";
    case 13:
        return "laboratory";
    case 14:
        return "graveyard";
    case 15:
        return "hospital";
    case 16:
        return "abbey";
    case 17:
        return "church";
    case 18:
        return "shop";
    default:
        return "";
    }
}
//========================================================================================================================//
string Monster::get_monster_place()
{
    return wher_is_monster;
}
//========================================================================================================================//
Hero::Hero() {}
//========================================================================================================================//
void Hero::set_location(string place_name)
{
    wher_is_hero = place_name;
}
//========================================================================================================================//
void Monster::set_location(string place_name)
{
    wher_is_monster = place_name;
}
//========================================================================================================================//
void Hero::increase_action(int new_action)
{
    action += new_action;
}
//=================================================================
void Hero::get_one_item()
{
    if (items.size() > 0)
    {
        item temp = items.back();
        bag_items::icraese_item_out_the_game(temp);
        items.pop_back();
    }
    else
    {
        throw runtime_error("you dont havr enogh item");
    }
}

//========================================================================================================================//

string Hero::get_hero_place() const
{
    return wher_is_hero;
}
//========================================================================================================================//
void Hero::increase_perk_card(perk_card *new_perk)
{
    perk_cards.push_back(new_perk);
}

//========================================================================================================================//void Hero::domp_perk(perk_card *domp)void Hero::domp_perk(perk_card *domp)

//========================================================================================================================//
Hero::Hero(const Hero &h)
{
    this->name = h.name;
    for (auto &p : h.perk_cards)
    {
        this->perk_cards.push_back(p);
    }
}
//========================================================================================================================//
Archaeologist::Archaeologist()
{
    perk_cards.push_back(bag_perks::get_one_perk_card());
    name = "Archaeologist";
}
//========================================================================================================================//
void Archaeologist::set_action()
{
    action = 4;
}
//***************************************************************************** //
Mayor::Mayor()
{
    perk_cards.push_back(bag_perks::get_one_perk_card());
    name = "Mayor";
}

//========================================================================================================================//
void Mayor::set_action()
{
    action = 5;
}
//========================================================================================================================//
bool Hero::can_distroy(int power, string color)
{
    bool can = false;
    int p = 0;
    std::vector<item *> temp;

    for (auto &i : items)
    {
        if (i.get_coler() == color)
        {
            temp.push_back(&i);
            p += i.get_power();
        }

        if (p >= power)
        {
            can = true;
            break;
        }
    }
    if (p >= power)
    { // tempباید به کیسه اضافهشود
        for (auto &i : temp)
        {
            bag_items::icraese_item_out_the_game(*i);
        }
        items.erase(std::remove_if(items.begin(), items.end(),
                                   [&temp](const item &i)
                                   {
                                       return std::any_of(temp.begin(), temp.end(),
                                                          [&i](item *ptr)
                                                          { return &i == ptr; });
                                   }),
                    items.end());
    }

    return can;
}
//========================================================================================================================//

void Hero::do_action(bool &f)
{
    static int how_many_item = 0;
    int a;
    actions what_action;

    while (this->action > 0)
    {
        // درخواست دوباره مقدار `what_action`
        cout << "Enter the action ID you want to perform (between 0 to 5):\n";
        cin >> a;

        if (a >= 0 && a <= 5)
        {
            what_action = which_action(a);
        }
        else
        {
            cerr << "The given number is incorrect. Your turn is over!\n";
            return;
        }

        place *p = moving::get_place(wher_is_hero);

        switch (what_action)
        {
        case Move:
        {
            --this->action;
            bool moved = false;

            while (!moved)
            {
                cout << "Please enter the place you want to go (0 to 18):\n";
                cin >> a;
                if (a >= 0 && a <= 18)
                {
                    string name_place = to_string_place(a);
                    if (name_place != "")
                    {
                        try
                        {
                            moving::set_new_location(this, name_place);
                            moved = true;
                        }
                        catch (runtime_error &e)
                        {
                            cout << e.what() << endl;
                        }
                    }
                }
                else
                {
                    cout << "Invalid number. Please enter a number between 0 and 18.\n";
                }
            }
            break;
        }

        case Guide:
        {
            --this->action;
            cout << "Do you want to move a villager in your location (enter 1) or bring one from a nearby place (enter 2)?\n";
            cin >> a;

            if (a == 1)
            {
                moving::set_new_lacation_for_villager(this, wher_is_hero, wher_is_hero);
            }
            if (a == 2)
            {
                moving::set_new_lacation_for_villager(this, wher_is_hero, "");
            }
            break;
        }

        case Pickup:
        {
            --this->action;
            vector<item> temp;
            cout << "How many items do you want to pick up?\n";
            cin >> a;

            if (a >= 0)
            {
                try
                {
                    temp = p->get_items(a);
                    for (const auto &i : temp)
                    {
                        if (wher_is_hero == "inn" || wher_is_hero == "mansion" || wher_is_hero == "barn" || wher_is_hero == "laboratory" || wher_is_hero == "institute")
                        {
                            items_for_distroy_invisble_man.push_back(i);
                        }
                        else
                        {
                            items.push_back(i);
                        }
                    }
                }
                catch (invalid_argument &e)
                {
                    cout << e.what() << endl;
                }
            }
            else
            {
                cout << "Invalid item count.\n";
            }
            break;
        }
        case Advance:
        {
            --this->action;
            cout << "please wait while the information is processed ... " << endl;
            --action;
            if (p->get_tabot())
            {
                cout << "here has tabot if you lik distroed it enter one\n";
            }
            else
            {
                cout << "here dont have tabot !!! \n";
                break;
            }
            if (p->name == "percinct")
            {
                cout << "for giv the items for kill invisble man enter 2\n";
            }
            else
            {
                break;
            }
            cin >> a;
            if (a == 1)
            {
                bool c = can_distroy(6, "red");
                if (c)
                {
                    p->destroy_tabot();
                }
            }
            if (a == 2)
            {
                how_many_item += items_for_distroy_invisble_man.size();
                items_for_distroy_invisble_man.clear();
            }
            break;
        }
        case Defeat:
        {
            --this->action;

            switch (p->get_monster_in_place())
            {
            case 1:
            {
                cout << "here has invisble_man and deracula for kill the invisble man enter 2 and for deracula enter 3\n";
                cin >> a;
                if (a == 2)
                {
                    if (how_many_item >= 5)
                    {
                        if (can_distroy(9, "red"))
                        {
                            p->kill_monster(1);
                            try
                            {
                                moving::kill_inviseble_man();
                            }
                            catch (runtime_error &e)
                            {
                                cerr << e.what() << endl;
                            }
                        }
                        else
                        {
                            cout << "you cant kill invisble man beacase you dont have enogh item\n";
                        }
                    }
                    else
                    {
                        cout << "you dont have enogh item\n";
                    }
                }
                if (a == 3)
                {
                    if (can_distroy(6, "yellow"))
                    {
                        p->kill_monster(2);
                        try
                        {
                            moving::kill_deracula();
                        }
                        catch (runtime_error &e)
                        {
                            cerr << e.what() << endl;
                        }
                    }
                    else
                    {
                        cout << "you dont have enogh yellow item\n";
                    }
                }
                break;
            }
            case 2:
            {
                if (how_many_item >= 5)
                {
                    if (can_distroy(9, "red"))
                    {
                        p->kill_monster(1);
                        try
                        {
                            moving::kill_inviseble_man();
                        }
                        catch (runtime_error &e)
                        {
                            cerr << e.what() << endl;
                        }
                    }
                    else
                    {
                        cout << "you cant kill invisble man beacase you dont have enogh item\n";
                    }
                }
                else
                {
                    cout << "each item dont catch\n";
                }
            }
            case 3:
            {
                if (can_distroy(6, "yellow"))
                {
                    p->kill_monster(2);
                    try
                    {
                        moving::kill_deracula();
                    }
                    catch (runtime_error &e)
                    {
                        cerr << e.what() << endl;
                    }
                }
                else
                {
                    cout << "you dont have enogh yellow item\n";
                }
            }
            default:
                cout << "here dont have moster !!!" << endl;
                break;
            }
            break;
        }
        case Special_Action:
        {
            --this->action;
            if (name == "Archaeologist")
            {
                cout << "what place you like catch item in that ? \n";
                cout << "enter place number " << endl;
                int l;
                cin >> l;
                if (l >= 0 && l <= 18)
                {
                    string p = to_string_place(l);

                    place *ph = moving::get_near_place(wher_is_hero);
                    place *pl = nullptr;
                    vector<string> near = ph->show_near_place();
                    for (auto &n : near)
                    {
                        if (p == n)
                        {
                            pl = moving::get_place(p);
                            break;
                        }
                    }
                    if (pl == nullptr)
                    {
                        cerr << "selected place is not your naghbor !! \n";
                        break;
                    }

                    vector<item> temp;
                    cout << "how many item do you want? \n";
                    int a;
                    cin >> a;
                    if (a >= 0)
                    {
                        try
                        {
                            temp = pl->get_items(a);
                            for (const auto &i : temp)
                            {
                                if (wher_is_hero == "inn" || wher_is_hero == "mansiom" || wher_is_hero == "barn" || wher_is_hero == "laboratory" || wher_is_hero == "institute")
                                {
                                    items_for_distroy_invisble_man.push_back(i);
                                }
                                else
                                {
                                    items.push_back(i);
                                }
                            }
                        }
                        catch (invalid_argument &e)
                        {
                            cout << e.what() << endl;
                        }
                    }
                    else
                    {
                        cout << "the entered number was wrong \n";
                    }
                }
            }
            else
            {
                cerr << "you cant do special power beacuse you are mayor !!! \n";
                break;
            }
            break;
        }
        default:
            break;
        }

        if (name == "Mayor" &&this->action>0)
        {
            cout << "Do you want to continue? Enter 1 to choose a new action or any other number to exit.\n";
            cin >> a;
            if (a != 1)
            {
                return;
            }
        }
    }
}

//========================================================================================================================//
void Archaeologist::do_action(bool &f)
{
    cout << "HERO PHASE : " << this->name << endl;
    this->set_action();
    Hero::do_action(f);
    cout << "do you like play perk enter one\n";
    int a;
    cin >> a;
    if (a == 1)
    {
        if (!perk_cards.empty())
        {
            do_perk(this, f);
        }
        else
        {
            cerr << "you dont have perk card\n";
        }
    }
}
//========================================================================================================================//
void Mayor::do_action(bool &f)
{
    cout << " HERO PHASE : " << this->name << endl;
    this->set_action();
    Hero::do_action(f);
    cout << "do you like play perk enter one\n";
    int a;
    cin >> a;
    if (a == 1)
    {
        if (!perk_cards.empty())
        {
            do_perk(this, f);
        }
        else
        {
            cerr << "you dont have perk card\n";
        }
    }
}

//========================================================================================================================//
Villager::Villager(std::string villger_name, std::string safe_place)
{
    name = villger_name;
    this->safe_place = safe_place;
}
//========================================================================================================================//
void Villager::set_place(std::string p)
{

    name_of_place = p;
}
//========================================================================================================================//
bool Villager::is_safe_place()
{
    if (name_of_place == safe_place)
    {
        return true;
    }
    else
    {
        return false;
    }
}
//=====================================================================================
void Invisible_man::invisible_man_special_power()
{
    moving::special_power_invi();
}
//============================================================================
bool Invisible_man::invisible_man_strike()
{
    if (moving::get_place(wher_is_monster)->can_invisible_man())
    {
        return true;
        // فاز هیولا رد شود
    }
    return false;
}
//================================================================================]
void Deracula::Deracula_special_power()
{
    moving::special_power_der();
}
//================================================================================

bool Deracula::Deracula_strike()
{
    if (moving::get_place(wher_is_monster)->can_deracola())
    {
        if (moving::get_place(wher_is_monster)->get_hero_in_place() != nullptr)
        {
            cout << moving::get_place(wher_is_monster)->get_hero_in_place()->name << "is in dangur";
            cout << moving::get_place(wher_is_monster)->get_hero_in_place()->name << "do you like get one item enter one if you like go to hospital enter 2 \n";
            int a;
            cin >> a;
            if (a == 1)
            {
                try
                {
                    moving::get_place(wher_is_monster)->get_hero_in_place()->get_one_item();
                    return true;
                }
                catch (runtime_error &e)
                {
                    cerr << e.what() << endl;
                    moving::set_new_location(moving::get_place(wher_is_monster)->get_hero_in_place(), "hospital", true);
                }
            }
            if (a != 1)
            {
                try
                {
                    moving::set_new_location(moving::get_place(wher_is_monster)->get_hero_in_place(), "hospital", true);
                }
                catch (runtime_error &e)
                {
                    cerr << e.what() << endl;
                }
                return true;
            }
        }
    }
    Villager *mordeh = moving::get_place(wher_is_monster)->get_one_villager();
    if (mordeh != nullptr)
    {
        cout << "villager whit name : " << mordeh->name << " is kill \n";
        moving::get_place(wher_is_monster)->villager_raft(mordeh);
        return true;
    }
    return false;
}
//===============================================================================
Hero::~Hero()
{
    for (auto &p : perk_cards)
    {
        delete p;
    }
}
//=========================================================================
string Villager::name_of_safe_place()
{
    return safe_place;
}
string Villager::name_place()
{
    return name_of_place;
}
//=================================================================
int Hero::show_items_n()
{
    return items.size();
}
//==============================================================
int Hero::show_perks_n()
{
    return perk_cards.size();
}