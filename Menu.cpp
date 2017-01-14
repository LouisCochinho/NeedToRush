#include <SFML/Graphics.hpp>
#include "Menu.h"

string Menu::pathMusic = "data/music/";

Menu::Menu(sf::RenderWindow& window) : mWindow(window), mGame(window), mPause(0), compteur(0), mNumMusic(0) {



    mBackground.setTexture(*RessourcesManager::getTexture("sample2.png"));
    mTitre.setTexture(*RessourcesManager::getTexture("logo (copy).png"));
    mTitre.setPosition(window.getSize().x / 2 - mTitre.getGlobalBounds().width / 2, 10);

    chargerMusic(musicDeb, "menu.ogg");
    chargerMusic(music0, "0.ogg");
    chargerMusic(music1, "1.ogg");
    chargerMusic(music2, "2.ogg");
    chargerMusic(music3, "3.ogg");
    chargerMusic(music4, "4.ogg");
    chargerMusic(music5, "5.ogg");
    chargerMusic(musicA, "A.ogg");
    chargerMusic(musicB, "B.ogg");
    chargerMusic(musicC, "C.ogg");

    musicDeb.play();

    this->addBouton(new sf::Text, "Jouer");
    this->getBouton("Jouer")->setString("Jouer");
    this->getBouton("Jouer")->setColor(sf::Color::Blue);
    this->getBouton("Jouer")->setFont(*RessourcesManager::getFont("oj.ttf"));
    this->getBouton("Jouer")->setCharacterSize(100);
    this->getBouton("Jouer")->setPosition(window.getSize().x / 2 - this->getBouton("Jouer")->getGlobalBounds().width / 2, 150);

    this->addBouton(new sf::Text, "Options");
    this->getBouton("Options")->setString("Options");
    this->getBouton("Options")->setColor(sf::Color::Blue);
    this->getBouton("Options")->setFont(*RessourcesManager::getFont("oj.ttf"));
    this->getBouton("Options")->setCharacterSize(50);
    this->getBouton("Options")->setPosition(window.getSize().x / 2 - this->getBouton("Options")->getGlobalBounds().width / 2, 300);

    this->addBouton(new sf::Text, "Credits");
    this->getBouton("Credits")->setString("Credits");
    this->getBouton("Credits")->setColor(sf::Color::Blue);
    this->getBouton("Credits")->setFont(*RessourcesManager::getFont("oj.ttf"));
    this->getBouton("Credits")->setCharacterSize(50);
    this->getBouton("Credits")->setPosition(window.getSize().x / 2 - this->getBouton("Credits")->getGlobalBounds().width / 2, 400);

    this->addBouton(new sf::Text, "Quitter");
    this->getBouton("Quitter")->setString("Quitter");
    this->getBouton("Quitter")->setColor(sf::Color::Blue);
    this->getBouton("Quitter")->setFont(*RessourcesManager::getFont("oj.ttf"));
    this->getBouton("Quitter")->setCharacterSize(50);
    this->getBouton("Quitter")->setPosition(window.getSize().x / 2 - this->getBouton("Quitter")->getGlobalBounds().width / 2, 500);

    this->addBouton(new sf::Text, "Reprendre");
    this->getBouton("Reprendre")->setString("Reprendre");
    this->getBouton("Reprendre")->setColor(sf::Color::Blue);
    this->getBouton("Reprendre")->setFont(*RessourcesManager::getFont("oj.ttf"));
    this->getBouton("Reprendre")->setCharacterSize(50);
    this->getBouton("Reprendre")->setPosition(window.getSize().x / 2 - this->getBouton("Reprendre")->getGlobalBounds().width / 2, 150);

    this->addBouton(new sf::Text, "Niveau suivant");
    this->getBouton("Niveau suivant")->setString("Niveau suivant");
    this->getBouton("Niveau suivant")->setColor(sf::Color::Blue);
    this->getBouton("Niveau suivant")->setFont(*RessourcesManager::getFont("oj.ttf"));
    this->getBouton("Niveau suivant")->setCharacterSize(50);
    this->getBouton("Niveau suivant")->setPosition(window.getSize().x / 2 - this->getBouton("Niveau suivant")->getGlobalBounds().width / 2, 250);

    this->addBouton(new sf::Text, "Recommencer");
    this->getBouton("Recommencer")->setString("Recommencer");
    this->getBouton("Recommencer")->setColor(sf::Color::Blue);
    this->getBouton("Recommencer")->setFont(*RessourcesManager::getFont("oj.ttf"));
    this->getBouton("Recommencer")->setCharacterSize(50);
    this->getBouton("Recommencer")->setPosition(window.getSize().x / 2 - this->getBouton("Recommencer")->getGlobalBounds().width / 2, 350);

    this->addBouton(new sf::Text, "Retour au menu");
    this->getBouton("Retour au menu")->setString("Retour au menu");
    this->getBouton("Retour au menu")->setColor(sf::Color::Blue);
    this->getBouton("Retour au menu")->setFont(*RessourcesManager::getFont("oj.ttf"));
    this->getBouton("Retour au menu")->setCharacterSize(50);
    this->getBouton("Retour au menu")->setPosition(window.getSize().x / 2 - this->getBouton("Retour au menu")->getGlobalBounds().width / 2, 450);

    this->addBouton(new sf::Text, "Resultat");

    this->getBouton("Resultat")->setColor(sf::Color::Blue);
    this->getBouton("Resultat")->setFont(*RessourcesManager::getFont("cl.ttf"));
    this->getBouton("Resultat")->setCharacterSize(20);
    this->getBouton("Resultat")->setPosition(0, 600);

	mWin = sf::Text("winner", *RessourcesManager::getFont("cl.ttf"), 70);
	mWin.setColor(sf::Color::Red);
}

