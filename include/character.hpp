#ifndef CHARACTER - HPP
#define CHARACTER -HPP
//========================================================================================================================//
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "place.hpp"
#include "monster_card.hpp"
//========================================================================================================================//
enum actions {Move , Guide , Pickup , Advance , Defeat , Special_Action};
//========================================================================================================================//
enum Place {precinct , mansion ,musium , inn , camp , theatre , cave , institute , crypt , barn , dungeon , docks , tower , laboratory , graveyard , hospital , abbey , church , shop};

//========================================================================================================================//
struct monster_card_info{
    int items_push_in_game;
    std::string monster_card_event;
    std::string strike;
    std::string strike_arrangment;
};

//========================================================================================================================//

class Monster{

protected:
    static::std::string wher_is_monster;
public:
    std::string m_name;

    std::string  get_monster_place();
    virtual ~Monster();
    
    void set_location(std::string); // اسم مکانی که او قرار دارد ست میشود
    // پیاده سازی کلاس
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
        m_name="Deracula";
    }
    static bool Deracula_strike();
    static void Deracula_special_power();
    void set_location(std::string place); 
    Deracula();
    virtual ~Deracula();
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
    static bool invisible_man_strike();
    static void invisible_man_special_power();
    void set_location(std::string place); 
    Invisible_man();
    virtual ~Invisible_man();
};

//========================================================================================================================//
class Hero{
    friend void do_perk(Hero*);
public:
    std::string name;

    Hero(const Hero &);
    Hero();
    void set_location(std::string);
    virtual int do_action();  // do actions
    virtual void set_action() = 0; // reset the action
    void increase_action(int);
    void increase_perk_card(perk_card *);
    void domp_perk(perk_card *);
    std::string get_hero_place();
    bool can_distroy(int , std::string);
    void get_one_item();

protected:
    std::string wher_is_hero;
    std::vector<perk_card *> perk_cards;
    std::vector<item> items;
    std::vector<item> items_for_distroy_invisble_man;
    int action;
};

//========================================================================================================================//

class Archaeologist : public Hero{
public:
    using Hero::Hero;
    Archaeologist(std::string);
    int do_action() override;
    void set_action() override;
};

//========================================================================================================================//
class Mayor : public Hero{
public:
    using Hero::Hero;
    int do_action() override;
    Mayor(place);
    void set_action() override;
};
//========================================================================================================================//
class Villager{
    public:
    Villager(std::string , std::string);
    void set_place(std::string);
    bool is_safe_place();
    std::string name_of_safe_place();
    std::string name;
    private:
    std::string name_of_place;
    std::string safe_place;
};
//========================================================================================================================//

#endif