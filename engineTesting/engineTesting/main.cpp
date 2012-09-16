#include "screens.h"
#include "GameClass.h"

int main(void)
{

	GameClass *GC = Game::getInstance();
    std::vector<ScreenClass*> Screens;
	//the main menu is number 3 thus we start on the main menu by letting
	//screen equal 3
    int screen = 3;

	sf::RenderWindow App(sf::VideoMode(GC->ScreenWidth, GC->ScreenHeight, 32), GC->screenName);
	sf::Image Icon; 
	if (!Icon.LoadFromFile("Images/Icon.bmp")) 
		return EXIT_FAILURE; 
	App.SetIcon(16, 16, Icon.GetPixelsPtr());

	//add all screens to the screen vector
	GameScreen game;
	Screens.push_back (&game);
	LoadGameScreen loadgame;
	Screens.push_back (&loadgame);
	 OptionsScreen options;
    Screens.push_back (&options);
    MainMenuScreen main;
    Screens.push_back (&main);
   
 
    //Main loop
	//NOTE: This section of code will be placed in the front end task
    while (screen >= 0)
    {
        screen = Screens[screen]->Run(App);
    }
}


//******************************************************//
//              OLD MAIN CODE
//******************************************************//

//	sf::RenderWindow App(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), SCREEN_NAME);
//
//	std::map<std::string, sf::Image> images;
//	std::map<std::string, sf::Sprite> sprites;
//
//	//used to interface the sprite mapping by indexing insteading 
//	//using a mass amount of if statements. This reduced the need 
//	//for branching.
//	std::vector<std::string> tileNames;
//	tileNames.push_back("Red");
//	tileNames.push_back("Blue");
//	tileNames.push_back("Green");
//	tileNames.push_back("Pink");
//	tileNames.push_back("White");
//	tileNames.push_back("Black");
//	tileNames.push_back("Orange");
//	tileNames.push_back("Purple");
//	tileNames.push_back("Yellow");
//	tileNames.push_back("Grey");
//	tileNames.push_back("Void");
//
//	int **map = new int*[MAP_WIDTH];
//	bool **mapset = new bool*[MAP_WIDTH];
//	for (int i = 0; i < MAP_WIDTH; ++i)
//	{
//		map[i] = new int[MAP_HEIGHT];
//		mapset[i] = new bool[MAP_HEIGHT];
//	}
//	for( int i = 0; i < MAP_WIDTH; i++ )
//		for( int j = 0; j < MAP_HEIGHT; j++ )
//		{
//			map[i][j] = TileTypes::cvoid;
//			mapset[i][j] = false;
//		}
//
//		// Load the sprite image from a file
//		LoadImages( "Level.xml", &images );
//		LoadSprites( "Level.xml", images, &sprites );
//
//		sf::Font Font;
//		if(!Font.LoadFromFile("font.ttf"))
//			return EXIT_FAILURE;
//
//		sf::String Text("BREAK", Font );
//		Text.SetPosition(100,100);
//		Text.SetColor(sf::Color::Green);
//
//		GameClass *GC = Game::getInstance();
//		GC->PlayerSprite = sprites.find("Angel")->second;
//		GC->PlayerSprite.SetCenter(images.find("Angel")->second.GetWidth() / 2.f, images.find("Angel")->second.GetHeight() / 2.f);
//		GC->App = &App;
//
//		GameObjectManager *GOM = GameOM::getInstance();
//
//		GameObject::Init( &App );
//		InputModule::Init();
//
//		//Initialize the Goblin and Tree images to their correct image.
//		//Soon this will not only set the image but also set the subrect
//		//to display of that image. The Game object images will be compiled
//		//to individual png or bmp or some other form of image picture.
//		//Thus the need for the image to be loaded and the subrect of where
//		//the Game objects sprite of that image should be will need to be passed.
//		Goblin::Init(&images.find("Antidote")->second, &GC->PlayerSprite);
//		Tree::Init(&images.find("Tree")->second, &GC->PlayerSprite);
//
//		InputModule input;
//		GenericSpawner<Tree>::Init();
//		GenericSpawner<Goblin>::Init();
//		//NOTE Spawners automatically add themselves to the GameObject map
//		//in the GameClass object. Then they are updated below in the main
//		//while loop. So set it and forget it :D!
//		GenericSpawner<Goblin> GS1(100, 100, 50, 5, 5, 10 );
//		GenericSpawner<Goblin> GS2(200, 200, 100, 5, 5, 10 );
//		GenericSpawner<Goblin> GS3(300, 300, 260, 5, 5, 10 );
//		GenericSpawner<Tree> GS4(400, 300, 250, 1, 7, 100 );
//
//		// Start game loop
//		while (App.IsOpened())
//		{
//			// Process events
//			sf::Event Event;
//			while (App.GetEvent(Event))
//			{
//				// Close window : exit
//				if (Event.Type == sf::Event::Closed)
//					App.Close();
//			}
//#if TILE_DRAW
//			//player location + and - the radius, divide the radus by 16(basic tile unit) 
//			//to get the tile units the radius encompasses. use this value as your forloop
//			//size when checking the square around the player. do a double for loop around
//			//the player checking whether the current tile in the forloop is in the radius
//			//or outside the radius. if in place new tile if out do nothing
//			int px = (int)( (GC->PlayerSprite.GetPosition().x / SCREEN_WIDTH) * MAP_WIDTH);
//			int py = (int)( (GC->PlayerSprite.GetPosition().y / SCREEN_HEIGHT ) * MAP_HEIGHT);
//
//			//make sure to stay in bounds of the map array
//			if( px > radius - 1 && px < MAP_WIDTH - radius && py > radius - 1 && py < MAP_HEIGHT - radius)
//			{
//				for( int i = -radius + 1; i < radius; i++ )
//				{
//					for( int j = -radius + 1; j < radius; j++ )
//					{
//						bool set = (i*i) + (j*j) < radius * radius;
//						if( mapset[px + i][py + j] == false && set )
//						{
//							map[px + i][py + j] = random(TileTypes::red, TileTypes::cvoid - 1);
//							mapset[px + i][py + j] = true;
//						}
//					}
//				}
//			}
//#endif
//			//Clear screen
//			App.Clear();
//			for( mGameObject_iter i = GC->mGameObjects.begin(); i != GC->mGameObjects.end(); i++ )
//			{
//				i->second->draw();
//				i->second->update();
//			}
//			App.Draw(sprites.find("Background")->second);
//#if TILE_DRAW
//			sf::Sprite tmpSpr;
//			for( int i = 0; i < MAP_WIDTH; i++ )
//				for( int j = 0; j < MAP_HEIGHT; j++ )
//				{
//					if( map[i][j] != TileTypes::cvoid )
//					{
//						//tmpSpr = sprites.find("Void")->second;
//						tmpSpr = sprites.find(tileNames[map[i][j]])->second;
//						tmpSpr.SetPosition(i*32, j*32);
//						App.Draw( tmpSpr );
//					}
//					//tmpSpr = sprites.find("Void")->second;
//				}
//#endif
//				//update the users input and respond accordingly
//				input.update();
//
//				//Update all the game object in the game at this frame.
//				for( mGameObject_iter i = GC->mGameObjects.begin(); i != GC->mGameObjects.end(); i++ )
//				{
//					i->second->draw();
//					i->second->update();
//				}
//				//Takes care of deleting any thing in the GameClass Singleton object
//				//if the object has died or been turned off.
//				GOM->update();
//				App.Draw(GC->PlayerSprite);
//
//				//Displays the number of spawns between the 3 goblin spawners
//				char buf1[20];
//				Text.SetText(itoa(GS1.Count() + GS2.Count() + GS3.Count(), buf1, 10 ));
//				App.Draw( Text );
//
//				// Display window contents on screen
//				App.Display();
//		}
//		return EXIT_SUCCESS;

