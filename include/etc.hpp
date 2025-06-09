#ifndef ETC_HPP
#define  ETC_HPP

#include <iostream>
#include <string>
#include <vector>
#include <variant>
#include <ctime>
#include <iomanip>
#include <map>
#include <set>
#include <sstream>
#include <algorithm>
#include"card.hpp"
#include"monster_card.hpp"
#include"character.hpp"
#include"moving.hpp"
#include"place.hpp"

constexpr int totalWidth = 120;
constexpr int colHalfWidth = totalWidth / 2;
constexpr int colQuarterWidth = totalWidth / 4;

class dice{
private:


public:
};

//*********************************************************************************************************//
struct Hero1 {
    std::string name;
    int health;
    int power;
    std::string position;
};

struct Creature1 {
    std::string name;
    std::string location;
};

struct Place1 {
    std::string name;
    std::string items; // یا داده مناسب دیگه
    int get_num_of_items() const;               // باید این متد پیاده‌سازی بشه
    std::vector<std::string> Show_villager_monster() const;  // همینطور این هم باید موجود باشه
};

void gameboard_operation();

void TUI_refresh(const Hero* hero1, const Hero* hero2, const std::vector<Place>& places, int terrorLevel);

void clearScreen();





#endif