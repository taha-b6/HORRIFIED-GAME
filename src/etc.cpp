#include "etc.hpp"
using namespace std;
//==================================================
void clearScreen()
{
#ifdef __WIN32
    system("cls");
#else
    system("clear");
#endif
}
//==================================================
void gameboard_operation()
{
    int terror_level = 0;
    Hero *first = nullptr;
    Hero *seccend = nullptr;
    bag_items bag_item;
    bag_of_monster_card bag_monster;
    Villager MALEVA("MALEVA", "shop");
    Villager WILBUR("WILBUR_&_CHICK", "dungion");
    Villager DR_CRANLY("DR_CRANLY", "precinct");
    Villager FRITZ("FRITZ", "institute");
    Villager MARIA("MARIA", "camp");
    Villager PROF_PEARSON("PROF_PEARSON", "musium");
    Villager DR_REED("DR_REED", "camp");
    vector<Villager *> vil = {&MALEVA, &WILBUR, &DR_CRANLY, &FRITZ, &MARIA, &PROF_PEARSON, &DR_REED};
    bag_perks p;
    p.constract_perk_cart();

    cout << "When did you eat garlic enter two intiger\n";
    int a;
    int b;
    cin >> a;
    cin >> b;
    if (a >= b)
    {
        cout << "player one is your priority . which hero do you want enter its name\n";
        string name;
        cin >> name;
        if (name == "mayor" ||name=="archaeologist")
        {
            if (name == "mayor")
            {
                first = new Mayor;
                seccend = new Archaeologist;
            }
            else
            {
                seccend = new Mayor;
                first = new Archaeologist;
            }
        }
        else
        {
            cout << " wrong informatoin please try egain \n";
            exit(0);
        }
    }

    else
    {
        cout << "player two is your priority . which hero do you want enter its name\n";
        string name;
        cin >> name;
        if (name == "mayor" ||name== "archaeologist")
        {
            if (name == "mayor")
            {
                first = new Mayor;
                seccend = new Archaeologist;
            }
            else
            {
                seccend = new Mayor;
                first = new Archaeologist;
            }
        }
        else
        {
            cout << " wrong informatoin please try egain \n";
            exit(0);
        }
    }        
        cout<<"Enter any character when you want to continue !!!!!!"<<endl;
        getchar();
        cout<<"RESUMING THE GAME!!!!!!!1"<<endl;
        clearScreen();

    Monster *deracula = new Deracula;
    Monster *invisble_man = new Invisible_man;
    place cave("cave");
    place camp("camp");
    place precinct("precinct");
    place inn("inn");
    place barn("barn");
    place dungion("dungion");
    place theatre("theatre");
    place tower("tower");
    place mansion("mansion");
    place docks("docks");
    place abbey("abbey");
    place shop("shop");
    place crypt("crypt");
    place musium("musium");
    place church("church");
    place laboratory("laboratory");
    place hospital("hospital");
    place graveyard("graveyard");
    place institute("institute");

    std::map<std::string, place *> places{
        {"cave", &cave}, {"camp", &camp}, {"precinct", &precinct}, {"inn", &inn}, {"barn", &barn}, {"dungion", &dungion}, {"theatre", &theatre}, {"tower", &tower}, {"mansion", &mansion}, {"docks", &docks}, {"abbey", &abbey}, {"shop", &shop}, {"crypt", &crypt}, {"musium", &musium}, {"church", &church}, {"laboratory", &laboratory}, {"hospital", &hospital}, {"graveyard", &graveyard}, {"institute", &institute}};
    vector<place *> pl = {
        &cave, &camp, &precinct, &inn, &barn, &dungion, &theatre, &tower,
        &mansion, &docks, &abbey, &shop, &crypt, &musium, &church,
        &laboratory, &hospital, &graveyard, &institute};
    moving mov(first, seccend, deracula, invisble_man);
    try
    {
        mov.set_places(places);
    }
    catch (runtime_error &e)
    {
        cout << e.what() << endl;
    }
    mov.start();
    bool next_faz = false;
    while (1)
    {   

        // pl همان چیز خواسته شدس
        TUI_refresh(first, seccend, pl, terror_level); // نمایش ترمینال
        if (terror_level == 5)
        {
            cout << "the heros lost beacuse terror level is 5\n";
            exit(0);
        }
        if (bag_monster.moster_cards_is_end())
        {
            cout << "the heros lost becouse monster cards is end\n";
            exit(0);
        }
        if (mov.hero_won())
        {
            cout << "hero won\n";
            exit(0);
        }

        first->do_action(next_faz);
        mov.set_last_hero(first);
       
        cout<<"Enter any character when you want to continue !!!!!!"<<endl;
        getchar();
        cout<<"RESUMING THE GAME!!!!!!!1"<<endl;
        clearScreen();
        TUI_refresh(first, seccend, pl, terror_level);
        if (!next_faz)
        {
            monster_card *m = bag_monster.draw_random_card();
            clog << "after draw random card" << endl;
            if (m != nullptr)
            {
                m->show_monster_card();
                m->play_monster_card(vil, terror_level, invisble_man, deracula);
            }
            else
            {
                cout << "[INFO] No more monster cards in the bag." << endl;
            }
            
        }
        
        cout<<"Enter any character when you want to continue !!!!!!"<<endl;
        getchar();
        cout<<"RESUMING THE GAME!!!!!!!1"<<endl;
        clearScreen();
        TUI_refresh(first, seccend, pl, terror_level);
        seccend->do_action(next_faz);
        mov.set_last_hero(seccend);
        if (!next_faz)
        {
            monster_card *m = bag_monster.draw_random_card();
            clog << "after draw random card" << endl;
            if (m != nullptr)
            {
                m->show_monster_card();
                m->play_monster_card(vil, terror_level, invisble_man, deracula);
            }
            else
            {
                cout << "[INFO] No more monster cards in the bag." << endl;
            }
        }
       
        cout<<"Enter any character when you want to continue !!!!!!"<<endl;
        getchar();
        cout<<"RESUMING THE GAME!!!!!!!1"<<endl;
        clearScreen();
        clearScreen();
    }
}
//=============================================================//

