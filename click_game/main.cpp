#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>

#include "GameObject.h"
using namespace sf;

void game_run();
void start_menu();
void scorelist_view();

int main()
{
    //game_run();
    start_menu();
    //scorelist_view();

    return 0;
}

void game_run()
{
    float SPEED = 10.0;
    int FRAME_NUMBER = 0;
    int SCORE = 0;
    bool SCORE_RECORDED = false;
    bool PLAY = true;
    RenderWindow window(VideoMode(1600, 800), "Clicker");
    window.setFramerateLimit(30);

    Font font;
    font.loadFromFile("./data/fonts/HotMustardBTNPosterRegular.ttf");
    Text scoreText("", font, 30);
    scoreText.setPosition(10, 10);

    Texture characterTexture;
    GameObject::MaskedTexture(characterTexture, "./data/img/nyan_cat.png");

    Texture characterStuffTexture1;
    GameObject::MaskedTexture(characterStuffTexture1, "./data/img/rainbow_1.png");
    Texture characterStuffTexture2;
    GameObject::MaskedTexture(characterStuffTexture2, "./data/img/rainbow_2.png");

    Texture lavaTexture;
    GameObject::MaskedTexture(lavaTexture, "./data/img/lava.png");

    Texture splashTexture;
    GameObject::MaskedTexture(splashTexture, "./data/img/splash.png");
    Texture bloodSplashTexture;
    GameObject::MaskedTexture(bloodSplashTexture, "./data/img/blood_splash.png");

    Texture skyTexture;
    GameObject::MaskedTexture(skyTexture, "./data/img/sky.png");

    Texture dogTexture1;
    GameObject::MaskedTexture(dogTexture1, "./data/img/dog1.png");
    Texture dogTexture2;
    GameObject::MaskedTexture(dogTexture2, "./data/img/dog2.png");
    Texture dogTexture3;
    GameObject::MaskedTexture(dogTexture3, "./data/img/dog3.png");
    Texture dogTexture4;
    GameObject::MaskedTexture(dogTexture4, "./data/img/dog4.png");
    Texture dogTexture5;
    GameObject::MaskedTexture(dogTexture5, "./data/img/dog5.png");

    Texture UFOTexture;
    GameObject::MaskedTexture(UFOTexture, "./data/img/icecream.png");
    Texture UFOSplashTexture;
    GameObject::MaskedTexture(UFOSplashTexture, "./data/img/splash_icecream.png");

    Sprite characterStuff;
    characterStuff.setTexture(characterStuffTexture1);
    characterStuff.setPosition(0, window.getSize().y / 4);

    Sprite character;
    character.setTexture(characterTexture);
    character.setPosition(characterStuff.getLocalBounds().width - character.getLocalBounds().width, window.getSize().y / 4);

    Sprite splash;
    splash.setTexture(splashTexture);
    splash.setPosition(260, window.getSize().y - 260);
    Sprite blood_splash;
    blood_splash.setTexture(bloodSplashTexture);

    int sky_length = window.getSize().x / skyTexture.getSize().x + 2;
    Sprite* sky = new Sprite[sky_length];
    for (int i = 0; i < sky_length; i++) {
        sky[i].setTexture(skyTexture);
        sky[i].setPosition(i * sky[i].getLocalBounds().width, 0);
    }

    int lava_length = window.getSize().x / lavaTexture.getSize().x + 2;
    Sprite* lava = new Sprite[lava_length];
    for (int j = 0; j < lava_length; j++) {
        lava[j].setTexture(lavaTexture);
        lava[j].setPosition(j * lava[j].getLocalBounds().width, window.getSize().y - lava[j].getLocalBounds().height);
    }

    int dog_length = 5;
    Sprite* dog = new Sprite[dog_length];
    dog[0].setTexture(dogTexture1);
    dog[1].setTexture(dogTexture2);
    dog[2].setTexture(dogTexture3);
    dog[3].setTexture(dogTexture4);
    dog[4].setTexture(dogTexture5);
    for (int k = 0; k < dog_length; k++) {
        dog[k].setPosition(rand() % 3200 + window.getSize().x, window.getSize().y - dog[k].getLocalBounds().height - 100);
    }

    int UFO_length = 5;
    Sprite* UFO = new Sprite[UFO_length];
    for (int k = 0; k < UFO_length; k++) {
        UFO[k].setTexture(UFOTexture);
        UFO[k].setPosition(rand() % 3200 + window.getSize().x, rand() % 200);
    }

    RectangleShape rectangle(Vector2f(window.getSize().x * 0.6, window.getSize().y * 0.6));
    rectangle.move((window.getSize().x - rectangle.getLocalBounds().width) / 2, (window.getSize().y - rectangle.getLocalBounds().height) / 2);
    rectangle.setFillColor(Color(255, 255, 255, 100));

    Text restartBtn("Restart playing", font, 70);
    restartBtn.setPosition(rectangle.getPosition().x + (rectangle.getLocalBounds().width - restartBtn.getLocalBounds().width) / 2, rectangle.getPosition().y + (rectangle.getLocalBounds().height - restartBtn.getLocalBounds().height) / 2);
    restartBtn.setFillColor(Color(0, 7, 77));

    Text scorelistBtn("Score list", font, 70);
    scorelistBtn.setPosition(rectangle.getPosition().x + (rectangle.getLocalBounds().width - scorelistBtn.getLocalBounds().width) / 2, restartBtn.getPosition().y - restartBtn.getLocalBounds().height - 80);
    scorelistBtn.setFillColor(Color(0, 7, 77));

    Text exitBtn("Exit", font, 70);
    exitBtn.setPosition(rectangle.getPosition().x + (rectangle.getLocalBounds().width - exitBtn.getLocalBounds().width) / 2, restartBtn.getPosition().y + restartBtn.getLocalBounds().height + 80);
    exitBtn.setFillColor(Color(0, 7, 77));


    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                void (*funct) ();
                funct = start_menu;
                funct();
                break;

            case Event::KeyPressed:
                break;
            case Event::MouseMoved:
                if (GameObject::CursorCheck(event.mouseMove.x, event.mouseMove.y, restartBtn)) {
                    restartBtn.setFillColor(Color(255, 255, 255));
                }
                else {
                    restartBtn.setFillColor(Color(0, 7, 77));
                }
                if (GameObject::CursorCheck(event.mouseMove.x, event.mouseMove.y, scorelistBtn)) {
                    scorelistBtn.setFillColor(Color(255, 255, 255));
                }
                else {
                    scorelistBtn.setFillColor(Color(0, 7, 77));
                }
                if (GameObject::CursorCheck(event.mouseMove.x, event.mouseMove.y, exitBtn)) {
                    exitBtn.setFillColor(Color(255, 255, 255));
                }
                else {
                    exitBtn.setFillColor(Color(0, 7, 77));
                }
                break;
            case Event::MouseButtonPressed:
                if (not PLAY) {
                    if (GameObject::CursorCheck(event.mouseButton.x, event.mouseButton.y, restartBtn)) {
                        window.close();
                        void (*func) ();
                        func = game_run;
                        func();
                    }
                    else if (GameObject::CursorCheck(event.mouseButton.x, event.mouseButton.y, scorelistBtn)) {
                        window.close();
                        void (*func) ();
                        func = scorelist_view;
                        func();
                    }
                    else if (GameObject::CursorCheck(event.mouseButton.x, event.mouseButton.y, exitBtn)) {
                        window.close();
                    }
                    break;
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Key::Up) or Keyboard::isKeyPressed(Keyboard::Key::Space))
        {
            if (character.getPosition().y > 0) {
                character.move(0, -SPEED);
                characterStuff.move(0, -SPEED);
            }
        }
        else {
            character.move(0, SPEED);
            characterStuff.move(0, SPEED);
        }

        window.clear();

        for (int i = 0; i < sky_length; i++) {
            window.draw(sky[i]);
            sky[i].move(-SPEED, 0);
            if (sky[i].getPosition().x < (i - 1) * sky[i].getLocalBounds().width) {
                sky[i].setPosition(i * sky[i].getLocalBounds().width, 0);
            }
        }

        FRAME_NUMBER++;
        if (FRAME_NUMBER % 6 == 0 or FRAME_NUMBER % 6 == 1 or FRAME_NUMBER % 6 == 2) {
            characterStuff.setTexture(characterStuffTexture1);
        }
        else {
            characterStuff.setTexture(characterStuffTexture2);
        }
        window.draw(character);
        window.draw(characterStuff);

        if (GameObject::CollisionsTest(character, lava))
        {
            window.draw(splash);
            SPEED = 0;
            PLAY = false;
        }

        for (int j = 0; j < lava_length; j++) {
            window.draw(lava[j]);
            lava[j].move(-SPEED, 0);
            if (lava[j].getPosition().x < (j - 1) * lava[j].getLocalBounds().width) {
                lava[j].setPosition(j * lava[j].getLocalBounds().width, window.getSize().y - lava[j].getLocalBounds().height);
            }
        }

        for (int k = 0; k < dog_length; k++) {
            window.draw(dog[k]);
            dog[k].move(-SPEED, 0);
            if (dog[k].getPosition().x < -dog[k].getLocalBounds().width) {
                dog[k].setPosition(rand() % 3200 + window.getSize().x, window.getSize().y - dog[k].getLocalBounds().height - 100);

            }
            if (GameObject::CollisionTest(character, dog[k]))
            {
                blood_splash.setPosition(characterStuff.getLocalBounds().width - 140, character.getPosition().y - 80);
                window.draw(blood_splash);
                SPEED = 0;
                PLAY = false;
            }
        }

        for (int k = 0; k < UFO_length; k++) {
            window.draw(UFO[k]);
            UFO[k].move(-SPEED * 2, 0);
            if (UFO[k].getPosition().x < -UFO[k].getLocalBounds().width) {
                UFO[k].setPosition(rand() % 3200 + window.getSize().x, rand() % 200);

            }
            if (GameObject::CollisionTest(character, UFO[k]))
            {
                UFO[k].setTexture(UFOSplashTexture);
                window.draw(UFO[k]);
                SPEED = 0;
                PLAY = false;
            }
        }
        if (PLAY and FRAME_NUMBER % 30 == 0) {
            SCORE++;
        }
        std::stringstream ss;
        ss << SCORE;
        scoreText.setString(ss.str());
        window.draw(scoreText);

        if (not PLAY) {
            window.draw(rectangle);
            window.draw(restartBtn);
            window.draw(scorelistBtn);
            window.draw(exitBtn);
            if (not SCORE_RECORDED) {
                SCORE_RECORDED = true;
                GameObject::ScoreRecord(SCORE);
            }
        }
        window.display();
    }
}

