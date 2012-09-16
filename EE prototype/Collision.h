///////////////////////////////////////////////////////////////////////////////
// COPYRIGHT © 2009 Jeb Bradwell & Adam Zech
// This file is distributed under the terms of the GNU General Public License
///////////////////////////////////////////////////////////////////////////////
/// @file collision.h
///
/// @brief
/// Header file for the collision functions
///
/// @remarks
/// The collision functions are used to determine if two sprites collide and how they react to the collision.
///////////////////////////////////////////////////////////////////////////////

#ifndef COLLISION_H
#define COLLISION_H

//SYSTEM INCLUDES
#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <ostream>
#include <fstream>

//SFML INCLUDES
#include "SFML/Graphics.hpp"
#include "GameObject.h"
//#include "SFML/Rect.hpp"


//USING STATEMENTS
using std::vector;
using std::string;
using std::pair;
using std::ofstream;
using std::cerr;
using std::cout;
using std::endl;
//using std::auto_ptr;
using sf::Image;
using sf::Sprite;
using namespace std;


///////////////////////////////////////////////////////////////////////////////
/// @namesapce Collision
///
/// @brief
/// Collision functions.
///
/// @remarks
/// methods for collision detection.
///////////////////////////////////////////////////////////////////////////////
namespace Collision
{
	bool ObjectsCollide(GameObject *o1, GameObject *o2);
	vector< sf::Vector2< int > > PixelsCollide(GameObject *o1, GameObject *o2);
	sf::Rect<int> RectFromShapes(vector<sf::Shape>);
}

#endif //#define COLLISION_H
