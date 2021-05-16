#include "../Headers/menu.h"


//35 39  100  80
Menu::Menu(const std::string &backgrnd) {

    BackGround_t.loadFromFile(backgrnd);
    BackGround_s.setTexture(BackGround_t);
    BackGround_s.setTextureRect({0, 0, 1920, 1080});

    Died_t.loadFromFile("Images//died.png");
    Died_s.setTexture(Died_t);
    Died_s.setOrigin(DIED_X/2, DIED_Y/2);

    Buttons_t.loadFromFile("Images//buttons.png");

    Start_button_s.setTexture(Buttons_t);
    Start_button_s.setTextureRect({35, 39, 300, 80});
    Start_button_s.setPosition(200, 200);
    Start_button_rect = {200,200, 300, 80};
    Start_button_s_pressed.setTexture(Buttons_t);
    Start_button_s_pressed.setTextureRect({35, 145, 300, 80});
    Start_button_s_pressed.setPosition(200, 200);

    Options_button_s.setTexture(Buttons_t);
    Options_button_s.setTextureRect({345, 39, 300, 80});
    Options_button_s.setPosition(200, 300);
    Options_button_rect = {200,300, 300, 80};
    Options_button_s_pressed.setTexture(Buttons_t);
    Options_button_s_pressed.setTextureRect({347, 145, 300, 80});
    Options_button_s_pressed.setPosition(200, 300);

    Exit_button_s.setTexture(Buttons_t);
    Exit_button_s.setTextureRect({663, 39, 300, 80});
    Exit_button_s.setPosition(200, 400);
    Exit_button_rect = {200,400, 300, 80};
    Exit_button_s_pressed.setTexture(Buttons_t);
    Exit_button_s_pressed.setTextureRect({665, 145, 300, 80});
    Exit_button_s_pressed.setPosition(200, 400);

    Heart_t.loadFromFile("Images//heart.png");

    Pause_t.loadFromFile("Images//pause.png");
    Pause_s.setTexture(Pause_t);
}

bool Menu::Start(sf::RenderWindow &window) {

    Choosed_Button choosed = Choosed_Button::Nop;

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();


            window.clear();

            window.draw(BackGround_s);

            if (Start_button_rect.contains(sf::Mouse::getPosition(window))) {
                choosed = Choosed_Button::Start;
                window.draw(Start_button_s_pressed);
            }
            else
                window.draw(Start_button_s);

            /*if (Options_button_rect.contains(sf::Mouse::getPosition(window))) {
                choosed = Choosed_Button::Options;
                window.draw(Options_button_s_pressed);
            }
            else
                window.draw(Options_button_s);*/

            if (Exit_button_rect.contains(sf::Mouse::getPosition(window))) {
                choosed = Choosed_Button::Exit;
                window.draw(Exit_button_s_pressed);
            }
            else
                window.draw(Exit_button_s);


            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                switch (choosed) {

                    case Choosed_Button::Start : {
                        window.clear();
                        return true;
                    }
                    case Choosed_Button::Options : {
                        break;
                    }
                    case Choosed_Button::Exit : {
                        window.clear();
                        return false;
                    }
                    case Choosed_Button::Nop:
                        break;
                }

            }

            window.display();

            choosed = Choosed_Button::Nop;
        }
    }
}

void Menu::Died(sf::RenderWindow& window, float x, float y, size_t kills) {

    sf::Font font;
    font.loadFromFile("Images//shrift.ttf");
    sf::Text text("", font, 50);
    text.setColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    text.setString("Your kills: " + std::to_string(kills));
    text.setPosition(x , y + 100 );
    window.draw(text);

    Died_s.setPosition(x, y);

    window.draw(Died_s);
    window.display();

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.clear();
                window.close();
                return;
            }


            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                window.clear();
                return;
            }
        }

    }

}

bool Menu::Pause(sf::RenderWindow& window, float x, float y) {

    Pause_s.setOrigin(PAUSE_X /2, PAUSE_Y / 2);
    Pause_s.setPosition(x, y);

    window.draw(Pause_s);
    window.display();

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.clear();
                window.close();
                return false;

            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                //window.clear();
                return true;
            }
        }

    }

}

void Menu::DrawLives(sf::RenderWindow &window, size_t lives, float x, float y) {

    assert(lives <= LIVES_NUM);

    sf::Sprite h;
    h.setTexture(Heart_t);
    for (int i = 0; i < lives; ++i) {
        h.setPosition(x + 10 + i * 15, y + 10);
        window.draw(h);
    }
}
