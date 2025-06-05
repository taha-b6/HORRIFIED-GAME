#ifndef MOVING_HPP
#define MOVING_HPP
#include <map>
#include "place.hpp"
class moving
{
private:
    static std::map<std::string, place> places;
    static Hero *first_hero;
    static Hero *seccend_hero;
    static Monster *invisable_man;
    static Monster *deracola;

public:
    moving(Hero *, Hero *, Monster *, Monster *);
    void set_places(std::map<std::string, place> &);
    std::string name_of_place;
    static void set_new_location(int=0);        // برای حرکت دادن هیولا ها دو خانه و اگر ورودی داشت حرکت قهرمان ها
    static void set_new_location(Hero *, std::string);
    static void set_new_location(std::string); // برای حرکت دادن مرد نامرئی
    static void set_new_lacation_for_villager( Hero* ,  std::string, std::string ="");
    static place& get_place(std::string);
    static bool each_tabot_distroy();
    static void kill_inviseble_man();
    static void kill_deracola();
    static place & get_near_place(std::string);

};
#endif