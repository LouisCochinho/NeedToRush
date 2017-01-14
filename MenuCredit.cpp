/* 
 * File:   MenuCredit.cpp
 * Author: cochinhl
 * 
 * Created on 3 février 2015, 16:46
 */

#include "MenuCredit.h"

MenuCredit::MenuCredit(sf::RenderWindow& window) : mWindow(window), mFont(*RessourcesManager::getFont("oj.ttf")) {

    this->addBouton(new sf::Text, "Equipe de développement");
    this->getBouton("Equipe de développement")->setString("Equipe de developpement : \n\n\t\tChef de projet   : Samy Rezzouqi\n\t\tDeveloppement : Louis Cochinho\n\t\t\t\t\t\t\t\t   Cassandra Miras\n\t\tGraphismes        : Yacine Abbas\n\t\t\t\t\t\t\t\t   Thomas Smara \n\t\tLevel Design    :  Thomas Smara ");
    this->getBouton("Equipe de développement")->setColor(sf::Color::White);
    this->getBouton("Equipe de développement")->setFont(*RessourcesManager::getFont("cl.ttf"));
    this->getBouton("Equipe de développement")->setCharacterSize(30);
    this->getBouton("Equipe de développement")->setPosition(100, 30);

    this->addBouton(new sf::Text, "Sources");
    this->getBouton("Sources")->setString("Sources : \n\n\t\tTilesets   : http://i5.photobucket.com/albums/y157/TilesetExample.jpg\n\t\tPersonnages :  http://i47.tinypic.com/2gvpo3b.gif \n\t\tCompositeur : Kevin MacLeod \n\t\tFond d'ecran : http://wallpaperswide.com/paper_plane_2-wallpapers.html\n\t\tPolices : http://www.dafont.com/fr/ ");
    this->getBouton("Sources")->setColor(sf::Color::White);
    this->getBouton("Sources")->setFont(*RessourcesManager::getFont("cl.ttf"));
    this->getBouton("Sources")->setCharacterSize(30);
    this->getBouton("Sources")->setPosition(100, 320);

    this->addBouton(new sf::Text, "Retour");
    this->getBouton("Retour")->setString("Retour");
    this->getBouton("Retour")->setColor(sf::Color::Blue);
    this->getBouton("Retour")->setFont(mFont);
    this->getBouton("Retour")->setCharacterSize(50);
    this->getBouton("Retour")->setPosition(760, 540);
}

sf::Text* MenuCredit::getBouton(string key) {
    return (*mBoutons.find(key)).second;
}

bool MenuCredit::processEventsCre() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            mWindow.close();
        }
    }

    if (isMouseOver("Retour")) {
        getBouton("Retour")->setColor(sf::Color::Red);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            return false;
        }
    } else {
        getBouton("Retour")->setColor(sf::Color::Blue);
    }

    return true;
}

void MenuCredit::addBouton(sf::Text* txt, string key) {
    mBoutons.insert(pair<string, sf::Text*>(key, txt));

}

void MenuCredit::afficherBoutons() {

    auto deb = mBoutons.begin();
    auto fin = mBoutons.end();

    while (deb != fin) {
        mWindow.draw(*(*deb).second);
        ++deb;
    }
}

bool MenuCredit::isMouseOver(string key) {
    int mouseX = sf::Mouse::getPosition(mWindow).x;
    int mouseY = sf::Mouse::getPosition(mWindow).y;

    sf::Text& text = *(getBouton(key));

    return ((mouseX > text.getPosition().x && mouseX < text.getGlobalBounds().width + text.getPosition().x)
            && (mouseY > text.getPosition().y && mouseY < text.getGlobalBounds().height + text.getPosition().y + 20));

}

MenuCredit::~MenuCredit() {
    auto deb = mBoutons.begin();
    auto fin = mBoutons.end();

    while (deb != fin) {
        delete (*deb).second;
        ++deb;
    }
}
