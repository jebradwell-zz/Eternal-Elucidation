#include "InputModule.h"
#include "GameClass.h"

sf::RenderWindow * InputModule::mApp;
GameClass *InputModule::GC;

InputModule::InputModule()
{
}
int InputModule::update()
{
	GameClass *GC = Game::getInstance();
	mTest.dir = NULL;
	mTest.extra = NULL;
	mElapseTime = mApp->GetFrameTime();

	if (mApp->GetInput().IsKeyDown(sf::Key::Escape))
		return -1;

	if (mApp->GetInput().IsKeyDown(sf::Key::F)) 
		mApp->Create(sf::VideoMode(GC->ScreenWidth, GC->ScreenHeight, 32), SCREEN_NAME, sf::Style::Fullscreen);

	if (mApp->GetInput().IsKeyDown(sf::Key::G)) 
		mApp->Create(sf::VideoMode(GC->ScreenWidth, GC->ScreenHeight, 32), SCREEN_NAME, sf::Style::Close);
	

	//if (mApp->GetInput().IsKeyDown(sf::Key::R)) 
	//	radius++;

	//if (mApp->GetInput().IsKeyDown(sf::Key::T)) 
	//	radius--;


	if( GC->input == 1) //Controller
	{
		// Movement Keys
		if (mApp->GetInput().IsKeyDown(sf::Key::W)) mTest.dir |= 9; //1000
		if (mApp->GetInput().IsKeyDown(sf::Key::D)) mTest.dir |= 5; //1000
		if (mApp->GetInput().IsKeyDown(sf::Key::S)) mTest.dir |= 6; //1000
		if (mApp->GetInput().IsKeyDown(sf::Key::A)) mTest.dir |= 10; //1000

		if (mApp->GetInput().IsKeyDown(sf::Key::Up)) mTest.dir |= 8; //1000
		if (mApp->GetInput().IsKeyDown(sf::Key::Down)) mTest.dir |= 4; //0100
		if (mApp->GetInput().IsKeyDown(sf::Key::Left)) mTest.dir |= 2; //0010
		if (mApp->GetInput().IsKeyDown(sf::Key::Right)) mTest.dir |= 1; //0001
#if G_DEBUG
		std::cout << test.dir << std::endl;
#endif
		switch(mTest.dir)
		{

		case 8:
			GC->PlayerSprite.Move(0, -speed * mElapseTime);
			break;
		case 4:
			GC->PlayerSprite.Move(0, speed * mElapseTime);
			break;
		case 2:
			GC->PlayerSprite.Move(-speed * mElapseTime, 0);
			break;
		case 1:
			GC->PlayerSprite.Move(speed * mElapseTime, 0);
			break;

		case 10:
			GC->PlayerSprite.Move( -speed * mElapseTime * SQRT2OVER2, -speed * mElapseTime * SQRT2OVER2);
			break;
		case 9:
			GC->PlayerSprite.Move(speed * mElapseTime * SQRT2OVER2, -speed * mElapseTime * SQRT2OVER2);
			break;
		case 6:
			GC->PlayerSprite.Move(-speed * mElapseTime * SQRT2OVER2, speed * mElapseTime * SQRT2OVER2);
			break;
		case 5:
			GC->PlayerSprite.Move(speed * mElapseTime * SQRT2OVER2, speed * mElapseTime * SQRT2OVER2);
			break;
		}
	}

	if( GC->input == 0) //Keyboard	
	{
		// Movement Keys
		if (mApp->GetInput().IsKeyDown(sf::Key::Up)) mTest.dir |= 8; //1000
		if (mApp->GetInput().IsKeyDown(sf::Key::Down)) mTest.dir |= 4; //0100
		if (mApp->GetInput().IsKeyDown(sf::Key::Left)) mTest.dir |= 2; //0010
		if (mApp->GetInput().IsKeyDown(sf::Key::Right)) mTest.dir |= 1; //0001
#if G_DEBUG
		std::cout << test.dir << std::endl;
#endif
		//if (mTest.dir & 8)
		//{
		//	GC->PlayerSprite.Move(0, -speed * mElapseTime);
		//}
		//if (mTest.dir & 4)
		//{
		//	GC->PlayerSprite.Move(0, speed * mElapseTime);
		//}
		//if (mTest.dir & 2)
		//{
		//	GC->PlayerSprite.Move(-speed * mElapseTime, 0);
		//}
		//if (mTest.dir & 1)
		//{
		//	GC->PlayerSprite.Move(speed * mElapseTime, 0);
		//}
		 switch(mTest.dir)
		{
		case 11:
		case 8:
			GC->PlayerSprite.Move(0, -speed * mElapseTime);
			break;
		case 7:
		case 4:
			GC->PlayerSprite.Move(0, speed * mElapseTime);
			break;
		case 14:
		case 2:
			GC->PlayerSprite.Move(-speed * mElapseTime, 0);
			break;
		case 13:
		case 1:
			GC->PlayerSprite.Move(speed * mElapseTime, 0);
			break;
		case 10:
			GC->PlayerSprite.Move( -speed * mElapseTime * SQRT2OVER2, -speed * mElapseTime * SQRT2OVER2);
			break;
		case 9:
			GC->PlayerSprite.Move(speed * mElapseTime * SQRT2OVER2, -speed * mElapseTime * SQRT2OVER2);
			break;
		case 6:
			GC->PlayerSprite.Move(-speed * mElapseTime * SQRT2OVER2, speed * mElapseTime * SQRT2OVER2);
			break;
		case 5:
			GC->PlayerSprite.Move(speed * mElapseTime * SQRT2OVER2, speed * mElapseTime * SQRT2OVER2);
			break;
		} 
	}
	return EXIT_SUCCESS;
}