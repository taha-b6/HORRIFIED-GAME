#include <iostream>
#include <vector>
#include <string>
#include <random>
#include "monster_card.hpp"

#include "character.hpp"
//=====================================================================================================//
using namespace std;
Villager* findVillagerByName(const vector<Villager*>& vil, const string& targetName) {
    for (Villager* v : vil) {
        if (v->name == targetName) {
            return v; // مقدار را پیدا کردیم، آن را برمی‌گردانیم
        }
    }
    return nullptr; // اگر نام یافت نشد، مقدار `nullptr` را برمی‌گردانیم
}

//=====================================================================================================//
void monster_card::play_monster_card( vector<Villager*>& vil, int& trrorlevel , Monster * inv , Monster* de)
{

    Invisible_man * invisible_man=dynamic_cast<Invisible_man*>(inv);
    Deracula* deracula=dynamic_cast<Deracula*>(de);
    if(invisible_man||deracula){
    bag_items::put_Itme_IN_Place(items_num);

    if (event_bio_id == 1)
    {
        try{
        moving::set_location_deracula();}
        catch(runtime_error & e){
            cerr<<e.what()<<endl;
        }
    } // دراکولا رو به موقعیت قهرمان ببر
    
    
    if (event_bio_id == 2)
    {
        try{
        moving::set_location_deracula("abbey");}
        catch(runtime_error & e){
            cerr<<e.what()<<endl;
        }
    } // DERACULA -----> CRYPT
    
    
    if (event_bio_id == 3)
    {
        moving::set_location_invisible_man();
    } // اول مرد نامرِی رو به مکانی که بیشترین ایتم را دارد ببر دوم ایتم ها را از بازی خراج کن کن
    
    
    if (event_bio_id == 4)
    {   
        Villager* t= findVillagerByName(vil , "WILBUR_&_CHICK");
        if(t!=nullptr){ 
        moving::get_place("docks")->put_vilager(t);}
    } // WILBUR & CHICK -------> DOCK
    
    
    if (event_bio_id == 5)
    {
        Villager* t= findVillagerByName(vil , "MELVA");
        if(t!= nullptr){
        moving::get_place("camp")->put_vilager(t);}
        
    } // MALEVA ------>CAMP
    
    if (event_bio_id == 6)
    {
        Villager* t= findVillagerByName(vil , "DR_CRANLY");
        if(t!= nullptr){
        moving::get_place("laboratory")->put_vilager(t);}
        
    } // DR.CRANLY-------->LABORATORY
    if (event_bio_id == 7)
    {
        Villager* t= findVillagerByName(vil , "FRITZ");
        if(t!= nullptr){
        moving::get_place( "tower")->put_vilager(t);}
        
    } // FRITZ ------->TOWER
    
    if (event_bio_id == 8)
    {
        Villager* t= findVillagerByName(vil , "MARIA");
        if(t!= nullptr){
        moving::get_place("barn")->put_vilager(t);}
        
    } // MARIA ------->BARN
    
    if (event_bio_id == 9)
    {
        Villager* t= findVillagerByName(vil , "PROF_PEARSON");
        if(t!= nullptr){
        moving::get_place( "cave")->put_vilager(t);}
        
    } // PR.PEARSON --------->CAVE    
    if (event_bio_id == 10)
    {
        Villager* t= findVillagerByName(vil , "DR_REED");
        if(t!= nullptr){
        moving::get_place("institute")->put_vilager(t);}
        
    } // SDR.READ ------->INSTITUTE
    bool flag_invisible_man_power = false;

    for (auto &a : strike_arrange)
    {
        moving::set_new_location(a, strike_move);
        cout << a << "strike turn..." << endl;
        if (strike_dice_num == 2)
        { // تابعی که هیولای مشخص شده در در فور را به تعداد خواسته شده جابجا کند
            Dice t1 = play_dice();
            Dice t2 = play_dice();

            if (t1 == 0 && t2 == 0)
            {
            } // done

            if (t1 == 0 && t2 == 1)
            {
                if (a == "invisible man")
                {
                    cout << "STALK UNSEEN IS ON!!!!!!" << endl;
                    flag_invisible_man_power = true;
                } // edit
                if (a == "deracula")
                {
                    deracula->Deracula_special_power();
                } // done
            }

            if (t1 == 0 && t2 == 2)
            {
                if (a == "invisible_man")
                {
                    bool f=invisible_man->invisible_man_strike();
                    if(f){
                        trrorlevel++;
                        return;
                    }
                } // done
                if (a == "deracula")
                {
                    bool f= deracula->Deracula_strike();
                         if(f){
                        trrorlevel++;
                        return;
                    }
                } // done
            }

            if (t1 == 1 && t2 == 0)
            {
                if (a == "invisible_man")
                {
                    cout << "STALK UNSEEN IS ON!!!!!!" << endl;
                    flag_invisible_man_power = true;
                } // edit
                if (a == "Deracula")
                {
                    deracula->Deracula_special_power();
                } // done
            }

            if (t1 == 1 && t2 == 1)
            {
                if (a == "invisible_man")
                {
                    cout << "STALK UNSEEN IS ON!!!!!!" << endl;
                    flag_invisible_man_power = true;
                } // edit
                if (a == "Deracula")
                {
                   deracula->Deracula_special_power();
                } // done
            }

            if (t1 == 1 && t2 == 2)
            {
                if (a == "invisible_man")
                {
                    invisible_man->invisible_man_strike();
                    cout << "STALK UNSEEN IS ON!!!!!!" << endl;
                    flag_invisible_man_power = true;
                } // edit
                if (a == "deracula")
                {
                    deracula->Deracula_special_power();
                    bool f= deracula->Deracula_strike();
                         if(f){
                        trrorlevel++;
                        return;
                    }
                } // done
            }

            if (t1 == 2 && t2 == 0)
            {
                if (a == "invisible_man")
                {
                    bool f= invisible_man->invisible_man_strike();
                         if(f){
                        trrorlevel++;
                        return;
                    }
                } // done
                if (a == "deracula")
                {
                    bool f= deracula->Deracula_strike();
                         if(f){
                        trrorlevel++;
                        return;
                    }
                } // done
            }

            if (t1 == 2 && t2 == 1)
            {
                if (a == "invisible_man")
                {
                    bool f=invisible_man->invisible_man_strike();
                         if(f){
                        trrorlevel++;
                        return;
                    }
                    cout << "STALK UNSEEN IS ON!!!!!!" << endl;
                    flag_invisible_man_power = true;
                } // edit
                if (a == "deracula")
                {
                    deracula->Deracula_special_power();
                    bool f= deracula->Deracula_strike();
                         if(f){
                        trrorlevel++;
                        return;
                    }
                } // done
            }

            if (t1 == 2 && t2 == 2)
            {
                if (a == "invisible_man")
                {
                   invisible_man->invisible_man_strike();
                } // done
                if (a == "deracula")
                {
                   bool f=deracula->Deracula_strike();
                        if(f){
                        trrorlevel++;
                        return;
                    }
                } // done
            }
        }

        if (strike_dice_num == 3)
        {
            Dice t1 = play_dice();
            Dice t2 = play_dice();
            Dice t3 = play_dice();

            if (t1 == 0 && t2 == 0 && t3 == 0)
            {
            } // done

            if (t1 == 1 && t2 == 0 && t3 == 0)
            {
                if (a == "invisible_man")
                {
                    cout << "STALK UNSEEN IS ON!!!!!!" << endl;
                    flag_invisible_man_power = true;
                } // edit
                if (a == "deracula")
                {
                   deracula->Deracula_special_power();
                }
            }

            if (t1 == 1 && t2 == 1 && t3 == 0)
            {
                if (a == "invisible_man")
                {
                    cout << "STALK UNSEEN IS ON!!!!!!" << endl;
                    flag_invisible_man_power = true;
                } // edit
                if (a == "deracula")
                {
                   deracula->Deracula_special_power();
                } // done
            }

            if (t1 == 1 && t2 == 1 && t3 == 1)
            {
                if (a == "invisible_man")
                {
                    cout << "STALK UNSEEN IS ON!!!!!!" << endl;
                    flag_invisible_man_power = true;
                } // edit
                if (a == "deracula")
                {
                   deracula->Deracula_special_power();
                } // done
            }

            if (t1 == 2 && t2 == 1 && t3 == 1)
            {
                if (a == "invisible_man")
                {
                    bool f=invisible_man->invisible_man_strike();
                         if(f){
                        trrorlevel++;
                    }
                    cout << "STALK UNSEEN IS ON!!!!!!" << endl;
                    flag_invisible_man_power = true;
                } // edit
                if (a == "deracula")
                {
                   deracula->Deracula_special_power();
                    bool f=deracula->Deracula_strike();
                         if(f){
                        trrorlevel++;
                        return;
                    }
                } // done
            }

            if (t1 == 2 && t2 == 2 && t3 == 1)
            {
                if (a == "invisible_man")
                {
                    bool f= invisible_man->invisible_man_strike();
                         if(f){
                        trrorlevel++;
                        return;
                    }
                    cout << "STALK UNSEEN IS ON!!!!!!" << endl;
                    flag_invisible_man_power = true;
                } // edit
                if (a == "deracula")
                {
                    deracula->Deracula_special_power();
                   bool f= deracula->Deracula_strike();
                        if(f){
                        trrorlevel++;
                        return;
                    }
                } // done
            }

            if (t1 == 2 && t2 == 2 && t3 == 2)
            {
                if (a == "invisible_man")
                {
                    bool f= invisible_man->invisible_man_strike();
                         if(f){
                        trrorlevel++;
                        return;
                    }
                } // done
                if (a == "deracula")
                {
                    bool f =deracula->Deracula_strike();
                         if(f){
                        trrorlevel++;
                        return;
                    }
                } // done
            }

            if (t1 == 0 && t2 == 1 && t3 == 0)
            {
                if (a == "invisible_man")
                {
                    cout << "STALK UNSEEN IS ON!!!!!!" << endl;
                    flag_invisible_man_power = true;
                } // edit
                if (a == "deracula")
                {
                    deracula->Deracula_special_power();
                } // done
            }

            if (t1 == 0 && t2 == 0 && t3 == 1)
            {
                if (a == "invisible_man")
                {
                    cout << "STALK UNSEEN IS ON!!!!!!" << endl;
                    flag_invisible_man_power = true;
                } // edit
                if (a == "deracula")
                {
                    deracula->Deracula_special_power();
                } // done
            }

            if (t1 == 0 && t2 == 1 && t3 == 1)
            {
                if (a == "invisible_man")
                {
                    cout << "STALK UNSEEN IS ON!!!!!!" << endl;
                    flag_invisible_man_power = true;
                } // edit
                if (a == "deracula")
                {
                    deracula->Deracula_special_power();
                } // done
            }

            if (t1 == 1 && t2 == 0 && t3 == 1)
            {
                if (a == "invisible_man")
                {
                    cout << "STALK UNSEEN IS ON!!!!!!" << endl;
                    flag_invisible_man_power = true;
                } // edit
                if (a == "deracula")
                {
                    deracula->Deracula_special_power();
                } // done
            }

            if (t1 == 1 && t2 == 2 && t3 == 1)
            {
                if (a == "invisible_man")
                {
                    bool f= invisible_man->invisible_man_strike();
                         if(f){
                        trrorlevel++;
                        return;
                    }
                    cout << "STALK UNSEEN IS ON!!!!!!" << endl;
                    flag_invisible_man_power = true;
                } // edit
                if (a == "deracula")
                {
                    deracula->Deracula_special_power();
                    bool f= deracula->Deracula_strike();
                         if(f){
                        trrorlevel++;
                        return;
                    }
                } // done
            }

            if (t1 == 1 && t2 == 1 && t3 == 2)
            {
                if (a == "invisible_man")
                {
                    bool f= invisible_man->invisible_man_strike();
                         if(f){
                        trrorlevel++;
                        return;
                    }
                    cout << "STALK UNSEEN IS ON!!!!!!" << endl;
                    flag_invisible_man_power = true;
                } // edit
                if (a == "deracula")
                {
                    deracula->Deracula_special_power();
                   bool f= deracula->Deracula_strike();
                        if(f){
                        trrorlevel++;
                        return;
                    }
                } // done
            }

            if (t1 == 2 && t2 == 1 && t3 == 2)
            {
                if (a == "invisible_man")
                {
                    bool f= invisible_man->invisible_man_strike();
                         if(f){
                        trrorlevel++;
                        return;
                    }
                    cout << "STALK UNSEEN IS ON!!!!!!" << endl;
                    flag_invisible_man_power = true;
                } // edit
                if (a == "deracula")
                {
                    deracula->Deracula_special_power();
                   bool f= deracula->Deracula_strike();
                        if(f){
                        trrorlevel++;
                        return;
                    }
                } // done
            }

            if (t1 == 1 && t2 == 2 && t3 == 2)
            {
                if (a == "invisible_man")
                {
                    bool f= invisible_man->invisible_man_strike();
                         if(f){
                        trrorlevel++;
                        return;
                    }
                    cout << "STALK UNSEEN IS ON!!!!!!" << endl;
                    flag_invisible_man_power = true;
                } // edit
                if (a == "deracula")
                {
                    deracula->Deracula_special_power();
                   bool f= deracula->Deracula_strike();
                        if(f){
                        trrorlevel++;
                        return;
                    }
                } // done
            }
        }
    }
    if (flag_invisible_man_power == true)
    {
        invisible_man->invisible_man_special_power();
    }
cout<<"end of play monster card!!!!!!!!!!!!!!!!!!!!"<<endl;}
}

