///////////////////////////////////////////////////////////////////////////////
// COPYRIGHT © 2009 Jeb Bradwell, Adam Zech & Ron Moore
// This file is distributed under the terms of the GNU General Public License
///////////////////////////////////////////////////////////////////////////////
/// @file tile.cpp
///
/// @brief
/// Defines the tile class functions.
///
/// @remarks
/// This file has the default constructor which sets all member variables to
/// their default values
/// @see Tile Default Document { need URL here }
////////////////////////////////////////////////////////////////////////////////

#include "tile.h"

Tile::Tile()
{
	this->chipSetName = "chipset0";
	this->height = 0;
	this->level = 0;
	this->rotation = 0;
	this->srcX = 0;
	this->srcY = 0;
	this->terrainType = 0;
	this->tileID = 0;
	this->width = 0;
}