#include "SFML/Graphics.hpp"

#include "Personnage.h"

Personnage::Personnage(string pathData, float x, float y, string pseudo) : mVitesseX(250), mEtat(COURS), mDirection(DROITE), V_GRAV(900), V_SAUT(325), mVitesseY(0),
mPosition(x, y), mPositionSpawn(x, y), mSaute(false), mPeutSauter(false), mPseudo(pseudo) {

    ifstream fichier("data/players/" + pathData, ios::in);

    if (fichier) {
        string imgCours, imgAttend, imgSaut;
        fichier >> imgCours;
        fichier >> imgAttend;
        fichier >> imgSaut;

        mAnimationCourante = "Attend Droite";
        mAnimations.insert(pair<string, Animation*>("Cours Droite", new Animation(imgCours, 3, sf::seconds(0.08f))));
        mAnimations.insert(pair<string, Animation*>("Cours Gauche", new Animation(imgCours, 3, sf::seconds(0.08f))));
        mAnimations.insert(pair<string, Animation*>("Attend Droite", new Animation(imgAttend, 2, sf::seconds(0.12f))));
        mAnimations.insert(pair<string, Animation*>("Attend Gauche", new Animation(imgAttend, 2, sf::seconds(0.12f))));
        mAnimations.insert(pair<string, Animation*>("Saute Gauche", new Animation(imgSaut, 1, sf::seconds(0.12f))));
        mAnimations.insert(pair<string, Animation*>("Saute Droite", new Animation(imgSaut, 1, sf::seconds(0.08f))));

        int kS, kG, kD;
        fichier >> kS;
        fichier >> kG;
        fichier >> kD;
        mKeySaut = static_cast<sf::Keyboard::Key>(kS);
        mKeyGauche = static_cast<sf::Keyboard::Key>(kG);
        mKeyDroite = static_cast<sf::Keyboard::Key>(kD);

        fichier.close();
    }
}

sf::Sprite Personnage::getSprite() {
    return *getAnimationCourante();
}

Animation* Personnage::getAnimationCourante() {
    return (mAnimations.find(mAnimationCourante))->second;
}

void Personnage::update(sf::Time time) {
    if (mEtat == COURS) {
        if (mDirection == DROITE) {
            mAnimationCourante = "Cours Droite";
            mPosition.x += mVitesseX * time.asSeconds();
        } else if (mDirection == GAUCHE) {
            mAnimationCourante = "Cours Gauche";
            mPosition.x -= mVitesseX * time.asSeconds();
        }
    } else {
        if (mDirection == DROITE)
            mAnimationCourante = "Attend Droite";
        else if (mDirection == GAUCHE)
            mAnimationCourante = "Attend Gauche";
    }

    if (mSaute) {
        if (mDirection == DROITE)
            mAnimationCourante = "Saute Droite";
        else if (mDirection == GAUCHE)
            mAnimationCourante = "Saute Gauche";
    }

    if (mSaute && mVitesseY <= 10) {
        mSaute = false;
    }

    getAnimationCourante()->update(time);
    getAnimationCourante()->setPosition(mPosition);

    if (mAnimationCourante == "Attend Gauche" || mAnimationCourante == "Cours Gauche" || mAnimationCourante == "Saute Gauche") {
        getAnimationCourante()->setOrigin(72, 0);
        getAnimationCourante()->setScale(-0.5f, 0.5f);
    } else {
        getAnimationCourante()->setScale(0.5f, 0.5f);
    }

    mVitesseY -= V_GRAV * time.asSeconds();
    mPosition.y -= mVitesseY * time.asSeconds();
}

void Personnage::handleInput() {
    if (sf::Keyboard::isKeyPressed(mKeyDroite) && !sf::Keyboard::isKeyPressed(mKeyGauche)) {
        mEtat = COURS;
        mDirection = DROITE;
    } else if (sf::Keyboard::isKeyPressed(mKeyGauche) && !sf::Keyboard::isKeyPressed(mKeyDroite)) {
        mEtat = COURS;
        mDirection = GAUCHE;
    } else {
        mEtat = ATTEND;
    }

    if (sf::Keyboard::isKeyPressed(mKeySaut) && mPeutSauter) {
        mSaute = true;
        mVitesseY = V_SAUT;
    }
}

sf::FloatRect Personnage::getHitbox() {
    sf::FloatRect hitbox = this->getAnimationCourante()->getGlobalBounds();
    hitbox.width -= 2;
    hitbox.height -= 2;
    hitbox.top = mPosition.y + 1;
    hitbox.left = mPosition.x + 1;
    return hitbox;
}

bool Personnage::isPeutSauter() {
    return mPeutSauter;
}

void Personnage::setPeutSauter(bool peutSauter) {
    this->mPeutSauter = peutSauter;
}

sf::Vector2f Personnage::getPosition() const {
    return mPosition;
}

void Personnage::setPosition(sf::Vector2f mPosition) {
    this->mPosition = mPosition;
}

void Personnage::setVitesseY(float vitesseY) {
    this->mVitesseY = vitesseY;
}

float Personnage::getVitesseY() {
    return this->mVitesseY;
}

void Personnage::setSpawn(sf::Vector2f spawn) {
	mPositionSpawn = spawn;
}

void Personnage::respawn() {
    setPosition(mPositionSpawn);

	mVitesseY = 0;
}

string Personnage::getPseudo() {
    return mPseudo;
}


Personnage::~Personnage() {
    auto deb = mAnimations.begin();
    auto fin = mAnimations.end();

    while (deb != fin) {
        delete (*deb).second;
        ++deb;
    }
}