//******************************************************//
//              END OF OLD MAIN CODE
//******************************************************//



//Code to get RGB colors divided by 12 different colors.
	//int R = 0, G = 0, B = 0;
	//int n = 0;
	//int colors[12];
	//int delta = 16581375 / 12;
	//for( int i = 0; i < 12; i++ )
	//{
	//	colors[i] = delta * i;
	//}
	//for(int i = 0; i < 16581375; i++)
	//{
	//	if( i == colors[n])
	//	{
	//		printf("%d %d %d\n", R, G, B);
	//		n++;
	//	}
	//	if( R < 255 )
	//	{
	//		R++;
	//	}
	//	else
	//	{
	//		R = 0;
	//		G++;
	//		if( G > 254 )
	//		{
	//			G = 0;
	//			B++;
	//		}
	//	}
	//	
	//}

//******************************************************//
//            BELOW: All this is now in GameClass.h
//******************************************************//

//#define PI 3.14159265f
//#define SQRT2OVER2 0.70710678118654752440084436210485f
//#define KEYBOARD 1
//#define CONTROLLER 0
//#define TILE_DRAW 0
//#define SCREEN_WIDTH 800
//#define SCREEN_HEIGHT 600
//#define SCREEN_NAME "Engine Testing"
////for a 800 X 600 pixel screen 800/32 600/32 roughly 25 and 19:
//#define MAP_WIDTH 25
//#define MAP_HEIGHT 19
//
//const float speed = 300;
//int radius = 2;