bool Menu::isMouseOver(string key) {
    int mouseX = sf::Mouse::getPosition(mWindow).x;
    int mouseY = sf::Mouse::getPosition(mWindow).y;
    sf::Text& text = *(getBouton(key));
    return ((mouseX > text.getPosition().x && mouseX < text.getGlobalBounds().width + text.getPosition().x)
            && (mouseY > text.getPosition().y && mouseY < text.getGlobalBounds().height + text.getPosition().y + 20));
}

sf::Text* Menu::getBouton(string key) {
    return (*mBoutons.find(key)).second;
}

void Menu::addBouton(sf::Text* txt, string key) {
    mBoutons.insert(pair<string, sf::Text*>(key, txt));

}

void Menu::afficherBoutons() {
    string afficheResultat = "";
    auto deb = mBoutons.begin();
    auto fin = mBoutons.end();
    mWindow.draw(mBackground);
    mWindow.draw(mTitre);
    if (mPause == 1) {
        if (music0.getStatus() == sf::Music::Status::Playing) {
            music0.pause();
        } else if (music1.getStatus() == sf::Music::Status::Playing) {
            music1.pause();
        } else if (music2.getStatus() == sf::Music::Status::Playing) {
            music2.pause();
        } else if (music3.getStatus() == sf::Music::Status::Playing) {
            music3.pause();
        } else if (music4.getStatus() == sf::Music::Status::Playing) {
            music4.pause();
        } else if (music5.getStatus() == sf::Music::Status::Playing) {
            music5.pause();
        }
        afficheResultat = "Temps ecoule : " + to_string(mGame.getTempsEcoule()) + " sec";

        auto res = mBoutons.find("Resultat");
        (*res).second->setString(afficheResultat);
        mWindow.draw(*(*res).second);

        auto repr = mBoutons.find("Reprendre");
        mWindow.draw(*(*repr).second);

        auto quit = mBoutons.find("Retour au menu");
        mWindow.draw(*(*quit).second);

    } else if (mPause == 2) {
        if (music0.getStatus() == sf::Music::Status::Playing) {
            music0.stop();
            musicB.play();
        } else if (music1.getStatus() == sf::Music::Status::Playing) {
            music1.stop();
            musicB.play();
        } else if (music2.getStatus() == sf::Music::Status::Playing) {
            music2.stop();
            musicB.play();
        } else if (music3.getStatus() == sf::Music::Status::Playing) {
            music3.stop();
            musicB.play();
        } else if (music4.getStatus() == sf::Music::Status::Playing) {
            music4.stop();
            musicB.play();
        } else if (music5.getStatus() == sf::Music::Status::Playing) {
            music5.stop();
            musicB.play();
        }

        afficheResultat = "Temps ecoule : " + to_string(mGame.getTempsEcoule()) + " sec";

        auto res = mBoutons.find("Resultat");
        (*res).second->setString(afficheResultat);
        mWindow.draw(*(*res).second);

        auto reco = mBoutons.find("Recommencer");
        mWindow.draw(*(*reco).second);

        auto ns = mBoutons.find("Niveau suivant");
        mWindow.draw(*(*ns).second);

        auto quitt = mBoutons.find("Retour au menu");
        mWindow.draw(*(*quitt).second);

		mWin.setString(mGame.getWinner() + " a gagné en " + to_string(mGame.getTempsEcoule()) + "s");
		mWin.setPosition(mWindow.getSize().x / 2 - mWin.getGlobalBounds().width / 2, 130);
		mWindow.draw(mWin);
	}
	else {

        while (deb != fin) {
            if (((*deb).first.compare("Reprendre")) != 0 && ((*deb).first.compare("Recommencer")) != 0 && ((*deb).first.compare("Niveau suivant")) != 0 && ((*deb).first.compare("Retour au menu")) != 0 && ((*deb).first.compare("Resultat")) != 0) {
                mWindow.draw(*(*deb).second);
            }
            ++deb;
        }
    }
}

