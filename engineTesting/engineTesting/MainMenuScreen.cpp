#include "MainMenuScreen.h"
#include "GameClass.h"
#include <iostream>
MainMenuScreen::MainMenuScreen()
{
}

int MainMenuScreen::Run( sf::RenderWindow &App )
{
	App.ShowMouseCursor(false);
	sf::Event Event;
    bool Running = true;
    sf::Image Image, ImageLarge;
    sf::Sprite Sprite;
    float menuX = 280, menuY = 340;
    sf::Font Font;
	const int menuSize = 4;
	sf::String Menus[menuSize];
	std::string MenuStrs[menuSize] = {"New Game","Load Game","Options","Quit"};
    int menu = 0;
	GameClass *GC = Game::getInstance();
    if (!Image.LoadFromFile("Images/MainMenu.png"))
    {
        std::cerr<<"Error loading MainMenu.png"<<std::endl;
        return -1;
    }
	if (!ImageLarge.LoadFromFile("Images/MainMenuLarge.png"))
	{
		std::cerr<<"Error loading MainMenuLarge.png"<<std::endl;
		return -1;
	}

    if (!Font.LoadFromFile("AquaductPlain.ttf"))
    {
        std::cerr<<"Error loading AquaductPlain.ttf"<<std::endl;
        return -1;
    }
	if( GC->screenSize == 0 ) //800 X 600
	{
		menuX = 280;
		menuY = 340;
		Sprite.SetImage(Image);
	}
	if( GC->screenSize == 1) //1024 X 768
	{
		menuX = 358;
		menuY = 435;
		Sprite.SetImage(ImageLarge); //set Sprite to large Main Menu image
	}
	for( int i = 0; i < menuSize; i++ )
	{
		Menus[i].SetFont(Font);
		Menus[i].SetSize(32);
		Menus[i].SetText(MenuStrs[i]);
		Menus[i].SetPosition(menuX, menuY + (30 * i));
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
						if( menu == menuSize - 1 )
							return -1;
						return menu;
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
		}
        App.Display();
    }
 
    //Never reaching this point normally, but just in case, exit the application
    return (-1);

}