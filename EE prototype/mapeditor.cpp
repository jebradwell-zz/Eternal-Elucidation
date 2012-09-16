#include "mapeditor.h"
#include "assert.h"
#include "math.h"
#include "Singleton.h"
#include "dirent.h"
#include "to_string.h"

#include <sstream>

#define TILE_SQUARE 16
#define FRAME_RATE 24

typedef Singleton< std::pair< std::pair<float, float>, std::pair<float, float> > > selection_i;

bool tile_change_tile_editor = false;
bool addTilePushed = false;

std::vector<sf::Image> chipsetImages;
int chipset_selected = 0;
std::vector<std::string> chipsetNamesVec;

std::vector<Tile> tileQueue;
int tileQueueIndex = 0;

int getChipsetIndex(std::string chipsetName)
{
	for(unsigned int i = 0; i < chipsetNamesVec.size(); i++)
	{
		if( chipsetName.compare(chipsetNamesVec.at(i)) == 0 )
		{
			return i;
		}
	}
	//index will never be -1 thus a good number to check for.
	return -1;
}
void setTileQueueBtns( cp::cpImageButton *b1, 
					  cp::cpImageButton *b2, 
					  cp::cpImageButton *b3, 
					  cp::cpImageButton *b4, 
					  cp::cpImageButton *b5, sf::Image placeHolder)
{

	if( tileQueue.size() > 0 )
	{
		int btnIndex = 0;
		//create a temp tile to make code look cleaner.
		Tile *tmptile = &tileQueue.at(tileQueueIndex + btnIndex);
		b1->SetImage(
			&chipsetImages.at(
			getChipsetIndex(tmptile->chipSetName)));
		//set the buttons sprite subrec.
		sf::IntRect subrec(tmptile->srcX,
			tmptile->srcY,
			tmptile->srcX + tmptile->width,
			tmptile->srcY + tmptile->height);
		b1->SetSubRect(subrec);
		b1->SetSize(placeHolder.GetWidth(),
			placeHolder.GetHeight());
		b1->SetBackgroundColor(sf::Color::Black);
		float x = (placeHolder.GetWidth() / 2) - (tmptile->width / 2);
		float y = (placeHolder.GetHeight() / 2) - (tmptile->height / 2);
		b1->SetSpritePos( x, y);

	}

	if( tileQueue.size() > 1 )
	{
		int btnIndex = 1;
		//create a temp tile to make code look cleaner.
		Tile *tmptile = &tileQueue.at(tileQueueIndex + btnIndex);
		b2->SetImage(
			&chipsetImages.at(
			getChipsetIndex(tmptile->chipSetName)));
		//set the buttons sprite subrec.
		sf::IntRect subrec(tmptile->srcX,
			tmptile->srcY,
			tmptile->srcX + tmptile->width,
			tmptile->srcY + tmptile->height);
		b2->SetSubRect(subrec);
		b2->SetSize(placeHolder.GetWidth(),
			placeHolder.GetHeight());
		b2->SetBackgroundColor(sf::Color::Black);
		float x = (placeHolder.GetWidth() / 2) - (tmptile->width / 2);
		float y = (placeHolder.GetHeight() / 2) - (tmptile->height / 2);
		b2->SetSpritePos( x, y);
	}

	if( tileQueue.size() > 2 )
	{
		int btnIndex = 2;
		//create a temp tile to make code look cleaner.
		Tile *tmptile = &tileQueue.at(tileQueueIndex + btnIndex);
		b3->SetImage(
			&chipsetImages.at(
			getChipsetIndex(tmptile->chipSetName)));
		//set the buttons sprite subrec.
		sf::IntRect subrec(tmptile->srcX,
			tmptile->srcY,
			tmptile->srcX + tmptile->width,
			tmptile->srcY + tmptile->height);
		b3->SetSubRect(subrec);
		b3->SetSize(placeHolder.GetWidth(),
			placeHolder.GetHeight());
		b3->SetBackgroundColor(sf::Color::Black);
		float x = (placeHolder.GetWidth() / 2) - (tmptile->width / 2);
		float y = (placeHolder.GetHeight() / 2) - (tmptile->height / 2);
		b3->SetSpritePos( x, y);
	}

	if( tileQueue.size() > 3 )
	{
		int btnIndex = 3;
		//create a temp tile to make code look cleaner.
		Tile *tmptile = &tileQueue.at(tileQueueIndex + btnIndex);
		b4->SetImage(
			&chipsetImages.at(
			getChipsetIndex(tmptile->chipSetName)));
		//set the buttons sprite subrec.
		sf::IntRect subrec(tmptile->srcX,
			tmptile->srcY,
			tmptile->srcX + tmptile->width,
			tmptile->srcY + tmptile->height);
		b4->SetSubRect(subrec);
		b4->SetSize(placeHolder.GetWidth(),
			placeHolder.GetHeight());
		b4->SetBackgroundColor(sf::Color::Black);
		float x = (placeHolder.GetWidth() / 2) - (tmptile->width / 2);
		float y = (placeHolder.GetHeight() / 2) - (tmptile->height / 2);
		b4->SetSpritePos( x, y);
	}

	if( tileQueue.size() > 4 )
	{
		int btnIndex = 4;
		//create a temp tile to make code look cleaner.
		Tile *tmptile = &tileQueue.at(tileQueueIndex + btnIndex);
		b5->SetImage(
			&chipsetImages.at(
			getChipsetIndex(tmptile->chipSetName)));
		//set the buttons sprite subrec.
		sf::IntRect subrec(tmptile->srcX,
			tmptile->srcY,
			tmptile->srcX + tmptile->width,
			tmptile->srcY + tmptile->height);
		b5->SetSubRect(subrec);
		//set the width and height of the tile
		b5->SetSize(placeHolder.GetWidth(),
			placeHolder.GetHeight());
		//set the buttons background to black to help
		//show the tile with a constrat on it.
		b5->SetBackgroundColor(sf::Color::Black);
		float x = (placeHolder.GetWidth() / 2) - (tmptile->width / 2);
		float y = (placeHolder.GetHeight() / 2) - (tmptile->height / 2);
		b5->SetSpritePos( x, y);
	}
}

