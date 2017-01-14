/* 
 * File:   MenuCredit.h
 * Author: cochinhl
 *
 * Created on 3 février 2015, 16:46
 */

#ifndef MENUCREDIT_H
#define	MENUCREDIT_H
#include "Menu.h"

class MenuCredit {
public:
    MenuCredit(sf::RenderWindow& window);
    bool isMouseOver(string key);
    sf::Text* getBouton(string key);
    void addBouton(sf::Text* txt, string key);
    void afficherBoutons();
    bool processEventsCre();

    ~MenuCredit();

private:
    map<string, sf::Text*> mBoutons;
    sf::RenderWindow& mWindow;
    sf::Font mFont;

};

#endif	/* MENUCREDIT_H */

