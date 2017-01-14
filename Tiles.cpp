#include "Tiles.h"

Tiles::Tiles(std::string nomImage, float x, float y, int id, int type) : mID(id), mType(type) {

    setTexture(*RessourcesManager::getTexture(nomImage));

    setPosition(SIZE_TILES * x, SIZE_TILES * y);

    setTextureRect(sf::IntRect(
            MARGE + (SIZE_TILES + ESPACEMENT) * (mID % 30),
            MARGE + (SIZE_TILES + ESPACEMENT) * (mID / 30),
            SIZE_TILES, SIZE_TILES)
            );

    mHitBox = getGlobalBounds();

	if (mID == 70 || mID == 573) {
		mHitBox.top += mHitBox.height / 2;
	}
	else if (mID == 894 || mID == 896) {
		mHitBox.height /= 2;
		mHitBox.top += mHitBox.height / 2;
	}
}

sf::FloatRect Tiles::getHitBox() {
    return mHitBox;
}

void Tiles::setHitBox(sf::FloatRect hitBox) {
    mHitBox = hitBox;
}

void Tiles::setHitBox(float left, float top, float with, float height) {
    mHitBox.left = left;
    mHitBox.top = top;
    mHitBox.width = with;
    mHitBox.height = height;
}

int Tiles::getType() {
    return mType;
}
