#include "OptionsScreen.h"
#include <iostream>
#include "GameClass.h"

OptionsScreen::OptionsScreen()
{
}

int OptionsScreen::Run( sf::RenderWindow &App )
{
	sf::Event Event;
    bool Running = true;
    sf::Image Images[2];
    sf::Sprite Sprite;
    float menuX = 280, menuY = 340;
    sf::Font Font;
	const int menuSize = 5;
	sf::String Menus[menuSize];
	sf::String MenuOptions[menuSize];

	std::string MenuStrs[menuSize] = {"Screen Size","Fullscreen", "Input Type","Difficulty","Back"};
	std::string screenSizeStr[2] = {"800 X 600","1024 X 768"};
	std::string inputTypeStr[2] = {"Keyboard", "Controller"};
	std::string difficultyStr[3] = {"Easy","Medium","Hard"};
	std::string fullscreenStr[2] = {"Window", "Fullscreen"};

	GameClass *GC = Game::getInstance();
    int menu = 0;
	int screenSize = GC->screenSize; //can be 0-800x600 1-1024x768
	int fullscreen = GC->fullscreen; //can be 0-Window 1-Fullscreen
	int input = GC->input; //can be 0-Keyboard 1-Controller
	int difficulty = GC->difficulty; //can be 0-Easy 1-Medium 2-Hard

	//load images
    if (!Images[0].LoadFromFile("Images/MainMenu.png"))
    {
        std::cerr<<"Error loading MainMenu.png"<<std::endl;
        return -1;
	}
	if (!Images[1].LoadFromFile("Images/MainMenuLarge.png"))
	{
		std::cerr<<"Error loading MainMenuLarge.png"<<std::endl;
		return -1;
	}
	//set the sprite.
	Sprite.SetImage(Images[screenSize]);
	//load the font
    if (!Font.LoadFromFile("AquaductPlain.ttf"))
    {
        std::cerr<<"Error loading AquaductPlain.ttf"<<std::endl;
        return -1;
    }
	// change the menu position if the screen is 800 X 600.
	if( GC->screenSize == 0 ) //800 X 600
	{
		menuX = 280;
		menuY = 340;
	}
	// change the menu position if the screen is 1024 X 768.
	if( GC->screenSize == 1) //1024 X 768
	{
		menuX = 358;
		menuY = 435;
	}
	for(int i = 0; i < menuSize; i++ )
	{
		//set the menu strings.
		Menus[i].SetFont(Font);
		Menus[i].SetSize(32);
		Menus[i].SetText(MenuStrs[i]);
		Menus[i].SetPosition(menuX, menuY + (30 * i));
		//set the options per menu entry
		MenuOptions[i].SetFont(Font);
		MenuOptions[i].SetSize(32);
		if( MenuStrs[i].compare("Screen Size") == 0)
			MenuOptions[i].SetText(screenSizeStr[screenSize]);
		if( MenuStrs[i].compare("Fullscreen") == 0)
			MenuOptions[i].SetText(fullscreenStr[fullscreen]);
		if( MenuStrs[i].compare("Input Type") == 0)
			MenuOptions[i].SetText(inputTypeStr[input]);
		if( MenuStrs[i].compare("Difficulty") == 0)
			MenuOptions[i].SetText(difficultyStr[difficulty]);
		MenuOptions[i].SetPosition(menuX + 170, menuY + (30 * i));
		//set color of the options to black
		MenuOptions[i].SetColor(sf::Color(0, 0, 0, 180));
	}

    while (Running)
    {
        while (App.GetEvent(Event))
        {
            if (Event.Type == sf::Event::Closed)
            {
                return (-1);
            }
            if (Event.Type == sf::Event::KeyPressed)
            {
                switch (Event.Key.Code)
                {
                    case sf::Key::Up:
						if( menu > 0 )
							menu--;
						else
							menu = menuSize - 1;
                        break;
                    case sf::Key::Down:
						if( menu < menuSize - 1 )
							menu++;
						else
							menu = 0;
                        break;
                    case sf::Key::Return:
						if( menu == 0 ) //screen size
						{
							//increment screen size and check to see if we need to rotate back to the beginning.
							screenSize++;
							if( screenSize > 1 )
								screenSize = 0;
							//set the menu options new text
							MenuOptions[NSOptions::screenSize].SetText(screenSizeStr[screenSize]);
							//set the game class with the new screen size
							GC->screenSize = screenSize;
							//set the correct screen size for the options selected.
							if( screenSize == 0 )
							{
								GC->ScreenWidth = 800;
								GC->ScreenHeight = 600;
								GC->MapWidth = 25;
								GC->MapHeight = 19;
								GC->characterSheet_XPos = 564;
								GC->characterSheet_YPos = 10;
								GC->elucidatePalette_XPos = 236;
								GC->elucidatePalette_YPos = 540;
								//re-locate the menus to fit with the 800 X 600 image
								menuX = 280;
								menuY = 340;
							}
							if( screenSize == 1 )
							{
								GC->ScreenWidth = 1024;
								GC->ScreenHeight = 768;
								GC->MapWidth = 32;
								GC->MapHeight = 24;
								GC->characterSheet_XPos = 788;
								GC->characterSheet_YPos = 10;
								GC->elucidatePalette_XPos = 348;
								GC->elucidatePalette_YPos = 708;
								//re-locate the menus to fit with the 1024 X 768 image
								menuX = 358;
								menuY = 435;
							}
							//reset the sprite to hold the new one.
							//Create a new sprite and set the old sprite to it
							//taking advantage of the copy constructer to copy all
							//the new sprites info over i.e. width height.
							sf::Sprite tmp;
							tmp.SetImage(Images[screenSize]);
							Sprite = tmp;
							//set the new video mode with correct settings.
							if(GC->fullscreen == 0)
								App.Create(sf::VideoMode(GC->ScreenWidth, GC->ScreenHeight, 32), GC->screenName, sf::Style::Close);
							if(GC->fullscreen == 1)
								App.Create(sf::VideoMode(GC->ScreenWidth, GC->ScreenHeight, 32), GC->screenName, sf::Style::Fullscreen);
							for(int i = 0; i < menuSize; i++ )
							{
								Menus[i].SetPosition(menuX, menuY + (30 * i));
								MenuOptions[i].SetPosition(menuX + 170, menuY + (30 * i));
							}
						}
						if( menu == 1 ) //Fullscreen
						{
							fullscreen++;
							if( fullscreen > 1 )
								fullscreen = 0;
							MenuOptions[NSOptions::fullScreen].SetText(fullscreenStr[fullscreen]);
							GC->fullscreen = fullscreen;
							if(GC->fullscreen == 0)
								App.Create(sf::VideoMode(GC->ScreenWidth, GC->ScreenHeight, 32), GC->screenName, sf::Style::Close);
							if(GC->fullscreen == 1)
								App.Create(sf::VideoMode(GC->ScreenWidth, GC->ScreenHeight, 32), GC->screenName, sf::Style::Fullscreen);
						}
						if( menu == 2 ) //Input Type
						{
							input++;
							if( input > 1 )
								input = 0;
							MenuOptions[NSOptions::inputType].SetText(inputTypeStr[input]);
							GC->input = input;
						}
						if( menu == 3 ) //Difficulty
						{
							difficulty++;
							if( difficulty > 2 )
								difficulty = 0;
							MenuOptions[NSOptions::difficulty].SetText(difficultyStr[difficulty]);
							GC->difficulty = difficulty;
						}
						if( menu == menuSize - 1 )
							return 3; //return to main menu
                        break;
					case sf::Key::Escape:
						return -1;
                    default :
                        break;
                }
            }
        }
		for( int i = 0; i < menuSize; i++ )
		{
			if( menu == i )
				Menus[i].SetColor(sf::Color(255, 255, 255, 180));
			else
				Menus[i].SetColor(sf::Color(255, 0, 0, 180));
		}

		//Clearing screen
		App.Clear();

        //Drawing
        App.Draw(Sprite);

		for(int i = 0; i < menuSize; i++ )
		{
			App.Draw(Menus[i]);
			App.Draw(MenuOptions[i]);
		}
        App.Display();
    }
    //Never reaching this point normally, but just in case, exit the application
    return (-1);
}