//used for directional input for the keyboard and controller.
//typedef struct Directions
//{
//	unsigned int dir : 4;
//	unsigned int extra : 4;
//} directions;

//******************************************************//
//        ABOVE:  All this is now in GameClass.h
//******************************************************//

//******************************************************//
//              OLD TILE DRAWING CODE
//******************************************************//
/*
if( map[i][j] == TileTypes::black )
tmpSpr = sprites.find("Black")->second;
if( map[i][j] == TileTypes::blue )
tmpSpr = sprites.find("Blue")->second;
if( map[i][j] == TileTypes::green )
tmpSpr = sprites.find("Green")->second;
if( map[i][j] == TileTypes::grey )
tmpSpr = sprites.find("Grey")->second;
if( map[i][j] == TileTypes::orange )
tmpSpr = sprites.find("Orange")->second;
if( map[i][j] == TileTypes::pink )
tmpSpr = sprites.find("Pink")->second;
if( map[i][j] == TileTypes::purple )
tmpSpr = sprites.find("Purple")->second;
if( map[i][j] == TileTypes::red )
tmpSpr = sprites.find("Red")->second;
if( map[i][j] == TileTypes::white )
tmpSpr = sprites.find("White")->second;
if( map[i][j] == TileTypes::yellow )
tmpSpr = sprites.find("Yellow")->second;*/

//******************************************************//
//             END OF OLD TILE DRAWING CODE
//******************************************************//

//******************************************************//
//              OLD RANDOM TILE CODE
//******************************************************//
//if( mapset[px][py - 2] == false )
//{
//	
//	map[px][py - 2] = random(TileTypes::red, TileTypes::cvoid - 1);
//	mapset[px][py - 2] = true;
//}
//if( mapset[px][py - 1] == false )
//{
//	map[px][py - 1] = random(TileTypes::red, TileTypes::cvoid - 1);
//	mapset[px][py - 1] = true;
//}
//if( mapset[px][py] == false )
//{
//	map[px][py] = random(TileTypes::red, TileTypes::cvoid - 1);
//	mapset[px][py] = true;
//}
//if( mapset[px][py + 1] == false )
//{
//	map[px][py + 1] = random(TileTypes::red, TileTypes::cvoid - 1);
//	mapset[px][py + 1] = true;
//}
//if( mapset[px][py + 2] == false )
//{
//	map[px][py + 2] = random(TileTypes::red, TileTypes::cvoid - 1 );
//	mapset[px][py + 2] = true;
//}
//if( mapset[px + 1][py + 1] == false )
//{
//	map[px + 1][py + 1] = random(TileTypes::red, TileTypes::cvoid - 1 );
//	mapset[px + 1][py + 1] = true;
//}
//if( mapset[px - 1][py + 1] == false )
//{
//	map[px - 1][py + 1] = random(TileTypes::red, TileTypes::cvoid - 1 );
//	mapset[px - 1][py + 1] = true;
//}