void TUI_refresh(Hero *h1, Hero *h2, vector<place *> places, int terrorLevel)
{

    cout << "\033[2J\033[H";

    auto getPlaceNumber = [&](const string &name) -> int
    {
        if (name == "precinct")
            return 0;
        else if (name == "mansion")
            return 1;
        else if (name == "musium")
            return 2;
        else if (name == "inn")
            return 3;
        else if (name == "camp")
            return 4;
        else if (name == "theatre")
            return 5;
        else if (name == "cave")
            return 6;
        else if (name == "institute")
            return 7;
        else if (name == "crypt")
            return 8;
        else if (name == "barn")
            return 9;
        else if (name == "dungion")
            return 10;
        else if (name == "docks")
            return 11;
        else if (name == "tower")
            return 12;
        else if (name == "laboratory")
            return 13;
        else if (name == "graveyard")
            return 14;
        else if (name == "hospital")
            return 15;
        else if (name == "abbey")
            return 16;
        else if (name == "church")
            return 17;
        else if (name == "shop")
            return 18;
        else
            return -1;
    };

    if (!h1 || !h2)
    {
        cerr << "Error: Null Hero pointer detected.\n";
        return;
    }
    if (places.empty())
    {
        cerr << "Error: Places vector is empty.\n";
        return;
    }

    const int totalWidth = 180;
    const int mapColWidth = 70;
    const int placeInfoWidth = totalWidth - 4 - mapColWidth;

    auto printFullBorder = [&]()
    {
        cout << "+" << string(totalWidth - 2, '-') << "+\n";
    };
    auto printCenteredTitle = [&](const string &title)
    {
        int padding = (totalWidth - 2 - static_cast<int>(title.size())) / 2;
        cout << "|" << string(padding, ' ') << title
             << string(totalWidth - 2 - padding - static_cast<int>(title.size()), ' ') << "|\n";
    };

    printFullBorder();
    printCenteredTitle("GAME DASHBOARD");
    printFullBorder();

    cout << "| " << left << setw(mapColWidth) << "Map (Location & Neighbors):"
         << " | " << left << setw(placeInfoWidth) << "Place Info & Villager/Monster Info:"
         << " |\n";
    printFullBorder();

    for (size_t i = 0; i < places.size(); i++)
    {
        place *p = places[i];
        if (!p)
            continue;
        string mapStr = p->name;
        int num = getPlaceNumber(p->name);
        if (num != -1)
            mapStr += " [" + to_string(num) + "]";

        vector<string> neighbors = p->show_near_place();
        if (!neighbors.empty())
        {
            mapStr += " | Neighbors: ";
            for (size_t j = 0; j < neighbors.size(); j++)
            {
                mapStr += neighbors[j];
                if (j != neighbors.size() - 1)
                    mapStr += ", ";
            }
        }
        if (static_cast<int>(mapStr.size()) > mapColWidth)
            mapStr = mapStr.substr(0, mapColWidth - 3) + "...";
        string itemsStr = "Items: " + to_string(p->get_num_of_items());
        vector<string> vm = p->show_villager_monster();
        string vmStr;
        for (size_t j = 0; j < vm.size(); j++)
        {
            vmStr += vm[j];
            if (j != vm.size() - 1)
                vmStr += ", ";
        }
        string infoStr = itemsStr + " | " + vmStr;
        if (static_cast<int>(infoStr.size()) > placeInfoWidth)
            infoStr = infoStr.substr(0, placeInfoWidth - 3) + "...";

        cout << "| " << left << setw(mapColWidth) << mapStr
             << " | " << left << setw(placeInfoWidth) << infoStr
             << " |\n";
    }
    printFullBorder();

    const int colQuarterWidth = totalWidth / 4;
    cout << "| " << left << setw(colQuarterWidth - 2) << "Hero 1 Info"
         << "| " << left << setw(colQuarterWidth - 2) << "Hero 2 Info"
         << "| " << left << setw(colQuarterWidth - 2) << "Terror Level"
         << "| " << left << setw(colQuarterWidth - 2) << "Action Menu"
         << "|\n";
    printFullBorder();

    vector<string> actionMenu = {"[0] Move", "[1] Guide", "[2] Pick Up", "[3] Advance",
                                 "[4] Defeat", "[5] Special Action"};
    size_t maxRows = max(actionMenu.size(), static_cast<size_t>(4));
    for (size_t i = 0; i < maxRows; i++)
    {
        string h1Info, h2Info;
        switch (i)
        {
        case 0:
            h1Info = "Name: " + h1->name;
            break;
        case 1:
            h1Info = "Items: " + to_string(h1->show_items_n());
            break;
        case 2:
            h1Info = "Perks: " + to_string(h1->show_perks_n());
            break;
        case 3:
            h1Info = "Position: " + h1->get_hero_place();
            break;
        default:
            h1Info = "";
            break;
        }
        switch (i)
        {
        case 0:
            h2Info = "Name: " + h2->name;
            break;
        case 1:
            h2Info = "Items: " + to_string(h2->show_items_n());
            break;
        case 2:
            h2Info = "Perks: " + to_string(h2->show_perks_n());
            break;
        case 3:
            h2Info = "Position: " + h2->get_hero_place();
            break;
        default:
            h2Info = "";
            break;
        }
        string terrorStr = (i == 0) ? "Level: " + to_string(terrorLevel) : "";
        string actionStr = (i < actionMenu.size()) ? actionMenu[i] : "";

        cout << "| " << left << setw(colQuarterWidth - 2) << h1Info
             << "| " << left << setw(colQuarterWidth - 2) << h2Info
             << "| " << left << setw(colQuarterWidth - 2) << terrorStr
             << "| " << left << setw(colQuarterWidth - 2) << actionStr
             << "|\n";
    }
    printFullBorder();
}