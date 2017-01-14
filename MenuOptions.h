/* 
 * File:   MenuOptions.h
 * Author: cochinhl
 *
 * Created on 3 février 2015, 14:17
 */

#ifndef MENUOPTIONS_H
#define	MENUOPTIONS_H

#include "Menu.h"

class MenuOptions {
public:
    MenuOptions(sf::RenderWindow& window);
    bool isMouseOver(string key);
    sf::Text* getBouton(string key);
    void addBouton(sf::Text* txt,string key);
    void afficherBoutons();
    bool processEventsOpt();
    
     ~MenuOptions();
    
private:
    sf::Sprite mFond;
    map<string,sf::Text*> mBoutons;
    sf::RenderWindow& mWindow;
    sf::Font mFont;
};

#endif	/* MENUOPTIONS_H */

