#ifndef ANIMATION_H
#define	ANIMATION_H

#include "RessourcesManager.h"

class Animation : public sf::Sprite {
public:
    Animation(string path, int nbFrameX, sf::Time timeLoop);

    void update(sf::Time time);

private:
    sf::Time mTimeLoop;
    sf::Time mTimeSinceLastUpdateFrame;

    std::vector<sf::IntRect> mFrames;
    int mNumFrame, mNbFrame;
};

#endif	/* ANIMATION_H */

