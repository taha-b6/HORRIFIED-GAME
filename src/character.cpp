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
std::string Monster::wher_is_monster="";  

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



void do_perk(Hero *h ,bool & f)
{
    int a;
    while (1)
    {
        perk_card *p = h->perk_cards.back();
        switch (which_perk_card(p))
        {
        case 1:
        {
            visit_from_the_detective *v = dynamic_cast<visit_from_the_detective *>(p);
            v->play_perk(moving::get_invisible_man() ,f);
            break;
        }
        case 2:
        {
            break_of_dawn *b = dynamic_cast<break_of_dawn *>(p);
            b->play_perk(f);
            // فاز هیولا را رد کن
            break;
        }
        case 3:
        {
            overstock *o = dynamic_cast<overstock *>(p);
            o->play_perk(f);
            break;
        }
        case 4:
        {
            late_into_the_night *l = dynamic_cast<late_into_the_night *>(p);
            l->play_perk(h , f);
            break;
        }
        case 5:
        {
            repel *r = dynamic_cast<repel *>(p);
            r->play_perk(moving::get_deracula(), moving::get_invisible_man() , f);
            break;
        }
        case 6:
        {
            hurry *h = dynamic_cast<hurry *>(p);
            h->play_perk(moving::get_first_hero(), moving::get_seccend_hero() , f);
            break;
        }
        default:
            break;
        }
        cout << "do you like play eater perk_card enter one\n";
        cin >> a;
        if (a != 1)
        {
            break;
        }
    }
}

