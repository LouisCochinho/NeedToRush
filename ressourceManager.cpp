#include "RessourcesManager.h"

std::map<string, unique_ptr<sf::Texture>> RessourcesManager::mTextures;
std::map<string, unique_ptr<sf::Font>> RessourcesManager::mFonts;

string RessourcesManager::pathImage = "data/images/";
string RessourcesManager::pathFont = "data/font/";



void RessourcesManager::addTextureWithMask(string nom, sf::Color colorMask) {
    sf::Image i;
    if (i.loadFromFile(pathImage + nom)) {
        i.createMaskFromColor(colorMask);
        sf::Texture t;
        t.loadFromImage(i);
        RessourcesManager::mTextures.insert(pair<string, unique_ptr < sf::Texture >> ( nom, std::unique_ptr<sf::Texture>(new sf::Texture(t)) ));
    }
}

sf::Texture* RessourcesManager::getTexture(string nom) {
    if (RessourcesManager::mTextures.find(nom) != RessourcesManager::mTextures.end())
        return RessourcesManager::mTextures.at(nom).get();

    sf::Texture tmp;
    if (tmp.loadFromFile(pathImage + nom)) {
        RessourcesManager::mTextures.insert(pair<string, unique_ptr < sf::Texture >> ( nom, std::unique_ptr<sf::Texture>(new sf::Texture(tmp)) ));
        
        return RessourcesManager::mTextures.at(nom).get();
    }
    
    return nullptr;
}

sf::Font* RessourcesManager::getFont(string nom) {
    if (RessourcesManager::mFonts.find(nom) != RessourcesManager::mFonts.end())
        return RessourcesManager::mFonts.at(nom).get();

    sf::Font font;
    if (font.loadFromFile(pathFont + nom)) {
        RessourcesManager::mFonts.insert(pair<string, unique_ptr < sf::Font >>(nom, std::unique_ptr<sf::Font>(new sf::Font(font))));
    
        return RessourcesManager::mFonts.at(nom).get();
    }
    
    return nullptr;
}

