#include "Testing.h"

#include "GameClass.h"

#include "ResourceManager.h"
#include "pngResource.h"
#include "wavResource.h"
#include "oggResource.h"

#include "ExtensibleFactory.h"
#include "GameObject.h"
#include "GameBullet.h"

#include "Collision.h"

#include <SFML/Graphics.hpp>
#include "cpGUI_base.h"
#include "cpTextBox.h"
#include "cpSelection-DropDownBox.h"
#include "cpImageButton.h"
#include "cpShapeButton.h"
#include "cpCheckBox.h"
#include "cpTextInputBox.h"

#include "mapeditor.h"


Testing::Testing()
{
}

void Testing::Update()
{
	int choice = 1;
	while( choice != 0 )
	{
		system("cls");
		std::cout << "Please enter you test number and press enter to run " << std::endl;
		std::cout << "0: exit" << std::endl;
		std::cout << "1: Test Singleton" << std::endl;
		std::cout << "2: Test Map load and save" << std::endl;
		std::cout << "3: Test resource manager" << std::endl;
		std::cout << "4: Test extensible factory" << std::endl;
		std::cout << "5: Test collision" << std::endl;
		std::cout << "6: Test cpGUI example" << std::endl;
		std::cout << "7: Test Map Editor GUI" << std::endl;
		std::cin >> choice;
		switch(choice)
		{
		case 0:
			break;
		case 1:
			{
				//Test getting the instance of the GameClass using the singleton pattern
				GC::getInstance();
			}
			break;
		case 2:
			{
				ResourceManager *mgr = RM::getInstance();
				mgr->Register (new PNGResourceMaker());
				mgr->Register (new WAVResourceMaker());
				mgr->Register (new OGGResourceMaker());
				//Test Map class load and save
				Map m;
				m.load("Assets/test.xml");
				printMap(m);
				m.save("Assets/test2.xml");

			}
			break;
		case 3:
			{
				//Test Resource Manager
				ResourceManager mgr;
				mgr.Register (new PNGResourceMaker());
				mgr.Register (new WAVResourceMaker());
				mgr.Register (new OGGResourceMaker());

				Resource * pRes1 = mgr.Create("Assets/heart.png");
				assert (pRes1 != NULL);
				std::cout << *pRes1;
				sf::Image *test = (sf::Image *)pRes1->GetResource();
				std::cout << "1 height of heart.png is: " << test->GetHeight() << std::endl;

				Resource *pRes2 = mgr.Create("Assets/heart.png");
				assert (pRes2 != NULL);
				std::cout << *pRes2;
				test = (sf::Image *)pRes2->GetResource();
				std::cout << "2 height of heart.png is: " << test->GetHeight() << std::endl;

				Resource * pRes3 = mgr.Create("Assets/Test.wav");
				assert (pRes3 != NULL);
				std::cout << *pRes3;
				sf::SoundBuffer *test2 = (sf::SoundBuffer *)pRes3->GetResource();
				std::cout << "sound duration is:   " << test2->GetDuration() << std::endl;

				Resource * pRes4 = mgr.Create("Assets/Test.ogg");
				assert (pRes4 != NULL);
				std::cout << *pRes4;
				test2 = (sf::SoundBuffer *)pRes4->GetResource();
				std::cout << "sound duration is:   " << test2->GetDuration() << std::endl;

			}
			break;
		case 4:
			{
				//Test Extensible factory

				ExtensibleFactory<GameObject> factory;
				factory.Register(new FactoryMaker<GameBullet, GameObject>);
				GameObject * p1 = factory.Create("GameBullet");
				printf ("object type : %s\n", p1->GetObjectType());
				p1->Update();
				delete p1;
				factory.Unregister(GameBullet::GetClassType());
			}
			break;
		case 5:
			{
				//testing collision
				ExtensibleFactory<GameObject> factory;
				factory.Register(new FactoryMaker<GameBullet, GameObject>);
				GameObject * bullet1 = factory.Create("GameBullet");
				GameObject * bullet2 = factory.Create("GameBullet");

				sf::Vector2<int> *pos1 = new sf::Vector2<int>(1,1);				
				sf::Vector2<int> *pos2 = pos1;

				bullet1->Position = *pos1;
				bullet2->Position = *pos2;
				
				//TODO: set up collision bounds so this test is meaningfull... -Adam
				bool objectsCollide = Collision::ObjectsCollide(bullet1,bullet2);
				vector< sf::Vector2<int> > pixelsCollide= Collision::PixelsCollide(bullet1,bullet2);

				//changing to std::cout -Ron
				std::cout << "objects collide? : " << (objectsCollide==true ?
				   "yes" : "no") << "\n";
				//memory optimization... getting rid of stringstream... -Ron
				//converting to std::cout because printf shouldn't be used with
				//objects... -Ron
				std::cout << "number of colliding pixels : " <<
				   pixelsCollide.size() << "\n";

				delete bullet1;
				delete bullet2;
				factory.Unregister(GameBullet::GetClassType());

			}
			break;
		case 6:
			{
				sf::RenderWindow App(sf::VideoMode(800,600,32), "cpGUI");
				App.SetPosition(10,10);

				// Create a GuiContainer to contain all of the controls we create.
				// This is used mainly for setting focus.
				// YOU HAVE TO HAVE ONE OF THESE or nothing will work.

				cp::cpGuiContainer myGUI;


				// *** Create a non-editable read only Text Box & display a txt file ***
				// Parameters: 1. the parent render window; 2. your GuiContainer;
				// 3&4. the x & y coordinates; 5&6. the width & height

				cp::cpTextBox textBox(&App, &myGUI, 20,20,300,300);

				// When setting the font size, the current font is reloaded with the new
				// size for better quality.
				textBox.SetFontSize(14);
				//added cast to get gcc to not complain... -Ron
				textBox.LoadFile((char*)"Assets/license.txt");


				// *** Create a Selection Box and populate it with choices ***

				cp::cpSelectionBox selBox(&App, &myGUI, 450, 70, 200, 150);

				std::string choices[] = {"Dwarf", "Elf", "Warrior", "Wizard",
					"Adventurer", "Guild Leader", "Cleric", "eight", "nine",
					"ten", "eleven", "twelve", "thirteen", "fourteen"};
				for(int t=0; t < 14; t++)
					selBox.AddChoice(choices[t]);

				selBox.SetFontSize(20);


				// *** Create a Drop Down Box and populate it with choices ***

				cp::cpDropDownBox dropdownBox(&App, &myGUI, "Select your weapon", 450, 250, 200, 20);

				// Set the maximum selection box depth before a scrollbar is used.
				// 100 is default
				dropdownBox.SetMaxDepth(200);

				std::string choices2[] = {"Broad sword", "Axe", "Crossbow", "Long bow", "Mace"};
				for(int t=0; t < 5; t++)
					dropdownBox.AddChoice(choices2[t]);


				// *** Create an Image button using an sf::Image ***
				// These buttons do not have a label, and the size is based on the image's size

				sf::Image image;
				if(!image.LoadFromFile("Assets/dragon.png"))
					assert(99);

				cp::cpImageButton imageBtn(&App, &myGUI, &image, 50, 400);


				// *** Create a regular Button with a label ***
				// if you don't set the button big enough for the text,
				// the button will automatically be resized.
				// default fontsize is 20, you can resize the font and the button
				// later.

				cp::cpButton btn(&App, &myGUI, "Exit Game", 200, 440, 70, 30);


				// *** Create a Shape Button from an sf::Shape ***

				sf::Shape shape;
				shape.AddPoint(200,200, sf::Color::Red);
				shape.AddPoint(250,300, sf::Color::Yellow);
				shape.AddPoint(150,300, sf::Color::Blue);

				cp::cpShapeButton shapeBtn(&App, &myGUI, &shape, 350, 420);


				// *** Create a simple on/off Check Box ***
				// The size of the box is based on the size of the Label's font

				cp::cpCheckBox checkBox(&App, &myGUI, "Play background music", 500, 480);
				checkBox.SetFontSize(20);
				checkBox.SetChecked(true); // unchecked by default
				checkBox.SetMouseoverColor(sf::Color(200,100,100));


				// *** Create a Text Input Box which is a one line input box ***
				// We will also create an sf::String do display above it for a description

				sf::String textInputString("Enter your name:", sf::Font::GetDefaultFont(), 20);
				textInputString.SetPosition(500, 400);
				textInputString.SetColor(sf::Color::Black);

				cp::cpTextInputBox textInputBox(&App, &myGUI, "", 500, 430, 230, 25);





				const sf::Input& input = App.GetInput();

				while(App.IsOpened())
				{

					// The standard Event loop

					sf::Event Event;
					while(App.GetEvent(Event))
					{
						if(Event.Type == sf::Event::Closed)
							App.Close();
						if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
							App.Close();

						// if you are using a Text Input box, this is where you
						// put the function that processes your text input
						textInputBox.ProcessTextInput(&Event);

						// This is the function that takes care of which control
						// has focus out of all the controls registered to your
						// GuiContainer.
						myGUI.ProcessKeys(&Event);
					}

					// After the events are processed, we need to check the state of every
					// control we create using your Input as a parameter.
					// Most controls will return an integer that will tell you the
					// mouse activity within that control.  For these controls, the
					// possible return values are included in an enumeration:
					// CP_STATE_MOUSE_ENTER, CP_STATE_MOUSE_EXIT, CP_STATE_MOUSE_IN,
					// CP_STATE_MOUSE_LBUTTON_DOWN, CP_STATE_MOUSE_LBUTTON_RELEASED,
					// CP_STATE_CHANGED, & CP_STATE_NONE
					// you can use these values to decide what to do.

					textBox.CheckState(&input);

					int selection; // an int to store the selection choice from
					// our selection box & drop down box

					if(selBox.CheckState(&input) == cp::CP_ST_MOUSE_LBUTTON_RELEASED)
					{
						selection = selBox.GetSelection();
						if(selection == 10)
							selBox.RemoveLastChoice();
					}

					if(dropdownBox.CheckState(&input) == cp::CP_ST_MOUSE_LBUTTON_RELEASED)
						selection = dropdownBox.GetSelection();

					if(imageBtn.CheckState(&input) == cp::CP_ST_MOUSE_LBUTTON_RELEASED)
						App.Close();

					if(btn.CheckState(&input) == cp::CP_ST_MOUSE_LBUTTON_RELEASED)
						App.Close();

					// Put the results of CheckState for the shape button in an int
					// so we only have to call the function once.
					// If the mouse enters the shape button, the normal button is
					// hidden.  When the mouse exits the shape button, the normal
					// button is shown.  When the shape button is clicked, the App closes
					int state = shapeBtn.CheckState(&input);
					if(state == cp::CP_ST_MOUSE_ENTER)
						btn.Show(false);
					if(state == cp::CP_ST_MOUSE_EXIT)
						btn.Show(true);
					if(state == cp::CP_ST_MOUSE_LBUTTON_RELEASED)
						App.Close();

					// When the Check Box is clicked, store the check state in 'playmusic'
					bool playmusic;
					if(checkBox.CheckState(&input) == cp::CP_ST_MOUSE_LBUTTON_RELEASED)
						playmusic = checkBox.GetChecked();

					std::string name;
					if(textInputBox.CheckState(&input) == cp::CP_ST_MOUSE_LBUTTON_RELEASED)
						name = textInputBox.GetLabelText();



					App.Clear(sf::Color(180,180,180));


					// Every object you create should have the Draw() function
					// called on every cycle.  If you don't want an object to
					// be visible, set Show(false) for that object.
					textBox.Draw();
					selBox.Draw();
					imageBtn.Draw();
					btn.Draw();
					shapeBtn.Draw();
					checkBox.Draw();
					App.Draw(textInputString);
					textInputBox.Draw();
					dropdownBox.Draw(); // drop down boxes should always be drawn last

					App.Display();
				}
			}
			break;
		case 7:
			{
				MapEditor me;
				me.editorWindow();
			}
			break;
		default:
			break;

		}
		system("pause");
	}

}

