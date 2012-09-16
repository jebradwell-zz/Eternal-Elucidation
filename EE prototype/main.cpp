#include "GameInit.h"
#include "MainGameLoop.h"
#include "GameShutdown.h"
#include "Testing.h"

int main( int argc, char *argv[])
{
	GameInit m_GameInit;
	MainGameLoop m_MainGameLoop;
	GameShutdown m_GameShutdown;

	//Testing game tasks, initialization, Resource Manager, Extended Factory and Map Load & Save
	Testing m_Testing;
	m_Testing.Update();

	m_GameInit.Update();
	m_MainGameLoop.Update();
	m_GameShutdown.Update();

	return EXIT_SUCCESS;
}

//////////////////////////////////////////////////////////////
//// Headers
//////////////////////////////////////////////////////////////
//#include <iostream>
//#include <SFML/Graphics.hpp>
//
//#include "bullet.h"
//#include "GameInit.h"
//
//#define PI 3.14159265f
//
//
//////////////////////////////////////////////////////////////
///// Entry point of Application
/////
///// \return Application exit code
/////
//////////////////////////////////////////////////////////////
//int main()
//{
//    // Create the main rendering window
//    sf::RenderWindow App(sf::VideoMode(800, 600, 32), "SFML Graphics");
//
//    // Load the sprite image from a file
//    sf::Image Image;
//    if (!Image.LoadFromFile("sprite.png"))
//        return EXIT_FAILURE;
//
//	sf::Image Image2;
//    if (!Image2.LoadFromFile("heart.png"))
//        return EXIT_FAILURE;
//
//	sf::Font Font;
//	if(!Font.LoadFromFile("font.ttf"))
//		return EXIT_FAILURE;
//
//	sf::String Text("BREAK", Font );
//	Text.SetPosition(-100,-100);
//
//	//sf::Uint32 charset[] = {0X4E16, 0x754C, 0x597D, 0x0};
//
//	bullet b1(-100, -100);
//	
//
//    // Create the sprites and change some of their properties
//    sf::Sprite Sprite(Image);
//	Sprite.SetPosition(200.f, 100.f);
//	Sprite.SetCenter(Image.GetHeight() / 2.f, Image.GetWidth() / 2.f );
//
//	sf::Sprite Sprite2(Image2);
//	Sprite2.SetPosition(350.f, 250.f);
//
//	//create a rect for sprite 2 to do some collision detection.
//	sf::Rect<float> sprite2Rect(350.f, 250.f, 350.f + Image.GetWidth(), 250.f + Image.GetHeight() );
//   
//	int rotationSpeed = 100;
//	float spriteX = 0;
//	float spriteY = 0;
//	float bulletX = 0;
//	float bulletY = 0;
//	bool spaceDown = false;
//
//    // Start game loop
//    while (App.IsOpened())
//    {
//        // Process events
//        sf::Event Event;
//        while (App.GetEvent(Event))
//        {
//            // Close window : exit
//            if (Event.Type == sf::Event::Closed)
//                App.Close();
//        }
//
//        // Get elapsed time
//        float ElapsedTime = App.GetFrameTime();
//
//        // Move the sprite
//
//		if (App.GetInput().IsKeyDown(sf::Key::Escape)) App.Close();
//        
//        if (App.GetInput().IsKeyDown(sf::Key::W)) Sprite.Move(-100 * ElapsedTime * spriteX, -100 * ElapsedTime * spriteY);
//		if (App.GetInput().IsKeyDown(sf::Key::S)) Sprite.Move(100 * ElapsedTime * spriteX, 100 * ElapsedTime * spriteY);
//
//		if (spaceDown == false &&  b1.bulletDead() && App.GetInput().IsKeyDown(sf::Key::Space) )
//		{
//			bulletX = spriteX;
//			bulletY = spriteY;
//			b1.reset( Sprite.GetPosition().x, Sprite.GetPosition().y );
//			spaceDown = true;
//		}
//		if (spaceDown == true && !App.GetInput().IsKeyDown(sf::Key::Space) )
//		{
//			spaceDown = false;
//		}
//
//        // Rotate the sprite
//		if (App.GetInput().IsKeyDown(sf::Key::D)) 
//		{
//			Sprite.Rotate( -rotationSpeed * ElapsedTime);
//			spriteY = cos(Sprite.GetRotation() * PI/180.f);
//			spriteX = sin(Sprite.GetRotation() * PI/180 );
//			
//			std::cout << Sprite.GetRotation() << std::endl;
//			std::cout << spriteX << spriteY << std::endl;
//		}
//		if (App.GetInput().IsKeyDown(sf::Key::A)) 
//		{
//			Sprite.Rotate( rotationSpeed * ElapsedTime);
//			spriteY = cos(Sprite.GetRotation() * PI/180);
//			spriteX = sin(Sprite.GetRotation() * PI/180 );
//			
//			std::cout << Sprite.GetRotation() << std::endl;
//			std::cout << spriteX << spriteY << std::endl;
//		}
//		if (App.GetInput().IsKeyDown(sf::Key::Left)) 
//		{
//			Sprite.Move(100 * ElapsedTime * sin((Sprite.GetRotation() - 90 ) * PI/180 ),
//						100 * ElapsedTime * cos((Sprite.GetRotation() - 90) * PI/180));
//		}
//
//		if (App.GetInput().IsKeyDown(sf::Key::Right)) 
//		{
//			Sprite.Move(100 * ElapsedTime * sin((Sprite.GetRotation() + 90 ) * PI/180 ),
//						100 * ElapsedTime * cos((Sprite.GetRotation() + 90) * PI/180));
//		}
//		if (App.GetInput().IsKeyDown(sf::Key::I)) rotationSpeed++;
//		if (App.GetInput().IsKeyDown(sf::Key::O)) rotationSpeed--;
//
//		if( sprite2Rect.Intersects(b1.bulletRect()) )
//		{
//			std::cout << "*******************************HIT*******************************" << std::endl;
//			Text.SetPosition(b1.bulletSprite().GetPosition().x, b1.bulletSprite().GetPosition().y);
//			b1.reset(-100, -100);
//			b1.killBullet();
//		}
//
//        // Clear screen
//        App.Clear();
//
//        // Display sprite in our window
//		App.Draw(Sprite);
//		App.Draw(Sprite2);
//		App.Draw( Text );
//		if( !b1.bulletDead() )
//		{
//			b1.move(-1000 * ElapsedTime * bulletX, -1000 * ElapsedTime * bulletY);
//			App.Draw( b1.bulletSprite() );
//		}
//        // Display window contents on screen
//        App.Display();
//    }
//
//    return EXIT_SUCCESS;
//}









