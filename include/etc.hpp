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

//constexpr int totalWidth = 120;
//constexpr int colHalfWidth = totalWidth / 2;
//constexpr int colQuarterWidth = totalWidth / 4;



//*********************************************************************************************************//



// اعلام کلاس‌ها (فوروارد دکلریشن)
class Hero;
class place;

// تابع رابط کاربری متنی
void TUI_refresh(const Hero* hero1, const Hero* hero2, const std::vector<Place*>& places, int terrorLevel);





void gameboard_operation();

void TUI_refresh(const Hero* hero1, const Hero* hero2, const std::vector<Place>& places, int terrorLevel);

void clearScreen();





#endif