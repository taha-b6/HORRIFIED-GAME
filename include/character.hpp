#ifndef CHARACTER-HPP
#define CHARACTER-HPP

#include <iostream>
#include <vector>
#include <string>
#include <variant>
#include <map>

struct  monster_card_info{
int items_push_in_game;
std:: string monster_card_event;
std:: string strike;
std:: string strike_arrangment;
};


//***********************************************************************************************************************//

class character{
private:

public:
    std:: string name;
    std:: string start_place;
    std:: string spcial_action;
    character();
    ~character();

                    //add other methods

};


class Hero : public character{
private:
    std:: vector <class item> itmes_list;
    std:: vector <class perk> perks_list;
    //Action action();
                            
public:
    int Action_num;
                    //add other methods
};

class Monster : public character {
private:
    std::string target_attack();


public:
                    //add other methods
};

class villager : public character{
//===================================== under construction ================================================
};

//*************************************************************************************************************//

class monster_card{
private:

                                    //add static vector       monster card list
std:: vector <monster_card_info> m_card_list; // ممد گفتی چیز بهتری از وکتور براش داری
public:
};

//*************************************************************************************************************//

#endif