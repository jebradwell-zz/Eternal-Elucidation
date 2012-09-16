#ifndef TILEEDITOR_H
#define TILEEDITOR_H

#include "tile.h"

#define BLOCKSIZE 16

class TileEditor
{
public:
	TileEditor(){}
	TileEditor( Tile &tile ){}
	void setTile( Tile &tile );
	const char *tileName();
	void tileName( const char * name );
	const char *chipSetName();
	void chipSetName( const char * name );
	int width();
	void width( int width );
	int height();
	void height( int height );
	void chipset( const char *name );
	int srcX();
	void srcX( int srcX );
	int srcY();
	void srcY( int srcY );
	int srcWidth();
	void srcWidth( int srcWidth );
	int srcHeight();
	void srcHeight( int srcHeight );
	int level();
	void level( int level );
	int terrain();
	void terrain( int terrainType );

private:
	Tile tile;
};

#endif //TILEEDITOR_H