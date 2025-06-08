#include "moving.hpp"
#include <stdexcept>
#include <iostream>
using namespace std;
moving::moving(Hero *first, Hero *seccend, Monster *dera, Monster *Invisable_man)
{
    first_hero = first;
    seccend_hero = seccend;
    deracola = dera;
    invisable_man = Invisable_man;
}
//****************************************************************//
void moving::set_new_location(Hero *h, std::string place_name)
{
    bool succesful = false;
    place &themp = places[h->get_place()];
    for (auto &p : themp.near_place)
    {
        if (place_name == p.name)
        {
            succesful = true;
            try
            {
                p.put_in_place(h);
                cout << "do you like move villager if yes enter one\n";
                int a;
                cin >> a;
                if (a == 1)
                {

                    place::put_villager_in_place( h , themp, p);
                }
                else{
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
void moving::set_new_location(int a = 0)
{
    if (a == 0)
    {
        places[deracola->get_place()].go_to_near_place(deracola);
        places[invisable_man->get_place()].go_to_near_place(invisable_man);
    }
    else
    {
        places[first_hero->get_place()].go_to_near_place(first_hero);
        places[first_hero->get_place()].go_to_near_place(first_hero);
        places[seccend_hero->get_place()].go_to_near_place(first_hero);
        places[seccend_hero->get_place()].go_to_near_place(first_hero);
    }
}
//*************************************************************************//
void moving::set_new_lacation_for_villager( Hero* h, string place_of_hero, string place_name = "")
{
    place &themp = places[place_of_hero];
    if (place_name != "")
    {
        place::put_villager_in_place(h , themp, place_name);
    }
    if (place_name == "")
    {
        place::put_villager_in_place( h, themp, place_name);
    }
}
//***************************************************************************************************//
place &moving::get_place(std::string place_name)
{
    return places[place_name];
}
//*********************************************************************************************//
bool moving::each_tabot_distroy(){
    bool can=false;
    for(auto & p : places){
        can = p.second.get_tabot();
    }
    return can;
}
//*********************************************************************************//
void moving::kill_inviseble_man(){
    invisable_man=nullptr;
}
//**********************************************************************************//
void moving::kill_deracola(){
    deracola=nullptr;
}
//**************************************************************//
place & moving::get_near_place(std::string n){
    vector<place>p=places[n].get_p();
    cout<<"near place is\n";
    for(auto & pl: p){
        cout<<pl.name<<endl;
    }
    cout<<"which place you like \n";
    string pla;
    cin>>pla;
    return places[pla];
}
//**********************************************************************//
 void moving::set_new_location(Monster* m, int a ){
    //code
    if(m==deracola){
        deracola.set;
    }
 }




