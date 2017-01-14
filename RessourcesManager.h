#ifndef RESSOURCEMANAGER_H
#define	RESSOURCEMANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <memory>
#include <map>
#include <list>
#include <fstream>

using namespace std;

class RessourcesManager {
public:
    static sf::Texture* getTexture(string nom);
    static sf::Font* getFont(string nom);
    static void addTextureWithMask(string nom, sf::Color colorMask);


private:
    static std::map<string, unique_ptr<sf::Texture>> mTextures;
    static std::map<string, unique_ptr<sf::Font>> mFonts;

    static string pathImage;
    static string pathFont;
};

#endif	/* RESSOURCEMANAGER_H */

