#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <map>
#include <set>
#include <sstream>
#include <algorithm>
#include "etc.hpp"

using namespace std;

// ثابت‌های نمایش
const int totalWidth = 120;
const int colHalfWidth = totalWidth / 2;
const int colQuarterWidth = totalWidth / 4;

// --- ساختارهای موردنیاز ---
// فرض کردم ساختارها به این شکل هستن (شما تعریف‌شون کن یا جایگزین کن)
struct Hero {
    std::string name;
    int health;
    int power;
    std::string position;
};

struct Creature {
    std::string name;
    std::string location;
};

struct Place {
    std::string name;
    std::string items; // یا داده مناسب دیگه
    int get_num_of_items() const;               // باید این متد پیاده‌سازی بشه
    std::vector<std::string> Show_villager_monster() const;  // همینطور این هم باید موجود باشه
};

// --- توابع کمکی ---
void printFullBorder() {
    cout << "+" << string(totalWidth - 2, '-') << "+\n";
}

void printCenteredTitle(const string& title) {
    int padding = (totalWidth - 2 - title.length()) / 2;
    cout << "|" << string(padding, ' ') << title
         << string(totalWidth - 2 - padding - title.length(), ' ') << "|\n";
}

void printDoubleColumnHeader(const string& left, const string& right) {
    cout << "|" 
         << left << string(colHalfWidth - left.size() - 1, ' ') << "|"
         << right << string(colHalfWidth - right.size() - 1, ' ') << "|\n";
}

void printQuadColumnHeader(const string& c1, const string& c2, const string& c3, const string& c4) {
    cout << "|" 
         << setw(colQuarterWidth - 1) << left << c1 << "|"
         << setw(colQuarterWidth - 1) << left << c2 << "|"
         << setw(colQuarterWidth - 1) << left << c3 << "|"
         << setw(colQuarterWidth - 1) << left << c4 << "|\n";
}

// --- تابع اصلی رابط کاربری ---
void TUI_refresh(const Hero* hero1, const Hero* hero2, const vector<Place>& places, int terrorLevel) {
    // جدول بالای صفحه: عنوان و حاشیه
    printFullBorder();
    printCenteredTitle("GAME DASHBOARD");
    printFullBorder();

    // بخش نقشه
    // ساخت گراف مجاورتی براساس مکان‌ها و ارتباطات
    // فرض می‌کنیم که هر Place ارتباطات را نگه می‌دارد یا باید جای دیگه بگیریم

    // ابتدا نمایش هدر نقشه
    printDoubleColumnHeader("Map", "Location Overview");

    // ساخت adjacency map برای مکان‌ها
    map<string, set<string>> adjacency;
    // ساخت adjacency نیازمند اطلاعات اتصالات است. فرضاً در places، ارتباطات نیست.
    // پس این قسمت باید بر اساس داده‌های ورودی شما نوشته شود.
    // فعلاً فرض می‌کنیم adjacency خالی است.

    // نمایش مکان‌ها و همسایه‌ها
    for (const auto& loc : places) {
        ostringstream line;
        line << left << setw(12) << loc.name << "--> ";

        if (adjacency.count(loc.name)) {
            bool first = true;
            for (const auto& neighbor : adjacency[loc.name]) {
                if (!first) line << ", ";
                line << neighbor;
                first = false;
            }
        } else {
            line << "(No connections)";
        }

        cout << "|"
             << left << setw(colHalfWidth - 1) << line.str()
             << "|" << string(colHalfWidth - 1, ' ') << "|\n";
    }

    printFullBorder();

    // بخش Place Info (نمایش مکان‌ها و تعداد ایتم‌ها)
    printDoubleColumnHeader("Place Info", "Villager & Monster Info");

    // تعداد خطوط برای نمایش جدول: بیشترین تعداد بین مکان‌ها و موجودات
    size_t maxRows = max(places.size(), size_t(4)); // 4 حداقل ردیف نمایش

    for (size_t i = 0; i < maxRows; ++i) {
        string placeInfo = "";
        string villMonInfo = "";

        if (i < places.size()) {
            const Place& place = places[i];
            placeInfo = place.name + " (" + to_string(place.get_num_of_items()) + " items)";
            auto creatures = place.Show_villager_monster();
            villMonInfo = creatures.empty() ? "-" : creatures[0];
            for (size_t j = 1; j < creatures.size(); ++j) {
                villMonInfo += ", " + creatures[j];
            }
        }cout << "|"
             << left << setw(colHalfWidth - 1) << placeInfo
             << "|" << left << setw(colHalfWidth - 1) << villMonInfo
             << "|\n";
    }

    printFullBorder();

    // بخش قهرمان‌ها، ترس و منو اکشن
    printQuadColumnHeader("Hero 1 Info", "Hero 2 Info", "Terror Level", "Action Menu");

    vector<string> actionMenu = {
        "[0] Move", "[1] Guide", "[2] Pick Up",
        "[3] Advance", "[4] Defeat", "[5] Special Action"
    };

    size_t maxActionRows = max(actionMenu.size(), size_t(4));

    for (size_t i = 0; i < maxActionRows; ++i) {
        string h1 = "", h2 = "", terror = "", action = "";

        if (i == 0) {
            h1 = "Name: " + hero1->name;
            h2 = "Name: " + hero2->name;
            terror = "Level: " + to_string(terrorLevel);
        } else if (i == 1) {
            h1 = "Health: " + to_string(hero1->health);
            h2 = "Health: " + to_string(hero2->health);
        } else if (i == 2) {
            h1 = "Power: " + to_string(hero1->power);
            h2 = "Power: " + to_string(hero2->power);
        } else if (i == 3) {
            h1 = "Position: " + hero1->position;
            h2 = "Position: " + hero2->position;
        }

        if (i < actionMenu.size()) {
            action = actionMenu[i];
        }

        cout << "|"
             << left << setw(colQuarterWidth - 1) << h1
             << "|" << left << setw(colQuarterWidth - 1) << h2
             << "|" << left << setw(colQuarterWidth - 1) << terror
             << "|" << left << setw(colQuarterWidth - 1) << action
             << "|\n";
    }

    printFullBorder();
}




void clearScreen() {
    #ifdef __WIN32 
        system("cls");
    #else 
        system("clear");
    #endif
}