void Menu::processEvents() {
//	mGame.run();/////////////////////////////////// test

    sf::Event event;
    if (isMouseOver("Jouer") && mPause == 0) {
        getBouton("Jouer")->setColor(sf::Color::Red);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            musicDeb.stop();
            music0.play();
            mPause = mGame.run();

        }
    } else if (isMouseOver("Options") && mPause == 0) {
        getBouton("Options")->setColor(sf::Color::Red);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            MenuOptions opt(mWindow);
            while (opt.processEventsOpt()) {
                mWindow.clear();
                opt.afficherBoutons();
                mWindow.display();
            }

            mPause = 0;
        }
    } else if (isMouseOver("Credits") && mPause == 0) {
        getBouton("Credits")->setColor(sf::Color::Red);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            MenuCredit cre(mWindow);
            while (cre.processEventsCre()) {
                mWindow.clear();
                cre.afficherBoutons();
                mWindow.display();
            }

            mPause = 0;
        }
    } else if (isMouseOver("Quitter") && mPause == 0) {
        getBouton("Quitter")->setColor(sf::Color::Red);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            mWindow.close();
        }

    } else if (isMouseOver("Reprendre") && mPause == 1) {
        getBouton("Reprendre")->setColor(sf::Color::Red);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (music0.getStatus() == sf::Music::Status::Paused) {
                music0.play();
            } else if (music1.getStatus() == sf::Music::Status::Paused) {
                music1.play();
            } else if (music2.getStatus() == sf::Music::Status::Paused) {
                music2.play();
            } else if (music3.getStatus() == sf::Music::Status::Paused) {
                music3.play();
            } else if (music4.getStatus() == sf::Music::Status::Paused) {
                music4.play();
            } else {
                music5.play();
            }
            mPause = mGame.run();
        }
    } else if (isMouseOver("Niveau suivant") && mPause == 2) {
        getBouton("Niveau suivant")->setColor(sf::Color::Red);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            musicB.stop();
			if (mNumMusic <= 0 || mNumMusic >= 6) {
				mNumMusic = 0;
                music0.play();
            } else if (mNumMusic == 1) {
                music1.play();
            } else if (mNumMusic == 2) {
                music2.play();
            } else if (mNumMusic == 3) {
                music3.play();
            } else if (mNumMusic == 4) {
                music4.play();
            } else if (mNumMusic == 5) {
                music5.play();
            }

            mNumMusic++;

			mGame.mapSuivante();
            mPause = mGame.run();
        }

    } else if (isMouseOver("Recommencer") && mPause == 2) {
        getBouton("Recommencer")->setColor(sf::Color::Red);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            musicB.stop();
            if (music0.getStatus() == sf::Music::Status::Stopped) {
                music0.play();
            } else if (music1.getStatus() == sf::Music::Status::Stopped) {
                music1.play();
            } else if (music2.getStatus() == sf::Music::Status::Stopped) {
                music2.play();
            } else if (music3.getStatus() == sf::Music::Status::Stopped) {
                music3.play();
            } else if (music4.getStatus() == sf::Music::Status::Stopped) {
                music4.play();
            } else {
                music5.play();
            }

			mGame.reset();
            mPause = mGame.run();
        }
    } else if (isMouseOver("Retour au menu")&& (mPause == 1 || mPause == 2)) {
        getBouton("Retour au menu")->setColor(sf::Color::Red);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            musicB.stop();
            if (music0.getStatus() == sf::Music::Status::Paused || music0.getStatus() == sf::Music::Status::Stopped) {
                music0.stop();
                musicDeb.play();
            } else if (music1.getStatus() == sf::Music::Status::Paused || music1.getStatus() == sf::Music::Status::Stopped) {
                music1.stop();
                musicDeb.play();
            } else if (music2.getStatus() == sf::Music::Status::Paused || music2.getStatus() == sf::Music::Status::Stopped) {
                music2.stop();
                musicDeb.play();
            } else if (music3.getStatus() == sf::Music::Status::Paused || music3.getStatus() == sf::Music::Status::Stopped) {
                music3.stop();
                musicDeb.play();
            } else if (music4.getStatus() == sf::Music::Status::Paused || music4.getStatus() == sf::Music::Status::Stopped) {
                music4.stop();
                musicDeb.play();
            } else {
                music5.stop();
                musicDeb.play();
            }
            mPause = 0;
        }

    } else {
        getBouton("Jouer")->setColor(sf::Color::Blue);
        getBouton("Options")->setColor(sf::Color::Blue);
        getBouton("Credits")->setColor(sf::Color::Blue);
        getBouton("Quitter")->setColor(sf::Color::Blue);
        getBouton("Reprendre")->setColor(sf::Color::Blue);
        getBouton("Niveau suivant")->setColor(sf::Color::Blue);
        getBouton("Recommencer")->setColor(sf::Color::Blue);
        getBouton("Retour au menu")->setColor(sf::Color::Blue);
    }

    while (mWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            mWindow.close();
        }
    }
}

void Menu::chargerMusic(sf::Music& music, string nom) {

    if (music.openFromFile(pathMusic + nom)) {

        music.setVolume(10);
        if (nom.compare("B.ogg") != 0) {
            music.setLoop(true);
        }
    }
}

Menu::~Menu() {
    auto deb = mBoutons.begin();
    auto fin = mBoutons.end();

    while (deb != fin) {
        delete (*deb).second;
        ++deb;
    }
}
