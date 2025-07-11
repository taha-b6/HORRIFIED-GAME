#include "manage_box.hpp"

void HorrorGame::showHeroInfoPanel(Hero *h)
{
    sf::RenderWindow infoWindow(sf::VideoMode(1000, 700), "Hero Information", sf::Style::Close);
    infoWindow.setVerticalSyncEnabled(true);

    sf::Font infoFont;
    if (!infoFont.loadFromFile("DejaVuSans.ttf"))
    {
        std::cerr << "Failed to load font for info panel\n";
        return;
    }

    sf::Text heroName("Hero: " + h->name, infoFont, 36);
    heroName.setPosition(50, 30);
    heroName.setFillColor(sf::Color::White);

    sf::Text location("Location: " + h->get_hero_place(), infoFont, 36);
    location.setPosition(50, 80);
    location.setFillColor(sf::Color::White);

    sf::Text actions("Remaining Actions: " + std::to_string(remainingActions), infoFont, 36);
    actions.setPosition(50, 130);
    actions.setFillColor(sf::Color::White);

    sf::Text itemsTitle("Inventory Items:", infoFont, 32);
    itemsTitle.setPosition(50, 200);
    itemsTitle.setFillColor(sf::Color(200, 200, 100));

    sf::Text specialItemsTitle("Special Items:", infoFont, 32);
    specialItemsTitle.setPosition(50, 400);
    specialItemsTitle.setFillColor(sf::Color(200, 100, 100));

    sf::Text perksTitle("Perk Cards:", infoFont, 32);
    perksTitle.setPosition(550, 200);
    perksTitle.setFillColor(sf::Color(100, 100, 200));

    std::vector<std::string> regularItems = h->getRegularItems(); // تابعی که آیتم‌های عادی را برمی‌گرداند
    std::vector<std::string> specialItems = h->getSpecialItems(); // تابعی که آیتم‌های ویژه را برمی‌گرداند
    std::vector<std::string> perkCards = h->getPerkCards();       // تابعی که کارت‌های perk را برمی‌گرداند

    static size_t regularIndex = 0;
    static size_t specialIndex = 0;
    static size_t perkIndex = 0;

    sf::Text regularItemText("", infoFont, 28);
    regularItemText.setPosition(70, 250);
    regularItemText.setFillColor(sf::Color::White);

    sf::Text specialItemText("", infoFont, 28);
    specialItemText.setPosition(70, 450);
    specialItemText.setFillColor(sf::Color::White);

    sf::Text perkCardText("", infoFont, 28);
    perkCardText.setPosition(570, 250);
    perkCardText.setFillColor(sf::Color::White);

    sf::Text helpText("Press: Left/Right to navigate, Enter to exit", infoFont, 24);
    helpText.setPosition(300, 650);
    helpText.setFillColor(sf::Color(150, 150, 150));

    while (infoWindow.isOpen())
    {
        sf::Event event;
        while (infoWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                infoWindow.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Enter:
                    infoWindow.close();
                    break;

                case sf::Keyboard::Left:
                    // حرکت به عقب در وکتورها
                    if (regularIndex > 0)
                        regularIndex--;
                    if (specialIndex > 0)
                        specialIndex--;
                    if (perkIndex > 0)
                        perkIndex--;
                    break;

                case sf::Keyboard::Right:
                    // حرکت به جلو در وکتورها
                    if (!regularItems.empty() && regularIndex < regularItems.size() - 1)
                        regularIndex++;
                    if (!specialItems.empty() && specialIndex < specialItems.size() - 1)
                        specialIndex++;
                    if (!perkCards.empty() && perkIndex < perkCards.size() - 1)
                        perkIndex++;
                    break;

                default:
                    break;
                }
            }
        }

        if (!regularItems.empty())
        {
            regularItemText.setString(regularItems[regularIndex]);
        }
        else
        {
            regularItemText.setString("No regular items");
        }

        if (!specialItems.empty())
        {
            specialItemText.setString(specialItems[specialIndex]);
        }
        else
        {
            specialItemText.setString("No special items");
        }

        if (!perkCards.empty())
        {
            perkCardText.setString(perkCards[perkIndex]);
        }
        else
        {
            perkCardText.setString("No perk cards");
        }

        // رندرینگ
        infoWindow.clear(sf::Color(25, 15, 20));

        // رسم اطلاعات پایه
        infoWindow.draw(heroName);
        infoWindow.draw(location);
        infoWindow.draw(actions);

        // رسم عنوان بخش‌ها
        infoWindow.draw(itemsTitle);
        infoWindow.draw(specialItemsTitle);
        infoWindow.draw(perksTitle);

        // رسم آیتم‌ها
        infoWindow.draw(regularItemText);
        infoWindow.draw(specialItemText);
        infoWindow.draw(perkCardText);

        // رسم راهنما
        infoWindow.draw(helpText);

        // ----------------------------
        // بخشی که دوستتان باید کدهای لود کردن عکس را اضافه کند
        // اینجا موقعیت‌های مناسب برای نمایش عکس‌ها مشخص شده است

        // 1. عکس آیتم عادی (موقعیت: 70, 300)
        if (!regularItems.empty())
        {
            // sf::Texture itemTexture;
            // if (itemTexture.loadFromFile("items/" + regularItems[regularIndex] + ".png")) {
            //     sf::Sprite itemSprite(itemTexture);
            //     itemSprite.setPosition(70, 300);
            //     itemSprite.setScale(0.5f, 0.5f); // اندازه مناسب
            //     infoWindow.draw(itemSprite);
            // }
        }

        // 2. عکس آیتم ویژه (موقعیت: 70, 500)
        if (!specialItems.empty())
        {
            // مشابه بالا برای آیتم‌های ویژه
        }

        // 3. عکس کارت perk (موقعیت: 570, 300)
        if (!perkCards.empty())
        {
            // مشابه بالا برای کارت‌های perk
        }
        // ----------------------------

        infoWindow.display();
    }
}

