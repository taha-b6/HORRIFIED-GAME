#include <iostream>
#include <vector>
#include <string>
#include <variant>
#include <map>
#include "card.hpp"
#include"place.hpp"

using namespace std;

 void item::put_Itme_IN_Place(multimap<string, place>& places, int a) {
    if (items_in_the_game.empty()) {
        for (int i = 0; i < a; i++) {
            std::string n = items_out_the_game.back().name;
            auto range = places.equal_range(n);
    
            for (auto it = range.first; it != range.second; ++it) {
                item newItem(items_out_the_game.back());  
                it->second.items_list.push_back(newItem);
                items_out_the_game.back().count--;
                if(items_out_the_game.back().count==0){
                    items_in_the_game.push_back(items_out_the_game.back());
                    items_out_the_game.pop_back();
                }
            }
        }
    }
    for (int i = 0; i < a; i++) {
        std::string n = items_in_the_game.back().name;
        auto range = places.equal_range(n);

        for (auto it = range.first; it != range.second; ++it) {
            item newItem(items_in_the_game.back());  
            it->second.items_list.push_back(newItem);
            items_in_the_game.back().count--;
            if(items_in_the_game.back().count==0){
                items_out_the_game.push_back(items_in_the_game.back());
                items_in_the_game.pop_back();
            }
        }
    }
}
//***********************************************************************************************//
void visit_from_the_detective::play_perk(Monster* monster) {
    std::string name;
    bool success = false;

    while (!success) {
        std::cout << "\t ----------- Name the place where you want the invisible man to be : ---------- \n";
        std::cin >> name;

        try {
            moving::set_new_location(name);
            success = true; 
        } catch (std::invalid_argument& e) {
            std::cerr << e.what() << std::endl;
            std::cerr << "Please try again with a valid place name.\n";
        }
    }
}


//*********************************************************************************************//

void repel::play_perk(Monster* deracola , Monster* inviseble_man){//برای حرکت دادن هیولا ها دو خانه
    moving::set_new_location();
}
void break_of_dawn::play_perk(multimap<string,place> & places ){
    item::put_Itme_IN_Place(places , 2);
}
//***************************************************************************************//

void overstock::play_perk(multimap<string,place> & places){
    item::put_Itme_IN_Place(places , 2);
}

//********************************************************************************//

void late_into_the_night::play_perk(Hero* hero){
    hero->increase_action(2);
}
//********************************************************************//
void hurry::play_perk( Hero* archaeologist , Hero* mayor ){

}
//*********************************************************** //
void perk_card::set_count(int new_count){
    count = new_count;
}
int& perk_card::get_count(){
    return count;
}


