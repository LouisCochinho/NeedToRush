#ifndef MENU_H
#define	MENU_H

#include "Game.h"
#include "MenuOptions.h"
#include "MenuCredit.h"

class Menu {
public:
    Menu(sf::RenderWindow& window);

    bool isMouseOver(string key);
    sf::Text* getBouton(string key);

    void addBouton(sf::Text* txt, string key);
    void afficherBoutons();
    void processEvents();
    sf::Sprite* getTitre();
    
    ~Menu();
    
private:
    map<string, sf::Text*> mBoutons;
	sf::Text mWin;
    sf::RenderWindow& mWindow;
    string mBoutonSelectionne;
    int mPause;
    Game mGame;
    sf::Sprite mBackground;
    sf::Sprite mTitre;
    int compteur, mNumMusic;
    
    sf::Music musicDeb;
    sf::Music music0;
    sf::Music music1;
    sf::Music music2;
    sf::Music music3;
    sf::Music music4;
    sf::Music music5;
    sf::Music musicA;
    sf::Music musicB;
    sf::Music musicC;
    
    void chargerMusic(sf::Music& music, string nom);    
    static string pathMusic;
};

#endif	/* MENU_H */

