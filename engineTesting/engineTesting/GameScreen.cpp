#include "GameScreen.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>

#include "GenericSpawner.h"

#include "InputModule.h"
#include "loadImages.h"
#include "loadSprites.h"
#include "random.h"
#include "GameClass.h"

#include "GameObjects.h"
#include "screens.h"

namespace TileTypes
{
	enum tileTypes
	{
		red,
		blue,
		green,
		pink,
		black,
		orange,
		purple,
		yellow,
		grey,
		cvoid,
	};
}
GameScreen::GameScreen()
{
}

int GameScreen::Run( sf::RenderWindow &App )
{
	App.ShowMouseCursor(true);
	GameClass *GC = Game::getInstance();
	std::map<std::string, sf::Image> images;
	std::map<std::string, sf::Sprite> sprites;

	//used to interface the sprite mapping by indexing insteading 
	//using a mass amount of if statements. This reduced the need 
	//for branching.
	std::vector<std::string> tileNames;
	tileNames.push_back("Red");
	tileNames.push_back("Blue");
	tileNames.push_back("Green");
	tileNames.push_back("Pink");
	tileNames.push_back("Black");
	tileNames.push_back("Orange");
	tileNames.push_back("Purple");
	tileNames.push_back("Yellow");
	tileNames.push_back("Grey");
	tileNames.push_back("Void");

	int **map = new int*[GC->MapWidth];
	bool **mapset = new bool*[GC->MapWidth];
	for (int i = 0; i < GC->MapWidth; ++i)
	{
		map[i] = new int[GC->MapHeight];
		mapset[i] = new bool[GC->MapHeight];
	}
	for( int i = 0; i < GC->MapWidth; i++ )
		for( int j = 0; j < GC->MapHeight; j++ )
		{
			map[i][j] = TileTypes::cvoid;
			mapset[i][j] = false;
		}

		// Load the sprite image from a file
		LoadImages( "Level.xml", &images );
		LoadSprites( "Level.xml", images, &sprites );

		sf::Font Font;
		if(!Font.LoadFromFile("font.ttf"))
			return EXIT_FAILURE;

		sf::String Text("BREAK", Font );
		Text.SetPosition(5,-10);
		Text.SetColor(sf::Color::Yellow);


		GC->PlayerSprite = sprites.find("Angel")->second;
		GC->PlayerSprite.SetCenter(images.find("Angel")->second.GetWidth() / 2.f, images.find("Angel")->second.GetHeight() / 2.f);
		GC->App = &App;

		GameObjectManager *GOM = GameOM::getInstance();

		GameObjectClass::Init( &App );
		InputModule::Init();

		//Initialize the Goblin and Tree images to their correct image.
		//Soon this will not only set the image but also set the subrect
		//to display of that image. The Game object images will be compiled
		//to individual png or bmp or some other form of image picture.
		//Thus the need for the image to be loaded and the subrect of where
		//the Game objects sprite of that image should be will need to be passed.
		Goblin::Init(&images.find("Antidote")->second, &GC->PlayerSprite);
		Demon::Init(&images.find("Demon")->second, &GC->PlayerSprite);
		Poison::Init(&images.find("Poison")->second, &GC->PlayerSprite);
		Yin::Init(&images.find("Yin")->second, &GC->PlayerSprite);
		Yang::Init(&images.find("Yang")->second, &GC->PlayerSprite);
		Tree::Init(&images.find("Tree")->second, &GC->PlayerSprite);
		CharacterSheet::Init(&images.find("CharacterSheet")->second);
		InventorySheet::Init(&images.find("InventorySheet")->second);
		ElucidatePalette::Init(&images.find("ElucidatePalette")->second);

		//Add an item to the inventory
		InventoryClass *IC = Inventory::getInstance();
		Item tmpIteminv;
		
		tmpIteminv.setImage(images.find("Equipment")->second);
		tmpIteminv.setSubRec(28,0,54,28);
		tmpIteminv.mType = ItemTypes::Equipment;
		tmpIteminv.mEquipmentType = EquipmentTypes::ElucidationTile;
		Item *tmpItemPtrinv = &tmpIteminv;

		IC->addItem(0, tmpItemPtrinv);

		Item tmpIteminv2;
		
		tmpIteminv2.setImage(images.find("Equipment")->second);
		tmpIteminv2.setSubRec(55,0,81,28);
		tmpIteminv2.mType = ItemTypes::Orb;
		Item *tmpItemPtrinv2 = &tmpIteminv2;

		IC->addItem(1, tmpItemPtrinv2);

		Item tmpIteminv3;
		
		tmpIteminv3.setImage(images.find("Equipment")->second);
		tmpIteminv3.setSubRec(82,0,108,28);
		tmpIteminv3.mType = ItemTypes::Orb;
		Item *tmpItemPtrinv3 = &tmpIteminv3;

		IC->addItem(2, tmpItemPtrinv3);

		Item tmpIteminv4;
		
		tmpIteminv4.setImage(images.find("Equipment")->second);
		tmpIteminv4.setSubRec(109,0,135,28);
		tmpIteminv4.mType = ItemTypes::Orb;
		Item *tmpItemPtrinv4 = &tmpIteminv4;

		IC->addItem(3, tmpItemPtrinv4);

		Item tmpIteminv5;
		
		tmpIteminv5.setImage(images.find("Equipment")->second);
		tmpIteminv5.setSubRec(136,0,163,28);
		tmpIteminv5.mType = ItemTypes::Orb;
		Item *tmpItemPtrinv5 = &tmpIteminv5;

		IC->addItem(4, tmpItemPtrinv5);

		//Character Sheet
		CharacterSheet CS(GC->characterSheet_XPos,GC->characterSheet_YPos);
		CharacterSheet *characterSheet = &CS;
		GC->characterSheetID = GOM->addGameObject(characterSheet);

		//Inventory Sheet
		InventorySheet IS(GC->inventorySheet_XPos, GC->inventorySheet_YPos);
		InventorySheet *inventorySheet = &IS;
		GC->inventorySheetID = GOM->addGameObject(inventorySheet);

		//ElucidatePalette
		ElucidatePalette EP(GC->elucidatePalette_XPos,GC->elucidatePalette_YPos);
		ElucidatePalette * elucidatePalette = &EP;
		GC->elucidatePaletteID = GOM->addGameObject(elucidatePalette);

		//EquipmentClass
		EquipmentClass *EC = Equipment::getInstance();
		Item tmpItem;
		
		tmpItem.setImage(images.find("Equipment")->second);
		tmpItem.setSubRec(0,0,27,28);
		tmpItem.mType = ItemTypes::Equipment;
		tmpItem.mEquipmentType = EquipmentTypes::Head;
		Item *tmpItemPtr = &tmpItem;

		EC->addEquipment(EquipmentTypes::Head, tmpItemPtr);

		Item tmpItem2;
		
		tmpItem2.setImage(images.find("Equipment")->second);
		tmpItem2.setSubRec(135,112,163,141);
		tmpItem2.mType = ItemTypes::Equipment;
		tmpItem2.mEquipmentType = EquipmentTypes::Legs;
		Item *tmpItemPtr2 = &tmpItem2;

		EC->addEquipment(EquipmentTypes::Legs, tmpItemPtr2);

		Item tmpItem3;
		
		tmpItem3.setImage(images.find("Equipment")->second);
		tmpItem3.setSubRec(0,0,27,28);
		tmpItem3.mType = ItemTypes::Equipment;
		tmpItem3.mEquipmentType = EquipmentTypes::Legs;
		
		//GC->itemHolder = &tmpItem3;

		//Init input and module
		InputModule input;
		GenericSpawner<Tree>::Init();
		GenericSpawner<Goblin>::Init();
		GenericSpawner<Demon>::Init();
		GenericSpawner<Poison>::Init();
		GenericSpawner<Yin>::Init();
		GenericSpawner<Yang>::Init();
		//NOTE Spawners automatically add themselves to the GameObject map
		//in the GameClass object. Then they are updated below in the main
		//while loop. So set it and forget it :D!
		GenericSpawner<Goblin> GS1(100, 100, 50, 3, 10, 10 );
		GenericSpawner<Tree> GS4(400, 300, 250, 3, 5, 20 );
		GenericSpawner<Demon> GS5(600, 500, 100, 3, 15, 20 );
		GenericSpawner<Poison> GS6(600, 200, 100, 3, 20, 20 );
		GenericSpawner<Yin> GS7(200, 200, 100, 3, 17, 20 );
		GenericSpawner<Yang> GS8(200, 400, 100, 3, 25, 20 );

		// Start game loop
		while (App.IsOpened())
		{
			// Process events
			sf::Event Event;
			while (App.GetEvent(Event))
			{
				// Close window : exit
				if (Event.Type == sf::Event::Closed)
					return 3;
			}

#if TILE_DRAW
			//player location + and - the radius, divide the radus by 16(basic tile unit) 
			//to get the tile units the radius encompasses. use this value as your forloop
			//size when checking the square around the player. do a double for loop around
			//the player checking whether the current tile in the forloop is in the radius
			//or outside the radius. if in place new tile if out do nothing
			int px = (int)( (GC->PlayerSprite.GetPosition().x / GC->ScreenWidth) * GC->MapWidth);
			int py = (int)( (GC->PlayerSprite.GetPosition().y / GC->ScreenHeight ) * GC->MapHeight);

			//make sure to stay in bounds of the map array
			if( px > radius - 2 && px < GC->MapWidth - radius + 1 && py > radius - 2 && py < GC->MapHeight - radius +1)
			{
				for( int i = -radius + 1; i < radius; i++ )
				{
					for( int j = -radius + 1; j < radius; j++ )
					{
						//creates better looking radius for radius 3 and up
						bool set = (i*i) + (j*j) < (radius * radius) - 4;
						//creates better looking radius for radius 2
						if(radius == 2)
							set = set = (i*i) + (j*j) < (radius * radius) - 2;
						//creates better looking radius for radius 1
						if(radius == 1)
							set = set = (i*i) + (j*j) < (radius * radius);
						if( mapset[px + i][py + j] == false && set )
						{
							map[px + i][py + j] = random(TileTypes::red, TileTypes::cvoid - 1);
							mapset[px + i][py + j] = true;
						}
					}
				}
			}
#endif
			//Clear screen
			App.Clear();
			//update all game objects once here before the tiles are drawn
			//also update one more time afterwards. see down below.
			//NOTE we update twice to remove any gitter caused by the large delta time
			//gap created by drawing all the tiles. This is only a TEMP FIX.

			App.Draw(sprites.find("Background")->second);
#if TILE_DRAW
			sf::Sprite tmpSpr;
			for( int i = 0; i < GC->MapWidth; i++ )
				for( int j = 0; j < GC->MapHeight; j++ )
				{
					if( map[i][j] != TileTypes::cvoid )
					{
						//tmpSpr = sprites.find("Void")->second;
						tmpSpr = sprites.find(tileNames[map[i][j]])->second;
						tmpSpr.SetPosition(i*32.0f, j*32.0f);
						App.Draw( tmpSpr );
					}
					//tmpSpr = sprites.find("Void")->second;
				}
#endif
				//update the users input and respond accordingly
				if( input.update() == -1 )
				{
					Game::Destroy();
					Equipment::Destroy();
					Orbs::Destroy();
					Inventory::Destroy();
					return 3;
				}

				//Takes care of deleting any thing in the GameClass Singleton object
				//if the object has died or been turned off.
				GOM->update();

				/*****************************************************************************************/
				for( mGameObject_iter i = GC->mGameObjects.begin(); i != GC->mGameObjects.end(); i++ )
				{
					i->second->update();
					i->second->draw();
				}
				/*****************************************************************************************/

				App.Draw(GC->PlayerSprite);

				//Displays the number of spawns between the 3 goblin spawners
				//Basically use string streams to convert ints to a string then
				//set the SFML Text object's text to the value of all the spawners.
				std::string s;
				std::stringstream out;
				out << GS1.Count() + GS4.Count() + GS5.Count() + GS6.Count() + GS7.Count() + GS8.Count() ;
				s = out.str();
				Text.SetText(s);
				App.Draw( Text );

				//Draw Character Sheet over everything. NOTE CHANGE THIS BY CREATING A PRIOTIY DRAWING
				//QUEUE FOR ALL GAME OBJECT DRAW CALLS
				GC->mGameObjects.find(GC->elucidatePaletteID)->second->draw();
				GC->mGameObjects.find(GC->characterSheetID)->second->draw();
				GC->mGameObjects.find(GC->inventorySheetID)->second->draw();
				if( GC->itemHolder != NULL )
				{
					GC->itemHolder->setPosition(App.GetInput().GetMouseX(), App.GetInput().GetMouseY());
					GC->itemHolder->draw();
				}
				//IC->draw();
				// Display window contents on screen
				App.Display();
		}
		return EXIT_SUCCESS;
}