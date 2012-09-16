#ifndef GAME_CLASS_H
#define GAME_CLASS_H

//SYSTEM INCLUDES
#include <map>
#include <vector>

//LOCAL INCLUDES
#include "GameObjectClass.h"
#include "Singleton.h"
#include "Item.h"

#define PI 3.14159265f
#define SQRT2OVER2 0.70710678118654752440084436210485f
#define KEYBOARD 1
#define CONTROLLER 0
#define TILE_DRAW 1
#define SCREEN_NAME "Engine Testing"

//these need to be in the player class eventually
const float speed = 90;
const int radius = 5;

class GameClass
{
public:
	GameClass();
	std::map<int, GameObjectClass *> mGameObjects;
	sf::Sprite PlayerSprite;
	sf::RenderWindow *App;
	int ScreenWidth;
	int ScreenHeight;
	int MapWidth;
	int MapHeight;
	int difficulty; //can be 0-Easy 1-Medium 2-Hard
	int screenSize; //can be 0-800x600 1-1024x768
	int input; //can be 0-Keyboard 1-Controller 
	int fullscreen; //whether the game is played in fullscreen or window mode
	std::string screenName;
	int characterSheetID;
	int elucidatePaletteID;
	int inventorySheetID;
	int elucidatePalette_XPos;
	int elucidatePalette_YPos;
	int characterSheet_XPos;
	int characterSheet_YPos;
	int inventorySheet_XPos;
	int inventorySheet_YPos;
	Item *itemHolder;
};
typedef std::map<int, GameObjectClass *>::iterator mGameObject_iter;

typedef Singleton<GameClass> Game;
#endif