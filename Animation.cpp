/* 
 * File:   Animation.cpp
 * Author: rezzouqs
 * 
 * Created on 2 février 2015, 15:26
 */

#include "Animation.h"

Animation::Animation(string nomImage, int nbFrameX, sf::Time timeLoop) :
mTimeLoop(timeLoop), mNumFrame(0), mNbFrame(nbFrameX) {
    setTexture(*RessourcesManager::getTexture(nomImage));

    int L = getGlobalBounds().width / nbFrameX;
    for (int i = 0; i < nbFrameX; i++)
        mFrames.push_back(sf::IntRect(i * L, 0, L, getGlobalBounds().height));

    setTextureRect(mFrames[mNumFrame]);
}

void Animation::update(sf::Time time) {
    mTimeSinceLastUpdateFrame += time;
    if (mTimeSinceLastUpdateFrame > mTimeLoop) {
        if (++mNumFrame >= mNbFrame)
            mNumFrame = 0;

        setTextureRect(mFrames[mNumFrame]);
        mTimeSinceLastUpdateFrame = sf::Time::Zero;
    }
}
