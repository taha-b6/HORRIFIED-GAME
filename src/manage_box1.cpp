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
void HorrorGame::updateActionDisplay(int actionId, sf::Text &infoText,
                                     Hero *h, int selectedOption,
                                     const std::string &selectedPlace)
{
    std::string infoStr;
    place *p = moving::get_place(h->get_hero_place());

    switch (actionId)
    {
    case 1:
    { // Move
        infoStr = "Please select destination from the map\n";
        infoStr += "Press Enter to open location selection";
        break;
    }

    case 2:
    { // Guide
        infoStr = "Current Location: " + h->get_hero_place() + "\n\n";
        infoStr += "Guide options:\n";
        infoStr += "1. Move villager within current location\n";
        infoStr += "2. Bring villager from nearby place\n";
        infoStr += "\nEnter your choice (1 or 2):";
        break;
    }

    case 3:
    { // Pickup
        infoStr = "Current Location: " + h->get_hero_place() + "\n\n";
        infoStr += "Special pickup locations for distroy Invisible man:\n";
        infoStr += "- Inn\n- Mansion\n- Barn\n- Laboratory\n- Institute\n";
        infoStr += "\nHow many items to pick up?";
        break;
    }

    case 4:
    { // Advance
        if (p->get_tabot())
        {
            infoStr = "Tabot found here!\n1. Destroy Tabot\n";
            if (p->name == "precinct")
            {
                infoStr += "2. Give items to kill invisible man\n";
            }
            infoStr += "\nEnter your choice:";
        }
        else
        {
            infoStr = "No Tabot here!";
        }
        break;
    }

    case 5:
    { // Defeat
        int monsterType = p->get_monster_in_place();
        infoStr = "Monster Status:\n";

        if (monsterType == 1)
        {
            infoStr += "Both monsters present!\n";
            infoStr += "2. Kill Invisible Man\n3. Kill Dracula\n";
        }
        else if (monsterType == 2)
        {
            infoStr += "Invisible Man present!\n";
            infoStr += "2. Kill Invisible Man\n";
        }
        else if (monsterType == 3)
        {
            infoStr += "Dracula present!\n";
            infoStr += "3. Kill Dracula\n";
        }
        else
        {
            infoStr += "No monsters here!";
        }
        infoStr += "\nEnter your choice:";
        break;
    }

    case 6:
    { // Special Action
        if (h->name != "Archaeologist")
        {
            infoStr = "You can't use special power as Mayor!";
            break;
        }

        if (selectedOption == -1)
        {
            infoStr = "Available Places (0-18):\n";
            for (int i = 0; i <= 18; ++i)
            {
                infoStr += std::to_string(i) + ". " + to_string_place(i) + "\n";
            }
            infoStr += "\nEnter place number:";
        }
        else
        {
            infoStr = "How many items to take from " + to_string_place(selectedOption) + "?";
        }
        break;
    }

    case 7:
    { // Play Perk Cards

        if (!h->is_bag_perk_empty())
        {

            perk_card *pc = h->get_one_perk();
            infoStr = "Perk Card: " + pc->name + "\n";
            infoStr += "Press Enter to play or Backspace to skip";
        }
        else
        {
            infoStr = "No perk cards left!";
        }
        break;
    }

    default:
        infoStr = "Invalid action!";
        break;
    }

    infoText.setString(infoStr);
}
void HorrorGame::drawHorrorBackground(sf::RenderTarget &target)
{
    // 1. گرادیانت تاریک با سایه‌های عمیق‌تر
    sf::VertexArray background(sf::Quads, 4);
    background[0].position = sf::Vector2f(0, 0);
    background[1].position = sf::Vector2f(target.getSize().x, 0);
    background[2].position = sf::Vector2f(target.getSize().x, target.getSize().y);
    background[3].position = sf::Vector2f(0, target.getSize().y);

    background[0].color = sf::Color(8, 1, 3);  // گوشه بالا چپ - تیره‌ترین
    background[1].color = sf::Color(18, 4, 8); // گوشه بالا راست
    background[2].color = sf::Color(4, 0, 1);  // گوشه پایین راست - تاریک
    background[3].color = sf::Color(12, 2, 6); // گوشه پایین چپ

    target.draw(background);

    // 2. خطوط ترسناک پویا (هر بار تصادفی)
    static sf::Clock lineClock;
    if (lineClock.getElapsedTime().asSeconds() > 0.5f)
    {
        lineClock.restart();

        sf::VertexArray lines(sf::Lines, 12); // افزایش تعداد خطوط
        for (int i = 0; i < 12; ++i)
        {
            lines[i].position = sf::Vector2f(
                std::rand() % target.getSize().x,
                std::rand() % target.getSize().y);

            // تنوع رنگی بیشتر برای خطوط
            int darkRed = 50 + std::rand() % 60;
            lines[i].color = sf::Color(darkRed, 0, 0, 80 + std::rand() % 60);
        }
        target.draw(lines);
    }

    // 3. لکه‌های خون تصادفی (تنها یک بار تولید می‌شوند)
    static std::vector<sf::CircleShape> bloodStains;
    static bool stainsInitialized = false;

    if (!stainsInitialized)
    {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        int stainCount = 10 + std::rand() % 10; // بین 10 تا 20 لکه

        for (int i = 0; i < stainCount; ++i)
        {
            sf::CircleShape stain(5.f + std::rand() % 20);
            stain.setPosition(
                std::rand() % (target.getSize().x - 40),
                std::rand() % (target.getSize().y - 40));

            // تنوع در رنگ و شفافیت خون
            int red = 70 + std::rand() % 60;
            int alpha = 30 + std::rand() % 70;
            stain.setFillColor(sf::Color(red, 0, 0, alpha));

            // چرخش تصادفی برای طبیعی‌تر شدن
            stain.setRotation(std::rand() % 360);

            bloodStains.push_back(stain);
        }
        stainsInitialized = true;
    }

    // رسم لکه‌های خون
    for (const auto &stain : bloodStains)
    {
        target.draw(stain);
    }

    // 4. سایه‌های متحرک (با استفاده از شیدر)
    static sf::Shader shadowShader;
    if (!shadowShader.isAvailable())
    {
        shadowShader.loadFromMemory(
            "uniform float time;"
            "void main() {"
            "    vec2 uv = gl_FragCoord.xy / vec2(800.0, 600.0);"
            "    float shade = 0.5 + 0.3 * sin(time * 1.5 + uv.x * 10.0);"
            "    gl_FragColor = vec4(0.0, 0.0, 0.0, shade * 0.3);"
            "}",
            sf::Shader::Fragment);
    }

    static sf::Clock shadowClock;
    shadowShader.setUniform("time", shadowClock.getElapsedTime().asSeconds());

    sf::RectangleShape shadowOverlay(sf::Vector2f(target.getSize().x, target.getSize().y));
    shadowOverlay.setFillColor(sf::Color::Black);
    target.draw(shadowOverlay, &shadowShader);

    // 5. ذرات گرد و غبار (پویا)
    static std::vector<sf::CircleShape> dustParticles;
    static sf::Clock dustClock;

    if (dustParticles.empty() || dustClock.getElapsedTime().asSeconds() > 0.1f)
    {
        dustClock.restart();

        // اضافه کردن ذرات جدید
        if (dustParticles.size() < 50)
        {
            sf::CircleShape particle(1.f + std::rand() % 3);
            particle.setPosition(
                std::rand() % target.getSize().x,
                std::rand() % target.getSize().y);
            particle.setFillColor(sf::Color(150, 150, 150, 30 + std::rand() % 60));
            dustParticles.push_back(particle);
        }

        // حرکت دادن ذرات موجود
        for (auto &particle : dustParticles)
        {
            particle.move(-0.5f + (std::rand() % 100) / 100.f,
                          -0.5f + (std::rand() % 100) / 100.f);

            // اگر ذره از صفحه خارج شد، جایگزین شود
            if (particle.getPosition().x < 0 || particle.getPosition().x > target.getSize().x ||
                particle.getPosition().y < 0 || particle.getPosition().y > target.getSize().y)
            {
                particle.setPosition(
                    std::rand() % target.getSize().x,
                    std::rand() % target.getSize().y);
            }
        }
    }

    // رسم ذرات گرد و غبار
    for (const auto &particle : dustParticles)
    {
        target.draw(particle);
    }
}
bool createHeroesWithSelection(Hero *&hero1, Hero *&hero2)
{
    // ایجاد پنجره با تنظیمات ضدعلیاسینگ
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1000, 700), "Hero Selection", sf::Style::Close, settings);

    // بارگذاری فونت
    sf::Font font;
    if (!font.loadFromFile("DejaVuSans.ttf"))
    {
        std::cerr << "Failed to load font\n";
        return false;
    }

    // ==================== UI Elements ====================
    // عنوان اصلی با سایز مناسب
    sf::Text title("SELECT YOUR HEROES", font, 42);
    title.setFillColor(sf::Color(180, 0, 0));
    title.setOutlineColor(sf::Color::Black);
    title.setOutlineThickness(2);
    title.setPosition(300, 30);
    title.setLineSpacing(1.2f);

    // فیلدهای ورودی با سایز کوچکتر
    sf::Text prompt1("Enter first player name:", font, 22);
    prompt1.setFillColor(sf::Color(200, 200, 200));
    prompt1.setPosition(150, 100);

    sf::Text prompt2("Enter second player name:", font, 22);
    prompt2.setFillColor(sf::Color(200, 200, 200));
    prompt2.setPosition(150, 160);

    // سوال زمان خوردن سیر
    sf::Text garlicPrompt("When did you eat garlic? (lower = ate later)", font, 20);
    garlicPrompt.setFillColor(sf::Color(200, 150, 150));
    garlicPrompt.setPosition(150, 220);

    // فیلدهای زمان
    sf::Text timePrompt1("", font, 20);
    timePrompt1.setFillColor(sf::Color(200, 200, 200));
    timePrompt1.setPosition(150, 280);

    sf::Text timePrompt2("", font, 20);
    timePrompt2.setFillColor(sf::Color(200, 200, 200));
    timePrompt2.setPosition(150, 320);

    // انتخاب نوع قهرمان
    sf::Text heroPrompt("", font, 22);
    heroPrompt.setFillColor(sf::Color(150, 200, 255));
    heroPrompt.setPosition(150, 380);

    // پیغام خطا
    sf::Text errorText("", font, 20);
    errorText.setFillColor(sf::Color(255, 80, 80));
    errorText.setPosition(150, 450);

    // ==================== Input Boxes ====================
    auto createInputBox = [](sf::Vector2f size, sf::Vector2f pos)
    {
        sf::RectangleShape box(size);
        box.setFillColor(sf::Color(40, 0, 0, 180));
        box.setOutlineThickness(1.5f);
        box.setOutlineColor(sf::Color(120, 0, 0));
        box.setPosition(pos);
        return box;
    };

    // کادرهای ورودی با اندازه‌های متناسب
    sf::RectangleShape inputBox1 = createInputBox(sf::Vector2f(350, 32), sf::Vector2f(500, 100));
    sf::RectangleShape inputBox2 = createInputBox(sf::Vector2f(350, 32), sf::Vector2f(500, 160));
    sf::RectangleShape timeBox1 = createInputBox(sf::Vector2f(120, 32), sf::Vector2f(500, 280));
    sf::RectangleShape timeBox2 = createInputBox(sf::Vector2f(120, 32), sf::Vector2f(500, 320));
    sf::RectangleShape heroBox = createInputBox(sf::Vector2f(250, 32), sf::Vector2f(510, 410));
    // ==================== State Management ====================
    sf::String player1Name, player2Name;
    sf::String time1Input, time2Input, heroInput;
    int time1 = 0, time2 = 0;
    std::string selectedHeroType;
    bool selectionComplete = false;

    enum class State
    {
        Name1,
        Name2,
        Time1,
        Time2,
        Hero,
        Done
    };
    State state = State::Name1;

    // ==================== Main Loop ====================
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return false;
            }

            // پردازش ورودی‌ها
            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == '\b')
                { // Backspace
                    switch (state)
                    {
                    case State::Name1:
                        if (!player1Name.isEmpty())
                            player1Name.erase(player1Name.getSize() - 1);
                        break;
                    case State::Name2:
                        if (!player2Name.isEmpty())
                            player2Name.erase(player2Name.getSize() - 1);
                        break;
                    case State::Time1:
                        if (!time1Input.isEmpty())
                            time1Input.erase(time1Input.getSize() - 1);
                        break;
                    case State::Time2:
                        if (!time2Input.isEmpty())
                            time2Input.erase(time2Input.getSize() - 1);
                        break;
                    case State::Hero:
                        if (!heroInput.isEmpty())
                            heroInput.erase(heroInput.getSize() - 1);
                        break;
                    default:
                        break;
                    }
                }
                else if (event.text.unicode == '\r')
                { // Enter
                    switch (state)
                    {
                    case State::Name1:
                        if (!player1Name.isEmpty())
                        {
                            state = State::Name2;
                            timePrompt1.setString("Time for " + player1Name.toAnsiString() + ":");
                        }
                        break;
                    case State::Name2:
                        if (!player2Name.isEmpty())
                        {
                            state = State::Time1;
                            timePrompt2.setString("Time for " + player2Name.toAnsiString() + ":");
                        }
                        break;
                    case State::Time1:
                        if (!time1Input.isEmpty())
                        {
                            try
                            {
                                time1 = std::stoi(time1Input.toAnsiString());
                                state = State::Time2;
                            }
                            catch (...)
                            {
                                errorText.setString("Invalid time! Numbers only");
                            }
                        }
                        break;
                    case State::Time2:
                        if (!time2Input.isEmpty())
                        {
                            try
                            {
                                time2 = std::stoi(time2Input.toAnsiString());
                                heroPrompt.setString((time1 <= time2 ? player1Name : player2Name) +
                                                     ", choose hero (mayor/archaeologist):");
                                state = State::Hero;
                            }
                            catch (...)
                            {
                                errorText.setString("Invalid time! Numbers only");
                            }
                        }
                        break;
                    case State::Hero:
                        if (!heroInput.isEmpty())
                        {
                            std::string heroChoice = heroInput.toAnsiString();
                            std::transform(heroChoice.begin(), heroChoice.end(), heroChoice.begin(), ::tolower);

                            if (heroChoice == "mayor" || heroChoice == "archaeologist")
                            {
                                selectedHeroType = heroChoice;
                                selectionComplete = true;
                                window.close();
                            }
                            else
                            {
                                errorText.setString("Invalid hero! Choose 'mayor' or 'archaeologist'");
                            }
                        }
                        break;
                    default:
                        break;
                    }
                }
                else if (isalpha(event.text.unicode) && (state == State::Name1 || state == State::Name2))
                {
                    if (state == State::Name1)
                        player1Name += event.text.unicode;
                    else
                        player2Name += event.text.unicode;
                }
                else if (isdigit(event.text.unicode) && (state == State::Time1 || state == State::Time2))
                {
                    if (state == State::Time1)
                        time1Input += event.text.unicode;
                    else
                        time2Input += event.text.unicode;
                }
                else if (isalpha(event.text.unicode) && state == State::Hero)
                {
                    heroInput += event.text.unicode;
                }
                // [کد پردازش ورودی مانند قبل]
                // (همان منطق قبلی برای مدیریت ورودی‌ها)
            }
        }

        // ==================== Rendering ====================
        window.clear(sf::Color(25, 15, 20));

        // رسم عناصر UI
        window.draw(title);
        window.draw(prompt1);
        window.draw(prompt2);
        window.draw(garlicPrompt);
        window.draw(timePrompt1);
        window.draw(timePrompt2);
        window.draw(heroPrompt);
        window.draw(errorText);

        // رسم کادرهای ورودی
        window.draw(inputBox1);
        window.draw(inputBox2);
        window.draw(timeBox1);
        window.draw(timeBox2);
        window.draw(heroBox);

        // نمایش متن‌های وارد شده
        sf::Text name1Text(player1Name, font, 24);
        name1Text.setPosition(510, 100);
        window.draw(name1Text);

        sf::Text name2Text(player2Name, font, 24);
        name2Text.setPosition(510, 160);
        window.draw(name2Text);

        sf::Text time1Text(time1Input, font, 24);
        time1Text.setPosition(510, 280);
        window.draw(time1Text);

        sf::Text time2Text(time2Input, font, 24);
        time2Text.setPosition(510, 320);
        window.draw(time2Text);

        sf::Text heroText(heroInput, font, 24);
        heroText.setFillColor(sf::Color::White); // اضافه کردن رنگ سفید برای خوانایی بهتر
        heroText.setPosition(510, 405);          // تنظیم موقعیت دقیق تر
        window.draw(heroText);

        window.display();
    }

    // ==================== Hero Creation ====================
    if (selectionComplete)
    {
        std::string priorityPlayer = (time1 <= time2) ? player1Name.toAnsiString() : player2Name.toAnsiString();

        if (selectedHeroType == "mayor")
        {
            hero1 = new Mayor;
            hero2 = new Archaeologist;
        }
        if (selectedHeroType == "archaeologist")
        {
            hero2 = new Mayor;
            hero1 = new Archaeologist;
        }
        return true;
    }

    return false;
}
void HorrorGame::waitForUserAcknowledge()
{
    sf::RenderWindow ackWindow(sf::VideoMode(600, 200), "Message", sf::Style::Close);

    sf::Text messageText(actionText.getString(), font, 30);
    messageText.setPosition(50, 50);

    sf::Text promptText("Press Enter to continue...", font, 25);
    promptText.setPosition(150, 120);

    bool acknowledged = false;
    while (ackWindow.isOpen() && !acknowledged)
    {
        sf::Event event;
        while (ackWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                ackWindow.close();
                window.close(); // اضافه کردن این خط
            }
            else if (event.type == sf::Event::KeyPressed &&
                     event.key.code == sf::Keyboard::Enter)
            {
                acknowledged = true;
                ackWindow.close();
                window.close(); // اضافه کردن این خط
            }
        }

        ackWindow.clear(sf::Color(20, 5, 10));
        ackWindow.draw(messageText);
        ackWindow.draw(promptText);
        ackWindow.display();
    }
}
void HorrorGame::executeAction(int actionId, Hero *h, bool &gameEnded)
{
    if (remainingActions <= 0 && actionId != 7 && actionId != 8)
    {
        actionText.setString("No more actions left!\nPress Enter to exit...");
        waitForUserAcknowledge();
        gameEnded = true;
            window.close(); 
        return;
    }

    sf::RenderWindow actionWindow(sf::VideoMode(800, 600), "Action", sf::Style::Close);
    actionWindow.setVerticalSyncEnabled(true);

    // Setup UI elements
    sf::Text titleText("Action Menu", font, 40);
    titleText.setFillColor(sf::Color(180, 0, 0));
    titleText.setOutlineColor(sf::Color::Black);
    titleText.setOutlineThickness(2);
    titleText.setPosition(300, 30);

    sf::RectangleShape inputBox(sf::Vector2f(400, 40));
    inputBox.setFillColor(sf::Color(40, 0, 0, 180));
    inputBox.setOutlineColor(sf::Color(150, 0, 0));
    inputBox.setOutlineThickness(2);
    inputBox.setPosition(390, 400);

    sf::Text inputText("", font, 30);
    inputText.setFillColor(sf::Color::White);
    inputText.setPosition(391, 405);

    sf::Text infoText("", font, 25);
    infoText.setFillColor(sf::Color(200, 200, 100));
    infoText.setPosition(150, 100);
    infoText.setLineSpacing(1.5f);

    sf::Text errorText("", font, 25);
    errorText.setFillColor(sf::Color(255, 80, 80));
    errorText.setPosition(150, 350);

    std::string userInput;
    bool actionCompleted = false;
    int selectedOption = -1;
    int itemCount = 0;
    std::string selectedPlace;
    static int how_many_item = 0;

    // Update display with initial action info
    updateActionDisplay(actionId, infoText, h, selectedOption, selectedPlace);

    // حلقه اصلی اکشن
    while (actionWindow.isOpen() && !gameEnded && !actionCompleted)
    {
        sf::Event event;
        while (actionWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                actionWindow.close();
                return;
            }

            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == '\b') // Backspace
                {
                    if (!userInput.empty())
                        userInput.pop_back();
                }
                else if (event.text.unicode == '\r') // Enter
                {
                    try
                    {
                        place *p = moving::get_place(h->get_hero_place());

                        switch (actionId)
                        {
                        case 1:
                        { // Move

                            // فقط پنجره انتخاب مکان را باز می‌کنیم و نیازی به پردازش ورودی نیست
                            moving::set_new_location_graphical(h, font);
                            actionCompleted = true;
                            break;
                        }

                        case 2:
                        { // Guide
                            int choice = std::stoi(userInput);
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
                                place *currentPlace = moving::get_place(h->get_hero_place());
                                int availableItems = currentPlace->get_items_count();

                                // Check if there are any items available
                                if (availableItems <= 0)
                                {
                                    errorText.setString("No items available in this location!");
                                    break;
                                }

                                itemCount = std::stoi(userInput);

                                // Validate input range
                                if (itemCount <= 0)
                                {
                                    errorText.setString("Please enter a positive number!");
                                    break;
                                }

                                if (itemCount > availableItems)
                                {
                                    errorText.setString("Only " + std::to_string(availableItems) +
                                                        " items available!");
                                    break;
                                }

                                // Process the pickup
                                std::vector<item> temp = currentPlace->get_items(itemCount);
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

                                // Success message
                                std::string dest = (h->get_hero_place() == "inn" || h->get_hero_place() == "mansion" ||
                                                    h->get_hero_place() == "barn" || h->get_hero_place() == "laboratory" ||
                                                    h->get_hero_place() == "institute")
                                                       ? "Invisible Man stash"
                                                       : "inventory";

                                infoText.setString("Picked up " + std::to_string(itemCount) +
                                                   " items to your " + dest + "!");
                                actionWindow.display();
                                sf::sleep(sf::seconds(1.5f)); // Show success message briefly
                                actionCompleted = true;
                            }
                            catch (const std::exception &e)
                            {
                                errorText.setString("Invalid number!");
                            }
                            break;
                        }
                        case 4:
                        { // Advance
                            selectedOption = std::stoi(userInput);
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
                                else if (selectedOption == 2 && p->name == "precinct")
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

                        case 5:
                        { // Defeat
                            selectedOption = std::stoi(userInput);
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

                        case 6:
                        { // Special Action
                            if (h->name != "Archaeologist")
                            {
                                errorText.setString("You can't use special power as Mayor!");
                                break;
                            }

                            if (selectedOption == -1)
                            {
                                int placeNum = std::stoi(userInput);
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
                                        selectedOption = placeNum;
                                        updateActionDisplay(actionId, infoText, h, selectedOption, selectedPlace);
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
                                itemCount = std::stoi(userInput);
                                if (itemCount >= 0)
                                {
                                    place *pl = moving::get_place(selectedPlace);
                                    std::vector<item> temp = pl->get_items(itemCount);

                                    for (const auto &i : temp)
                                    {
                                        if (h->get_hero_place() == "inn" ||
                                            h->get_hero_place() == "mansion" ||
                                            h->get_hero_place() == "barn" ||
                                            h->get_hero_place() == "laboratory" ||
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
                                    selectedOption = -1; // Reset for next use
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
                                infoText.setString("No more perk cards left!");
                                actionWindow.display();
                                sf::sleep(sf::seconds(1.5f)); // نمایش پیام به مدت 1.5 ثانیه
                                actionCompleted = true;
                                break;
                            }

                            perk_card *pc = h->get_one_perk();
                            int perkType = which_perk_card(pc);
                            // نمایش اطلاعات کارت
                            infoText.setString("Perk Card: " + pc->name + "\n\n" +
                                               "\n\nPress Enter to play or Backspace to skip");

                            bool cardProcessed = false;
                            while (!cardProcessed && actionWindow.isOpen())
                            {
                                sf::Event perkEvent;
                                while (actionWindow.pollEvent(perkEvent))
                                {
                                    if (perkEvent.type == sf::Event::Closed)
                                    {
                                        actionWindow.close();
                                        return;
                                    }
                                    else if (perkEvent.type == sf::Event::KeyPressed)
                                    {
                                        if (perkEvent.key.code == sf::Keyboard::Enter)
                                        {
                                            try
                                            {
                                                switch (perkType)
                                                {
                                                case 1:
                                                { // visit_from_the_detective
                                                    visit_from_the_detective *v = dynamic_cast<visit_from_the_detective *>(pc);
                                                    if (v)
                                                        v->play_perk(moving::get_invisible_man(), gameEnded);
                                                    break;
                                                }
                                                case 2:
                                                { // break_of_dawn
                                                    break_of_dawn *b = dynamic_cast<break_of_dawn *>(pc);
                                                    if (b)
                                                        b->play_perk(gameEnded);
                                                    break;
                                                }
                                                case 3:
                                                { // overstock
                                                    overstock *o = dynamic_cast<overstock *>(pc);
                                                    if (o)
                                                        o->play_perk(gameEnded);
                                                    break;
                                                }
                                                case 4:
                                                { // late_into_the_night
                                                    late_into_the_night *l = dynamic_cast<late_into_the_night *>(pc);
                                                    if (l)
                                                        l->play_perk(h, gameEnded);
                                                    break;
                                                }
                                                case 5:
                                                { // repel
                                                    repel *r = dynamic_cast<repel *>(pc);
                                                    if (r)
                                                        r->play_perk(moving::get_deracula(), moving::get_invisible_man(), gameEnded);
                                                    break;
                                                }
                                                case 6:
                                                { // hurry
                                                    hurry *hr = dynamic_cast<hurry *>(pc);
                                                    if (hr)
                                                        hr->play_perk(moving::get_first_hero(), moving::get_seccend_hero(), gameEnded);
                                                    break;
                                                }
                                                }
                                                h->delete_one_perk();
                                                delete pc;
                                                actionCompleted = true;
                                                cardProcessed = true;
                                            }
                                            catch (...)
                                            {
                                                errorText.setString("Error playing perk card!");
                                                h->delete_one_perk();
                                                delete pc;
                                                cardProcessed = true;
                                            }
                                        }
                                        else if (perkEvent.key.code == sf::Keyboard::BackSpace)
                                        {
                                            h->delete_one_perk();
                                            delete pc;
                                            actionCompleted = false;
                                            cardProcessed = true;
                                        }
                                    }
                                }

                                // رندر کردن
                                actionWindow.clear(sf::Color(15, 5, 10));
                                drawHorrorBackground(actionWindow);
                                actionWindow.draw(titleText);
                                actionWindow.draw(infoText);
                                actionWindow.draw(errorText);
                                actionWindow.display();
                            }
                            break;
                        }
                        case 8: // Show Info
                        {
                            showHeroInfoPanel(h);
                            actionCompleted = true;
                            break;
                        }
                        default:
                            errorText.setString("Invalid action!");
                            break;
                        }
                    }
                    catch (...)
                    {
                        errorText.setString("Invalid input!");
                    }

                    if (actionCompleted)
                    {
                        actionWindow.close();
                    }
                    userInput.clear();
                }
                else if (event.text.unicode < 128)
                {
                    userInput += static_cast<char>(event.text.unicode);
                }
            }
        }

        // Update display
        inputText.setString(userInput);

        // Render
        actionWindow.clear(sf::Color(15, 5, 10));

        // Draw background elements first
        drawHorrorBackground(actionWindow);

        // Then draw text elements
        actionWindow.draw(titleText);
        actionWindow.draw(infoText);
        actionWindow.draw(errorText);

        // Draw input elements last
        actionWindow.draw(inputBox);
        actionWindow.draw(inputText);

        actionWindow.display();
    }

// Post-action processing
if (actionCompleted)
{
    // فقط اگر اکشن 7 یا 8 نبود، از تعداد اکشن‌ها کم شود
    if (actionId != 7 && actionId != 8)
    {
        remainingActions--;
        h->reduction_action();
        updateActionsText();

        if (remainingActions <= 0)
        {
            actionText.setString("No more actions left!\nPress Enter to exit...");
            waitForUserAcknowledge();
            gameEnded = true;
        }
    }
}
}
bool HorrorGame::processAction(int actionId, const std::string &input,
                               Hero *h, bool &f, int &selectedOption,
                               int &itemCount, std::string &selectedPlace,
                               sf::Text &errorText)
{
    try
    {
        place *p = moving::get_place(h->get_hero_place());
        static int how_many_item = 0;

        switch (actionId)
        {
        case 1:
        { // Move

            moving::set_new_location_graphical(h, font);
            return true;
        }

        case 2:
        { // Guide
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
                return true;
            }
            else
            {
                errorText.setString("Please enter 1 or 2 only!");
                return false;
            }
        }

        case 3: // Pickup
        {
            itemCount = std::stoi(input);
            place *currentPlace = moving::get_place(h->get_hero_place());

            // بررسی وجود آیتم‌ها در مکان فعلی
            if (currentPlace->get_items(1).empty())
            {
                errorText.setString("No items available in this place!");
                return false;
            }

            if (itemCount <= 0)
            {
                errorText.setString("Item count must be > 0");
                return false;
            }

            // بررسی تعداد آیتم‌های درخواستی
            if (itemCount > currentPlace->get_items_count())
            {
                errorText.setString("Not enough items! Only " +
                                    std::to_string(currentPlace->get_items_count()) +
                                    " available");
                return false;
            }

            std::vector<item> temp = currentPlace->get_items(itemCount);
            for (const auto &i : temp)
            {
                //قرار شد کل مکان ها با اسم ایتم ها بیاد پس اینجا به تابع نیاز نیست و باید قیل نمایش نقشه از ان تابع get_name_of_items()استفاده کرد
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
            return true;
        }
        case 4:
        { // Advance
            selectedOption = std::stoi(input);
            if (p->get_tabot())
            {
                if (selectedOption == 1)
                {
                    if (h->can_distroy(6, "red"))
                    {
                        //اینجا باید تابعی که که اسم مکان میدهم و تابوت ان مکان را از روی نقشه پاک میکند صدا زده شود
                        // اسم تابع(h->get_hero_place)
                        p->destroy_tabot();
                        
                        return true;
                    }
                    else
                    {
                        errorText.setString("Not enough items to destroy Tabot!");
                        return false;
                    }
                }
                else if (selectedOption == 2 && p->name == "percinct")
                {
                    how_many_item += h->items_for_distroy_invisble_man.size();
                    h->items_for_distroy_invisble_man.clear();
                    return true;
                }
                else
                {
                    errorText.setString("Invalid choice!");
                    return false;
                }
            }
            else
            {
                errorText.setString("No Tabot here!");
                return false;
            }
        }

        case 5:
        { // Defeat
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
                            return true;
                        }
                        else
                        {
                            errorText.setString("Not enough items to kill Invisible Man!");
                            return false;
                        }
                    }
                    else
                    {
                        errorText.setString("You need at least 5 items!");
                        return false;
                    }
                }
                else if (selectedOption == 3)
                {
                    if (h->can_distroy(6, "yellow"))
                    {
                        p->kill_monster(2);
                        moving::kill_deracula();
                        return true;
                    }
                    else
                    {
                        errorText.setString("Not enough yellow items!");
                        return false;
                    }
                }
            }
            else
            {
                errorText.setString("Invalid choice for this monster!");
                return false;
            }
            break;
        }

        case 6:
        { // Special Action
            if (h->name != "Archaeologist")
            {
                errorText.setString("You can't use special power as Mayor!");
                return false;
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
                        return false;       // Still need item count
                    }
                    else
                    {
                        errorText.setString("Selected place is not your neighbor!");
                        return false;
                    }
                }
                else
                {
                    errorText.setString("Invalid place number (0-18)!");
                    return false;
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
                    selectedOption = -1; // Reset for next use
                    return true;
                }
                else
                {
                    errorText.setString("Item count must be >= 0");
                    return false;
                }
            }
        }

        case 7: // Play Perk Cards
        {

            if (h->is_bag_perk_empty())
            {
                errorText.setString("No more perk cards left!");
                return true; // این خط تغییر کرد
            }

            perk_card *pc = h->get_one_perk();
            int perkType = which_perk_card(pc);

            if (input == "\b")
            { // Skip card
                h->delete_one_perk();
                delete pc;
                return false;
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
                    return true;
                }
                catch (...)
                {
                    errorText.setString("Error playing perk card!");
                    return false;
                }
            }
            break;
        }
        case 8:          // Show Info
            return true; // بدون انجام عملیات خاص

        default:
            errorText.setString("Invalid action!");
            return false;
        }
    }
    catch (const std::exception &e)
    {
        errorText.setString("Error: " + std::string(e.what()));
        return false;
    }
    return false;
}

