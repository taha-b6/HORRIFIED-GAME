#ifndef ETC-HPP
#define  ETC-HPP

#include <iostream>
#include <string>
#include <vector>
#include <variant>
#include <ctime>

class dice{
private:


public:
};

//*********************************************************************************************************//

class Action{
private:



public:

void show_near_place();

};

void gameboard_operation();

void TGUI_refresh();






struct Hero;
struct Place;
struct Creature;

void TUI_refresh(const Hero* hero1, const Hero* hero2, const std::vector<Place>& places, int terrorLevel);

void clearScreen();





#endif