//if( mapset[px + 1][py - 1] == false )
//{
//	map[px + 1][py - 1] = random(TileTypes::red, TileTypes::cvoid - 1 );
//	mapset[px + 1][py - 1] = true;
//}
//if( mapset[px - 1][py - 1] == false )
//{
//	map[px - 1][py - 1] = random(TileTypes::red, TileTypes::cvoid - 1 );
//	mapset[px - 1][py - 1] = true;
//}

//if( mapset[px - 2][py] == false )
//{
//	map[px - 2][py] = random(TileTypes::red, TileTypes::cvoid - 1 );
//	mapset[px - 2][py] = true;
//}
//if( mapset[px - 1][py] == false )
//{
//	map[px - 1][py] = random(TileTypes::red, TileTypes::cvoid - 1 );
//	mapset[px - 1][py] = true;
//}
//if( mapset[px + 1][py] == false )
//{
//	map[px + 1][py] = random(TileTypes::red, TileTypes::cvoid - 1 );
//	mapset[px + 1][py] = true;
//}
//if( mapset[px + 2][py] == false )
//{
//	map[px + 2][py] = random(TileTypes::red, TileTypes::cvoid - 1 );
//	mapset[px + 2][py] = true;
//}
//******************************************************//
//           END OF OLD RANDOM TILE CODE
//******************************************************//

//******************************************************//
//                   OLD INPUT CODE
//******************************************************//

// Get elapsed time
//float ElapsedTime = App.GetFrameTime();