void updateActionDisplay(int actionId, sf::Text &infoText,
                         Hero *h, int selectedOption,
                         const std::string &selectedPlace)
{
    std::string infoStr;
    place *p = moving::get_place(h->get_hero_place());
    static std::vector<std::string> places = {"precinct", "mansion", "musium", "inn", "camp", "theatre",
                                              "cave", "institute", "crypt", "barn", "dungion", "docks",
                                              "tower", "laboratory", "graveyard", "hospital", "abbey",
                                              "church", "shop"};

    switch (actionId)
    {
    case 1:
    { // Move

        infoStr = "Available Places:\n";
        for (size_t i = 0; i < places.size(); i++)
        {
            infoStr += std::to_string(i) + ". " + places[i] + "\n";
        }
        infoStr += "\nEnter destination number (0-" + std::to_string(places.size() - 1) + "):";
        break;
    }

    case 2:
    { // Guide
        infoStr = "Current Location: " + h->get_hero_place() + "\n\n";
        infoStr += "Guide options:\n";
        infoStr += "1. Move villager within current location\n";
        infoStr += "2. Bring villager from nearby place\n";
        infoStr += "\nEnter your choice (1 or 2):";
        break;
    }

    case 3: // Pickup
    {
        place *p = moving::get_place(h->get_hero_place());
        int availableItems = p->get_items_count();

        infoStr = "┌───────────────────────────────────────┐\n";
        infoStr += "│         PICKUP ITEMS MENU          │\n";
        infoStr += "├───────────────────────────────────────┤\n";
        infoStr += "│ Current Location: " + h->get_hero_place();
        infoStr += std::string(25 - h->get_hero_place().length(), ' ') + "│\n";

        if (availableItems <= 0)
        {
            infoStr += "│                                       │\n";
            infoStr += "│      NO ITEMS AVAILABLE HERE!        │\n";
            infoStr += "│                                       │\n";
        }
        else
        {
            infoStr += "│ Available items: " + std::to_string(availableItems);
            infoStr += std::string(24 - std::to_string(availableItems).length(), ' ') + "│\n";
            infoStr += "│                                       │\n";

            if (h->get_hero_place() == "inn" || h->get_hero_place() == "mansion" ||
                h->get_hero_place() == "barn" || h->get_hero_place() == "laboratory" ||
                h->get_hero_place() == "institute")
            {
                infoStr += "│ Items go to Invisible Man stash    │\n";
            }
            else
            {
                infoStr += "│ Items go to your main inventory    │\n";
            }

            infoStr += "│                                       │\n";
            infoStr += "│ Enter amount (1-" + std::to_string(availableItems) + "): ";
            infoStr += std::string(17 - std::to_string(availableItems).length(), ' ') + "│\n";
        }

        infoStr += "└───────────────────────────────────────┘";

        // Additional instructions if needed
        if (availableItems > 0)
        {
            infoStr += "\n\nNote: Enter 0 to cancel pickup";
        }
        else
        {
            infoStr += "\n\nPress Enter to return to main menu";
        }
        break;
    }

    case 4:
    { // Advance
        if (p->get_tabot())
        {
            infoStr = "Tabot found here!\n1. Destroy Tabot\n";
            if (p->name == "percinct")
            {
                infoStr += "2. Give items to kill invisible man\n";
            }
            infoStr += "\nEnter your choice:";
        }
        else
        {
            infoStr = "No Tabot here!";
        }
        break;
    }

    case 5:
    { // Defeat
        int monsterType = p->get_monster_in_place();
        infoStr = "Monster Status:\n";

        if (monsterType == 1)
        {
            infoStr += "Both monsters present!\n";
            infoStr += "2. Kill Invisible Man\n3. Kill Dracula\n";
        }
        else if (monsterType == 2)
        {
            infoStr += "Invisible Man present!\n";
            infoStr += "2. Kill Invisible Man\n";
        }
        else if (monsterType == 3)
        {
            infoStr += "Dracula present!\n";
            infoStr += "3. Kill Dracula\n";
        }
        else
        {
            infoStr += "No monsters here!";
        }
        infoStr += "\nEnter your choice:";
        break;
    }

    case 6:
    { // Special Action
        if (h->name != "Archaeologist")
        {
            infoStr = "You can't use special power as Mayor!";
            break;
        }

        if (selectedOption == -1)
        {
            infoStr = "Available Places (0-18):\n";
            for (int i = 0; i <= 18; ++i)
            {
                try
                {
                    infoStr += std::to_string(i) + ". " + to_string_place(i) + "\n";
                }
                catch (...)
                {
                    infoStr += std::to_string(i) + ". Unknown\n";
                }
            }
            infoStr += "\nEnter place number:";
        }
        else
        {
            try
            {
                std::string currentPlaceName = to_string_place(selectedOption);
                infoStr = "How many items to take from " + currentPlaceName + "?";
            }
            catch (...)
            {
                infoStr = "Invalid place selected!\nEnter place number again:";
            }
        }
        break;
    }

    case 7: // Play Perk Cards
    {
        if (h->is_bag_perk_empty())
        {
            infoStr = "No perk cards left!";
        }
        else
        {
            perk_card *pc = h->get_one_perk();
            infoStr = "Perk Card: " + pc->name + "\n";
            infoStr += "Press Enter to play or Backspace to skip";
        }

        break;
    }
    case 8: // Show Info
    {
        infoStr = "Hero Information:\n";
        infoStr += "Name: " + h->name + "\n";
        infoStr += "Location: " + h->get_hero_place() + "\n";
        infoStr += "Items: " + std::to_string(h->items.size()) + "\n";
        infoStr += "Special Items: " + std::to_string(h->items_for_distroy_invisble_man.size()) + "\n";
        infoStr += "\nPress Enter to continue...";
        break;
    }

    default:
        infoStr = "Invalid action!";
        break;
    }

    infoText.setString(infoStr);
}

