#include"etc.hpp"
using namespace std;
//==================================================
void gameboard_operation(){
    int terror_level=0;
    Hero* first = nullptr;
    Hero* seccend = nullptr;
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
            first = new Mayor;
            seccend= new Archaeologist ;
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
    place cave ("cave"); place comp("comp"); place precinct("precinct"); place inn("inn"); 
    place barn("barn"); place dungion("dungion"); place theatre("theatre"); place tower("tower");
    place mansion("mansion"); place docks("docks"); place abbey("abbey"); place shop("shop");
    place crypt("crypt"); place musium("musium"); place charch("charch"); place laboratory("laboratory");
    place hospital ("hospital"); place graveyard("graveyard"); place institute("institute");


    map <string , place> places{{"cave" , cave},{"comp" , comp} , {"precinct" , precinct}
    , {"inn" , inn},{"barn" , barn},{"dungion" , dungion},{"theatre", theatre},{"tower",tower},
     {"mansiom" , mansion},{"docks",docks},{"abbey",abbey},{"shop",shop},{"crypt",crypt},
    {"musium" , musium},{"charch",charch},{"laboratory",laboratory},{"hospital",hospital},
    {"graveyrd",graveyard},{"institute",institute}};

    moving mov(first ,seccend , deracula , invisble_man );

    while(1){
        first->do_action();

    }



}