void chipsetWindow(void* UserData)
{
	sf::RenderWindow App(sf::VideoMode(480,600,32), "Tile Editor");
	App.SetPosition( 600, 0 );
	App.SetFramerateLimit(FRAME_RATE);

	// Create a GuiContainer to contain all of the controls we create.
	// This is used mainly for setting focus.
	// YOU HAVE TO HAVE ONE OF THESE or nothing will work.

	cp::cpGuiContainer myGUI;


	// *** Create a Drop Down Box and populate it with choices ***

	cp::cpSelectionBox dropdownBox(&App, &myGUI/*, "Selection Color"*/, 5, 425, 100, 100);
	cp::cpSelectionBox dropdownBox2(&App, &myGUI/*, "Selection Width"*/, 350, 280, 100, 60);
	cp::cpSelectionBox dropdownBox3(&App, &myGUI/*, "Chipset"*/, 5, 280, 300, 100);

	dropdownBox.SetFontSize(12);
	dropdownBox2.SetFontSize(12);
	dropdownBox3.SetFontSize(12);

	std::string choices[] = {"Red", "Blue", "Green", "Yellow", "Black", "White"};
	for(int t=0; t < 6; t++)
		dropdownBox.AddChoice(choices[t]);
	dropdownBox.SetSelection(0);

	std::string choices2[] = {"1", "2", "3", "4"};
	for(int t=0; t < 4; t++)
		dropdownBox2.AddChoice(choices2[t]);
	dropdownBox2.SetSelection(1);

	//open the chipset directory  and load all their 
	//images
	DIR *dir;
	struct dirent *ent;
	dir = opendir ("Assets\\chipsets\\");
	if (dir != NULL) {

		//add all the chipsets to the drop down menu
		//and load all them into chipsetImages vector
		while ((ent = readdir (dir)) != NULL) {

			std::string tmp = ent->d_name;

			//get the extention of the file name which is 3 characters
			//back then put those characters into a testing string and
			//do a comparision to see if the extention is a png or bmp
			//if so load the file into an image else pass over it
			if( tmp.size() > 3 )
			{
				std::string end_tmp;
				std::string::iterator i = tmp.end();
				i--;
				i--;
				i--;
				for(; i != tmp.end(); i++)
				{
					end_tmp.push_back( *i );
				}

				if( end_tmp.compare("png") == 0 || end_tmp.compare("bmp") == 0)
				{
					dropdownBox3.AddChoice( tmp );
					sf::Image tmpImage;
					if( !tmpImage.LoadFromFile("Assets/chipsets/" + tmp) )
						assert(98);
					chipsetImages.push_back( tmpImage );
					chipsetNamesVec.push_back( tmp );
					printf ("%s\n", ent->d_name);
				}
			}
		}
		closedir (dir);
	} else {
		/* could not open directory */
		perror ("");
	}

	//sprite for the chipset to be drawn in
	sf::Sprite mapBoxSprite;
	mapBoxSprite.SetPosition(0, 0);

	//sprite to show the currently selected tile
	sf::Sprite current_tile_sprite;

	//This is the image for the box that the tile is shown in
	sf::Image currentTilePlaceHolderImage;
	if( !currentTilePlaceHolderImage.LoadFromFile("Assets/currenttileplaceholder.png") )
		assert(97);

	sf::Sprite currentTilePlaceHolderSprite;
	currentTilePlaceHolderSprite.SetImage(currentTilePlaceHolderImage);
	currentTilePlaceHolderSprite.SetPosition(305, 475);


	cp::cpButton btnAddToQueue(&App, &myGUI, "Add To Queue", 310, 445, 70, 30 );
	btnAddToQueue.SetFontSize(12);


	std::pair<float, float> select_left, select_bottom;
	bool mouse_switch = true;

	unsigned int mouse_x = 0, mouse_y = 0;

	std::ostringstream convertedInt;

	//holds the current selection box color default is red
	sf::Color myColor = sf::Color::Red;

	//holds the width of the selection box
	int mySelectionWidth = 2;


	const sf::Input& input = App.GetInput();
	while(App.IsOpened())
	{
		sf::Event Event;
		const sf::Input& input = App.GetInput();
		while(App.GetEvent(Event))
		{
			mouse_x = input.GetMouseX();
			mouse_y = input.GetMouseY();

			if(Event.Type == sf::Event::Closed)
				App.Close();
			if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
				App.Close();

			// if you are using a Text Input box, this is where you
			// put the function that processes your text input
			//textInputBox.ProcessTextInput(&Event);


			// This is the function that takes care of which control
			// has focus out of all the controls registered to your
			// GuiContainer.
			myGUI.ProcessKeys(&Event);

			//int selection;
			if(dropdownBox.CheckState(&input) == cp::CP_ST_MOUSE_LBUTTON_RELEASED)
			{
			}

			if(dropdownBox2.CheckState(&input) == cp::CP_ST_MOUSE_LBUTTON_RELEASED)
			{
			}

			if(dropdownBox3.CheckState(&input) == cp::CP_ST_MOUSE_LBUTTON_DOWN)
			{

			}

			mapBoxSprite.SetImage(chipsetImages.at(dropdownBox3.GetSelection()));

			chipset_selected = dropdownBox3.GetSelection();

			switch( dropdownBox.GetSelection() )
			{
			case 0:
				myColor = sf::Color::Red;
				break;
			case 1:
				myColor = sf::Color::Blue;
				break;
			case 2:
				myColor = sf::Color::Green;
				break;
			case 3:
				myColor = sf::Color::Yellow;
				break;
			case 4:
				myColor = sf::Color::Black;
				break;
			case 5:
				myColor = sf::Color::White;
				break;
			default:
				myColor = sf::Color::Red;
				break;
			}

			switch( dropdownBox2.GetSelection() )
			{
			case 0:
				mySelectionWidth = 1;
				break;
			case 1:
				mySelectionWidth = 2;
				break;
			case 2:
				mySelectionWidth = 3;
				break;
			case 3:
				mySelectionWidth = 4;
				break;
			default:
				mySelectionWidth = 2;
				break;
			}

			//checks if AddToQueue Button was pressed. Closes App if so.
			if(btnAddToQueue.CheckState(&input) == cp::CP_ST_MOUSE_LBUTTON_RELEASED)
			{
				//get the width and height of the currently selected tile
				int tile_height = (int)selection_i::getInstance()->second.second - 
					(int)selection_i::getInstance()->first.second;
				int tile_width = (int)selection_i::getInstance()->second.first -
					(int)selection_i::getInstance()->first.first;

				//set all the tile properties that the tile editor 
				//can change i.e. everything except the terrain type
				//level and rotation properties
				Tile newTile;
				newTile.chipSetName = chipsetNamesVec.at(dropdownBox3.GetSelection());
				newTile.height = tile_height;
				newTile.width = tile_width;
				newTile.srcX = selection_i::getInstance()->first.first;
				newTile.srcY = selection_i::getInstance()->first.second;
				newTile.tileID = (unsigned int)tileQueue.size() + 1;

				tileQueue.push_back(newTile);
				addTilePushed = true;
				//int test_size = tileQueue.size();
			}


			//Here we are getting the left and bottom of the square that we currently want 
			//to select.

			//if left button is pressed and we have released our last press.
			if(  mouse_switch && App.GetInput().IsMouseButtonDown(sf::Mouse::Left))
			{
				mouse_switch = false;

				select_left.first = (float)(mouse_x / TILE_SQUARE);
				select_left.second = (float)(mouse_y / TILE_SQUARE);

				select_left.first *= TILE_SQUARE;
				select_left.second *= TILE_SQUARE;
			}

			//if left button is up and the mouse switch is false. Means that we have pressed 
			//the left mouse button and have just released it.
			if( !mouse_switch && !App.GetInput().IsMouseButtonDown(sf::Mouse::Left) )
			{
				mouse_switch = true;

				select_bottom.first = (float)((mouse_x / TILE_SQUARE) + 1);
				select_bottom.second = (float)((mouse_y / TILE_SQUARE) + 1);

				select_bottom.first *= TILE_SQUARE;
				select_bottom.second *= TILE_SQUARE;

				//if we are in the region of the loaded chipset then send the selected tile 
				//to the selection instance singleton
				if( select_bottom.first < chipsetImages.at(dropdownBox3.GetSelection()).GetWidth() + 1 && select_bottom.second < chipsetImages.at(dropdownBox3.GetSelection()).GetHeight() + 1 )
				{
					//makes sure that the tile selected has with greater than zero.
					//compares the x and y cordinates and if they are equal we know
					//that either we have a horizontal line tile or a vertical line tile
					if( select_left.first != select_bottom.first && select_left.second != select_bottom.second )
					{
						//This gets the instance of the singleton pair of pairs 
						//then it sets it so that the main window can see what has been selected
						//through the use of this container.
						selection_i::getInstance()->first.first = select_left.first;
						selection_i::getInstance()->first.second = select_left.second;
						selection_i::getInstance()->second.first = select_bottom.first;
						selection_i::getInstance()->second.second = select_bottom.second;

						//if the selection goes from right to left then we need to switch 
						//our left x with the right x
						if( select_left.first > select_bottom.first )
						{
							selection_i::getInstance()->first.first = select_bottom.first;
							selection_i::getInstance()->second.first = select_left.first;
						}
						//if the selection goes from bottom to top then we need to switch 
						//our bottom y with the top y
						if( select_left.second > select_bottom.second )
						{
							selection_i::getInstance()->first.second = select_bottom.second;
							selection_i::getInstance()->second.second = select_left.second;
						}
						tile_change_tile_editor = true;
					}
				}
			}

			//set the background of the window to green
			App.Clear(sf::Color(97,216,67));

			//must draw the chipset before the selection box so that 
			//you can actually see the selection box.
			App.Draw(mapBoxSprite);

			//Draw box dynamically if the left mouse button is down 

			//makes sure that the mouse is with in the currently loaded chipset
			//bounds... so if mouse is less than the width and Y is less than the height
			//then we draw the selection box lines.
			if( !mouse_switch && mouse_x < chipsetImages.at(dropdownBox3.GetSelection()).GetWidth()
				&& mouse_y < chipsetImages.at(dropdownBox3.GetSelection()).GetHeight())
			{

				mouse_x = (int)(mouse_x / TILE_SQUARE);
				mouse_y = (int)(mouse_y / TILE_SQUARE);

				mouse_x++;
				mouse_y++;

				mouse_x *= TILE_SQUARE;
				mouse_y *= TILE_SQUARE;

				//top line
				App.Draw(sf::Shape::Line(select_left.first, select_left.second, (float)mouse_x, select_left.second, (float)mySelectionWidth, myColor));
				//bottom line
				App.Draw(sf::Shape::Line(select_left.first, (float)mouse_y, (float)mouse_x, (float)mouse_y, (float)mySelectionWidth, myColor));
				//left line
				App.Draw(sf::Shape::Line(select_left.first, select_left.second, select_left.first, (float)mouse_y, (float)mySelectionWidth, myColor));
				//right line
				App.Draw(sf::Shape::Line((float)mouse_x, select_left.second, (float)mouse_x, (float)mouse_y, (float)mySelectionWidth, myColor));
			}

			//Draw the box staticly if the left mouse button is up
			//at this point the bottom right corner has been found since the user released the mouse
			if( mouse_switch && select_bottom.first < chipsetImages.at(dropdownBox3.GetSelection()).GetWidth() + 1 
				&& select_bottom.second < chipsetImages.at(dropdownBox3.GetSelection()).GetHeight() + 1)
			{
				//makes sure not to draw lined tiles
				if( select_left.first != select_bottom.first && select_left.second != select_bottom.second )
				{
					//top line
					App.Draw(sf::Shape::Line(select_left.first, select_left.second, select_bottom.first, select_left.second, (float)mySelectionWidth, myColor));
					//bottom line
					App.Draw(sf::Shape::Line(select_left.first, select_bottom.second, select_bottom.first, select_bottom.second, (float)mySelectionWidth, myColor));
					//left line
					App.Draw(sf::Shape::Line(select_left.first, select_left.second, select_left.first, select_bottom.second, (float)mySelectionWidth, myColor));
					//right line
					App.Draw(sf::Shape::Line(select_bottom.first, select_left.second, select_bottom.first, select_bottom.second, (float)mySelectionWidth, myColor));
				}

			}


			if( tile_change_tile_editor )
			{
				current_tile_sprite.SetImage( chipsetImages.at(chipset_selected) );

				current_tile_sprite.SetSubRect( sf::IntRect(
					(int)selection_i::getInstance()->first.first,
					(int)selection_i::getInstance()->first.second, 
					(int)selection_i::getInstance()->second.first, 
					(int)selection_i::getInstance()->second.second ) );

				int tile_height = (int)selection_i::getInstance()->second.second - 
					(int)selection_i::getInstance()->first.second;
				int tile_width = (int)selection_i::getInstance()->second.first -
					(int)selection_i::getInstance()->first.first;

				float center_x = (float)(305 + (currentTilePlaceHolderImage.GetWidth() / 2)) - (tile_width / 2);
				float center_y = (float)(475 + (currentTilePlaceHolderImage.GetHeight() / 2)) - (tile_height / 2);

				current_tile_sprite.SetPosition( center_x, center_y);
				tile_change_tile_editor = false;

			}
			App.Draw(currentTilePlaceHolderSprite);
			App.Draw( current_tile_sprite );
			btnAddToQueue.Draw();

			dropdownBox.Draw();
			dropdownBox2.Draw();
			dropdownBox3.Draw();

			App.Display();
		}
	}

}