//=====================================================================================================//
Dice monster_card::play_dice()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(Empety, Attack);
    int chosen = dist(gen);
    cout << "Dice symbol is :" << chosen << endl;
    Dice temp;
    switch (chosen)
    {
    case 0:
        temp = Empety;
        break;
    case 1:
        temp = Special_power;
        break;
    case 2:
        temp = Attack;
        break;
    }
    return temp;
}
//=====================================================================================================//
void monster_card::show_monster_card()
{
    cout << "A monster card is shown" << endl;
    cout << "showing card details..." << endl;
    cout << "card name :" << name << endl;
    cout << "the number of item :" << items_num << endl;
    cout << "evnet :" << event_bio << endl;
    for (auto &a : strike_arrange)
    {
        cout << a << "--->" << strike_move << "move" << "--->" << strike_dice_num << "Dice" << endl;
    }
}

//======================================= constructor=======================================================//
form_of_the_bat::form_of_the_bat()
{
    event_bio_id = 1;
    name = "Form of the Bat";
    num_of_this_card = 3;
    strike_move = 1;
    strike_dice_num = 2;
    items_num = 2;
    event_bio = "Take Dracula to the current hero's location.";
    strike_arrange={};
}
//=====================================================================================================//

//======================================= constructor=======================================================//
sunrise::sunrise()
{
    event_bio_id = 2;
    num_of_this_card = 3;
    name="sunrise";
    strike_move = 1;
    strike_dice_num = 2;
    items_num = 0;
    event_bio = "Put Deracula in <abbay>.";
    strike_arrange = {"invisible_man"};
}

