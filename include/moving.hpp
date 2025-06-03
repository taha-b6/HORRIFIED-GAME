#ifndef MOVING_HPP
#define MOVING_HPP
#include<map>
#include"place.hpp"
class moving{
    private:
     static std::map<std::string , place> places;
    Hero* first_hero;
    Hero* seccend_hero;
    static Monster * invisable_man;
    static Monster * deracola;
    public:
    moving(Hero* , Hero* , Monster* , Monster*) ;
    void set_places(std::map<std::string , place> &);
    std::string name_of_place;
    void set_new_location( Hero* ,Hero*);//برای حرکت قهرمان ها دو خانه
    static void set_new_location();//برای حرکت دادن هیولا ها دو خانه
    void set_new_location( Hero* ,std::string);
    static void set_new_location( std::string);//برای حرکت دادن مرد نامرئی
    
};
#endif