void start_menu()
{
    float SPEED = 7.0;
    int FRAME_NUMBER = 0;
    
    RenderWindow window(VideoMode(1600, 800), "Clicker");
    window.setFramerateLimit(30);

    Texture characterTexture;
    GameObject::MaskedTexture(characterTexture, "./data/img/nyan_cat.png");

    Texture characterStuffTexture1;
    GameObject::MaskedTexture(characterStuffTexture1, "./data/img/rainbow_1.png");
    Texture characterStuffTexture2;
    GameObject::MaskedTexture(characterStuffTexture2, "./data/img/rainbow_2.png");

    Texture lavaTexture;
    GameObject::MaskedTexture(lavaTexture, "./data/img/lava.png");

    Texture skyTexture;
    GameObject::MaskedTexture(skyTexture, "./data/img/sky.png");

    Sprite characterStuff;
    characterStuff.setTexture(characterStuffTexture1);
    characterStuff.setPosition(0, window.getSize().y / 4);

    Sprite character;
    character.setTexture(characterTexture);
    character.setPosition(characterStuff.getLocalBounds().width - character.getLocalBounds().width, window.getSize().y / 4);

    int sky_length = window.getSize().x / skyTexture.getSize().x + 2;
    Sprite* sky = new Sprite[sky_length];
    for (int i = 0; i < sky_length; i++) {
        sky[i].setTexture(skyTexture);
        sky[i].setPosition(i * sky[i].getLocalBounds().width, 0);
    }

    int lava_length = window.getSize().x / lavaTexture.getSize().x + 2;
    Sprite* lava = new Sprite[lava_length];
    for (int j = 0; j < lava_length; j++) {
        lava[j].setTexture(lavaTexture);
        lava[j].setPosition(j * lava[j].getLocalBounds().width, window.getSize().y - lava[j].getLocalBounds().height);
    }

    RectangleShape rectangle(Vector2f(window.getSize().x * 0.6, window.getSize().y * 0.6));
    rectangle.move((window.getSize().x - rectangle.getLocalBounds().width) / 2, (window.getSize().y - rectangle.getLocalBounds().height) / 2);
    rectangle.setFillColor(Color(255, 255, 255, 100));

    Font font;
    font.loadFromFile("./data/fonts/HotMustardBTNPosterRegular.ttf");
    Text playBtn("Start playing", font, 70);
    playBtn.setFillColor(Color(0, 7, 77));
    Text scorelistBtn("Score list", font, 70);
    scorelistBtn.setFillColor(Color(0, 7, 77));

    playBtn.setPosition(rectangle.getPosition().x + (rectangle.getLocalBounds().width - playBtn.getLocalBounds().width) / 2, rectangle.getPosition().y + (rectangle.getLocalBounds().height - playBtn.getLocalBounds().height - scorelistBtn.getLocalBounds().height - 100) / 2);
    scorelistBtn.setPosition(rectangle.getPosition().x + (rectangle.getLocalBounds().width - scorelistBtn.getLocalBounds().width) / 2, playBtn.getPosition().y + 100);
    
    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                break;

            case Event::KeyPressed:
                break;
            case Event::MouseMoved:
                if (GameObject::CursorCheck(event.mouseMove.x, event.mouseMove.y, playBtn)) {
                    playBtn.setFillColor(Color(255, 255, 255));
                }
                else {
                    playBtn.setFillColor(Color(0, 7, 77));
                }
                if (GameObject::CursorCheck(event.mouseMove.x, event.mouseMove.y, scorelistBtn)) {
                    scorelistBtn.setFillColor(Color(255, 255, 255));
                }
                else {
                    scorelistBtn.setFillColor(Color(0, 7, 77));
                }
                break;
            case Event::MouseButtonPressed:
                if (GameObject::CursorCheck(event.mouseButton.x, event.mouseButton.y, playBtn)) {
                    window.close();
                    void (*func) ();
                    func = game_run;
                    func();
                }
                if (GameObject::CursorCheck(event.mouseButton.x, event.mouseButton.y, scorelistBtn)) {
                    window.close();
                    void (*func) ();
                    func = scorelist_view;
                    func();
                }
                break;
            }
            
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
        {
            window.close();
        }

        window.clear();

        for (int i = 0; i < sky_length; i++) {
            window.draw(sky[i]);
            sky[i].move(-SPEED, 0);
            if (sky[i].getPosition().x < (i - 1) * sky[i].getLocalBounds().width) {
                sky[i].setPosition(i * sky[i].getLocalBounds().width, 0);
            }
        }

        FRAME_NUMBER++;
        if (FRAME_NUMBER % 6 == 0 or FRAME_NUMBER % 6 == 1 or FRAME_NUMBER % 6 == 2) {
            characterStuff.setTexture(characterStuffTexture1);
        }
        else {
            characterStuff.setTexture(characterStuffTexture2);
        }
        window.draw(character);
        window.draw(characterStuff);

        for (int j = 0; j < lava_length; j++) {
            window.draw(lava[j]);
            lava[j].move(-SPEED, 0);
            if (lava[j].getPosition().x < (j - 1) * lava[j].getLocalBounds().width) {
                lava[j].setPosition(j * lava[j].getLocalBounds().width, window.getSize().y - lava[j].getLocalBounds().height);
            }
        }

        window.draw(rectangle);
        window.draw(playBtn);
        window.draw(scorelistBtn);

        window.display();
    }

}
void scorelist_view()
{
    float SPEED = 5.0;
    int SCROLL_START = 0;
    int FRAME_NUMBER = 0;

    RenderWindow window(VideoMode(1600, 800), "Clicker");
    window.setFramerateLimit(30);

    Texture skyTexture;
    GameObject::MaskedTexture(skyTexture, "./data/img/sky.png");

    int sky_length = window.getSize().x / skyTexture.getSize().x + 1;
    Sprite* sky = new Sprite[sky_length];
    for (int i = 0; i < sky_length; i++) {
        sky[i].setTexture(skyTexture);
        sky[i].setPosition(i * sky[i].getLocalBounds().width, 0);
    }

    RectangleShape rectangle(Vector2f(window.getSize().x * 0.6, window.getSize().y * 0.9));
    rectangle.move((window.getSize().x - rectangle.getLocalBounds().width) / 2, (window.getSize().y - rectangle.getLocalBounds().height) / 2);
    rectangle.setFillColor(Color(255, 255, 255, 200));

    Font font;
    font.loadFromFile("./data/fonts/HotMustardBTNPosterRegular.ttf");
    Text mainMenuBtn("Main menu", font, 50);
    mainMenuBtn.setFillColor(Color(0, 7, 77));
    mainMenuBtn.setPosition(rectangle.getPosition().x + (rectangle.getLocalBounds().width - mainMenuBtn.getLocalBounds().width) - 40, rectangle.getPosition().y + 10);

    Font title_list_font;
    title_list_font.loadFromFile("./data/fonts/LithosProBold.otf");
    Text list_title("", title_list_font, 30);
    list_title.setFillColor(Color(0, 7, 77));
    list_title.setString("Score list (the best result is " + GameObject::getBestResult() + ")");

    Font list_font;
    list_font.loadFromFile("./data/fonts/LithosProRegular.ttf");
    Text list("", list_font, 30);
    list.setFillColor(Color(0, 7, 77));
    list.setString(GameObject::getScoreList(SCROLL_START, 15));

    list_title.setPosition(rectangle.getPosition().x + 50, rectangle.getPosition().y + (rectangle.getLocalBounds().height - list.getLocalBounds().height) / 2 - 20);
    list.setPosition(rectangle.getPosition().x + 50, list_title.getPosition().y + list_title.getLocalBounds().height + 20);
    

    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                void (*funct) ();
                funct = start_menu;
                funct();
                break;
            case Event::KeyPressed:
                break;
            case Event::MouseMoved:
                if (GameObject::CursorCheck(event.mouseMove.x, event.mouseMove.y, mainMenuBtn)) {
                    mainMenuBtn.setFillColor(Color(255, 255, 255));
                }
                else {
                    mainMenuBtn.setFillColor(Color(0, 7, 77));
                }
                break;
            case Event::MouseButtonPressed:
                if (GameObject::CursorCheck(event.mouseButton.x, event.mouseButton.y, mainMenuBtn)) {
                    window.close();
                    void (*func) ();
                    func = start_menu;
                    func();
                }
                break;
            case Event::MouseWheelScrolled:
                SCROLL_START -= event.mouseWheelScroll.delta;
                if (SCROLL_START < 0) {
                    SCROLL_START = 0;
                }
                list.setString(GameObject::getScoreList(SCROLL_START, 15));
            }

        }
        if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
        {
            window.close();
        }

        window.clear();

        for (int i = 0; i < sky_length; i++) {
            window.draw(sky[i]);
        }
        window.draw(rectangle);
        window.draw(mainMenuBtn);
        window.draw(list_title);
        window.draw(list);

        window.display();
    }

}