/***********************************************************************
************************************************************************
************************************************************************
This is a test main for the Neural Network code
************************************************************************
************************************************************************
************************************************************************/
//#include "NeuralNetwork.h"
//
//double TrainSet[14][7] = {
//	//#Friends, Hit points, Enemy Engaged, Range, Chase, Flock, Evade
//	0,			1,			0,			   0.2,   0.9,   0.1,   0.1,
//	0,			1,			1,			   0.2,   0.9,   0.1,   0.1,
//	0,			1,			0,			   0.8,   0.1,   0.1,   0.1,
//	0.1,		0.5,		0,			   0.2,   0.9,   0.1,   0.1,
//	0,			0.25,		1,			   0.5,   0.1,   0.9,   0.1,
//	0,			0.2,		1,			   0.2,   0.1,   0.1,   0.9,
//	0.3,		0.2,		0,			   0.2,   0.9,   0.1,   0.1,
//	0,			0.2,		0,			   0.3,   0.1,   0.9,   0.1,
//	0,			1,			0,			   0.2,   0.1,   0.9,   0.1,
//	0,			1,			1,			   0.6,   0.1,   0.1,   0.1,
//	0,			1,			0,			   0.8,   0.1,   0.9,   0.1,
//	0.1,		0.2,		0,			   0.2,   0.1,   0.1,   0.9,
//	0,			0.25,		10,			   0.5,   0.1,   0.1,   0.9,
//	0,			0.6,		0,			   0.2,   0.1,   0.1,   0.9
//};
//
//int main()
//{
//
//	//testing the neural network
//	NeuralNetwork TheBrain;
//
//	TheBrain.Initialize( 4,3,3 );
//	
//	TheBrain.SetLearningRate( 0.2 );
//	TheBrain.SetMomentum(true, 0.9 );
//	//TheBrain.SetHyperbolicOutput(true);
//	int i;
//	double error = 1;
//	int c = 0;
//	TheBrain.DumpData("Assets/PreTraining.txt");
//	while( ( error > 0.05 ) && ( c < 50000 ) )
//	{
//		error = 0;
//		c++;
//		for( i = 0; i < 14; i++ )
//		{
//			TheBrain.SetInput(0, TrainSet[i][0] );
//			TheBrain.SetInput(1, TrainSet[i][1] );
//			TheBrain.SetInput(2, TrainSet[i][2] );
//			TheBrain.SetInput(3, TrainSet[i][3] );
//
//			TheBrain.SetDesiredOutput(0, TrainSet[i][4]);
//			TheBrain.SetDesiredOutput(1, TrainSet[i][5]);
//			TheBrain.SetDesiredOutput(2, TrainSet[i][6]);
//
//			TheBrain.FeedForward();
//			error += TheBrain.CalculateError();
//			TheBrain.BackPropagate();
//		}
//		error /= 14.0f;
//	}
//	TheBrain.DumpData("Assets/PostTraining.txt");
//
//	return 0;
//}






