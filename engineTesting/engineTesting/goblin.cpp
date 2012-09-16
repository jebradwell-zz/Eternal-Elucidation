#include "goblin.h"

#define COLLISION_DISTANCE 25

sf::Image *Goblin::mImage;
sf::Sprite *Goblin::mPlayer;

Goblin::Goblin() : mAlive(true)
{
	//mSprite.SetImage(*mImage);
	//SetPosition(100, 100);
	//mSprite.SetCenter( mImage->GetWidth() / 2, mImage->GetHeight() / 2 );
	//mMoveSpeed = (float)(((200 + 1) * rand()) / (RAND_MAX + 1.0)) + 100;
}
Goblin::Goblin( int x, int y ) : mAlive(true)
{
	mSprite.SetImage(*mImage);
	SetPosition(x, y);
	mSprite.SetCenter( mImage->GetWidth() / 2.0f, mImage->GetHeight() / 2.0f );
	mMoveSpeed = (float)(((50 + 1) * rand()) / (RAND_MAX + 1.0)) + 5;
}

//void Goblin::draw(sf::RenderWindow &App)
//{
//	App.Draw(mSprite);
//}

void Goblin::draw()
{
	mApp->Draw(mSprite);
}

//void Goblin::update(sf::RenderWindow &App, const sf::Sprite &player)
//{
//	float x = mSprite.GetPosition().x, y = mSprite.GetPosition().y;
//	float px = player.GetPosition().x, py = player.GetPosition().y;
//	float delta = mMoveSpeed * mApp->GetFrameTime();
//	if( x < px )
//		x += delta;
//	else
//		x -= delta;
//	if( y < py )
//		y += delta;
//	else
//		y -= delta;
//	if( x < px + COLLISION_DISTANCE && x > px - COLLISION_DISTANCE && y < py + COLLISION_DISTANCE && y > py - COLLISION_DISTANCE )
//		mAlive = false;
//	mSprite.SetPosition( x, y );
//}

void Goblin::update()
{
	float x = mSprite.GetPosition().x, y = mSprite.GetPosition().y;
	float px = mPlayer->GetPosition().x, py = mPlayer->GetPosition().y;
	float delta = mMoveSpeed * mApp->GetFrameTime();
	if( x < px )
		x += delta;
	else
		x -= delta;
	if( y < py )
		y += delta;
	else
		y -= delta;
	if( x < px + COLLISION_DISTANCE && x > px - COLLISION_DISTANCE && y < py + COLLISION_DISTANCE && y > py - COLLISION_DISTANCE )
		mAlive = false;
	mSprite.SetPosition( x, y );
}