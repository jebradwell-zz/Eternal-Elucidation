#include "ElucidatePalette.h"

sf::Image *ElucidatePalette::mImage;


ElucidatePalette::ElucidatePalette() : mAlive(true)
{
}

ElucidatePalette::ElucidatePalette( int x, int y ) : mAlive(true)
{
	mSprite.SetImage(*mImage);
	mSprite.SetPosition(x, y);	
}

void ElucidatePalette::draw()
{
	mApp->Draw(mSprite);
	int spriteXpos = (int)mSprite.GetPosition().x;
	int spriteYpos = (int)mSprite.GetPosition().y;
	int x = mApp->GetInput().GetMouseX();
		int y = mApp->GetInput().GetMouseY();
		//Blue outline.
		int xPosPairs[10][2] = { {1, 33}, {34, 65}, {66, 97}, {98, 129}, {130, 161}, {162, 193}, {194, 225}, {226, 257}, {258, 289}, {290, 324} };
		int yPosPairs[10][2] = { {1, 34}, {1, 34}, {1, 34}, {1, 34}, {1, 34}, {1, 34}, {1, 34}, {1, 34}, {1, 34}, {1, 34} };
		sf::Shape Rectangle;
		for( int i = 0; i < 10; i++ )
		{
			if( x >= spriteXpos + xPosPairs[i][0] && x < spriteXpos + xPosPairs[i][1] && y >= spriteYpos + yPosPairs[i][0] && y <= spriteYpos + yPosPairs[i][1] )
			{
				Rectangle = sf::Shape::Rectangle(spriteXpos + xPosPairs[i][0] + 2, spriteYpos +  yPosPairs[i][0] + 2, spriteXpos + xPosPairs[i][1] + 1, spriteYpos +  yPosPairs[i][1] + 1, sf::Color(0, 0, 0), 2.0f, sf::Color(0, 0, 255));
				Rectangle.EnableFill(false);
				mApp->Draw(Rectangle);
			}
		}
}

void ElucidatePalette::update()
{
}