string to_string(Place p)
{
    switch (p)
    {
    case precinct:
        return "precinct";
    case mansion:
        return "mansion";
    case inn:
        return "lnn";
    case camp:
        return "camp";
    case theatre:
        return "theatre";
    case cave:
        return "cave";
    case institute:
        return "institute";
    case crypt:
        return "crypt";
    case barn:
        return "barn";
    case dungeon:
        return "dungeon";
    case docks:
        return "docks";
    case tower:
        return "tower";
    case laboratory:
        return "laboratory";
    case graveyard:
        return "graveyard";
    case hospital:
        return "hospital";
        case abbey:
        return "abbey";
        case church:
        return "church";
        case musium:
        return "musium";
        case shop:
        return "shop";
    default:
        return "Unknown Place";
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

string Hero::get_hero_place()const
{
    return wher_is_hero;
}
//========================================================================================================================//
void Hero::increase_perk_card(perk_card *new_perk)
{
    for (auto &card : perk_cards)
    {
        if (card->name == new_perk->name)
        {
            // کارت وجود دارد، فقط تعداد را افزایش بده
            card->set_count(card->get_count() + 1);

            // کارت ورودی چون اضافه نشد، باید پاک شود
            delete new_perk;
            return;
        }
    }

    // کارت جدید است، پس کارت ورودی را به وکتور اضافه کن
    perk_cards.push_back(new_perk);
}

//========================================================================================================================//void Hero::domp_perk(perk_card *domp)
void Hero::domp_perk(perk_card *domp)
{
    for (auto it = perk_cards.begin(); it != perk_cards.end(); ++it)
    {
        if ((*it)->name == domp->name)
        {
            int count = (*it)->get_count();

            if (count > 1)
            {
                (*it)->set_count(count - 1);
            }
            else
            {
                // تعداد صفر شد، حذف و پاک کن
                delete *it;
                perk_cards.erase(it);
            }
            return;
        }
    }
}

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
Archaeologist::Archaeologist(std::string place_name)
{
    wher_is_hero = place_name;
    name = "Archaeologist";
}
//========================================================================================================================//
void Archaeologist::set_action()
{
    action = 4;
}
Mayor::Mayor(string pl){
    wher_is_hero=pl;
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
        for(auto & i :temp){
        bag_items::icraese_item_out_the_game(* i);}
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

int Hero::do_action(bool & f)
{
    int b = 0;
    static int how_many_item = 0;
    actions what_action;
    int a;
    cin >> a;
    if (a >= 0 && a <= 5)
    {
        what_action = static_cast<actions>(a);
    }
    while (this->action > 0)
    {
        place &p = moving::get_place(wher_is_hero);

        switch (what_action)
        {
        case Move:
        {
            b++;
            --action;
            bool moved = false;

            while (!moved)
            {
                cout << "Please enter the place which you like to go (0 to 14):\n";
                cin >> a;

                if (a >= 0 && a <= 17)
                {

                    string name_place = to_string(a);

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
                else
                {
                    cout << "Invalid number. Please enter a number between 0 and 14.\n";
                }
            }

            break;
        }
        case Guide:
        {
            b++;
            --action;
            cout << "do you like move villager who was in your location enter 1 and if you like come villager who was in near place enter 2 \n";
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
            ++b;
            --action;
            vector<item> temp;
            cout << "how many item do you want? \n";
            cin >> a;
            if (a >= 0)
            {
                try
                {
                    temp = p.get_items(a);
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
            break;
        }
        case Advance:
        {
            ++b;
            --action;
            if (p.get_tabot())
            {
                cout << "here has tabot if you lik distroed it enter one\n";
            }
            if (p.name == "percinct")
            {
                cout << "for giv the items for kill invisble man enter 2\n";
            }
            cin >> a;
            if (a == 1)
            {
                can_distroy(6, "red");
                p.destroy_tabot();
            }
            if (a == 2)
            {
                how_many_item += items_for_distroy_invisble_man.size();
                items_for_distroy_invisble_man.clear();
                // باید در صفحه هیولا ان ها نشان داده شوند
            }
            break;
        }
        case Defeat:
        {
            ++b;
            --action;

            switch (p.get_monster_in_place())
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
                            p.kill_monster(1);
                            moving::kill_inviseble_man();
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
                if (a == 3)
                {
                    if (can_distroy(6, "yellow"))
                    {
                        p.kill_monster(2);
                        moving::kill_deracula();
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
                        p.kill_monster(1);
                        moving::kill_inviseble_man();
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
                    p.kill_monster(2);
                    moving::kill_deracula();
                }
                else
                {
                    cout << "you dont have enogh yellow item\n";
                }
            }
            default:
                break;
            }
            break;
        }
        default:
            break;
        }
        cout << "do you like continue enter 1\n";
        cin >> a;
        if (a != 1)
            break;
    }
    return b;
}
//========================================================================================================================//
int Archaeologist::do_action(bool & f)
{
    this->set_action();
    int b = Hero::do_action(f);
    if (b < 4)
    {
        place &pl = moving::get_near_place(wher_is_hero);
        vector<item> temp;
        cout << "how many item do you want? \n";
        int a;
        cin >> a;
        if (a >= 0)
        {
            try
            {
                temp = pl.get_items(a);
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
    else
    {
        cerr << "you do all of the action\n";
    }
    cout << "do you like play perk enter one\n";
    int a;
    cin >> a;
    if (a == 1)
    {
        do_perk(this ,f);
    }
    return 0;
}
//========================================================================================================================//
int Mayor::do_action( bool & f)
{

    this->set_action();
    Hero::do_action(f);
    cout << "do you like play perk enter one\n";
    int a;
    cin >> a;
    if (a == 1)
    {
        do_perk(this , f);
    }
    return 0;
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
    if (moving::get_place(wher_is_monster).can_invisible_man())
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
    if (moving::get_place(wher_is_monster).can_deracola())
    {
        cout << moving::get_place(wher_is_monster).get_hero_in_place()->name << "is in dangur";
        cout << moving::get_place(wher_is_monster).get_hero_in_place()->name << "do you like get one item enter one if you like go to hospital enter 2 \n";
        int a;
        cin >> a;
        if (a == 1)
        {
            try
            {
                moving::get_place(wher_is_monster).get_hero_in_place()->get_one_item();
                return true;
            }
            catch (runtime_error &e)
            {
                cout << e.what() << endl;
                moving::set_new_location(moving::get_place(wher_is_monster).get_hero_in_place(), "hospital", true);
            }
        }
        if (a != 1)
        {
            moving::set_new_location(moving::get_place(wher_is_monster).get_hero_in_place(), "hospital", true);
            return true;
        }
    }
    return false;
}
//===============================================================================
Hero::~Hero(){
    for(auto & p : perk_cards){
        delete p;
    }
}
