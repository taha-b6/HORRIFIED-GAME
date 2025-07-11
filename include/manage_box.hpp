#ifndef MANAGE_BOX_HPP
#define MANAGE_BOX_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <iostream>
#include <string>
#include <vector>
#include <variant>
#include <memory>
#include <algorithm>
#include "character.hpp"
#include"item.hpp"
#include"perk.hpp"
#include "moving.hpp"
#include "place.hpp"
#include "monster_card.hpp"
#include <map>
class Hero;
class place;
class moving;
class Monster;
class HorrorGame
{
private:
    sf::RenderWindow window;
    sf::Font font;

    // عناصر UI ترسناک
    sf::Text titleText;
    sf::Text actionText;
    sf::RectangleShape inputBox;
    sf::String playerInput;

    // افکت‌های ویژه
    sf::Shader horrorShader;
    sf::RenderTexture sceneTexture;
    sf::Sprite sceneSprite;
    sf::Clock flickerClock;

    // عناصر دکور ترسناک
    sf::Texture bloodTexture;
    sf::Sprite bloodStain;
    std::vector<sf::CircleShape> floatingEyes;
    sf::Text remainingActionsText;
    int remainingActions = 0;

public:
    HorrorGame() : window(sf::VideoMode(1000, 700), "action box", sf::Style::Close)
    {
        loadResources();
        setupScene();
    }
    void set_actions_number(Hero *h);
    void run(Hero *h, bool &f);

private:
void showHeroInfoPanel(Hero* h);

void updateActionDisplay(int actionId, sf::Text& infoText, 
                       Hero* h, int selectedOption,
                       const std::string& selectedPlace);

    void processActionInput(int actionId, const std::string& input, 
                                  Hero* h, bool& f, place* p, 
                                  const std::vector<std::string>& places,
                                  int& selectedOption, int& itemCount,
                                  std::string& selectedPlace, 
                                  int& how_many_item,
                                  bool& actionCompleted,
                                  sf::Text& errorText)  ;                                   
    void loadResources();
    void createFloatingEyes();
    void setupScene();
    void updateActionsText();
    void handleEvents(Hero *h, bool &f);
    void update();
    void processInput(Hero *h, bool &f);
    void executeAction(int actionId, Hero *h, bool &f);
    void render();
    void drawHorrorBackground(sf::RenderTarget &target);
    void waitForUserAcknowledge();
    bool processAction(int actionId, const std::string& input, 
                             Hero* h, bool& f, int& selectedOption, 
                             int& itemCount, std::string& selectedPlace,
                             sf::Text& errorText);

};

bool createHeroesWithSelection(Hero *&hero1, Hero *&hero2);
#endif
