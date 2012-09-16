////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
//#include <SFML/Graphics.hpp>

//#include "Screen.h"
#include "UnitTests.h"
#include <iostream>

////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////
int main (int argc, char *argv[]) {
	int input;
	bool test_success = false;
	while (1) {
		std::cout	<< "Enter selection: " << std::endl
					<< "0. Quit"		   << std::endl
					<< "1. Screens Test"  << std::endl
					<< "2. Physics Test"  << std::endl;
		std::cin >> input;
		system("cls");
		switch(input) {
		case 0:
			return 1;
		case 1:
			test_success = screenTests();
			break;
		case 2:
			test_success = physicsTests();
			break;
		default:
			std::cout << "Invalid selection." << std::endl;
			system("pause");
			system("cls");
			continue;
		}

		if (test_success)
			std::cout << "Test successful." << std::endl;
		else
			std::cout << "Test failed!" << std::endl;
		system("pause");
		system("cls");
	}

	return EXIT_SUCCESS;
}

	// Create the main rendering window
	//   sf::RenderWindow App(sf::VideoMode(800, 600, 32), "SFML Graphics");
	//ScreenManager ScreenMgr;
	//if(ScreenMgr.LoadScreens("assets/xml/sample.xml")) {
	//	return 1; //there was an error
	//}
	//ScreenMgr.Run(App);



	//   // Load the sprite image from a file
	//   sf::Image Image;
	//   if (!Image.LoadFromFile("Cool.png"))
	//       return EXIT_FAILURE;


	////sf::Image Icon; 
	////if (!Icon.LoadFromFile("assets/Icon.bmp")) 
	////	return EXIT_FAILURE; 
	////App.SetIcon(16, 16, Icon.GetPixelsPtr());

	//   // Create the sprite
	//   sf::Sprite Sprite(Image);

	//   // Change its properties
	//   Sprite.SetColor(sf::Color(0, 255, 255, 128));
	//   Sprite.SetPosition(200.f, 100.f);
	//   Sprite.SetScale(2.f, 2.f);

	//   // Start game loop
	//   while (App.IsOpened())
	//   {
	//       // Process events
	//       sf::Event Event;
	//       while (App.GetEvent(Event))
	//       {
	//           // Close window : exit
	//           if (Event.Type == sf::Event::Closed)
	//               App.Close();
	//       }

	//       // Get elapsed time
	//       float ElapsedTime = App.GetFrameTime();

	//       // Move the sprite
	//       if (App.GetInput().IsKeyDown(sf::Key::Left))  Sprite.Move(-100 * ElapsedTime, 0);
	//       if (App.GetInput().IsKeyDown(sf::Key::Right)) Sprite.Move( 100 * ElapsedTime, 0);
	//       if (App.GetInput().IsKeyDown(sf::Key::Up))    Sprite.Move(0, -100 * ElapsedTime);
	//       if (App.GetInput().IsKeyDown(sf::Key::Down))  Sprite.Move(0,  100 * ElapsedTime);

	//       // Rotate the sprite
	//       if (App.GetInput().IsKeyDown(sf::Key::Add))      Sprite.Rotate(- 100 * ElapsedTime);
	//       if (App.GetInput().IsKeyDown(sf::Key::Subtract)) Sprite.Rotate(+ 100 * ElapsedTime);

	//       // Clear screen
	//       App.Clear();

	//       // Display sprite in our window
	//       App.Draw(Sprite);

	//       // Display window contents on screen
	//       App.Display();
	//   }


	////////////////////////////////////////////////////////////////////////////////////


	//std::vector<ScreenClass*> Screens;
	////the main menu is number 0 thus we start on the main menu by letting
	////screen equal 0
	//   int screen = 0;

	////add all screens to the screen vector
	//StartScreen start;
	//   Screens.push_back (&start);
	//GameScreen game;
	//Screens.push_back (&game);
	//LoadGameScreen loadgame;
	//Screens.push_back (&loadgame);
	//OptionsScreen options;
	//   Screens.push_back (&options);
	//   
	////foreach  screen process it's options
	////
	//  
	//
	//   //Main loop
	////NOTE: This section of code will be placed in the front end task
	//   while (screen >= 0)
	//   {
	//       screen = Screens[screen]->Run(App);
	//   }