//			//Action keys
//			if (App.GetInput().IsKeyDown(sf::Key::Escape))
//					App.Close();
//
//			if (App.GetInput().IsKeyDown(sf::Key::F)) 
//				App.Create(sf::VideoMode(1280, 768, 32), SCREEN_NAME, sf::Style::Fullscreen);
//
//			if (App.GetInput().IsKeyDown(sf::Key::D)) 
//				App.Create(sf::VideoMode(800, 600, 32), SCREEN_NAME, sf::Style::Fullscreen);
//
//			if (App.GetInput().IsKeyDown(sf::Key::G)) 
//				App.Create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), SCREEN_NAME, sf::Style::Close);
//
//			test.dir = NULL;
//			test.extra = NULL;
//
//#if CONTROLLER		
//			// Movement Keys
//			if (App.GetInput().IsKeyDown(sf::Key::W)) test.dir |= 9; //1000
//			if (App.GetInput().IsKeyDown(sf::Key::D)) test.dir |= 5; //1000
//			if (App.GetInput().IsKeyDown(sf::Key::S)) test.dir |= 6; //1000
//			if (App.GetInput().IsKeyDown(sf::Key::A)) test.dir |= 10; //1000
//
//			if (App.GetInput().IsKeyDown(sf::Key::Up)) test.dir |= 8; //1000
//			if (App.GetInput().IsKeyDown(sf::Key::Down)) test.dir |= 4; //0100
//			if (App.GetInput().IsKeyDown(sf::Key::Left)) test.dir |= 2; //0010
//			if (App.GetInput().IsKeyDown(sf::Key::Right)) test.dir |= 1; //0001
//#if G_DEBUG
//			std::cout << test.dir << std::endl;
//#endif
//			switch(test.dir)
//			{
//
//			case 8:
//				sp.Move(0, -speed * ElapsedTime);
//				break;
//			case 4:
//				sp.Move(0, speed * ElapsedTime);
//				break;
//			case 2:
//				sp.Move(-speed * ElapsedTime, 0);
//				break;
//			case 1:
//				sp.Move(speed * ElapsedTime, 0);
//				break;
//
//			case 10:
//				sp.Move( -speed * ElapsedTime * SQRT2OVER2, -speed * ElapsedTime * SQRT2OVER2);
//				break;
//			case 9:
//				sp.Move(speed * ElapsedTime * SQRT2OVER2, -speed * ElapsedTime * SQRT2OVER2);
//				break;
//			case 6:
//				sp.Move(-speed * ElapsedTime * SQRT2OVER2, speed * ElapsedTime * SQRT2OVER2);
//				break;
//			case 5:
//				sp.Move(speed * ElapsedTime * SQRT2OVER2, speed * ElapsedTime * SQRT2OVER2);
//				break;
//			}
//#endif
//
//#if KEYBOARD		
//			// Movement Keys
//			if (App.GetInput().IsKeyDown(sf::Key::Up)) test.dir |= 8; //1000
//			if (App.GetInput().IsKeyDown(sf::Key::Down)) test.dir |= 4; //0100
//			if (App.GetInput().IsKeyDown(sf::Key::Left)) test.dir |= 2; //0010
//			if (App.GetInput().IsKeyDown(sf::Key::Right)) test.dir |= 1; //0001
//#if G_DEBUG
//			std::cout << test.dir << std::endl;
//#endif
//			switch(test.dir)
//			{
//			case 11:
//			case 8:
//				sp.Move(0, -speed * ElapsedTime);
//				break;
//			case 7:
//			case 4:
//				sp.Move(0, speed * ElapsedTime);
//				break;
//			case 14:
//			case 2:
//				sp.Move(-speed * ElapsedTime, 0);
//				break;
//			case 13:
//			case 1:
//				sp.Move(speed * ElapsedTime, 0);
//				break;
//			case 10:
//				sp.Move( -speed * ElapsedTime * SQRT2OVER2, -speed * ElapsedTime * SQRT2OVER2);
//				break;
//			case 9:
//				sp.Move(speed * ElapsedTime * SQRT2OVER2, -speed * ElapsedTime * SQRT2OVER2);
//				break;
//			case 6:
//				sp.Move(-speed * ElapsedTime * SQRT2OVER2, speed * ElapsedTime * SQRT2OVER2);
//				break;
//			case 5:
//				sp.Move(speed * ElapsedTime * SQRT2OVER2, speed * ElapsedTime * SQRT2OVER2);
//				break;
//			}
//#endif

//******************************************************//
//               END OF OLD INPUT CODE
//******************************************************//


//******************************************************//
//Here are a few extra ways of drawing the loaded sprites
//******************************************************//

//for(std::map<std::string, sf::Sprite>::iterator it = sprites.begin(); it != sprites.end(); it++ )
//{
//	App.Draw(it->second);
//}


// Display sprite in our window
/*App.Draw(sprites.find("Background")->second);
App.Draw(sprites.find("Angel")->second);
App.Draw(sprites.find("Demon")->second);
App.Draw(sprites.find("Poison")->second);
App.Draw(sprites.find("Antidote")->second);
App.Draw(sprites.find("Ying")->second);
App.Draw(sprites.find("Yang")->second);
App.Draw(sprites.find("LeftPaddle")->second);
App.Draw(sprites.find("RightPaddle")->second);
App.Draw(sprites.find("Ball")->second);
App.Draw(sprites.find("Red")->second);
App.Draw(sprites.find("Blue")->second);
App.Draw(sprites.find("Pink")->second);
App.Draw(sprites.find("Orange")->second);
App.Draw(sprites.find("Purple")->second);
App.Draw(sprites.find("Green")->second);
App.Draw(sprites.find("Black")->second);
App.Draw(sprites.find("White")->second);
App.Draw(sprites.find("Grey")->second);
App.Draw(sprites.find("Yellow")->second);
App.Draw(sprites.find("Void")->second);*/