void Testing::printMap(Map &map)
{
	std::cout << "map Height:" << map.height << std::endl;
	std::cout << "map Level Total:" << map.levelTotal << std::endl;
	std::cout << "map Name:" << map.mapName << std::endl;
	std::cout << "map Width:" <<map.width << std::endl;
	
	///std::cout << "map Collision Map:" << map.collisionMap << std::endl;

	///PRINT TILES
	for( unsigned int i = 0; i < map.tiles.size(); ++i)
	{
		std::cout << "chipset name: " << map.tiles.at(i).chipSetName << " ";
		std::cout << "level: " << map.tiles.at(i).level <<  " ";
		std::cout << "rotation: " << map.tiles.at(i).rotation << " ";
		std::cout << "srcX: " << map.tiles.at(i).srcX << " ";
		std::cout << "srcY: " << map.tiles.at(i).srcY << " ";
		std::cout << "terrain type: " << map.tiles.at(i).terrainType << " ";
		std::cout << "height: " << map.tiles.at(i).height << " ";
		std::cout << "ID: " << map.tiles.at(i).tileID << " ";
		std::cout << "width: " << map.tiles.at(i).width << std::endl;
	}

	for( unsigned int i = 0; i < map.tileDestionations.size(); ++i )
	{
		std::cout << "TileID:" << map.tileDestionations.at(i).first << " ";
		std::cout << "DesX:" << map.tileDestionations.at(i).second.first << " ";
		std::cout << "DesY:" << map.tileDestionations.at(i).second.second << std::endl;
	}
}