//======================================= constructor=======================================================//
thief::thief()
{
    event_bio_id = 3;
    num_of_this_card = 5;
    strike_move = 1;
    strike_dice_num = 3;
    name="thief";
    items_num = 2;
    event_bio = "Move the Invisible Man character to the location with the most items and remove all items from that location from the map and return them to the out-of-game location.";
    strike_arrange = {"invisible_man", "deracula"};
}

//======================================= constructor=======================================================//
the_delivery::the_delivery()
{
    event_bio_id = 4;
    num_of_this_card = 1;
    strike_move = 1;
    strike_dice_num = 3;
    name="the_delivery";
    items_num = 3;
    event_bio = "You need to place the Chick & Wilbur characters at the Docks location.";
    strike_arrange = {};
}

//======================================= constructor=======================================================//
fortune_teller::fortune_teller()
{
    event_bio_id = 5;
    num_of_this_card = 1;
    strike_move = 1;
    strike_dice_num = 2;
    items_num = 3;
    name="fortune_teller";
    event_bio = "You need to place the Maleva character in the Camp location";
    strike_arrange = {};
}
//======================================= constructor=======================================================//
former_employer::former_employer()
{
    event_bio_id = 6;
    num_of_this_card = 1;
    strike_move = 1;
    strike_dice_num = 2;
    name="former_employer";
    items_num = 3;
    event_bio = "Put Dr.Cranly character in the Laboratory location.";
    strike_arrange = {"invisible_man"};
}