//******************************************************//
//   INPUT MODULE HANDLER FOR XML LOADING/SAVING SETUP
//******************************************************//

//#include <iostream>
//#include <fstream>
//#include <SFML/Graphics.hpp>
// 
//enum InputType
//{
//    KeyboardInput,
//    MouseInput,
//    JoystickInput
//};
// 
//struct MyKeys
//{
//    InputType myInputType;
//    sf::Event::EventType myEventType;
//    sf::Key::Code myKeyCode;
//    sf::Mouse::Button myMouseButton;
//};
// 
//bool TestEvent (MyKeys k, sf::Event e);
//void Shoot (void);
//void Jump(void);
// 
//int main(int argc, char** argv)
//{
//    //Variables for main
//    sf::RenderWindow App;
//    bool Running = true;
//    sf::Event Event;
// 
//    //Variables for demo
//    std::map<std::string,MyKeys> Keys;
//    MyKeys key;
//    //Let's bind the left mouse button to the "Shoot" action
//    key.myInputType = MouseInput;
//    key.myEventType = sf::Event::MouseButtonPressed;
//    key.myMouseButton = sf::Mouse::Left;
//    Keys["Shoot"] = key;
//    //Let's bind the Return key to the "Jump" action
//    key.myInputType = KeyboardInput;
//    key.myEventType = sf::Event::KeyPressed;
//    key.myKeyCode = sf::Key::Return;
//    Keys["Jump"] = key;
//    //Let's bind the Left Control key to the "Use" action
//    key.myInputType = KeyboardInput;
//    key.myEventType = sf::Event::KeyPressed;
//    key.myKeyCode = sf::Key::LControl;
//    Keys["Use"] = key;
// 
//    //Window creation
//    App.Create(sf::VideoMode(640, 480, 16), "config test");
// 
//    //Main loop
//    while (Running)
//    {
//        //Manage Events
//        while (App.GetEvent(Event))
//        {
//            //Using Event normally
// 
//            //Window closed
//            if (Event.Type == sf::Event::Closed)
//            {
//                Running = false;
//            }
// 
//            //Key pressed
//            if (Event.Type == sf::Event::KeyPressed)
//            {
//                switch (Event.Key.Code)
//                {
//                    case sf::Key::Escape :
//                        Running = false;
//                        break;
//                    case sf::Key::A :
//                        std::cout<<"Key A !"<<std::endl;
//                        break;
//                    default :
//                        break;
//                }
//            }
// 
//            //Using Event for binding
//            //Shoot
//            if (TestEvent(Keys["Shoot"],Event))
//            {
//                //You can use a function
//                Shoot ();
//            }
//            if (TestEvent(Keys["Jump"],Event))
//            {
//                Jump ();
//            }
//            if (TestEvent(Keys["Use"],Event))
//            {
//                //or only code
//                std::cout<<"Use !"<<std::endl;
//            }
//        }
// 
//        //Display the result
//        App.Display();
//    }
// 
//    //End of application
//    return EXIT_SUCCESS;
//}
// 
//bool TestEvent (MyKeys k, sf::Event e)
//{
//    //Mouse event
//    if (k.myInputType==MouseInput && k.myEventType==e.Type && k.myMouseButton==e.MouseButton.Button)
//    {
//        return (true);
//    }
//    //Keyboard event
//    if (k.myInputType==KeyboardInput && k.myEventType==e.Type && k.myKeyCode==e.Key.Code)
//    {
//        return (true);
//    }
//    return (false);
//}
// 
//void Shoot (void)
//{
//    std::cout<<"Shoot !"<<std::endl;
//}
// 
//void Jump (void)
//{
//    std::cout<<"Jump !"<<std::endl;
//}

//******************************************************//
//END OF INPUT MODULE HANDLER FOR XML LOADING/SAVING SETUP
//******************************************************//