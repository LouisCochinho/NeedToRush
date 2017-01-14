#include "Game.h"

Game::Game(sf::RenderWindow& window) : mPlayer("p1.txt", 30, 30, "Joueur Bleu"), mPlayer2("p2.txt", 30, 30, "Joueur Rose"), mWiner("none"),
mWindow(window), mContinuer(0), tpsEcoule(0) {

    mMap[0] = ifstream("data/maps/MapPourLesNoobs.txt", ios::out);
	mMap[1] = ifstream("data/maps/TuVeuxUnSusucre.txt", ios::out);
	mMap[2] = ifstream("data/maps/AuBistrotAvecRobert.txt", ios::out);
	mMap[3] = ifstream("data/maps/GillesBonhomme.txt", ios::out);
	mMap[4] = ifstream("data/maps/MapOpposeeRichard.txt", ios::out);
	mMap[5] = ifstream("data/maps/RainbowRoad.txt", ios::out);
	mMap[6] = ifstream("data/maps/ImInLoveWithTheCoco.txt", ios::out);

	int n, m;
	ifstream fichier("data/maps/listTilesNone.txt", ios::out);
	if (fichier) {
		while (!fichier.eof()) {
			fichier >> n;
			mTilesNONE.push_back(n);
		}
		fichier.close();
	}

	ifstream fichier2("data/maps/listTilesKill.txt", ios::out);
	if (fichier2) {
		while (!fichier2.eof()) {
			fichier2 >> n;
			mTilesKILL.push_back(n);
		}
		fichier2.close();
	}

	ifstream fichier3("data/maps/listTilesWin.txt", ios::out);
	if (fichier3) {
		while (!fichier3.eof()) {
			fichier3 >> n;
			mTilesWIN.push_back(n);
		}
		fichier3.close();
	}

	ifstream fichier4("data/maps/spawn.txt", ios::out);
	if (fichier4) {
		while (!fichier4.eof()) {
			fichier4 >> n;
			fichier4 >> m;
			mSpawn.push_back(sf::Vector2f(n, m));
		}
		fichier4.close();
	}

	setMapCourante(0);
}

Game::~Game() {
    auto deb = mTiles.begin();
    auto fin = mTiles.end();

    while (deb != fin) {
        delete(*deb);
        ++deb;
    }

	for (int i = 0; i < 6; i++)
		mMap[i].close();
}

int Game::run() {
    mContinuer = 0;
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

    while (mWindow.isOpen() && mContinuer == 0) {
        processEvents();

        timeSinceLastUpdate += clock.restart();

        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }

        render();
    }

    return mContinuer;
}

void Game::processEvents() {
    mPlayer.handleInput();
    mPlayer2.handleInput();

    sf::Event event;
    while (mWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            mWindow.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            mContinuer = 1;
            tpsEcoule = getChrono();
        }
    }
}

void Game::update(sf::Time time) {
    mPlayer.update(time);
    mPlayer2.update(time);

    auto deb = mTiles.begin();
    auto fin = mTiles.end();

    mPlayer.setPeutSauter(false);
    while (deb != fin) {
        repositionnementJoueur(mPlayer, *(*deb));
        ++deb;
    }

    deb = mTiles.begin();

    mPlayer2.setPeutSauter(false);
    while (deb != fin) {
        repositionnementJoueur(mPlayer2, *(*deb));
        ++deb;
    }
}

void Game::render() {
    mWindow.clear(sf::Color::White);

    auto deb = mTiles.begin();
    auto fin = mTiles.end();

    while (deb != fin) {
        mWindow.draw(*(*deb));

        ++deb;
    }

    mWindow.draw(mPlayer.getSprite());
    mWindow.draw(mPlayer2.getSprite());
    mWindow.display();
}

bool Game::collide(sf::FloatRect hitboxPlayer, Tiles &obj2) {
    if (hitboxPlayer.left + hitboxPlayer.width < obj2.getPosition().x ||
            hitboxPlayer.left > obj2.getPosition().x + obj2.getGlobalBounds().width ||
            hitboxPlayer.top + hitboxPlayer.height < obj2.getHitBox().top ||
			hitboxPlayer.top > obj2.getHitBox().top + obj2.getGlobalBounds().height)
        return false;
    else
        return true;
}

