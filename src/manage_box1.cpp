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
            // دوستتان باید این کد را جایگزین کند:
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
