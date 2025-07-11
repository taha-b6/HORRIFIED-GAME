#ifndef CHARACTER_HPP
#define CHARACTER_HPP
//========================================================================================================================//
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "place.hpp"
#include "monster_card.hpp"
#include "card.hpp"

//========================================================================================================================//
enum actions {Move , Guide , Pickup , Advance , Defeat , Special_Action};
//========================================================================================================================//
enum Place {precinct , mansion , musium , inn , camp , theatre , cave , institute , crypt , barn , dungeon , docks , tower , laboratory , graveyard , hospital , abbey , church , shop};

std::string to_string_place(int p);
//========================================================================================================================//
class perk_card;
class item;
struct monster_card_info{
    int items_push_in_game;
    std::string monster_card_event;
    std::string strike;
    std::string strike_arrangment;
};

//========================================================================================================================//

class Monster{
protected:
std::string wher_is_monster="";
public:
    std::string m_name;
    virtual ~Monster(){}
   std::string get_monster_place();
    void set_location(std::string); // اسم مکانی که او قرار دارد ست میشود
};

//========================================================================================================================//
class Deracula : public Monster{
friend class monster_Card;
friend class form_of_the_bat ;
friend class sunrise;
friend class thief ;
friend class the_delivery;
friend class fortune_teller;
friend class former_employer;
friend class hurried_assistant;
friend class the_inocent;
friend class egyptian_expert ;
friend class the_Ichthyologist;
private:
public:
    Deracula(){
        m_name="deracula";
    }
    bool Deracula_strike();
    void Deracula_special_power();
};

//========================================================================================================================//
class Invisible_man : public Monster{
friend class monster_Card;
friend class form_of_the_bat ;
friend class sunrise;
friend class thief ;
friend class the_delivery;
friend class fortune_teller;
friend class former_employer;
friend class hurried_assistant;
friend class the_inocent;
friend class egyptian_expert ;
friend class the_Ichthyologist;
private:
public:
    Invisible_man(){
        m_name="invisible_man";
    }
    bool invisible_man_strike();
    void invisible_man_special_power();
};

//========================================================================================================================//
class Hero{
    friend void do_perk(Hero* , bool&);
public:
    std::string name;

    Hero(const Hero &);
    Hero();
    void set_location(std::string);
    virtual void do_action(bool &);  // do actions
    virtual void set_action() = 0; // reset the action
    void increase_action(int);
    void increase_perk_card(perk_card *);
    std::string get_hero_place() const;
    bool can_distroy(int , std::string);
    virtual int show_items_n();
    virtual int show_perks_n();
    void get_one_item();
    virtual ~Hero();
protected:
    std::string wher_is_hero="";
    std::vector<perk_card *> perk_cards;
    std::vector<item> items;
    std::vector<item> items_for_distroy_invisble_man;
    int action;
};

//========================================================================================================================//

class Archaeologist : public Hero{
public:
    using Hero::Hero;
    Archaeologist();
    void do_action(bool &) override;
    void set_action() override;
};

//========================================================================================================================//
class Mayor : public Hero{
public:
    using Hero::Hero;
    Mayor();
    void do_action(bool &) override;
    void set_action() override;
};
//========================================================================================================================//
class Villager{
public:
    Villager(std::string , std::string);
    void set_place(std::string);
    bool is_safe_place();
    std::string name_of_safe_place();
    std::string name_place();
    std::string name="";
private:
    std::string name_of_place="";
    std::string safe_place;
};
//========================================================================================================================//

#endif