void MapEditor::editorWindow()
{
	sf::Thread secondThread(&chipsetWindow);

	sf::RenderWindow App(sf::VideoMode(800,600,32), "Eternal Elucidation Map Editor");
	App.SetFramerateLimit(FRAME_RATE);
	App.SetPosition(0,0);

	cp::cpGuiContainer myGUI;

	// *** Create a Selection Box and populate it with choices ***
	cp::cpSelectionBox terrainTypes(&App, &myGUI, 578, 55, 220, 150);

	std::string choices[] = {
		"normal",
		"water",
		"mud",
		"sand",
		"stairsLeftUp",
		"stairsLeftDown",
		"stairsRightUp",
		"stairsRightDown",
		"stairsUpUp",
		"stairsUpDown",
		"stairsDownUp",
		"stairsDownDown"};

		for(int t=0; t < 9; t++)
			terrainTypes.AddChoice(choices[t]);

		terrainTypes.SetFontSize(12);

		sf::String terrainTypesString("Terrain Types: ", sf::Font::GetDefaultFont(), 12);
		terrainTypesString.SetColor(sf::Color::Black);
		terrainTypesString.SetPosition(580, 35);

		cp::cpButton btnColGrid(&App, &myGUI, "Collsion Grid", 20, 20, 70, 30);
		cp::cpButton btnPlaceTile(&App, &myGUI, "Place Tile", 120, 20, 70, 30);
		cp::cpButton btnPlaceCol(&App, &myGUI, "Place Collision", 203, 20, 70, 30);
		cp::cpButton btnTerrainType(&App, &myGUI, "Assign Terrain Type", 314, 20, 70, 30);

		//Queue Buttons
		sf::Image leftTileQueueBtnImage;
		if(!leftTileQueueBtnImage.LoadFromFile("Assets/lefttilequeuebtn.png"))
			assert(99);
		sf::Image rightTileQueueBtnImage;
		if(!rightTileQueueBtnImage.LoadFromFile("Assets/righttilequeuebtn.png"))
			assert(99);

		cp::cpImageButton leftTileQueueBtn(&App, &myGUI, &leftTileQueueBtnImage, 0, 475);
		cp::cpImageButton rightTileQueueBtn(&App, &myGUI, &rightTileQueueBtnImage, 609, 475);

		btnColGrid.SetFontSize(12);
		btnPlaceTile.SetFontSize(12);
		btnPlaceCol.SetFontSize(12);
		btnTerrainType.SetFontSize(12);

		sf::Image mapBoxImage;
		sf::Image currentTilePlaceHolderImage;

		if( !mapBoxImage.LoadFromFile("Assets/mapbox.png") )
			assert(98);
		if( !currentTilePlaceHolderImage.LoadFromFile("Assets/currenttileplaceholder.png") )
			assert(97);

		sf::Sprite mapBoxSprite;
		sf::Sprite currentTilePlaceHolderSprite;

		mapBoxSprite.SetImage(mapBoxImage);
		mapBoxSprite.SetPosition(20, 55);
		currentTilePlaceHolderSprite.SetImage(currentTilePlaceHolderImage);
		currentTilePlaceHolderSprite.SetPosition(625, 210);

		//holds the five current tiles in the queue
		//offset the buttons so that the boarders of the left arrow 
		//dont overlap left most button. This is 29 units to the right
		//on the x axis.
		cp::cpImageButton tileQueuebtn1(&App, &myGUI, &currentTilePlaceHolderImage, (29 + (0 * 116)), 475);
		cp::cpImageButton tileQueuebtn2(&App, &myGUI, &currentTilePlaceHolderImage, (29 + (1 * 116)), 475);
		cp::cpImageButton tileQueuebtn3(&App, &myGUI, &currentTilePlaceHolderImage, (29 + (2 * 116)), 475);
		cp::cpImageButton tileQueuebtn4(&App, &myGUI, &currentTilePlaceHolderImage, (29 + (3 * 116)), 475);
		cp::cpImageButton tileQueuebtn5(&App, &myGUI, &currentTilePlaceHolderImage, (29 + (4 * 116)), 475);

		sf::Image current_tiles_chipset;
		if( !current_tiles_chipset.LoadFromFile("Assets/3.png") )
			assert(99);

		sf::Sprite current_tile_sprite;
		current_tile_sprite.SetImage( current_tiles_chipset );
		current_tile_sprite.SetPosition(630, 210);
		current_tile_sprite.SetSubRect( sf::IntRect(0, 0, 0, 0 ) );

		//After everything in this thread has loaded then run
		//the next thread. This is so that resource conflicts
		//opening and writing conflicts don't occure.
		secondThread.Launch(); 

		cp::cpTextInputBox chipSetNameTxb(&App, &myGUI, "", 660, 253, 135, 12);
		cp::cpTextInputBox tileIDTxb(&App, &myGUI, "", 660, 266, 135, 12);
		cp::cpTextInputBox srcXTxb(&App, &myGUI, "", 660, 279, 135, 12);
		cp::cpTextInputBox srcYTxb(&App, &myGUI, "", 660, 292, 135, 12);
		cp::cpTextInputBox tileWidthTxb(&App, &myGUI, "", 660, 305, 135, 12);
		cp::cpTextInputBox tileHeightTxb(&App, &myGUI, "", 660, 318, 135, 12);
		cp::cpTextInputBox rotationTxb(&App, &myGUI, "", 660, 331, 135, 12);
		cp::cpTextInputBox levelTxb(&App, &myGUI, "", 660, 344, 135, 12);
		cp::cpTextInputBox terrainTypeTxb(&App, &myGUI, "", 660, 357, 135, 12);

		sf::String tilePropertiesString("Tile Properties: ", sf::Font::GetDefaultFont(), 12);
		tilePropertiesString.SetColor(sf::Color::Black);
		tilePropertiesString.SetPosition(630, 325);

		sf::String chipSetNameString("Chipset Name: ", sf::Font::GetDefaultFont(), 12);
		sf::String tileIDString("Tile ID: ", sf::Font::GetDefaultFont(), 12);
		sf::String srcXString("Src X: ", sf::Font::GetDefaultFont(), 12);
		sf::String srcYString("Src Y: ", sf::Font::GetDefaultFont(), 12);
		sf::String tileWidthString("Tile Width: ", sf::Font::GetDefaultFont(), 12);
		sf::String tileHeightString("Tile Height: ", sf::Font::GetDefaultFont(), 12);
		sf::String rotationString("Rotation: ", sf::Font::GetDefaultFont(), 12);
		sf::String levelString("Level: ", sf::Font::GetDefaultFont(), 12);
		sf::String terrainTypeString("Terrain Type: ", sf::Font::GetDefaultFont(), 12);

		sf::String chipSetNameValueString("", sf::Font::GetDefaultFont(), 12);
		sf::String tileIDValueString("", sf::Font::GetDefaultFont(), 12);
		sf::String srcXValueString("", sf::Font::GetDefaultFont(), 12);
		sf::String srcYValueString("", sf::Font::GetDefaultFont(), 12);
		sf::String tileWidthValueString("", sf::Font::GetDefaultFont(), 12);
		sf::String tileHeightValueString("", sf::Font::GetDefaultFont(), 12);
		sf::String rotationValueString("", sf::Font::GetDefaultFont(), 12);
		sf::String levelValueString("", sf::Font::GetDefaultFont(), 12);
		sf::String terrainTypeValueString("", sf::Font::GetDefaultFont(), 12);

		chipSetNameString.SetColor(sf::Color::Black);
		tileIDString.SetColor(sf::Color::Black);
		srcXString.SetColor(sf::Color::Black);
		srcYString.SetColor(sf::Color::Black);
		tileWidthString.SetColor(sf::Color::Black);
		tileHeightString.SetColor(sf::Color::Black);
		rotationString.SetColor(sf::Color::Black);
		levelString.SetColor(sf::Color::Black);
		terrainTypeString.SetColor(sf::Color::Black);

		chipSetNameValueString.SetColor(sf::Color::Black);
		tileIDValueString.SetColor(sf::Color::Black);
		srcXValueString.SetColor(sf::Color::Black);
		srcYValueString.SetColor(sf::Color::Black);
		tileWidthValueString.SetColor(sf::Color::Black);
		tileHeightValueString.SetColor(sf::Color::Black);
		rotationValueString.SetColor(sf::Color::Black);
		levelValueString.SetColor(sf::Color::Black);
		terrainTypeValueString.SetColor(sf::Color::Black);

		chipSetNameString.SetPosition(580, 337);
		tileIDString.SetPosition(580, 350);
		srcXString.SetPosition(580, 363);
		srcYString.SetPosition(580, 376);
		tileWidthString.SetPosition(580, 389);
		tileHeightString.SetPosition(580, 402);
		rotationString.SetPosition(580, 415);
		levelString.SetPosition(580, 427);
		terrainTypeString.SetPosition(580, 440);

		chipSetNameValueString.SetPosition(700, 337);
		tileIDValueString.SetPosition(700, 350);
		srcXValueString.SetPosition(700, 363);
		srcYValueString.SetPosition(700, 376);
		tileWidthValueString.SetPosition(700, 389);
		tileHeightValueString.SetPosition(700, 402);
		rotationValueString.SetPosition(700, 415);
		levelValueString.SetPosition(700, 427);
		terrainTypeValueString.SetPosition(700, 440);

		const sf::Input& input = App.GetInput();
		//stores which button in the tile queue has been pressed.
		int selectedTileQueueBtn = 0;
		//tigers if a button in the tile queue has been pressed.
		bool tileQueueBtnPress = false;
		while(App.IsOpened())
		{
			// The standard Event loop
			sf::Event Event;
			const sf::Input& input = App.GetInput();
			while(App.GetEvent(Event))
			{
				if(Event.Type == sf::Event::Closed)
					App.Close();
				if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
					App.Close();

				// This is the function that takes care of which control
				// has focus out of all the controls registered to your
				// GuiContainer.
				myGUI.ProcessKeys(&Event);
			}

			int selection; // an int to store the selection choice from
			// our selection box & drop down box

			if(terrainTypes.CheckState(&input) == cp::CP_ST_MOUSE_LBUTTON_RELEASED)
			{
				selection = terrainTypes.GetSelection();
				if(selection == 10)
					terrainTypes.RemoveLastChoice();
			}

			if(leftTileQueueBtn.CheckState(&input) == cp::CP_ST_MOUSE_LBUTTON_RELEASED)
			{
				if( tileQueueIndex != 0 )
				{
					tileQueueIndex--;
					setTileQueueBtns( &tileQueuebtn1,
						&tileQueuebtn2,
						&tileQueuebtn3,
						&tileQueuebtn4,
						&tileQueuebtn5,
						currentTilePlaceHolderImage);
				}
			}
			if(rightTileQueueBtn.CheckState(&input) == cp::CP_ST_MOUSE_LBUTTON_RELEASED)
			{
				//if the tile queue size is greater than 5 tiles
				//then we can move to the right.
				if( tileQueueIndex + 5 < tileQueue.size())
				{
					tileQueueIndex++;
					setTileQueueBtns( &tileQueuebtn1,
						&tileQueuebtn2,
						&tileQueuebtn3,
						&tileQueuebtn4,
						&tileQueuebtn5,
						currentTilePlaceHolderImage);
				}
			}
			if( tileQueuebtn1.CheckState(&input) == cp::CP_ST_MOUSE_LBUTTON_RELEASED)
			{
				selectedTileQueueBtn = 0;
				tileQueueBtnPress = true;
			}
			if( tileQueuebtn2.CheckState(&input) == cp::CP_ST_MOUSE_LBUTTON_RELEASED)
			{
				selectedTileQueueBtn = 1;
				tileQueueBtnPress = true;
			}
			if( tileQueuebtn3.CheckState(&input) == cp::CP_ST_MOUSE_LBUTTON_RELEASED)
			{
				selectedTileQueueBtn = 2;
				tileQueueBtnPress = true;
			}
			if( tileQueuebtn4.CheckState(&input) == cp::CP_ST_MOUSE_LBUTTON_RELEASED)
			{
				selectedTileQueueBtn = 3;
				tileQueueBtnPress = true;
			}
			if( tileQueuebtn5.CheckState(&input) == cp::CP_ST_MOUSE_LBUTTON_RELEASED)
			{
				selectedTileQueueBtn = 4;
				tileQueueBtnPress = true;
			}

			if(btnColGrid.CheckState(&input) == cp::CP_ST_MOUSE_LBUTTON_RELEASED)
			{
				secondThread.Launch(); 
			}
			if(btnPlaceTile.CheckState(&input) == cp::CP_ST_MOUSE_LBUTTON_RELEASED)
				App.Close();
			if(btnPlaceCol.CheckState(&input) == cp::CP_ST_MOUSE_LBUTTON_RELEASED)
				App.Close();
			if(btnTerrainType.CheckState(&input) == cp::CP_ST_MOUSE_LBUTTON_RELEASED)
				App.Close();

			std::string name;

			if( addTilePushed )
			{
				if( tileQueue.size() > 5 )
				{
					tileQueueIndex = tileQueue.size() - 5;
				}
				setTileQueueBtns( &tileQueuebtn1,
					&tileQueuebtn2,
					&tileQueuebtn3,
					&tileQueuebtn4,
					&tileQueuebtn5,
					currentTilePlaceHolderImage);
				
				addTilePushed = false;
			}

			if( tileQueueBtnPress && tileQueue.size() > 0 )
			{
				Tile *tmptile;
				if( selectedTileQueueBtn < tileQueue.size() )
				{
					tmptile = &tileQueue.at(tileQueueIndex + selectedTileQueueBtn);
				}
				current_tile_sprite.SetImage( chipsetImages.at( getChipsetIndex(tmptile->chipSetName ) ) );
				//set current tile sub rect
				sf::IntRect tmprec(tmptile->srcX, tmptile->srcY, 
					tmptile->srcX + tmptile->width, tmptile->srcY + tmptile->height);
				current_tile_sprite.SetSubRect(tmprec);
				chipSetNameValueString.SetText( tmptile->chipSetName );
				tileIDValueString.SetText( to_string(tmptile->tileID) );
				srcXValueString.SetText( to_string(tmptile->srcX) );
				srcYValueString.SetText( to_string(tmptile->srcY) );
				tileWidthValueString.SetText( to_string(tmptile->width) );
				tileHeightValueString.SetText( to_string(tmptile->height) );
				rotationValueString.SetText("0");
				levelValueString.SetText("1");
				terrainTypeValueString.SetText("normal");

				tileQueueBtnPress = false;
			}

			App.Clear(sf::Color(97,216,67));

			// Every object you create should have the Draw() function
			// called on every cycle.  If you don't want an object to
			// be visible, set Show(false) for that object.
			App.Draw(mapBoxSprite);
			App.Draw(currentTilePlaceHolderSprite);

			terrainTypes.Draw();

			leftTileQueueBtn.Draw();
			rightTileQueueBtn.Draw();
			btnColGrid.Draw();
			btnPlaceTile.Draw();
			btnPlaceCol.Draw();
			btnTerrainType.Draw();
			App.Draw(tilePropertiesString);

			App.Draw(chipSetNameString);
			App.Draw(tileIDString);
			App.Draw(srcXString);
			App.Draw(srcYString);
			App.Draw(tileWidthString);
			App.Draw(tileHeightString);
			App.Draw(rotationString);
			App.Draw(levelString);
			App.Draw(terrainTypeString);

			App.Draw(chipSetNameValueString);
			App.Draw(tileIDValueString);
			App.Draw(srcXValueString);
			App.Draw(srcYValueString);
			App.Draw(tileWidthValueString);
			App.Draw(tileHeightValueString);
			App.Draw(rotationValueString);
			App.Draw(levelValueString);
			App.Draw(terrainTypeValueString);

			//Draw tile queue buttons
			tileQueuebtn1.Draw();
			tileQueuebtn2.Draw();
			tileQueuebtn3.Draw();
			tileQueuebtn4.Draw();
			tileQueuebtn5.Draw();

			App.Draw( current_tile_sprite );

			App.Display();
		}
}