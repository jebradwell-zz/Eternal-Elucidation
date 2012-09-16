#include "Poison.h"

#define COLLISION_DISTANCE 25

sf::Image *Poison::mImage;
sf::Sprite *Poison::mPlayer;

Poison::Poison() : mAlive(true)
{
}
Poison::Poison( int x, int y ) : mAlive(true)
{
	mSprite.SetImage(*mImage);
	SetPosition(x, y);
	mSprite.SetCenter( mImage->GetWidth() / 2.0f, mImage->GetHeight() / 2.0f );
	mMoveSpeed = (float)(((50 + 1) * rand()) / (RAND_MAX + 1.0)) + 5;
}

void Poison::draw()
{
	mApp->Draw(mSprite);
}


void Poison::update()
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