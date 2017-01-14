#ifndef GAME_H
#define	GAME_H

#include "Personnage.h"
#include "Tiles.h"

#define	NB_TILES_A_AFF_X 50
#define	NB_TILES_A_AFF_Y 30
#define	NB_MAP 7

class Game {
public:
    Game(sf::RenderWindow& window);
    ~Game(); 

    int run();
    float getChrono();
    float getTempsEcoule();

	void setMapCourante(int mapCourante);
	void mapSuivante();
	int getType(int idTile);

	string getWinner();
	void reset();

private:
    void processEvents();
    void update(sf::Time time);
    void render();
    bool collide(sf::FloatRect hitbox, Tiles &obj2);
    string whereIsTheCollision(sf::FloatRect hitbox, Tiles &obj2);
    void repositionnementJoueur(Personnage& player, Tiles &mur);

    sf::RenderWindow& mWindow;
    
    Personnage mPlayer, mPlayer2;
    list<Tiles*> mTiles;
    sf::Clock chrono;
    float tpsEcoule;
    int mContinuer, mMapCourante;
	string mWiner;

	ifstream mMap[NB_MAP];	
	vector<sf::Vector2f> mSpawn;

	vector<int> mTilesNONE;
	vector<int> mTilesKILL;
	vector<int> mTilesWIN;
	vector<int> mTilesDemi;
};

#endif	/* GAME_H */