//======================================= constructor=======================================================//
hurried_assistant::hurried_assistant()
{
    event_bio_id = 7;
    num_of_this_card = 1;
    strike_move = 2;
    strike_dice_num = 3;
    name="hurried_assistant";
    items_num = 3;
    event_bio = "Put Fritz in the Tower";
    strike_arrange = {"deracula"};
}

//======================================= constructor=======================================================//
the_inocent::the_inocent()
{
    event_bio_id = 8;
    num_of_this_card = 1;
    strike_move = 1;
    strike_dice_num = 3;
    name="the_inocent";
    items_num = 3;
    event_bio = "Put Maria in Barn";
    strike_arrange = {"deracula", "invisible_man"};
}
//======================================= constructor=======================================================//
egyptian_expert::egyptian_expert()
{
    event_bio_id = 9;
    num_of_this_card = 1;
    strike_move = 2;
    strike_dice_num = 2;
    name="egyptian_expert";
    items_num = 3;
    event_bio = "Put Prof.pearson in the Cave";
    strike_arrange = {"deracula"};
}

//======================================= constructor=======================================================//
the_Ichthyologist::the_Ichthyologist()
{
    event_bio_id = 10;
    num_of_this_card = 1;
    strike_move = 1;
    strike_dice_num = 2;
    name="the_Ichthyologist";
    items_num = 3;
    event_bio = "Put Dr.read character in Institute";
    strike_arrange = {};
}
//=====================================================================================================//
monster_card * bag_of_monster_card::draw_random_card()
{
    if (monster_card_bag.empty())
    {
        return nullptr; // یا throw std::runtime_error("Deck is empty");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, monster_card_bag.size() - 1);

    int index = dist(gen);
    monster_card *selected = monster_card_bag[index];
    clog<<"**********"<<endl<<selected->get_name()<<endl;
    monster_card_bag.erase(monster_card_bag.begin() + index); // حذف کارت از دسته

    return selected; // برگردوندن کارت انتخاب‌شده
}
//==============================================================================
 bool bag_of_monster_card::moster_cards_is_end(){
    if(monster_card_bag.empty()){
        return true;
    }
    return false;
}
//==================================================================================