void HorrorGame::set_actions_number(Hero *h)
{
    remainingActions = h->get_num_action();
    updateActionsText(); // به‌روزرسانی نمایش اکشن‌ها
}
void HorrorGame::run(Hero *h, bool &f)
{
    h->set_action();
    set_actions_number(h); // مقداردهی اولیه اکشن‌ها

    while (window.isOpen() && !f)
    {
        handleEvents(h, f);
        update();
        render();

        // اگر اکشن‌ها تمام شدند
        if (remainingActions <= 0)
        {
            actionText.setString("No more actions left!\nPress Enter to exit...");
            waitForUserAcknowledge();
            window.close();
            f = true;
        }
    }
}
void HorrorGame::render()
{
    // پاک کردن بافت صحنه
    sceneTexture.clear(sf::Color(15, 5, 10));

    // رسم پس‌زمینه ترسناک
    drawHorrorBackground(sceneTexture);

    // رسم عناصر دکور
    sceneTexture.draw(bloodStain);
    for (const auto &eye : floatingEyes)
    {
        sceneTexture.draw(eye);
    }

    // رسم عناصر UI
    sceneTexture.draw(titleText);
    sceneTexture.draw(actionText);
    sceneTexture.draw(inputBox);
    sceneTexture.draw(remainingActionsText);

    // نمایش متن ورودی کاربر
    sf::Text inputText(playerInput, font, 36);
    inputText.setFillColor(sf::Color::White);
    inputText.setPosition(410, 505);
    sceneTexture.draw(inputText);

    // پایان رندر به بافت
    sceneTexture.display();

    // رندر نهایی با اعمال شادر
    window.clear();
    horrorShader.setUniform("time", flickerClock.getElapsedTime().asSeconds());
    window.draw(sceneSprite, &horrorShader);
    window.display();
}
void HorrorGame::loadResources()
{
    // بارگذاری فونت ترسناک
    if (!font.loadFromFile("DejaVuSans.ttf"))
    {
        std::cerr << "Failed to load font\n";
    }

    // بارگذاری شادر ترسناک
    if (!horrorShader.loadFromFile("horror.frag", sf::Shader::Fragment))
    {
        std::cerr << "Failed to load shader\n";
    }

    bloodStain.setTexture(bloodTexture);
    bloodStain.setPosition(700, 500);
    bloodStain.setScale(0.7f, 0.7f);
    bloodStain.setRotation(-15);

    // ایجاد چشم‌های شناور
    createFloatingEyes();
}
void HorrorGame::createFloatingEyes()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> posX(50, 900);
    std::uniform_int_distribution<> posY(50, 600);
    std::uniform_int_distribution<> size(10, 30);

    for (int i = 0; i < 8; ++i)
    {
        sf::CircleShape eye(size(gen));
        eye.setFillColor(sf::Color(0, 255, 0, 150));
        eye.setPosition(posX(gen), posY(gen));
        floatingEyes.push_back(eye);
    }
}
void HorrorGame::setupScene()
{
    // عنوان بازی با افکت ترسناک
    titleText.setFont(font);
    titleText.setString("HORRIFIED");
    titleText.setCharacterSize(80);
    titleText.setFillColor(sf::Color(180, 0, 0));
    titleText.setOutlineColor(sf::Color::Black);
    titleText.setOutlineThickness(3);
    titleText.setPosition(280, 50);
    // متن نمایش تعداد اکشن‌های باقیمانده
    remainingActionsText.setFont(font);
    remainingActionsText.setCharacterSize(20);
    remainingActionsText.setFillColor(sf::Color(200, 50, 50));
    remainingActionsText.setPosition(700, 10);
    updateActionsText(); // به روزرسانی متن

    // متن راهنما برای اکشن‌ها
    std::string actions =
        "1. Move\n"
        "2. Guide\n"
        "3. Pickup\n"
        "4. Advance\n"
        "5. Defeat\n"
        "6. Special_Action\n"
        "7. Play Perk Cards\n"
        "8. Show Info";

    actionText.setFont(font);
    actionText.setString(actions);
    actionText.setCharacterSize(28);
    actionText.setFillColor(sf::Color(200, 200, 200));
    actionText.setPosition(150, 180);

    // کادر ورودی با ظاهر ترسناک
    inputBox.setSize(sf::Vector2f(150, 50));
    inputBox.setFillColor(sf::Color(40, 0, 0, 200));
    inputBox.setOutlineThickness(3);
    inputBox.setOutlineColor(sf::Color(120, 0, 0));
    inputBox.setPosition(400, 500);

    // آماده‌سازی رندر بافت
    sceneTexture.create(window.getSize().x, window.getSize().y);
    sceneSprite.setTexture(sceneTexture.getTexture());
}
void HorrorGame::updateActionsText()
{
    remainingActionsText.setString("Actions Left: " + std::to_string(remainingActions));
}
void HorrorGame::handleEvents(Hero *h, bool &f)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        else if (event.type == sf::Event::TextEntered)
        {
            if (event.text.unicode == '\b')
            {
                if (!playerInput.isEmpty())
                {
                    playerInput.erase(playerInput.getSize() - 1);
                }
            }
            else if (event.text.unicode == '\r')
            {
                processInput(h, f);
            }
            else if (event.text.unicode < 128)
            {
                playerInput += static_cast<char>(event.text.unicode);
            }
        }
    }
}
void HorrorGame::processInput(Hero *h, bool &f)
{
    if (playerInput.isEmpty())
        return;

    try
    {
        int actionId = std::stoi(playerInput.toAnsiString());
        if (actionId >= 1 && actionId <= 8)
        { // تغییر به 8
            executeAction(actionId, h, f);
        }
    }
    catch (...)
    {
        playerInput.clear();
    }
}
void HorrorGame::update()
{
    // به‌روزرسانی افکت چشمک زدن
    float flicker = 0.7f + 0.3f * std::sin(flickerClock.getElapsedTime().asSeconds() * 4);
    titleText.setFillColor(sf::Color(180 + 75 * flicker, 0, 0));

    // حرکت چشم‌های شناور
    float time = flickerClock.getElapsedTime().asSeconds();
    for (size_t i = 0; i < floatingEyes.size(); ++i)
    {
        float offsetX = std::sin(time * 2 + i) * 5;
        float offsetY = std::cos(time * 1.5f + i) * 3;
        floatingEyes[i].move(offsetX, offsetY);
    }
}

