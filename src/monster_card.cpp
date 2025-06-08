#include <iostream>
#include <vector>
#include <string>
#include <random>
#include "monster_card.hpp"
#include "character.hpp"
//=====================================================================================================//
using namespace std;
//======================================= constructor=======================================================//
void monster_card::show_event(){
cout<<"The monster card event is :"<<endl;
cout<<event_bio<<endl;
}
//=====================================================================================================//
void monster_card::play_monster_card(){
                                                  //( ابعی که دراکولا را به موقعیت قهرمان فاز قبلی ببد(برای یکی از کارتها
                                                 //تابعی که هیولا های خواشته شده را به تعداد گفته شده در کارت جابجا کند   
                                                //تابعی که ایتم ها را در مکان درست بزارد
                                                //تابعی که محلی های گفته شده را سرجایشان بزارد

if (event_bio_id == 1){}//دراکولا رو به موقعیت قهرمان ببر
if (event_bio_id == 2){}//DERACULA -----> CRYPT
if (event_bio_id == 3){}//اول مرد نامرِی رو به مکانی که بیشترین ایتم را دارد ببر دوم ایتم ها را از بازی خراج کن کن
if (event_bio_id == 4){}//WILBUR & CHICK -------> DOCK
if (event_bio_id == 5){}//MALEVA ------>CAMP
if (event_bio_id == 6){}//DR.CRANLY-------->LABORATORY
if (event_bio_id == 7){}//FRITZ ------->TOWER
if (event_bio_id == 8){}//MARIA ------->BARN
if (event_bio_id == 9){}//PR.PEARSON --------->CAVE
if (event_bio_id == 10){}//SDR.READ ------->INSTITUTE

bool flag_invisible_man_power = false;

for(auto& a :strike_arrange){
cout<<a<<"strike turn..."<<endl;
if(strike_dice_num == 2){                                              //تابعی که هیولای مشخص شده در در فور را به تعداد خواسته شده جابجا کند
Dice t1 = play_dice();
Dice t2 = play_dice();

if (t1 == 0 && t2 == 0){}//done

if (t1 == 0 && t2 == 1){
if(a == "invisible man"){cout<<"STALK UNSEEN IS ON!!!!!!"<<endl; flag_invisible_man_power = true;}//edit
if(a =="deracula"){Deracola::deracula_special_power();    }//done
}

if (t1 == 0 && t2 == 2){
if (a == "invisible man"){Invisable_man::invisible_man_strike();}//done
if (a == "deracula"){Deracola::deracula_strike();}//done
}

if (t1 == 1 && t2 == 0){
if(a == "invisible man"){cout<<"STALK UNSEEN IS ON!!!!!!"<<endl; flag_invisible_man_power = true;}//edit
if(a =="deracula"){Deracola::deracula_special_power();    }//done
}

if (t1 == 1 && t2 == 1){
if(a == "invisible man"){cout<<"STALK UNSEEN IS ON!!!!!!"<<endl; flag_invisible_man_power = true;}//edit
if(a =="deracula"){Deracola::deracula_special_power();    }//done
}

if (t1 == 1 && t2 == 2){
if(a == "invisible man"){Invisable_man::invisible_man_strike();
cout<<"STALK UNSEEN IS ON!!!!!!"<<endl; flag_invisible_man_power = true;}//edit
if(a =="deracula"){Deracola::deracula_special_power();
Deracola::deracula_strike();    }//done
}

if (t1 == 2 && t2 == 0){
if (a == "invisible man"){Invisable_man::invisible_man_strike();}//done
if (a == "deracula"){Deracola::deracula_strike();}//done
}

if (t1 == 2 && t2 == 1){
if(a == "invisible man"){Invisable_man::invisible_man_strike();
cout<<"STALK UNSEEN IS ON!!!!!!"<<endl; flag_invisible_man_power = true;}//edit
if(a =="deracula"){Deracola::deracula_special_power();
Deracola::deracula_strike();    }//done
}

if (t1 == 2 && t2 == 2){
if (a == "invisible man"){Invisable_man::invisible_man_strike();}//done
if (a == "deracula"){Deracola::deracula_strike();}//done
}
}

if (strike_dice_num == 3){
Dice t1 = play_dice();
Dice t2 = play_dice();
Dice t3 = play_dice();
   
if (t1 == 0 && t2 == 0 && t3 == 0){}//done

if (t1 == 1 && t2 == 0 && t3 == 0){
if (a == "invisible man"){cout<<"STALK UNSEEN IS ON!!!!!!"<<endl; flag_invisible_man_power = true;}//edit
if (a == "deracula"){Deracola::deracula_special_power();}
}

if (t1 == 1 && t2 == 1 && t3 == 0){
if (a == "invisible man"){cout<<"STALK UNSEEN IS ON!!!!!!"<<endl; flag_invisible_man_power = true;}//edit
if (a == "deracula"){Deracola::deracula_special_power();}//done
}

if (t1 == 1 && t2 == 1 && t3 == 1){
if (a == "invisible man"){cout<<"STALK UNSEEN IS ON!!!!!!"<<endl; flag_invisible_man_power = true;}//edit
if (a == "deracula"){Deracola::deracula_special_power();}//done
}

if (t1 == 2 && t2 == 1 && t3 == 1){
if (a == "invisible man"){Invisable_man::invisible_man_strike();
cout<<"STALK UNSEEN IS ON!!!!!!"<<endl; flag_invisible_man_power = true;}//edit
if (a == "deracula"){Deracola::deracula_special_power();
Deracola::deracula_strike();}//done
}

if (t1 == 2 && t2 == 2 && t3 == 1){
if (a == "invisible man"){Invisable_man::invisible_man_strike();
cout<<"STALK UNSEEN IS ON!!!!!!"<<endl; flag_invisible_man_power = true;}//edit
if (a == "deracula"){Deracola::deracula_special_power();
Deracola::deracula_strike();}//done
}

if (t1 == 2 && t2 == 2 && t3 == 2){
if (a == "invisible man"){Invisable_man::invisible_man_strike();}//done
if (a == "deracula"){Deracola::deracula_strike();}//done
}

if (t1 == 0 && t2 == 1 && t3 == 0){
if (a == "invisible man"){cout<<"STALK UNSEEN IS ON!!!!!!"<<endl; flag_invisible_man_power = true;}//edit
if (a == "deracula"){Deracola::deracula_special_power();}//done
}

if (t1 == 0 && t2 == 0 && t3 == 1){
if (a == "invisible man"){cout<<"STALK UNSEEN IS ON!!!!!!"<<endl; flag_invisible_man_power = true;}//edit
if (a == "deracula"){Deracola::deracula_special_power();}//done
}

if (t1 == 0 && t2 == 1 && t3 == 1){
if (a == "invisible man"){cout<<"STALK UNSEEN IS ON!!!!!!"<<endl; flag_invisible_man_power = true;}//edit
if (a == "deracula"){Deracola::deracula_special_power();}//done
}

if (t1 == 1 && t2 == 0 && t3 == 1){
if (a == "invisible man"){cout<<"STALK UNSEEN IS ON!!!!!!"<<endl; flag_invisible_man_power = true;}//edit
if (a == "deracula"){Deracola::deracula_special_power();}//done
}

if (t1 == 1 && t2 == 2 && t3 == 1){
if (a == "invisible man"){Invisable_man::invisible_man_strike();
cout<<"STALK UNSEEN IS ON!!!!!!"<<endl; flag_invisible_man_power = true;}//edit
if (a == "deracula"){Deracola::deracula_special_power();
Deracola::deracula_strike();}//done
}

if (t1 == 1 && t2 == 1 && t3 == 2){
if (a == "invisible man"){Invisable_man::invisible_man_strike();
cout<<"STALK UNSEEN IS ON!!!!!!"<<endl; flag_invisible_man_power = true;}//edit
if (a == "deracula"){Deracola::deracula_special_power();
Deracola::deracula_strike();}//done
}

if (t1 == 2 && t2 == 1 && t3 == 2){
if (a == "invisible man"){Invisable_man::invisible_man_strike();
cout<<"STALK UNSEEN IS ON!!!!!!"<<endl; flag_invisible_man_power = true;}//edit
if (a == "deracula"){Deracola::deracula_special_power();
Deracola::deracula_strike();}//done
}

if (t1 == 1 && t2 == 2 && t3 == 2){
if (a == "invisible man"){Invisable_man::invisible_man_strike();
cout<<"STALK UNSEEN IS ON!!!!!!"<<endl; flag_invisible_man_power = true;}//edit
if (a == "deracula"){Deracola::deracula_special_power();
Deracola::deracula_strike();}//done
}
}

}
if (flag_invisible_man_power == true){
Invisable_man::invisible_man_special_power();
}

}

