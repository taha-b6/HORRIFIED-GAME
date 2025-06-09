#include"etc.hpp"
using namespace std;
//==================================================
void gameboard_operation(){
    int terror_level=0;
    Hero* first = nullptr;
    Hero* seccend = nullptr;
    bag_items bag_item;
    bag_of_monster_card bag_monster;
    cout<<"When did you eat garlic enter two intiger\n";
    int a;
    int b;
    cin>>a;
    cin>>b;
    if(a>b){
        cout<<"player one is your priority . which hero do you want enter its name\n";
        string name;
        cin>>name;
        if(name=="mayor"){
            first = new Mayor("theatre");
            seccend= new Archaeologist("ducks") ;
        }
        else{
            seccend = new Mayor;
            first= new Archaeologist ;
        }
    }
    else{
        cout<<"player two is your priority . which hero do you want enter its name\n";
        string name;
        cin>>name;
        if(name=="mayor"){
            first = new Mayor;
            seccend= new Archaeologist ;
        }
        else{
            seccend = new Mayor;
            first= new Archaeologist ;
        }
    }
    Monster * deracula = new Deracula;
    Monster * invisble_man = new Invisible_man;

place cave("cave"); place comp("comp"); place precinct("precinct"); place inn("inn"); 
place barn("barn"); place dungion("dungion"); place theatre("theatre"); place tower("tower");
place mansion("mansion"); place docks("docks"); place abbey("abbey"); place shop("shop");
place crypt("crypt"); place musium("musium"); place charch("charch"); place laboratory("laboratory");
place hospital("hospital"); place graveyard("graveyard"); place institute("institute");

std::map<std::string, place*> places {
    {"cave", &cave}, {"comp", &comp}, {"precinct", &precinct}, {"inn", &inn},
    {"barn", &barn}, {"dungion", &dungion}, {"theatre", &theatre}, {"tower", &tower},
    {"mansion", &mansion}, {"docks", &docks}, {"abbey", &abbey}, {"shop", &shop},
    {"crypt", &crypt}, {"musium", &musium}, {"charch", &charch}, {"laboratory", &laboratory},
    {"hospital", &hospital}, {"graveyard", &graveyard}, {"institute", &institute}
};


    moving mov(first ,seccend , deracula , invisble_man );
    mov.set_places(places);
    bool next_faz=false;
    while(1){
        //نمایش ترمینال
        if(terror_level==5){
            cout<<"the heros lost beacuse terror level is 5\n";
            exit(0);
        }
        if(bag_monster.moster_cards_is_end()){
            cout<<"the heros lost becouse monster cards is end\n";
            exit(0);
        }
        if(mov.hero_won()){
            cout<<"hero won\n";
            exit(0);
        }

        first->do_action(next_faz);
        mov.set_last_hero(first);
        if(!next_faz){
            monster_card* m = bag_monster.draw_random_card();
            cout<<"monster card card is :\n";
            m->show_monster_card();
            m->play_monster_card( terror_level);
        }
        seccend->do_action(next_faz);
        mov.set_last_hero(seccend);
        if(!next_faz){
            monster_card* m = bag_monster.draw_random_card();
            cout<<"monster card card is :\n";
            m->show_monster_card();
            m->play_monster_card( terror_level);
        }
    }
}
//=============================================================//


void TUI_refresh( Hero* h1,  Hero* h2,  std::vector< place>& places, int terrorLevel) {
    const int totalWidth = 120;
    const int colHalfWidth = totalWidth / 2;
    const int colQuarterWidth = totalWidth / 4;

    // -------- توابع کمکی داخلی --------
    auto printFullBorder = [&]() {
        cout << "+" << string(totalWidth - 2, '-') << "+\n";
    };

    auto printCenteredTitle = [&](const string& title) {
        int padding = (totalWidth - 2 - (int)title.length()) / 2;
        cout << "|" << string(padding, ' ') << title
             << string(totalWidth - 2 - padding - (int)title.length(), ' ') << "|\n";
    };

    auto printLeftJustified = [&](const string& text, int width) {
        cout << left << setw(width) << text;
    };

    // -------- چاپ جدول --------
    printFullBorder();
    printCenteredTitle("GAME DASHBOARD");
    printFullBorder();

    // -------- Map section --------
    cout << "| Map (Location and Neighbors):" << string(colHalfWidth - 26, ' ') << "|"
         << "Place Info & Villager/Monster Info:" << string(colHalfWidth - 34, ' ') << "|\n";
    printFullBorder();

    // ساخت گراف مجاورتی
    // چون روابط در کلاس place نیست، این بخش رو باید به شکل ساده بنویسیم یا از جایی بگیریم
    // برای نمونه فرض می‌کنیم ارتباطات نداریم یا فقط نام مکان‌ها را می‌زنیم
    for ( auto& p : places) {
        cout << "| " << left << setw(colHalfWidth - 3) << p.name << "|";

        // نمایش Place Info: تعداد آیتم‌ها
        cout << " Items: " << p.get_num_of_items();

        // فاصله برای جای خالی
        int remainingSpace = colHalfWidth - 10 - (int)to_string(p.get_num_of_items()).length();

        cout << string(remainingSpace, ' ');

        cout << "|";

        // نمایش villager/monster info
        auto vm = p.show_villager_monster();
        string vmStr;
        for (size_t i = 0; i < vm.size(); ++i) {
            vmStr += vm[i];
            if (i != vm.size() - 1) vmStr += ", ";
        }
        cout << left << setw(colHalfWidth - 2) << vmStr << "|\n";
    }
    printFullBorder();

    // -------- Hero and Action Menu --------
    cout << "| " << left << setw(colQuarterWidth - 2) << "Hero 1 Info"
         << "| " << left << setw(colQuarterWidth - 2) << "Hero 2 Info"
         << "| " << left << setw(colQuarterWidth - 2) << "Terror Level"
         << "| " << left << setw(colQuarterWidth - 2) << "Action Menu"
         << "|\n";

    printFullBorder();

    vector<string> actionMenu = {
        "[0] Move", "[1] Guide", "[2] Pick Up",
        "[3] Advance", "[4] Defeat", "[5] Special Action",
        "[H] Help", "[Q] Quit"
    };

    size_t maxRows = max(actionMenu.size(), (size_t)4);

    for (size_t i = 0; i < maxRows; ++i) {
        // Hero1 info
        string h1Info;
        switch (i) {
            case 0: h1Info = "Name: " + h1->name; break;
            case 3: h1Info = "Position: " + h1->get_hero_place(); break;
            default: h1Info = ""; break;
        }

        // Hero2 info
        string h2Info;
        switch (i) {
            case 0: h2Info = "Name: " + h2->name; break;
            case 3: h2Info = "Position: " + h2->get_hero_place(); break;
            default: h2Info = ""; break;
        }

        // Terror Level
        string terrorStr = (i == 0) ? "Level: " + to_string(terrorLevel) : "";

        // Action menu
        string actionStr = (i < actionMenu.size()) ? actionMenu[i] : "";cout << "| " << left << setw(colQuarterWidth - 2) << h1Info
             << "| " << left << setw(colQuarterWidth - 2) << h2Info
             << "| " << left << setw(colQuarterWidth - 2) << terrorStr
             << "| " << left << setw(colQuarterWidth - 2) << actionStr
             << "|\n";
    }

    printFullBorder();
}
