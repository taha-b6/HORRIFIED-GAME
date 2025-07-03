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
#include<functional>






//*********************************************************************************************************//



// اعلام کلاس‌ها (فوروارد دکلریشن)
class Hero;
class place;

// تابع رابط کاربری متنی
void TUI_refresh( Hero* hero1,  Hero* hero2, std::vector<place*> places, int terrorLevel);





void gameboard_operation();


void clearScreen();





#endif