void HorrorGame::processActionInput(int actionId, const std::string &input,
                                    Hero *h, bool &f, place *p,
                                    const std::vector<std::string> &places,
                                    int &selectedOption, int &itemCount,
                                    std::string &selectedPlace,
                                    int &how_many_item,
                                    bool &actionCompleted,
                                    sf::Text &errorText)
{
    try
    {
        switch (actionId)
        {
        case 1: // Move
        {

            int placeNum = std::stoi(input);
            if (placeNum >= 0 && placeNum < places.size())
            {
                moving::set_new_location_graphical(h, font);
                actionCompleted = true;
            }
            else
            {
                errorText.setString("Invalid place number!");
            }
            break;
        }

        case 2: // Guide
        {
            int choice = std::stoi(input);
            if (choice == 1 || choice == 2)
            {
                std::string currentPlace = h->get_hero_place();
                if (choice == 1)
                {
                    moving::set_new_lacation_for_villager(h, currentPlace, currentPlace);
                }
                else
                {
                    moving::set_new_lacation_for_villager(h, currentPlace, "");
                }
                actionCompleted = true;
            }
            else
            {
                errorText.setString("Please enter 1 or 2 only!");
            }
            break;
        }
        case 3: // Pickup
        {
            try
            {
                itemCount = std::stoi(input);
                int availableItems = p->get_items_count();

                // Check if there are any items available
                if (availableItems <= 0)
                {
                    errorText.setString("No items available in this location!");
                    actionCompleted = false;
                    break;
                }

                // Validate input range
                if (itemCount <= 0)
                {
                    errorText.setString("Please enter a positive number (1-" +
                                        std::to_string(availableItems) + ")");
                    actionCompleted = false;
                    break;
                }

                if (itemCount > availableItems)
                {
                    errorText.setString("Only " + std::to_string(availableItems) +
                                        " items available!");
                    actionCompleted = false;
                    break;
                }

                // Process the pickup
                std::vector<item> temp = p->get_items(itemCount);
                if (temp.empty())
                {
                    errorText.setString("Failed to pick up items!");
                    actionCompleted = false;
                    break;
                }

                // Determine destination inventory
                bool isSpecialLocation = (h->get_hero_place() == "inn" ||
                                          h->get_hero_place() == "mansion" ||
                                          h->get_hero_place() == "barn" ||
                                          h->get_hero_place() == "laboratory" ||
                                          h->get_hero_place() == "institute");

                // Add items to appropriate inventory
                for (const auto &i : temp)
                {
                    if (isSpecialLocation)
                    {
                        h->items_for_distroy_invisble_man.push_back(i);
                    }
                    else
                    {
                        h->items.push_back(i);
                    }
                }

                // Success - no message needed as window will close
                actionCompleted = true;
            }
            catch (const std::exception &e)
            {
                errorText.setString("Please enter a valid number!");
                actionCompleted = false;
            }
            break;
        }
        case 4: // Advance
        {
            selectedOption = std::stoi(input);
            if (p->get_tabot())
            {
                if (selectedOption == 1)
                {
                    if (h->can_distroy(6, "red"))
                    {
                        p->destroy_tabot();
                        actionCompleted = true;
                    }
                    else
                    {
                        errorText.setString("Not enough items to destroy Tabot!");
                    }
                }
                else if (selectedOption == 2 && p->name == "percinct")
                {
                    how_many_item += h->items_for_distroy_invisble_man.size();
                    h->items_for_distroy_invisble_man.clear();
                    actionCompleted = true;
                }
                else
                {
                    errorText.setString("Invalid choice!");
                }
            }
            else
            {
                errorText.setString("No Tabot here!");
            }
            break;
        }

        case 5: // Defeat
        {
            selectedOption = std::stoi(input);
            int monsterType = p->get_monster_in_place();

            if ((monsterType == 1 && (selectedOption == 2 || selectedOption == 3)) ||
                (monsterType == 2 && selectedOption == 2) ||
                (monsterType == 3 && selectedOption == 3))
            {

                if (selectedOption == 2)
                {
                    if (how_many_item >= 5)
                    {
                        if (h->can_distroy(9, "red"))
                        {
                            p->kill_monster(1);
                            moving::kill_inviseble_man();
                            actionCompleted = true;
                        }
                        else
                        {
                            errorText.setString("Not enough items to kill Invisible Man!");
                        }
                    }
                    else
                    {
                        errorText.setString("You need at least 5 items!");
                    }
                }
                else if (selectedOption == 3)
                {
                    if (h->can_distroy(6, "yellow"))
                    {
                        p->kill_monster(2);
                        moving::kill_deracula();
                        actionCompleted = true;
                    }
                    else
                    {
                        errorText.setString("Not enough yellow items!");
                    }
                }
            }
            else
            {
                errorText.setString("Invalid choice for this monster!");
            }
            break;
        }

        case 6: // Special Action
        {
            if (h->name != "Archaeologist")
            {
                errorText.setString("You can't use special power as Mayor!");
                break;
            }

            if (selectedOption == -1)
            {
                // First step: select place
                int placeNum = std::stoi(input);
                if (placeNum >= 0 && placeNum <= 18)
                {
                    selectedPlace = to_string_place(placeNum);
                    place *ph = moving::get_near_place(h->get_hero_place());
                    bool isNeighbor = false;
                    for (const auto &n : ph->show_near_place())
                    {
                        if (selectedPlace == n)
                        {
                            isNeighbor = true;
                            break;
                        }
                    }

                    if (isNeighbor)
                    {
                        selectedOption = 0; // Move to next step
                    }
                    else
                    {
                        errorText.setString("Selected place is not your neighbor!");
                    }
                }
                else
                {
                    errorText.setString("Invalid place number (0-18)!");
                }
            }
            else
            {
                // Second step: select item count
                itemCount = std::stoi(input);
                if (itemCount >= 0)
                {
                    place *pl = moving::get_place(selectedPlace);
                    std::vector<item> temp = pl->get_items(itemCount);

                    for (const auto &i : temp)
                    {
                        if (h->get_hero_place() == "inn" || h->get_hero_place() == "mansion" ||
                            h->get_hero_place() == "barn" || h->get_hero_place() == "laboratory" ||
                            h->get_hero_place() == "institute")
                        {
                            h->items_for_distroy_invisble_man.push_back(i);
                        }
                        else
                        {
                            h->items.push_back(i);
                        }
                    }
                    actionCompleted = true;
                }
                else
                {
                    errorText.setString("Item count must be >= 0");
                }
            }
            break;
        }
        case 7: // Play Perk Cards
        {

            if (h->is_bag_perk_empty())
            {
                errorText.setString("No more perk cards left!");
                actionCompleted = true; // این خط تغییر کرد
                break;
            }

            perk_card *pc = h->get_one_perk();
            int perkType = which_perk_card(pc);

            if (input == "\b")
            { // Skip card
                h->delete_one_perk();
                delete pc;
                actionCompleted = false;
            }
            else if (input == "\r")
            { // Play card
                try
                {
                    switch (perkType)
                    {
                    case 1:
                    {
                        visit_from_the_detective *v = dynamic_cast<visit_from_the_detective *>(pc);
                        if (v)
                            v->play_perk(moving::get_invisible_man(), f);
                        break;
                    }
                    case 2:
                    {
                        break_of_dawn *b = dynamic_cast<break_of_dawn *>(pc);
                        if (b)
                            b->play_perk(f);
                        break;
                    }
                    case 3:
                    {
                        overstock *o = dynamic_cast<overstock *>(pc);
                        if (o)
                            o->play_perk(f);
                        break;
                    }
                    case 4:
                    {
                        late_into_the_night *l = dynamic_cast<late_into_the_night *>(pc);
                        if (l)
                            l->play_perk(h, f);
                        break;
                    }
                    case 5:
                    {
                        repel *r = dynamic_cast<repel *>(pc);
                        if (r)
                            r->play_perk(moving::get_deracula(), moving::get_invisible_man(), f);
                        break;
                    }
                    case 6:
                    {
                        hurry *hr = dynamic_cast<hurry *>(pc);
                        if (hr)
                            hr->play_perk(moving::get_first_hero(), moving::get_seccend_hero(), f);
                        break;
                    }
                    }
                    h->delete_one_perk();
                    delete pc;
                    actionCompleted = true;
                }
                catch (...)
                {
                    errorText.setString("Error playing perk card!");
                    actionCompleted = false;
                }
            }
            break;
        }
        case 8:                     // Show Info
            actionCompleted = true; // بدون انجام عملیات خاص، فقط نمایش اطلاعات
            break;

        default:
            errorText.setString("Invalid action!");
            break;
        }
    }
    catch (const std::exception &e)
    {
        errorText.setString("Error: " + std::string(e.what()));
    }
}
