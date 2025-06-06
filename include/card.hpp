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
{ //****** changed

    std::string color;
    std::string name;
    coordinate location;
    int count;
    int power;
};
//*******************************************************************************************************************//
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
    virtual void play_perk() = 0;
    virtual perk_card* clone() const = 0;
    void set_count(int);
    int &get_count();
    virtual ~perk_card();
};
//=======================================================        ===========================================
class bag_perks
{
public:
    static perk_card *get_one_perk_card();
    void constract_perk_cart(std::vector<card> c); // for read perk card from file
private:
    static std::vector<perk_card *> Perk_cards;
};
//=========================================          ==================================================
class visit_from_the_detective : public perk_card
{
private:
 void play_perk(Hero *, Hero *) override {}
 void play_perk(Hero *) override{}
 void play_perk(Monster *, Monster *)override{}
 void play_perk() override{}
public:
    visit_from_the_detective(int count)
    {
        this->count = count;
        name = "isit_from_the_detective";
    }
    void play_perk(Monster *) override;
    perk_card* clone() const override
    {
        return new visit_from_the_detective(*this);
    }

};
//=============================================           ================================================
class break_of_dawn : public perk_card
{
    private:
void play_perk(Hero *, Hero *) override {}
 void play_perk(Hero *) override{}
 void play_perk(Monster *, Monster *)override{}
 void play_perk(Monster *) override{}

public:
    break_of_dawn(int count)
    {
        this->count = count;
        name = "break_of_dawn";
    }
    void play_perk() override;
    perk_card* clone() const override
    {
        return new break_of_dawn(*this);
    }
};
//============================================          ================================================
class overstock : public perk_card
{
private:
void play_perk(Hero *, Hero *) override {}
 void play_perk(Hero *) override{}
 void play_perk(Monster *, Monster *)override{}
 void play_perk(Monster *) override{}
public:
    overstock(int count)
    {
        this->count = count;
        name = "overstock";
    }
    void play_perk() override;
    perk_card* clone() const override
    {
        return new overstock(*this);
    }
};
//===============================================                ============================================
class late_into_the_night : public perk_card
{
    private:
void play_perk(Hero *, Hero *) override {}
 void play_perk(Monster *, Monster *)override{}
 void play_perk(Monster *) override{}
 void play_perk() override{}

    public:
    late_into_the_night(int count)
    {
        this->count = count;
        name = "late_into_the_night";
    }
    void play_perk(Hero *) override;
    perk_card* clone() const override
    {
        return new late_into_the_night(*this);
    }
};
//=======================================            =================================================
class repel : public perk_card
{
    private:
    void play_perk(Hero *, Hero *) override {}
 void play_perk(Monster *) override{}
 void play_perk() override{}
 void play_perk(Hero *) override;

    public:
    repel(int const)
    {
        this->count = count;
        name = "repel";
    }
    void play_perk(Monster *, Monster *) override;
    perk_card* clone() const override
    {
        return new repel(*this);
    }
};
//==========================================          ===========================================
class hurry : public perk_card
{
    private:
    void play_perk(Monster *, Monster *) override;
    void play_perk(Monster *) override{}
    void play_perk() override{}
    void play_perk(Hero *) override;

    public:
    hurry(int count)
    {
        this->count = count;
        name = "hurry";
    }
    void play_perk(Hero *, Hero *) override;
    perk_card* clone() const override
    {
        return new hurry(*this);
    }
};
//========================================               ===============================================
class bag_items
{
    friend class item;

private:
    static std::vector<item_info> items_in_the_game;
    static std::vector<item_info> items_out_the_game;

public:
    bag_items(item_info); // باید از فایل بخوانی و شی درست کنیم
    static void put_Itme_IN_Place(int a);
};
//============================================               ===========================================
class item
{
private:
    std::string color;
    int power;

public:
    item(int, std::string);

    std::string get_coler() const;
    int get_power() const;
};

//********************************************************************************************************************//

#endif