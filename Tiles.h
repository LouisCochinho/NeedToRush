
#ifndef TILES_H
#define	TILES_H

#include "RessourcesManager.h"

#define	SIZE_TILES 21
#define	MARGE 2
#define	ESPACEMENT 2
#define	NB_TILES_PAR_LIGNE 30

class Tiles : public sf::Sprite {
public:
	Tiles(std::string path, float x, float y, int id, int type);


    sf::FloatRect getHitBox();
    void setHitBox(sf::FloatRect hitBox);
    void setHitBox(float left, float top, float with, float height);
    
    int getType();

    enum Type {
        NONE = 1, 
        NORMAL = 2, 
        KILL = 3, 
        WIN = 4
    };

private:
    sf::FloatRect mHitBox;
    int mID, mType;
};

#endif	/* TILES_H */

