#ifndef CARD_HPP
#define CARD_HPP

#include <iostream>
#include <vector>
#include <string>
#include <variant>
#include <map>
#include "place.hpp"
#include "moving.hpp"
#include <queue>

//*******************************************************************************************************************//

struct card
{
    std::string name;
    int count;
};
struct item_info
{ //****** change
    std::string color;
    std::string name;
    coordinate location;
    int count;
};
//*******************************************************************************************************************//
void constract_perk_cart(std::vector<card> c); // for read perk card from file
// after read we most construct object
class perk_card
{
protected:
    int count;

public:
    std::string name;
    virtual void play_perk(Hero *, Hero *) = 0;
    virtual void play_perk(Hero *) = 0;
    virtual void play_perk(Monster *, Monster *) = 0;
    virtual void play_perk(Monster *) = 0;
    virtual void play_perk(std::multimap<std::string, place> &places) = 0;
    void set_count(int);
    int &get_count();
    virtual ~perk_card();
};

class visit_from_the_detective : public perk_card
{

public:
    visit_from_the_detective(int count)
    {
        this->count = count;
        name = "isit_from_the_detective";
    }
    void play_perk(Monster *) override;
};
class break_of_dawn : public perk_card
{
public:
    break_of_dawn(int count)
    {
        this->count = count;
        name = "break_of_dawn";
    }
    void play_perk(std::multimap<std::string, place> &places) override;
};

class overstock : public perk_card
{

public:
    overstock(int count)
    {
        this->count = count;
        name = "overstock";
    }
    void play_perk(std::multimap<std::string, place> &places) override;
};

class late_into_the_night : public perk_card
{

    late_into_the_night(int count)
    {
        this->count = count;
        name = "late_into_the_night";
    }
    void play_perk(Hero *) override;
};

class repel : public perk_card
{
    repel(int const)
    {
        this->count = count;
        name = "repel";
    }
    void play_perk(Monster *, Monster *) override;
};

class hurry : public perk_card
{

    hurry(int count)
    {
        this->count = count;
        name = "hurry";
    }
    void play_perk(Hero *, Hero *) override;
};
class item
{
private:
    static std::vector<item_info> items_in_the_game;
    static std::vector<item_info> items_out_the_game;

public:
    item(const item_info &info)
    {
        items_in_the_game.push_back(info); // ذخیره `item_info` در وکتور
    }
    void Read_From_File();
    static void put_Itme_IN_Place(std::multimap<std::string, place> &places, int a);
    // add related methods
};

//********************************************************************************************************************//

#endif