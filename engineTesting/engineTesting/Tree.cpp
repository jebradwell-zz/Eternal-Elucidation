#include "Tree.h"

sf::Image *Tree::mImage;
sf::Sprite *Tree::mPlayer;

Tree::Tree( int x, int y )
{
	mSprite.SetImage(*mImage);
	mSprite.SetPosition((float)x, (float)y);
	mSprite.SetCenter( mImage->GetWidth() / 2.0f, mImage->GetHeight() / 2.0f );
}

void Tree::update()
{

}

void Tree::draw()
{
	mApp->Draw(mSprite);
}