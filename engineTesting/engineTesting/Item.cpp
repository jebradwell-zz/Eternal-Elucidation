#include "Item.h"



Item::Item() : mImageSet(false)
{
}

void Item::update()
{
}

void Item::draw()
{
	//dont draw if there has been no image set yet.
	if( mImageSet )
		mApp->Draw(mSprite);
}

void Item::setPosition(int x, int y)
{
	mSprite.SetPosition(x,y);
}

void Item::setSubRec( int L, int T, int R, int B)
{
	sf::IntRect rec(L,T,R,B);
	mSprite.SetSubRect(rec);
	//set the center to the middle of the sprite.
	mSprite.SetCenter((R - L) / 2, (B - T) / 2);
}

void Item::setImage( sf::Image &Image)
{
	mSprite.SetImage(Image);
	mImageSet = true;
}