/***********************************************************************
************************************************************************
************************************************************************
This is a test main for the A* Search code
************************************************************************
************************************************************************
************************************************************************/
////self note: Change where you use init_tile_type in the button clicking portion of the code
////so that it is reflected in the map object.
//
//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include <vector>
//#pragma warning(disable:4482)
//#pragma warning(disable:4996)
//
//#include "map.h"
//#include "astar.h"
//
//#define GRID_SIZE 16
//
//#define NUM_OF_TILE_TYPES 5
//
//#define TEXT_SIZE 10
//
////used for itoa conversions
//char buf[128];
//
//
//
////#define GRID_SIZE 5
////#define START_X 3
////#define START_Y 3
////#define END_X 3 
////#define END_Y 1
//
//using std::cout;
//using std::endl;
//using std::vector;
//
//
//
//// start = (1, 16) or (0, 15)
//// end = (12, 5) or (11, 4)
////                  Y  cord    X  cord
//int init_tile_type[GRID_SIZE][GRID_SIZE] = 
////     1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16
//{ {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },   //1
//{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },   //2
//{1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },   //3
//{1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1 },   //4
//{1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1 },   //5
//{1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1 },   //6
//{1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1 },   //7
//{1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1 },   //8
//{1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1 },   //9
//{1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1 },   //10
//{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },   //11
//{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },   //12
//{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },   //13
//{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },   //14
//{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },   //15
//{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } }; //16
//
//
//
//// start = (4, 4) or (3, 3)
//// end = (4, 2) or (3, 1)
////                  Y  cord    X  cord
////int init_tile_type[GRID_SIZE][GRID_SIZE] =
////{ { 1, 1, 1, 1},
////  { 1, 0, 1, 1},
////  { 1, 0, 0, 0},
////  { 1, 1, 1, 1} };
//
//
//int main( int argc, char *argv[] )
//{
//	//initialize map
//	Map map(GRID_SIZE,GRID_SIZE);
//	for( int j = 0; j < GRID_SIZE; j++ )
//	{
//		for( int i = 0; i < GRID_SIZE; i++ )
//		{
//			map.map[j][i].tile_type = init_tile_type[j][i];
//		}
//	}
//
//	int START_X = 0;
//	int START_Y = 15;
//	int END_X = 11;
//	int END_Y = 4;
//	//initialize our A* algorithm
//	Astar a(&map);
//	//find the shortest path vector
//	vector<Node *> path = a.find_path( START_X, START_Y, END_X, END_Y );
//	//print to the command line all the points in our map which are on
//	//the shortest path
//	std::cout << "this is the path size:" << path.size() << std::endl;
//	for( unsigned int i = 0; i < path.size(); i++ )
//	{
//		std::cout << "x: " << path[i]->pos.x << " y: " << path[i]->pos.y << std::endl;
//	}
//
//	//change our grid to reflect the new path positions found.
//	for( unsigned int i = 0; i < path.size(); i++ )
//	{
//		if( i == path.size() - 1 )
//			init_tile_type[path[i]->pos.y][path[i]->pos.x] = tile_type::start;
//		else if( i == 0 )
//			init_tile_type[path[i]->pos.y][path[i]->pos.x] = tile_type::end;
//		else
//			init_tile_type[path[i]->pos.y][path[i]->pos.x] = tile_type::path;
//	}
//
//	// Create the main rendering window
//	sf::RenderWindow App(sf::VideoMode(800, 600, 32), "A* Grid Search");
//
//	// Load the sprite images from their files
//	sf::Image Image[NUM_OF_TILE_TYPES];
//	if (!Image[tile_type::wall].LoadFromFile("wall.png"))
//		return EXIT_FAILURE;
//	if (!Image[tile_type::moveable].LoadFromFile("movable.png"))
//		return EXIT_FAILURE;
//	if (!Image[tile_type::start].LoadFromFile("start.png"))
//		return EXIT_FAILURE;
//	if (!Image[tile_type::end].LoadFromFile("end.png"))
//		return EXIT_FAILURE;
//	if (!Image[tile_type::path].LoadFromFile("path.png"))
//		return EXIT_FAILURE;
//
//	// Load the font from a file
//	sf::Font MyFont;
//	if (!MyFont.LoadFromFile("arial.ttf"))
//	{
//		return EXIT_FAILURE;
//	}
//	//Load our font and create our Text to display with that font
//	sf::String Text;
//	Text.SetFont(MyFont);
//	Text.SetSize(TEXT_SIZE);
//
//	// Create the sprites
//	sf::Sprite Sprite[NUM_OF_TILE_TYPES];
//	for(int i = 0; i < NUM_OF_TILE_TYPES; i++ )
//	{
//		Sprite[i].SetImage(Image[i]);
//	}
//
//	//check whether the right mouse button is clicked down or up
//	bool rup = false;
//	//check whether the left mouse button is clicked down or up
//	bool lup = false;
//	//if true prints the node stats of each node i.e. the s, c, h, values
//	bool info = false;
//	//makes sure that you only switch once when clicked down instead of 
//	//switching every loop
//	bool info_switch = true;
//	int heuristic = 0;
//	bool heuristic_switch = false;
//
//	bool edit_move = false;
//
//	// Start game loop
//	while (App.IsOpened())
//	{
//		// Process events
//		sf::Event Event;
//		while (App.GetEvent(Event))
//		{
//			// Close window : exit
//			if (Event.Type == sf::Event::Closed)
//				App.Close();
//		}
//
//		//if( edit_move == true && App.GetInput().IsKeyDown(sf::Key::E))
//		//{
//		//	edit_move = false;
//		//}
//		//else
//		//{
//			//this changes the start position and then searches for the shortest path
//			//between the start and end.
//			if(lup == true && info == false && App.GetInput().IsMouseButtonDown(sf::Mouse::Button::Left))
//			{
//				//switch off button click so that it only comes back on 
//				//once the mouse button has been released
//				lup = false;
//				//get the mouse position and find the gride location.
//				//I use the Image's height to divide by, i could just
//				//as easily use the width since our images are square
//				//and i use image 0 for no reason other than it's 
//				//a closer garrenty to be there other than a higher
//				//number.
//				int x = App.GetInput().GetMouseX(); 			
//				int y = App.GetInput().GetMouseY();
//				x = x / Image[0].GetHeight();
//				y = y / Image[0].GetHeight();
//
//				//check to make sure the mouse isn't over a wall piece
//				//so that we do not attempt to find a bath that goes into
//				//a wall
//				if( x < 16 && y < 16 && init_tile_type[y][x] != tile_type::wall && init_tile_type[y][x] != tile_type::end )
//				{
//					//clear the previous path that was drawn in the grid.
//					for( unsigned int i = 0; i < path.size(); i++ )
//					{
//						init_tile_type[path[i]->pos.y][path[i]->pos.x] = tile_type::moveable;
//					}
//					//remove the nodes in the path vector.
//					path.clear();
//					//create a new Astar object with the inituailzed map above
//					Astar a2(&map, heuristic);
//					//set the start location to the mouse pulled location
//					START_X = x;
//					START_Y = y;
//					//find the path and set it to the path vector.
//					path = a2.find_path( x, y, END_X, END_Y );
//					//add in the start, end and path nodes to the init_tile_type grid.
//					for( unsigned int i = 0; i < path.size(); i++ )
//					{
//						if( i == path.size() - 1 )
//							init_tile_type[path[i]->pos.y][path[i]->pos.x] = tile_type::start;
//						else if( i == 0 )
//							init_tile_type[path[i]->pos.y][path[i]->pos.x] = tile_type::end;
//						else
//							init_tile_type[path[i]->pos.y][path[i]->pos.x] = tile_type::path;
//					}
//					//clear the console screen for a fresh print out of the node positions
//					system("cls");
//					std::cout << "this is the path size:" << path.size() << std::endl;
//					//print out hte path size and all it's path node posistions
//					for( unsigned int i = 0; i < path.size(); i++ )
//					{
//						std::cout << "x: " << path[i]->pos.x << " y: " << path[i]->pos.y << std::endl;
//					}
//				}
//			}
//
//			//identical to the left click except this one changes the end instead of the start
//			if(rup == true && info == false && App.GetInput().IsMouseButtonDown(sf::Mouse::Button::Right))
//			{
//				//switch off button click so that it only comes back on 
//				//once the mouse button has been released
//				rup = false;
//				int x = App.GetInput().GetMouseX(); 			
//				int y = App.GetInput().GetMouseY();
//				x = x / Image[0].GetHeight();
//				y = y / Image[0].GetHeight();
//
//				if( x < 16 && y < 16 && init_tile_type[y][x] != tile_type::wall && init_tile_type[y][x] != tile_type::start )
//				{
//					for( unsigned int i = 0; i < path.size(); i++ )
//					{
//						init_tile_type[path[i]->pos.y][path[i]->pos.x] = tile_type::moveable;
//					}
//
//					path.clear();
//					Astar a2(&map, heuristic);
//					END_X = x;
//					END_Y = y;
//					path = a2.find_path( START_X, START_Y, x, y );
//
//					for( unsigned int i = 0; i < path.size(); i++ )
//					{
//						if( i == path.size() - 1 )
//							init_tile_type[path[i]->pos.y][path[i]->pos.x] = tile_type::start;
//						else if( i == 0 )
//							init_tile_type[path[i]->pos.y][path[i]->pos.x] = tile_type::end;
//						else
//							init_tile_type[path[i]->pos.y][path[i]->pos.x] = tile_type::path;
//					}
//					system("cls");
//					std::cout << "this is the path size:" << path.size() << std::endl;
//					for( unsigned int i = 0; i < path.size(); i++ )
//					{
//						std::cout << "x: " << path[i]->pos.x << " y: " << path[i]->pos.y << std::endl;
//					}
//				}
//			}
//
//			if( heuristic_switch == true && App.GetInput().IsKeyDown(sf::Key::H) )
//			{
//				heuristic_switch = false;
//				if( heuristic == heuristic_type::eigen_distance )
//					heuristic = heuristic_type::manhattan_distance;
//				else
//					heuristic = heuristic_type::eigen_distance;
//			}
//			if(!App.GetInput().IsMouseButtonDown(sf::Mouse::Button::Right) )
//			{
//				rup = true;
//			}
//			if( !App.GetInput().IsMouseButtonDown(sf::Mouse::Button::Left) )
//			{
//				lup = true;
//			}
//			if( !App.GetInput().IsKeyDown(sf::Key::H) )
//			{
//				heuristic_switch = true;
//			}
//
//		//}
//		if( !App.GetInput().IsKeyDown(sf::Key::E) )
//		{
//			edit_move = true;
//		}
//		if( info_switch == true && App.GetInput().IsKeyDown(sf::Key::I) )
//		{
//			info_switch = false;
//			info = !info;
//		}
//		if( !App.GetInput().IsKeyDown(sf::Key::I) )
//		{
//			info_switch = true;
//		}
//
//
//
//		// Clear screen
//		App.Clear();
//
//		// Display sprite in our window
//		for( int j = 0; j < GRID_SIZE; j++ )
//		{
//			for( int i = 0; i < GRID_SIZE; i++ )
//			{
//				//Set current sprite location
//				Sprite[init_tile_type[j][i]].SetPosition( (float)(i * Image[init_tile_type[j][i]].GetWidth()),
//					(float)(j * Image[init_tile_type[j][i]].GetHeight() ) );
//				//then draw the right spirit
//				App.Draw( Sprite[init_tile_type[j][i]] );
//
//				//draw the heuristc mode to the right of the screen next the the grid.
//				std::string heuristic_text;
//				if( heuristic == heuristic_type::eigen_distance )
//					heuristic_text = " Eigen Distance";
//				else
//					heuristic_text = " Manhattan Distance";
//
//				Text.SetText(heuristic_text);
//				//set the sprites text position for the sprites status information
//				Text.SetPosition( (float)(GRID_SIZE * Image[0].GetWidth()) + Image[0].GetWidth(), (float)TEXT_SIZE );
//				Text.SetSize(16);
//				App.Draw( Text );
//				Text.SetSize(TEXT_SIZE);
//
//				//if we have pressed the "I" key then allow for the information to be
//				//displayed in each node's image box.
//				if( info )
//				{
//					std::string text_c;
//					text_c = " C ";
//					text_c += itoa( map.map[j][i].c_value, buf, 10 );
//					Text.SetText(text_c);
//					//set the sprites text position for the sprites status information
//					Text.SetPosition((float)(i * Image[init_tile_type[j][i]].GetWidth()),
//						(float)(j * Image[init_tile_type[j][i]].GetHeight() ) );
//					App.Draw( Text );
//
//					std::string text_s;
//					text_s = " S ";
//					text_s += itoa( map.map[j][i].s_value, buf, 10 );
//					Text.SetText(text_s);
//					//set the sprites text position for the sprites status information
//					Text.SetPosition((float)(i * Image[init_tile_type[j][i]].GetWidth()),
//						(float)(j * Image[init_tile_type[j][i]].GetHeight() ) + TEXT_SIZE );
//					App.Draw( Text );
//
//					std::string text_h;
//					text_h = " H ";
//					text_h += itoa( map.map[j][i].s_value, buf, 10 );
//					Text.SetText(text_h);
//					//set the sprites text position for the sprites status information
//					Text.SetPosition((float)(i * Image[init_tile_type[j][i]].GetWidth()),
//						(float)(j * Image[init_tile_type[j][i]].GetHeight() ) + (TEXT_SIZE * 2) );
//					App.Draw( Text );
//
//					////print the list of nodes to the right of the grid with their node x and y
//					////positions.
//					//for( int i = 0; i < path.size(); i++ )
//					//{
//					//	std::string node_position;
//					//	node_position = " X: ";
//					//	node_position += itoa( path.at(i)->pos.x, buf, 10 );
//					//	node_position += " Y: ";
//					//	node_position += itoa( path.at(i)->pos.y, buf, 10 );
//					//	Text.SetText(node_position);
//					//	Text.SetPosition(GRID_SIZE * Image[0].GetWidth() + GRID_SIZE, 2 * TEXT_SIZE + (i * TEXT_SIZE)  );
//					//	App.Draw(Text);
//					//}
//				}
//			}
//		}
//
//		// Display window contents on screen
//		App.Display();
//	}
//	return EXIT_SUCCESS;
//}