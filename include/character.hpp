#ifndef CHARACTER - HPP
#define CHARACTER -HPP

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "place.hpp"

struct monster_card_info
{
    int items_push_in_game;
    std::string monster_card_event;
    std::string strike;
    std::string strike_arrangment;
};

//***********************************************************************************************************************//

class Monster
{
private:
    std::string wher_is_monster;

public:
    std::string get_place();
    std::string name;
    void set_location(std::string); // شی مکان میگیرد و در مپ داده شده در مکان اضافه میکند
    // پیاده سازی کلاس
};
class Deracola : public Monster
{
};

class Invisable_man : public Monster
{
    // همان متود های مانستر و بقیه
};

class Hero
{
public:
    std::string name;
    void set_location(std::string);
    virtual void do_action() = 0;  // do actions
    virtual void set_action() = 0; // reset the action
    void increase_action(int);
    void increase_perk_card(perk_card *);
    void domp_perk(perk_card *);
    std::string get_place();

protected:
    std::string wher_is_hero;
    std::vector<perk_card *> perk_cards;
    int action;
};

class Archaeologist : public Hero
{
public:
    Archaeologist(place);
    void do_action() override;
    void set_action() override;
};
class Mayor : public Hero
{
public:
    Mayor(place);
    void do_action() override;
    void set_action() override;
};

#endif