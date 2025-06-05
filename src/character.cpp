#include <iostream>
#include <string>
#include <vector>
#include <variant>
#include <algorithm>
#include "character.hpp"
#include <map>

//***********************************************************************************************************************//

using namespace std;

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
    default:
        return "Unknown Place";
    }
}

//=================================================     ================================================================//
string Monster::get_place()
{
    return wher_is_monster;
}
//***************************************************************************//
Hero::Hero() {}
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
//************************************************************//void Hero::domp_perk(perk_card *domp)
void Hero::domp_perk(perk_card *domp)

{
    for (auto it = perk_cards.begin(); it != perk_cards.end(); )
    {
        if ((*it)->name == domp->name)
        {
            if ((*it)->get_count() == 1)
            {
                delete *it;
                it = perk_cards.erase(it);
                break;
            }
            else
            {
                (*it)->set_count((*it)->get_count() - 1);
                break;
            }
        }
        else
        {
            ++it;
        }
    }
}

//***********************************************************************************//
Hero::Hero(const Hero &h)
{
    this->name = h.name;
    for (auto &p : h.perk_cards)
    {
        this->perk_cards.push_back(p);
    }
}
//***************************************************************************//
Archaeologist::Archaeologist(std::string place_name)
{
    wher_is_hero = place_name;
    name = "Archaeologist";
}
//*************************************************************************//
void Archaeologist::set_action()
{
    action = 4;
}
//**********************************************************************************//
void Mayor::set_action()
{
    action = 5;
}
//******************************************************************//
bool Hero::can_distroy(int power, string color){
    bool can = false;
    int p = 0;
    std::vector<item*> temp;
    
    for (auto& i : items) {
        if (i.get_coler() == color) {
            temp.push_back(&i); 
            p += i.get_power();
        }
    
        if (p >= power) {
            can=true;
            break;
        }
    }
    if(p>=power){
    items.erase(std::remove_if(items.begin(), items.end(),
    [&temp](const item& i) {
        return std::any_of(temp.begin(), temp.end(),
            [&i](item* ptr) { return &i == ptr; });
    }), items.end());}

    return can;
}
//*************************************************************//

int Hero::do_action()
{
    int b=0;
    static int how_many_item=0;
    actions what_action;
    int a;
    cin >> a;
    if (a >= 0 && a <= 5)
    {
        what_action = static_cast<actions>(a);
    }
    while(this->action>0)
    {
        place& p =moving::get_place(wher_is_hero);

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

                if (a >= 0 && a <= 14)
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
        case Guide :
        {
            b++;
            --action;
            cout<<"do you like move villager who was in your location enter 1 and if you like come villager who was in near place enter 2 \n";
            cin>>a;
            if(a==1){
                moving::set_new_lacation_for_villager( this ,wher_is_hero, wher_is_hero);
            }
            if(a==2){
                moving::set_new_lacation_for_villager(this , wher_is_hero , "");
            }
            break;
        }
        case Pickup:
        {
            ++b;
            --action;
            vector<item> temp;
            cout<<"how many item do you want? \n";
            cin>>a;
            if(a>=0){
                temp=p.get_items(a);
                for(const auto & i : temp ){
                    if(wher_is_hero=="inn"||wher_is_hero=="mansiom"||wher_is_hero=="barn"||wher_is_hero=="laboratory"
                    ||wher_is_hero=="institute"){
                    items_for_distroy_invisble_man.push_back(i);}
                    else{
                        items.push_back(i);
                    }
                }
            }
            else{
                cout<<"the entered number was wrong \n";
            }
            break;
        }
        case Advance:{
            ++b;
            --action;
            if(p.get_tabot()){
                cout<<"here has tabot if you lik distroed it enter one\n";
            }
            if(p.name=="percinct"){
                cout<<"for giv the items for kill invisble man enter 2\n";
            }
            cin>>a;
            if(a==1){
                can_distroy(6 , "red");
                p.destroy_tabot();
            }
            if(a==2){
                how_many_item+=items_for_distroy_invisble_man.size();
                items_for_distroy_invisble_man.clear();
                //باید در صفحه هیولا ان ها نشان داده شوند
            }
            break;                
        }
        case Defeat:
        {
            ++b;
            --action;

            switch (p.get_monster_in_place())
            {
            case 1:{
                cout<<"here has invisble_man and deracola for kill the invisble man enter 2 and for deracola enter 3\n";
                cin>>a;
                if(a==2){
                    if(how_many_item>=5){
                        if(can_distroy(9 , "red")){
                            p.kill_monster(1);
                            moving::kill_inviseble_man();
                        }
                        else{
                            cout<<"you cant kill invisble man beacase you dont have enogh item\n";
                        }
                    }
                    else{
                        cout<<"each item dont catch\n";
                    }
                }
                if(a==3){
                    if(can_distroy(6 , "yellow")){
                        p.kill_monster(2);
                        moving::kill_deracola();
                    }
                    else{
                        cout<<"you dont have enogh yellow item\n";
                    }
                }
                break;} 
                case 2:{
                    if(how_many_item>=5){
                        if(can_distroy(9 , "red")){
                            p.kill_monster(1);
                            moving::kill_inviseble_man();
                        }
                        else{
                            cout<<"you cant kill invisble man beacase you dont have enogh item\n";
                        }
                    }
                    else{
                        cout<<"each item dont catch\n";
                    }
                }
                case 3:{
                    if(can_distroy(6 , "yellow")){
                        p.kill_monster(2);
                        moving::kill_deracola();
                    }
                    else{
                        cout<<"you dont have enogh yellow item\n";
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
        cout<<"do you like continue enter 1\n";
        cin>>a;
        if(a!=1)
        break;
    }
    return b;
}
//**********************************************************************//
int Archaeologist::do_action(){
     int b = Hero::do_action();
    if(b<4){
       place& pl= moving::get_near_place(wher_is_hero);
       vector<item> temp;
       cout<<"how many item do you want? \n";
       int a;
       cin>>a;
       if(a>=0){
           temp=pl.get_items(a);
           for(const auto & i : temp ){
               if(wher_is_hero=="inn"||wher_is_hero=="mansiom"||wher_is_hero=="barn"||wher_is_hero=="laboratory"
               ||wher_is_hero=="institute"){
               items_for_distroy_invisble_man.push_back(i);}
               else{
                   items.push_back(i);
               }
           }
       }
       else{
           cout<<"the entered number was wrong \n";
       }
    }
    else{
        cerr<<"you do all of the action\n";
    }
    return 0;
}
//*********************************************************//
Villager::Villager(std::string villger_name , std::string safe_place){
    name=villger_name;
    this->safe_place=safe_place;
}
//***************************************************************************//
void Villager::set_place(std::string p){
    name_of_place=p;
}
//***********************************************************************************//
bool Villager::is_safe_place(){
    if(name_of_place==safe_place){
        return true;
    }
    else{
        return false;
    }
}


