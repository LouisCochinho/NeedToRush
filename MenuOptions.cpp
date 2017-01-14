/* 
 * File:   MenuOptions.cpp
 * Author: cochinhl
 * 
 * Created on 3 février 2015, 14:17
 */

#include "MenuOptions.h"

MenuOptions::MenuOptions(sf::RenderWindow& window) : mWindow(window), mFont(*RessourcesManager::getFont("oj.ttf")), mFond(*RessourcesManager::getTexture("sampleOption.png")) {

    this->addBouton(new sf::Text, "Son");
    this->getBouton("Son")->setString("Son");
    this->getBouton("Son")->setColor(sf::Color::Blue);
    this->getBouton("Son")->setFont(*RessourcesManager::getFont("calibri.ttf"));
    this->getBouton("Son")->setCharacterSize(50);
    this->getBouton("Son")->setPosition((window.getSize().x / 2 - this->getBouton("Son")->getGlobalBounds().width / 2) - 150, 150);

    this->addBouton(new sf::Text, "On");
    this->getBouton("On")->setString("On");
    this->getBouton("On")->setColor(sf::Color::Blue);
    this->getBouton("On")->setFont(mFont);
    this->getBouton("On")->setCharacterSize(50);
    this->getBouton("On")->setPosition((window.getSize().x / 2 - this->getBouton("On")->getGlobalBounds().width / 2) + 100, 150);

    this->addBouton(new sf::Text, "Off");
    this->getBouton("Off")->setString("Off");
    this->getBouton("Off")->setColor(sf::Color::Blue);
    this->getBouton("Off")->setFont(mFont);
    this->getBouton("Off")->setCharacterSize(50);
    this->getBouton("Off")->setPosition((window.getSize().x / 2 - this->getBouton("Off")->getGlobalBounds().width / 2) + 200, 150);

    this->addBouton(new sf::Text, "Retour");
    this->getBouton("Retour")->setString("Retour");
    this->getBouton("Retour")->setColor(sf::Color::Blue);
    this->getBouton("Retour")->setFont(mFont);
    this->getBouton("Retour")->setCharacterSize(50);
    this->getBouton("Retour")->setPosition(760, 540);
}

bool MenuOptions::processEventsOpt() {
    sf::Event event;
    if (isMouseOver("On")) {
        getBouton("On")->setColor(sf::Color::Red);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            //music.play(); sound.play();
        }
    }
    else if (isMouseOver("Off")) {
        getBouton("Off")->setColor(sf::Color::Red);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            //music.pause(); sound.pause(); 
        }
    }
    else if (isMouseOver("Retour")) {
        getBouton("Retour")->setColor(sf::Color::Red);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            return false;
        }
    } else {
        getBouton("On")->setColor(sf::Color::Blue);
        getBouton("Off")->setColor(sf::Color::Blue);
        getBouton("Retour")->setColor(sf::Color::Blue);
    }


    while (mWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            mWindow.close();
        }
    }

    return true;
}

bool MenuOptions::isMouseOver(string key) {
    int mouseX = sf::Mouse::getPosition(mWindow).x;
    int mouseY = sf::Mouse::getPosition(mWindow).y;

    sf::Text& text = *(getBouton(key));

    return ((mouseX > text.getPosition().x && mouseX < text.getGlobalBounds().width + text.getPosition().x)
            && (mouseY > text.getPosition().y && mouseY < text.getGlobalBounds().height + text.getPosition().y + 20));

}

sf::Text* MenuOptions::getBouton(string key) {
    return (*mBoutons.find(key)).second;
}

void MenuOptions::addBouton(sf::Text* txt, string key) {
    mBoutons.insert(pair<string, sf::Text*>(key, txt));

}

void MenuOptions::afficherBoutons() {
    mWindow.draw(mFond);
    
    auto deb = mBoutons.begin();
    auto fin = mBoutons.end();

    while (deb != fin) {
        mWindow.draw(*(*deb).second);
        ++deb;
    }
}

MenuOptions::~MenuOptions() {
    auto deb = mBoutons.begin();
    auto fin = mBoutons.end();

    while (deb != fin) {
        delete (*deb).second;
        ++deb;
    }
}
