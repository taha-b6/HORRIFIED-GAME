#ifndef MONSTER_CARD-HPP
#define MONSTER_CARD-HPP
//=======================================================================================================//
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
//=======================================================================================================//
enum Dice {Empety = 0 , Special_power = 1 , Attack = 2 };
//=======================================================================================================//
class monster_card{
private:

public:
    Dice D_E = Empety;
    Dice D_S = Special_power;
    Dice D_S = Attack;
    std::string name;
    monster_card();
    virtual ~monster_card();
    virtual void play_monster_card();
    Dice play_dice();
    std::string card_name;
    std::string event_name;
    virtual void show_event();
    virtual void show_item_num(); 
    virtual void do_strike();
    virtual void do_event();
    virtual void show_monster_card();
protected:
    int event_bio_id;
    int num_of_this_card;
    int strike_move;
    int strike_dice_num;
    int items_num;
    std::string event_bio;
    std::vector <std:: string> strike_arrange;
};
//=======================================================================================================//
class form_of_the_bat : public monster_card{   // سه تا شی ساخته شود
private:

public:
                                       //متدی میخوام که دراکولا از مکان فعلی به ماکان یک قهرمان مشخص ببرد
    form_of_the_bat();
    virtual ~ form_of_the_bat();
    void play_monster_card()override;
    void show_event()override;
    /*void do_strike()override;
    void do_event()override;*/
    virtual void show_item_num(); 
}; 
//=======================================================================================================//
class sunrise : public monster_card{
private:




public:
    sunrise();
    virtual ~sunrise();
    void play_monster_card();
    void show_event()override;
    /*void do_strike()override;
    void do_event()override;*/   
    virtual void show_item_num(); 
};
//=======================================================================================================//
class thief : public monster_card{
private:





public:
    thief();
    virtual ~thief();
    void play_monster_card();
    void show_event()override;
    /*void do_strike()override;
    void do_event()override;*/ 
    virtual void show_item_num();   
};
//=======================================================================================================//
class the_delivery : public monster_card{
private:



public:
    the_delivery();
    virtual ~the_delivery();
    void play_monster_card();
    void show_event()override;
    /*void do_strike()override;
    void do_event()override;*/ 
    virtual void show_item_num();  
};
//=======================================================================================================//
class fortune_teller : public monster_card{
private:



public:
    fortune_teller();
    virtual ~fortune_teller();
    void play_monster_card();
    void show_event()override;
    /*void do_strike()override;
    void do_event()override;*/  
    virtual void show_item_num(); 
};
//=======================================================================================================//
class former_employer : public monster_card{
private:



public:
    former_employer();
    virtual ~former_employer();
    void play_monster_card();
    void show_event()override;
    /*void do_strike()override;
    void do_event()override;*/ 
    virtual void show_item_num(); 
};
//=======================================================================================================//
class hurried_assistant : public monster_card{
private:



public:
    hurried_assistant();
    virtual ~hurried_assistant();
    void play_monster_card();
    void show_event()override;
    /*void do_strike()override;
    void do_event()override;*/ 
    virtual void show_item_num(); 
};
//=======================================================================================================//
class the_inocent :public monster_card{
private:



public:
    the_inocent();
    virtual ~the_inocent();
    void play_monster_card();
    void show_event()override;
    /*void do_strike()override;
    void do_event()override;*/ 
    virtual void show_item_num(); 
};
//=======================================================================================================//
class egyptian_expert : public monster_card{
private:



public:
    egyptian_expert();
    virtual ~egyptian_expert();
    void play_monster_card();
    void show_event()override;
    /*void do_strike()override;
    void do_event()override;*/ 
    virtual void show_item_num(); 
};
//=======================================================================================================//
class the_Ichthyologist : public monster_card{
private:



public:
    the_Ichthyologist();
    virtual ~ the_Ichthyologist();
    void play_monster_card();
    void show_event()override;
    /*void do_strike()override;
    void do_event()override;*/ 
    virtual void show_item_num(); 
};
//=======================================================================================================//
class bag_of_monster_card{
private:
monster_card m_card;
form_of_the_bat form_bat1;
form_of_the_bat form_bat2;
form_of_the_bat form_bat3;
sunrise sun1;
sunrise sun2;
sunrise sun3;
thief thief1;
thief thief2;
thief thief3;
thief thief4;
thief thief5;
the_delivery deliver;
fortune_teller tell;
former_employer former;
hurried_assistant assist;
the_inocent inocent;
egyptian_expert expert;
the_Ichthyologist ich;

std::vector<monster_card*> monster_card_bag{&form_bat1 , &form_bat2 , &form_bat3 ,&sun1 ,&sun2 ,&sun3 , &thief1 ,&thief2 ,&thief3 ,&thief4 ,&thief5 ,&deliver ,&tell ,&former ,&assist ,&inocent ,&expert ,&ich};
public:
monster_card* draw_random_card(std::vector<monster_card*>& deck); // بعد از استفاده از این تابع متد نشون دادن کارت رو که در کلاس های کارت هیولا نوشتم فراخوانی کن




protected:
};
#endif