string Game::whereIsTheCollision(sf::FloatRect hitboxPlayer, Tiles &obj2) {
    if (hitboxPlayer.left < obj2.getPosition().x &&
            hitboxPlayer.left + hitboxPlayer.width > obj2.getPosition().x &&
			hitboxPlayer.top + hitboxPlayer.height - 10 > obj2.getHitBox().top &&
			hitboxPlayer.top + hitboxPlayer.height - 10 < obj2.getHitBox().top + obj2.getGlobalBounds().height + 20) {
        return "gauche";
    } else if (hitboxPlayer.left < obj2.getPosition().x + obj2.getGlobalBounds().width &&
            hitboxPlayer.left + hitboxPlayer.width > obj2.getPosition().x + obj2.getGlobalBounds().width &&
			hitboxPlayer.top + hitboxPlayer.height - 10 > obj2.getHitBox().top &&
			hitboxPlayer.top + hitboxPlayer.height - 10 < obj2.getHitBox().top + obj2.getGlobalBounds().height + 20) {
        return "droite";
	} else if (hitboxPlayer.top < obj2.getHitBox().top &&
		hitboxPlayer.top + hitboxPlayer.height > obj2.getHitBox().top) {
        return "haut";
    } else {
        return "bas";
    }
}

void Game::repositionnementJoueur(Personnage& player, Tiles &obj2) {
	if (player.getPosition().x < -100 || player.getPosition().x > mWindow.getSize().x + 100 ||
		player.getPosition().y < -100 || player.getPosition().y > mWindow.getSize().y + 100)
	{
		player.respawn();
	} 
	else if (obj2.getType() != Tiles::NONE && collide(player.getHitbox(), obj2))
	{
        if (obj2.getType() == Tiles::KILL) {
            player.respawn();
        }
        else if (obj2.getType() == Tiles::WIN) {
            mContinuer = 2;
            tpsEcoule = chrono.restart().asSeconds();
			cout << "tpsEcoule = " << tpsEcoule << endl;
			mWiner = player.getPseudo();
        }

        else {
            string collisionPlace = whereIsTheCollision(player.getHitbox(), obj2);

            if (collisionPlace.compare("droite") == 0) {
                player.setPosition(sf::Vector2f(obj2.getPosition().x + obj2.getHitBox().width + 0.2f, player.getPosition().y));

            } else if (collisionPlace.compare("gauche") == 0) {
                player.setPosition(sf::Vector2f(obj2.getPosition().x - player.getHitbox().width - 0.2f, player.getPosition().y));

            } else if (collisionPlace.compare("haut") == 0) {
                if (player.getVitesseY() < -10 || player.getVitesseY() > 10)
                    player.setVitesseY(0);
                player.setPeutSauter(true);

				player.setPosition(sf::Vector2f(player.getPosition().x, obj2.getHitBox().top - player.getHitbox().height - 0.2f));

            } else {
                player.setVitesseY(0.f);
				player.setPosition(sf::Vector2f(player.getPosition().x, obj2.getHitBox().top + obj2.getHitBox().height + 0.2f));
            }
        }
    }
}

float Game::getChrono() {
    return chrono.getElapsedTime().asSeconds();
}

float Game::getTempsEcoule() {
    return tpsEcoule;
}

void Game::setMapCourante(int mapCourante) {
	mMapCourante = mapCourante;

	mPlayer2.setSpawn(mSpawn[mMapCourante]);
	mPlayer2.respawn();
	mPlayer.setSpawn(mSpawn[mMapCourante]);
	mPlayer.respawn();

	mTiles.clear();

	mMap[mMapCourante].seekg(0);
	int n = 0;
	if (mMap[mMapCourante]) {
		for (int j = 0; j < NB_TILES_A_AFF_Y; j++) {
			for (int i = 0; i < NB_TILES_A_AFF_X; i++) {
				mMap[mMapCourante] >> n;
				if (n != 0) {
					mTiles.emplace_back(new Tiles("spritesheet.png", i, j, (n - 1), getType(n)));
				}
			}
		}
	}
}

void Game::mapSuivante() {
	if (mMapCourante < NB_MAP-1)
		setMapCourante(mMapCourante + 1);
	else
		setMapCourante(0);
}

int Game::getType(int idTile) {

	auto deb = mTilesNONE.begin();
	auto fin = mTilesNONE.end();
	while (deb != fin) {
		if (idTile == (*deb))
			return Tiles::NONE;
		++deb;
	}

	deb = mTilesKILL.begin();
	fin = mTilesKILL.end();
	while (deb != fin) {
		if (idTile == (*deb))
			return Tiles::KILL;
		++deb;
	}

	deb = mTilesWIN.begin();
	fin = mTilesWIN.end();
	while (deb != fin) {
		if (idTile == (*deb))
			return Tiles::WIN;
		++deb;
	}

	return Tiles::NORMAL;
}

string Game::getWinner() {
	return mWiner;
}

void Game::reset() {
	mPlayer.respawn();
	mPlayer2.respawn();
}
