#ifndef PERSONNAGE_H
#define	PERSONNAGE_H

#include "Animation.h"
#include <fstream>

class Personnage {
public:

    enum Etat {
        COURS, ATTEND, SAUTE
    };

    enum Direction {
        DROITE, GAUCHE
    };

    Personnage(string pathData, float x, float y, string pseudo);
    ~Personnage() ;

    sf::Sprite getSprite();
    Animation* getAnimationCourante();

    void handleInput();
    void update(sf::Time time);

    sf::Vector2f getPosition() const;
    void setPosition(sf::Vector2f mPosition);

    sf::FloatRect getHitbox();

    void setVitesseY(float vitesseY);
    float getVitesseY();

    bool isPeutSauter();
    void setPeutSauter(bool peutSauter);

	void setSpawn(sf::Vector2f spawn);
	void respawn();
    string getPseudo();  

private:
    map<string, Animation*> mAnimations;
    string mAnimationCourante, mPseudo;

    sf::Vector2f mPosition, mPositionSpawn;

    int mEtat, mDirection;
    float mVitesseX, mVitesseY, mSaute, V_GRAV, V_SAUT;

    bool mPeutSauter;

    sf::Keyboard::Key mKeySaut, mKeyGauche, mKeyDroite;
};

#endif	/* PERSONNAGE_H */

