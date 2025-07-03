#ifndef MOVING_HPP
#define MOVING_HPP
//========================================================================================================================//
#include <map>
#include "place.hpp"
#include "card.hpp"
#include"character.hpp"
//========================================================================================================================//
class bag_items;
class place;
class Hero;
class Monster;
class Villager;
//========================================================================================================================//
class moving
{
    
private:
    
    static Hero * first_hero;
    static Hero *seccend_hero;
    static Hero* last;
    static Monster *invisible_man;
    static Monster *deracula;
    
public:
    static std::map<std::string, place *>& places;
    moving(Hero *, Hero *, Monster *, Monster *);
    void set_places(std::map<std::string, place *>& );
    std::string name_of_place;
    static void set_new_location(int = 0); // برای حرکت دادن هیولا ها دو خانه و اگر ورودی داشت حرکت قهرمان ها
    static void set_new_location(Hero *, std::string , bool f= false);
    static void set_new_location(std::string); // برای حرکت دادن مرد نامرئی
    static void set_new_location(std::string, int );
    static void set_new_lacation_for_villager(Hero *, std::string, std::string place_name = "");
    static void set_location_for_villagers( Villager*, std::string);
    static place *get_place(std::string);
    static bool each_tabot_distroy();
    static void kill_inviseble_man();
    static void kill_deracula();
    static place *get_near_place(std::string);
    static Monster* get_invisible_man(){
        return invisible_man;
    }
    static Monster* get_deracula(){
        return deracula;
    }
    static Hero* get_first_hero(){
        return first_hero;
    }
    static Hero* get_seccend_hero(){
        return seccend_hero;
    }
    static void set_last_hero(Hero*);
    static void set_location_deracula(std::string place_name ="");//یردن دراکولا به موقیت اخرین قهرمان
    static void set_location_invisible_man();
    static std::string get_place_whit_max_item();
    static void special_power_invi();
    static void special_power_der();
    static bool hero_won();
    static void start();
    ~moving(){}

    
};
//========================================================================================================================//
#endif