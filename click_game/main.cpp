#include <iostream>
#include <SFML/Graphics.hpp>

#include "GameObject.h"

float SPEED = 10.0;
int FRAME_NUMBER = 0;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(1600, 800), "Clicker");
    window.setFramerateLimit(30);

    Texture characterTexture;
    GameObject::MaskedTexture(characterTexture, "C:/mirea/c_plus_plus/click_game/click_game/data/img/nyan_cat.png");

    Texture characterStuffTexture1;
    GameObject::MaskedTexture(characterStuffTexture1, "C:/mirea/c_plus_plus/click_game/click_game/data/img/rainbow_1.png");
    Texture characterStuffTexture2;
    GameObject::MaskedTexture(characterStuffTexture2, "C:/mirea/c_plus_plus/click_game/click_game/data/img/rainbow_2.png");

    Texture lavaTexture;
    GameObject::MaskedTexture(lavaTexture, "C:/mirea/c_plus_plus/click_game/click_game/data/img/lava.png");
    
    Texture splashTexture;
    GameObject::MaskedTexture(splashTexture, "C:/mirea/c_plus_plus/click_game/click_game/data/img/splash.png");
    Texture bloodSplashTexture;
    GameObject::MaskedTexture(bloodSplashTexture, "C:/mirea/c_plus_plus/click_game/click_game/data/img/blood_splash.png");

    Texture skyTexture;
    GameObject::MaskedTexture(skyTexture, "C:/mirea/c_plus_plus/click_game/click_game/data/img/sky.png");

    Texture dogTexture1;
    GameObject::MaskedTexture(dogTexture1, "C:/mirea/c_plus_plus/click_game/click_game/data/img/dog1.png");
    Texture dogTexture2;
    GameObject::MaskedTexture(dogTexture2, "C:/mirea/c_plus_plus/click_game/click_game/data/img/dog2.png");
    Texture dogTexture3;
    GameObject::MaskedTexture(dogTexture3, "C:/mirea/c_plus_plus/click_game/click_game/data/img/dog3.png");
    Texture dogTexture4;
    GameObject::MaskedTexture(dogTexture4, "C:/mirea/c_plus_plus/click_game/click_game/data/img/dog4.png");
    Texture dogTexture5;
    GameObject::MaskedTexture(dogTexture5, "C:/mirea/c_plus_plus/click_game/click_game/data/img/dog5.png");

    Texture UFOTexture;
    GameObject::MaskedTexture(UFOTexture, "C:/mirea/c_plus_plus/click_game/click_game/data/img/icecream.png");
    Texture UFOSplashTexture;
    GameObject::MaskedTexture(UFOSplashTexture, "C:/mirea/c_plus_plus/click_game/click_game/data/img/splash_icecream.png");

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
    Sprite *lava = new Sprite[lava_length];
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
            }
        }

        //if (Keyboard::isKeyPressed(Keyboard::Key::Right))
        //{
        //    character.move(SPEED, 0);
        //}
        //else if (Keyboard::isKeyPressed(Keyboard::Key::Left))
        //{
        //    character.move(-SPEED, 0);
        //}

        if (Keyboard::isKeyPressed(Keyboard::Key::Up) or Keyboard::isKeyPressed(Keyboard::Key::Space))
        {
            character.move(0, -SPEED);
            characterStuff.move(0, -SPEED);
        }
        //else if (Keyboard::isKeyPressed(Keyboard::Key::Down))
        //{
        //    character.move(0, SPEED);
        //}
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
            }
        }

        window.display();
    }

    return 0;
}