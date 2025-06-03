#include <iostream>
#include <string>
#include <vector>
#include <variant>
#include <algorithm>
#include "place.hpp"
#include <map>

//***********************************************************************************************************************//

using namespace std;

place::~place() {}
//=========================================    ===================================================================

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
        cout << p.first << "\t";
    }
}
