#ifndef CARD_HPP
#define CARD_HPP
//========================================================================================================================//
#include <iostream>
#include <vector>
#include <string>
#include <variant>
#include <map>
#include "place.hpp"
#include "moving.hpp"
#include"character.hpp"
#include <queue>

//========================================================================================================================//
class Hero;
class Monster;
class perk_card;
struct card{
    std::string name;
    int count;
};

//========================================================================================================================//
struct item_info{ //****** changed

    std::string color;
    std::string name;
    std::string location;
    int power;
    item_info(std::string n , std::string m , std::string c , int p ){
        name=n;
        location = m;
        color=c;
        power=p;
    }
    item_info(){}
};


//*******************************************************************************************************************//

// after read we most construct object
class perk_card
{
protected:
    int count;

public:
    std::string name;
    virtual void play_perk(Hero *, Hero * , bool& f) = 0;
    virtual void play_perk(Hero * ,bool &) = 0;
    virtual void play_perk(Monster *, Monster * , bool &) = 0;
    virtual void play_perk(Monster * , bool &) = 0;
    virtual void play_perk(bool &) = 0;
    virtual perk_card* clone()  = 0;
    void set_count(int);
    int &get_count();
    virtual ~perk_card(){}
};
//========================================================================================================================//

class bag_perks
{
public:
    static perk_card *get_one_perk_card();
    static void constract_perk_cart(); // for read perk card from file
private:
    static std::vector<perk_card *> Perk_cards;
};

//========================================================================================================================//
class visit_from_the_detective : public perk_card
{
private:
 void play_perk(Hero *, Hero * , bool &) override {}
 void play_perk(Hero * , bool &) override{}
 void play_perk(Monster *, Monster * , bool &)override{}
 void play_perk(bool &) override{}
public:
    visit_from_the_detective(int count)
    {
        this->count = count;
        name = "isit_from_the_detective";
    }
    void play_perk(Monster * ,bool& ) override;
    perk_card* clone()  override
    {
        return new visit_from_the_detective(*this);
    }
    ~visit_from_the_detective(){}

};
//========================================================================================================================//
class break_of_dawn : public perk_card
{
    private:
void play_perk(Hero *, Hero * , bool &) override {}
 void play_perk(Hero *,bool&) override{}
 void play_perk(Monster *, Monster *,bool&)override{}
 void play_perk(Monster *,bool&) override{}

public:
    break_of_dawn(int count)
    {
        this->count = count;
        name = "break_of_dawn";
    }
    void play_perk(bool&) override;
    perk_card* clone() override
    {
        return new break_of_dawn(*this);
    }
    ~break_of_dawn(){}
};

//========================================================================================================================//
class overstock : public perk_card
{
private:
void play_perk(Hero *, Hero * , bool&) override {}
 void play_perk(Hero *,bool&) override{}
 void play_perk(Monster *, Monster * , bool&)override{}
 void play_perk(Monster *, bool&) override{}
public:
    overstock(int count)
    {
        this->count = count;
        name = "overstock";
    }
    void play_perk(bool&) override;
    perk_card* clone()  override
    {
        return new overstock(*this);
    }
    ~overstock(){}
};

//========================================================================================================================//
class late_into_the_night : public perk_card
{
    private:
void play_perk(Hero *, Hero * ,bool&) override {}
 void play_perk(Monster *, Monster *, bool&)override{}
 void play_perk(Monster * , bool&) override{}
 void play_perk(bool&) override{}

    public:
    late_into_the_night(int count)
    {
        this->count = count;
        name = "late_into_the_night";
    }
    void play_perk(Hero *, bool& ) override;
    perk_card* clone()  override
    {
        return new late_into_the_night(*this);
    }
    ~late_into_the_night(){}
};
//========================================================================================================================//
class repel : public perk_card
{
    private:
    void play_perk(Hero *, Hero * , bool&) override {}
 void play_perk(Monster *, bool&) override{}
 void play_perk(bool&) override{}
 void play_perk(Hero * , bool&) override {}

    public:
    repel(int const)
    {
        this->count = count;
        name = "repel";
    }
    void play_perk(Monster *, Monster * ,bool&) override;
    perk_card* clone()  override
    {
        return new repel(*this);
    }
    ~repel(){}
};
//========================================================================================================================//
class hurry : public perk_card
{
    private:
    void play_perk(Monster *, Monster * , bool&) override{}
    void play_perk(Monster * , bool&) override{}
    void play_perk(bool &) override{}
    void play_perk(Hero *, bool&) override{}

    public:
    hurry(int count)
    {
        this->count = count;
        name = "hurry";
    }
    void play_perk(Hero *, Hero * , bool&) override;
    perk_card* clone()  override
    {
        return new hurry(*this);
    }
    ~hurry(){}
};
//========================================================================================================================//
class item
{
private:
  item_info i;
public:
    std::string name;
    item(item_info);
    std::string get_coler() const;
    int get_power() const;
    item_info get_item_for_out_the_game();
    
};

//========================================================================================================================//


//========================================================================================================================//
class bag_items
{
    friend class item;

private:
    static std::vector<item_info> items_in_the_game;
    static std::vector<item_info> items_out_the_game;

public:
    bag_items(); // باید از فایل بخوانی و شی درست کنیم
    static void put_Itme_IN_Place(int a);
    static void icraese_item_out_the_game(item);
};

#endif