///////////////////////////////////////////////////////////////////////////////
// COPYRIGHT © 2009 Jeb Bradwell & Adam Zech
// This file is distributed under the terms of the GNU General Public License
///////////////////////////////////////////////////////////////////////////////
/// @file map.h
///
/// @brief
/// Map class header file
///
/// @remarks
/// Class for individual Maps
///////////////////////////////////////////////////////////////////////////////

#ifndef MAP_H
#define MAP_H

//SYSTEM INCLUDES
#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <ostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>

//SFML INCLUDES
#include "SFML/Graphics.hpp"

//LOCAL INCLUDES
#include "tile.h"
#include "to_string.h"


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


///////////////////////////////////////////////////////////////////////////////
/// @class Map
///
/// @brief
/// Map class definition.
///
/// @remarks
/// The Map class has member variables for all the different
/// properties a Map has.
///////////////////////////////////////////////////////////////////////////////
class Map
{
public:

	//PUBLIC FUNCTIONS

	/// Map Constructor.
	///
	/// constructs an empty Map object. All member variables are
	/// set to defaults
	/// @see Map Defaults Document
	Map();

	/// Map Constructor.
	///
	/// takes a map xml file name{string} and loads it into memory.
	Map( const char *mapFile );

	~Map();

	void load( const char *mapFile);
	void save(const char *mapFile);

	//PUBLIC VARIABLES

	/// A public variable - holds the name of the map
	string mapName;

	/// A public variable - holds the width in 16 pixel multiples.
	int width;

	/// A public variable - holds the height in 16 pixel multiples.
	int height;

	/// A public variable - stores the total number of levels this map contains.
	int levelTotal;

	/// A public variable - holds all individual tile's.
	vector<Tile> tiles;

	/// A public variable - holds each tile's name and ****** destination X & Y ******. Maps place their tiles.
	vector< pair< unsigned int /*Tile ID*/, pair<float/*DesX*/, float/*DesY*/> > > tileDestionations;
};

#endif //#define MAP_H
