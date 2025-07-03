#include <iostream>
#include <vector>
#include <string>
#include <variant>
#include <map>
#include "card.hpp"
#include "place.hpp"
#include <random>

//========================================================================================================================//
using namespace std;
vector<item_info> bag_items::items_in_the_game = {};
vector<item_info> bag_items::items_out_the_game = {};
vector<perk_card *> bag_perks::Perk_cards = {};

//========================================================================================================================//
bag_items::bag_items()
{
    item_info i;

    i = {"flower", "docks", "yellow", 2};
    items_in_the_game.push_back(i);
    i = {"flower", "docks", "yellow", 2};
    items_in_the_game.push_back(i);
    i = {"tarot deck", "camp", "yellow", 3};
    items_in_the_game.push_back(i);
    i = {"tarot deck", "camp", "yellow", 3};
    items_in_the_game.push_back(i);
    i = {"garlic", "inn", "yellow", 2};
    items_in_the_game.push_back(i);
    i = {"garlic", "inn", "yellow", 2};
    items_in_the_game.push_back(i);
    i = {"mirrored box", "mansion", "yellow", 3};
    items_in_the_game.push_back(i);
    i = {"mirrored box", "mansion", "yellow", 3};
    items_in_the_game.push_back(i);
    i = {"stake", "abbey", "yellow", 3};
    items_in_the_game.push_back(i);
    i = {"stake", "abbey", "yellow", 3};
    items_in_the_game.push_back(i);
    i = {"holy water", "church", "yellow", 4};
    items_in_the_game.push_back(i);
    i = {"holy water", "church", "yellow", 4};
    items_in_the_game.push_back(i);
    i = {"crucifix", "graveyard", "yellow", 2};
    items_in_the_game.push_back(i);
    i = {"crucifix", "graveyard", "yellow", 2};
    items_in_the_game.push_back(i);
    i = {"torch", "barn", "red", 2};
    items_in_the_game.push_back(i);
    i = {"torch", "barn", "red", 2};
    items_in_the_game.push_back(i);
    i = {"silver dagger", "tower", "red", 3};
    items_in_the_game.push_back(i);
    i = {"silver dagger", "tower", "red", 3};
    items_in_the_game.push_back(i);
    i = {"vampire book", "mansion", "red", 4};
    items_in_the_game.push_back(i);
    i = {"vampire book", "mansion", "red", 4};
    items_in_the_game.push_back(i);
    i = {"explosive vial", "cave", "red", 3};
    items_in_the_game.push_back(i);
    i = {"explosive vial", "cave", "red", 3};
    items_in_the_game.push_back(i);
    i = {"axe", "barn", "red", 2};
    items_in_the_game.push_back(i);
    i = {"axe", "barn", "red", 2};
    items_in_the_game.push_back(i);
    i = {"blood sample", "precinct", "red", 2};
    items_in_the_game.push_back(i);
    i = {"blood sample", "precinct", "red", 2};
    items_in_the_game.push_back(i);
    i = {"crossbow", "dungion", "red", 4};
    items_in_the_game.push_back(i);
    i = {"crossbow", "dungion", "red", 4};
    items_in_the_game.push_back(i);
    i = {"spear", "crypt", "red", 3};
    items_in_the_game.push_back(i);
    i = {"spear", "crypt", "red", 3};
    items_in_the_game.push_back(i);

    i = {"mind elixir", "laboratory", "blue", 2};
    items_in_the_game.push_back(i);
    i = {"mind elixir", "laboratory", "blue", 2};
    items_in_the_game.push_back(i);
    i = {"hypnotic charm", "institute", "blue", 3};
    items_in_the_game.push_back(i);
    i = {"hypnotic charm", "institute", "blue", 3};
    items_in_the_game.push_back(i);
    i = {"ghost mirror", "mansion", "blue", 2};
    items_in_the_game.push_back(i);
    i = {"ghost mirror", "mansion", "blue", 2};
    items_in_the_game.push_back(i);
    i = {"scientific journal", "institute", "blue", 4};
    items_in_the_game.push_back(i);
    i = {"scientific journal", "institute", "blue", 4};
    items_in_the_game.push_back(i);
    i = {"telepathy stone", "laboratory", "blue", 2};
    items_in_the_game.push_back(i);
    i = {"telepathy stone", "laboratory", "blue", 2};
    items_in_the_game.push_back(i);
    i = {"magnetic compass", "camp", "blue", 3};
    items_in_the_game.push_back(i);
    i = {"magnetic compass", "camp", "blue", 3};
    items_in_the_game.push_back(i);
    i = {"dream catcher", "inn", "blue", 2};
    items_in_the_game.push_back(i);
    i = {"dream catcher", "inn", "blue", 2};
    items_in_the_game.push_back(i);
    i = {"sacred scroll", "church", "yellow", 2};
    items_in_the_game.push_back(i);
    i = {"sacred scroll", "church", "yellow", 2};
    items_in_the_game.push_back(i);
    i = {"crystal ball", "tower", "yellow", 3};
    items_in_the_game.push_back(i);
    i = {"crystal ball", "tower", "yellow", 3};
    items_in_the_game.push_back(i);
    i = {"magic talisman", "cave", "yellow", 2};
    items_in_the_game.push_back(i);
    i = {"magic talisman", "cave", "yellow", 2};
    items_in_the_game.push_back(i);
    i = {"sun medallion", "graveyard", "yellow", 4};
    items_in_the_game.push_back(i);
    i = {"sun medallion", "graveyard", "yellow", 4};
    items_in_the_game.push_back(i);
    i = {"ancient relic", "musium", "red", 3};
    items_in_the_game.push_back(i);
    i = {"ancient relic", "musium", "red", 3};
    items_in_the_game.push_back(i);
    i = {"ritual knife", "crypt", "red", 2};
    items_in_the_game.push_back(i);
    i = {"ritual knife", "crypt", "red", 2};
    items_in_the_game.push_back(i);
    i = {"soul urn", "dungion", "red", 3};
    items_in_the_game.push_back(i);
    i = {"soul urn", "dungion", "red", 3};
    items_in_the_game.push_back(i);
    i = {"mental tonic", "hospital", "blue", 2};
    items_in_the_game.push_back(i);
    i = {"mental tonic", "hospital", "blue", 2};
    items_in_the_game.push_back(i);
    i = {"calming incense", "theatre", "blue", 2};
    items_in_the_game.push_back(i);
    i = {"calming incense", "theatre", "blue", 2};
    items_in_the_game.push_back(i);
    i = {"spirit lantern", "camp", "yellow", 2};
    items_in_the_game.push_back(i);
    i = {"spirit lantern", "camp", "yellow", 2};
    items_in_the_game.push_back(i);
    i = {"protective amulet", "precinct", "blue", 3};
    items_in_the_game.push_back(i);
    i = {"protective amulet", "precinct", "blue", 3};
    items_in_the_game.push_back(i);
    i = {"enchanted rope", "camp", "red", 2};
    items_in_the_game.push_back(i);
    i = {"enchanted rope", "camp", "red", 2};
    items_in_the_game.push_back(i);
}

