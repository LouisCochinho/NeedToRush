#include "Menu.h"

int main(int argc, char** argv) {
    
    RessourcesManager::addTextureWithMask("spritesheet.png", sf::Color(94, 129, 162));

    RessourcesManager::addTextureWithMask("player/p1_run.png", sf::Color(255, 255, 255));
    RessourcesManager::addTextureWithMask("player/p1_stand.png", sf::Color(255, 255, 255));
    RessourcesManager::addTextureWithMask("player/p1_saut.png", sf::Color(255, 255, 255));

	RessourcesManager::addTextureWithMask("player/p2_run.png", sf::Color(255, 255, 255));
	RessourcesManager::addTextureWithMask("player/p2_stand.png", sf::Color(255, 255, 255));
	RessourcesManager::addTextureWithMask("player/p2_saut.png", sf::Color(255, 255, 255));

	sf::RenderWindow window(sf::VideoMode(1050, 630), "GameJam");
    window.setPosition( sf::Vector2i(100, 20) );
    
    //jouer
    Menu menuJouer(window);

    while (window.isOpen()) {
        menuJouer.processEvents();

        window.clear();


        menuJouer.afficherBoutons();

        window.display();
    }

    return EXIT_SUCCESS;
}

