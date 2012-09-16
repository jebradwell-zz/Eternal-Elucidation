#ifndef MAPEDTIOR_H
#define MAPEDTIOR_H

#include "map.h"
#include "tile.h"
#include "tileeditor.h"

#include <SFML/Graphics.hpp>
#include "cpGUI_base.h"
#include "cpTextBox.h"
#include "cpSelection-DropDownBox.h"
#include "cpImageButton.h"
#include "cpShapeButton.h"
#include "cpCheckBox.h"
#include "cpTextInputBox.h"

class MapEditor
{
public:
	MapEditor(){}

	void width( int width );
	int width();

	void height( int height );
	int height();

	void selectTileLeftClick();
	void selectTileLeftUnclick();
	void selectTileRightClick();
	void selectTileRightUnclick();

	void placeTileLeftClick();
	void placeTileLeftUnclick();
	void placeTileRightClick();
	void placeTileRightUnclick();

	void collisionLeftClick();
	void collisionLeftUnclick();
	void collisionRightClick();
	void collisionRightUnclick();

	void terrainLeftClick();
	void terrainRightClick();

	void addTopLevel();
	void addBottomLevel();
	void deleteTopLevel();
	void deleteBottomLevel();

	void serializeMap(); //save
	void deserializeMap(); //load

	void loadChipset();

	void editorWindow();
	//void chipsetWindow(void* UserData);

private:
	Map *map;
	TileEditor *tileeditor;
};

#endif //MAPEDTIOR_H