//=============================================================================================================//

perk_card *bag_perks::get_one_perk_card()
{
    if (Perk_cards.empty())
        return nullptr;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, Perk_cards.size() - 1);

    int index = dist(gen);
    perk_card *original = Perk_cards[index];

    int count = original->get_count() - 1;
    original->set_count(count);

    if (count == 0)
    {
        delete original;
        Perk_cards.erase(Perk_cards.begin() + index);
        return nullptr;
    }

    perk_card *copy = original->clone();
    copy->set_count(1);

    return copy;
}

//========================================================================================================================//
void bag_perks::constract_perk_cart()
{
    perk_card *p = new visit_from_the_detective(3);
    Perk_cards.push_back(p);
    p = new break_of_dawn(3);
    Perk_cards.push_back(p);
    p = new overstock(4);
    Perk_cards.push_back(p);
    p = new late_into_the_night(4);
    Perk_cards.push_back(p);
    p = new repel(3);
    Perk_cards.push_back(p);
    p = new hurry(3);
    Perk_cards.push_back(p);
}
//========================================================================================================================//

void bag_items::put_Itme_IN_Place(int a)
{

    bool kodam_bag = false;
    while (a > 0)
    {
        if (items_in_the_game.empty())
        {
            item_info &currentItemInfo = items_out_the_game.back();
            place *target_place = moving::get_place(currentItemInfo.location);

            item newItem(currentItemInfo);

            target_place->items_list.push_back(newItem);
            items_in_the_game.push_back(currentItemInfo);
        }
        else
        {

            item_info &currentItemInfo = items_in_the_game.back();
            place *target_place = moving::get_place(currentItemInfo.location);

            item newItem(currentItemInfo);

            target_place->items_list.push_back(newItem);
            items_out_the_game.push_back(currentItemInfo);
            items_in_the_game.pop_back();
        }
        a--;
    }
}

//=======================================================================================
item::item(item_info b) : i(b)
{
}
//==================================================================================================
void bag_items::icraese_item_out_the_game(item i)
{
    items_out_the_game.push_back(i.get_item_for_out_the_game());
}
//========================================================================================================================//
string item::get_coler() const
{
    return i.color;
}
//========================================================================================================================//
int item::get_power() const
{
    return i.power;
}
//===============================================================================
item_info item::get_item_for_out_the_game()
{
    return i;
}
//========================================================================================================================//
void visit_from_the_detective::play_perk(Monster *monster, bool &)
{
    std::string name;
    bool success = false;

    while (!success)
    {
        std::cout << "\t ----------- Name the place where you want the invisible man to be : ---------- \n";
        std::cin >> name;

        try
        {
            moving::set_new_location(name);
            success = true;
        }
        catch (std::invalid_argument &e)
        {
            std::cerr << e.what() << std::endl;
            std::cerr << "Please try again with a valid place name.\n";
        }
    }
}
//========================================================================================================================//
void repel::play_perk(Monster *deracula, Monster *inviseble_man, bool &f)
{
    moving::set_new_location(2);
}
//========================================================================================================================//
void break_of_dawn::play_perk(bool &f)
{
    f = true;
    bag_items::put_Itme_IN_Place(2);
}
//========================================================================================================================//
void overstock::play_perk(bool &f)
{
    bag_items::put_Itme_IN_Place(2);
}
//========================================================================================================================//
void late_into_the_night::play_perk(Hero *hero, bool &f)
{
    hero->increase_action(2);
}
//========================================================================================================================//
void hurry::play_perk(Hero *archaeologist, Hero *mayor, bool &f)
{
    moving::set_new_location(1);
}
//========================================================================================================================//
void perk_card::set_count(int new_count)
{
    count = new_count;
}
//========================================================================================================================//
int &perk_card::get_count()
{
    return count;
}
//========================================================================================================================//
