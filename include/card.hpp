#ifndef CARD-HPP
#define CARD-HPP

#include <iostream>
#include <vector>
#include <string>
#include <variant>
#include <map>
#include "place.hpp"
struct item_info{
    int power;
    std:: string color;
    std:: string name;
    coordinate location;
};

//*******************************************************************************************************************//

 
//*******************************************************************************************************************//

class card{
private:

public:
    virtual void play();
};

class item : public card{
private:

std:: vector<item_info> items_in_the_game;

public:
            //add related methods
};

//********************************************************************************************************************//

class perk : public card{
private:

public:
std:: string name;
std:: string event;

};
#endif