//=====================================================================================================//
Dice monster_card::play_dice(){
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dist(Empety ,Attack);
int chosen = dist(gen);
cout << "Dice symbol is :" << chosen <<endl;
Dice temp;
switch (chosen){
case 0:
    temp = Empety;
    break;
case 1:
    temp = Special_power ;
    break;
case 2:
    temp = Attack;
    break;
}
return temp;
}
//=====================================================================================================//
void monster_card::show_monster_card(){
cout<<"A monster card is shown"<<endl;
cout<<"showing card details..."<<endl;
cout<<"card name :"<<name<<endl;
cout<<"the number of item :"<<items_num<<endl;
cout<<"evnet :"<<event_bio<<endl;
for (auto& a : strike_arrange){
cout<<a<<"--->"<<strike_move<<"move"<<"--->"<<strike_dice_num<<"Dice"<<endl;   
}

}
//=====================================================================================================//
void monster_card::show_item_num(){
cout<<"The number of items entering the game :"<<items_num<<endl;
}
//=====================================================================================================//
void monster_card::do_event(){}
//=====================================================================================================//
void monster_card::do_strike(){}
//======================================= constructor=======================================================// 
form_of_the_bat::form_of_the_bat(){
event_bio_id = 1;
name = "Form of the Bat";
num_of_this_card = 3;
strike_move = 1;
strike_dice_num = 2;
items_num = 2;
event_bio = "Take Dracula to the current hero's location.";
}
//=====================================================================================================//
void form_of_the_bat::play_monster_card(){}
//=====================================================================================================//
//void form_of_the_bat::show_event(){}
//=====================================================================================================//
//void form_of_the_bat::do_event(){}
//=====================================================================================================//
//void form_of_the_bat::show_item_num(){}
//=====================================================================================================//
//void form_of_the_bat::do_strike(){}
//======================================= constructor=======================================================//
sunrise::sunrise(){
event_bio_id = 2;
num_of_this_card = 3; 
strike_move = 1;
strike_dice_num = 2;
items_num = 0;
event_bio ="Put Deracula in <crypt>.";
strike_arrange = {"invisible man","frenzied monster"};
}
//=====================================================================================================//
void sunrise::play_monster_card(){}
//=====================================================================================================//
//void sunrise::show_event(){}
//=====================================================================================================//
//void sunrise::do_event(){}
//=====================================================================================================//
//void sunrise::show_item_num(){}
//=====================================================================================================//
//void sunrise::do_strike(){}
//======================================= constructor=======================================================//
thief::thief(){
event_bio_id = 3;
num_of_this_card = 5;
strike_move = 1;
strike_dice_num = 3;
items_num = 2;
event_bio = "Move the Invisible Man character to the location with the most items and remove all items from that location from the map and return them to the out-of-game location.";
strike_arrange = {"invisible man" , "deracula"};
}
//=====================================================================================================//
void thief::play_monster_card(){}
//=====================================================================================================//
//void thief::show_event(){}
//=====================================================================================================//
//void thief::do_event(){}
//=====================================================================================================//
//void thief::show_item_num(){}
//=====================================================================================================//
//void thief::do_strike(){}
//======================================= constructor=======================================================//
the_delivery::the_delivery(){
event_bio_id = 4;
num_of_this_card = 1;
strike_move = 1;
strike_dice_num = 3;
items_num = 3; 
event_bio = "You need to place the Chick & Wilbur characters at the Docks location.";
strike_arrange = {"frenzied monster"};
}
//=====================================================================================================//
void the_delivery::play_monster_card(){}
//=====================================================================================================//
//void the_delivery::show_event(){}
//=====================================================================================================//
//void the_delivery::do_event(){}
//=====================================================================================================//
//void the_delivery::show_item_num(){}
//=====================================================================================================//
//void the_delivery::do_strike(){}
//======================================= constructor=======================================================//
fortune_teller::fortune_teller(){
event_bio_id = 5;
num_of_this_card = 1;
strike_move = 1;
strike_dice_num = 2;
items_num = 3;
event_bio = "You need to place the Maleva character in the Camp location";
strike_arrange ={"frenzied monster"};
}
//=====================================================================================================//
void fortune_teller::play_monster_card(){}
//=====================================================================================================//
//void fortune_teller::show_event(){}
//=====================================================================================================//
//void fortune_teller::do_event(){}
//=====================================================================================================//
//void fortune_teller::do_strike(){}
//=====================================================================================================//
//void fortune_teller::show_item_num(){}
//======================================= constructor=======================================================//
former_employer::former_employer(){
event_bio_id = 6;
num_of_this_card = 1;
strike_move = 1;
strike_dice_num = 2; 
items_num = 3;
event_bio = "Put Dr.Cranly character in the Laboratory location.";
strike_arrange = {"invisible man" , "frenzied monster"};
}
//=====================================================================================================//
void former_employer::play_monster_card(){}
//=====================================================================================================//
//void former_employer::show_event(){}
//=====================================================================================================//
//void former_employer::do_event(){}
//=====================================================================================================//
// former_employer::show_item_num(){}
//=====================================================================================================//
//void former_employer::do_strike(){}
//======================================= constructor=======================================================//
hurried_assistant::hurried_assistant(){
event_bio_id = 7;
num_of_this_card = 1;
strike_move = 2;
strike_dice_num = 3; 
items_num = 3;
event_bio = "Put Fritz in the Tower";
strike_arrange = {"deracula"};
}
//=====================================================================================================//
void hurried_assistant::play_monster_card(){}
//=====================================================================================================//
//void hurried_assistant::show_event(){}
//=====================================================================================================//
//void hurried_assistant::do_event(){}
//=====================================================================================================//
//void hurried_assistant::show_item_num(){}
//=====================================================================================================//
//void hurried_assistant::do_strike(){}
//======================================= constructor=======================================================//
the_inocent::the_inocent(){
event_bio_id = 8;
num_of_this_card = 1;
strike_move = 1;
strike_dice_num = 3; 
items_num = 3;
event_bio = "Put Maria in Barn";
strike_arrange = {"frenzied monster" , "deracula" , "invisible man"};
}
//=====================================================================================================//
void the_inocent::play_monster_card(){}
//=====================================================================================================//
//void the_inocent::show_event(){}
//=====================================================================================================//
//void the_inocent::do_event(){}
//=====================================================================================================//
//void the_inocent::show_item_num(){}
//=====================================================================================================//
//void the_inocent::do_strike(){}
//======================================= constructor=======================================================//
egyptian_expert::egyptian_expert(){
event_bio_id = 9;
num_of_this_card = 1;
strike_move = 2;
strike_dice_num = 2; 
items_num = 3;
event_bio = "Put Prof.pearson in the Cave";
strike_arrange = {"deracula" , "frenzied monster"};
}
//=====================================================================================================//
void egyptian_expert::play_monster_card(){}
//=====================================================================================================//
//void egyptian_expert::show_event(){}
//=====================================================================================================//
//void egyptian_expert::do_event(){}
//=====================================================================================================//
//void egyptian_expert::show_item_num(){}
//=====================================================================================================//
//void egyptian_expert::do_strike(){}
//======================================= constructor=======================================================//
the_Ichthyologist::the_Ichthyologist(){
event_bio_id = 10;
num_of_this_card = 1;
strike_move = 1;
strike_dice_num = 2;
items_num = 3;
event_bio = "Put Dr.read character in Institute";
strike_arrange = {"frenzied monster"};
}
//=====================================================================================================//
void the_Ichthyologist::play_monster_card(){}
//=====================================================================================================//
//void the_Ichthyologist::show_event(){}
//=====================================================================================================//
//void the_Ichthyologist::do_event(){}
//=====================================================================================================//
//void the_Ichthyologist::show_item_num(){}
//=====================================================================================================//
//void the_Ichthyologist::do_strike(){}
//=====================================================================================================//