///////////////////////////////////////////////////////////////////////////////
// COPYRIGHT © 2009 Jeb Bradwell & Adam Zech
// This file is distributed under the terms of the GNU General Public License
///////////////////////////////////////////////////////////////////////////////
/// @file tile.h
///
/// @brief
/// Tile class header file
///
/// @remarks
/// Class for individual tiles
///////////////////////////////////////////////////////////////////////////////

#ifndef TILE_H
#define TILE_H

//SYSTEM INCLUDES
#include <string>

//USING STATEMENTS
using std::string;

///////////////////////////////////////////////////////////////////////////////
/// @class Tile
///
/// @brief
/// Tile class definition.
///
/// @remarks
/// The Tile class has member variables for all the different
/// properties a Tile has. Tiles do not hold their own destination
/// Tiles are placed by Maps. This helps save a lot of memory when
/// trying to serialize tiles, also uses less resources if you are
/// placing a tile in multiple places and the only difference is 
/// it's destination X & Y.
///////////////////////////////////////////////////////////////////////////////
class Tile
{
public:

	/// Tile default constructor.
	///
	/// Constructs an empty Tile object. All member variables are
	/// set to defaults
	/// @see Tile Defaults Document
	Tile();

	//PUBLIC VARIABLES

	enum terrains
	{
		normal,
		water,
		mud,
		sand,
		stairsLeftUp,
		stairsLeftDown,
		stairsRightUp,
		stairsRightDown,
		stairsUpUp,
		stairsUpDown,
		stairsDownUp,
		stairsDownDown,
	};

	enum rotations
	{
		R0,
		R90,
		R180,
		R270
	};

	/// A public variable - holds the chipset file name for this tile.
	string chipSetName;
	/// A public variable - used to uniquely identify tiles.
	unsigned int tileID;
	/// A public variable - holds the chipset X coordinate location for this tile.
	float srcX;
	/// A public variable - holds the chipset Y coordinate location for this tile.
	float srcY;
	/// A public variable - holds the tiles width in 16 pixel multiples
	int width;
	/// A public variable - holds the tiles height in 16 pixel multiples
	int height;
	/// A public variable - holds the rotation of the selected tile. values examples: 0, 90, 180, 270
	int rotation;
	/// A public variable - can be any integer from -infinity to +infinity, 0 being ground level.
	int level; 
	/// A public variable - holds the integer which is associated with the terrain type for this tile.
	int terrainType; 
};

#endif //TILE_H