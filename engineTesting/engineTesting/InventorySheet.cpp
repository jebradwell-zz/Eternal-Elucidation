#include "InventorySheet.h"
#include "InventoryClass.h"
#include "GameClass.h"

sf::Image *InventorySheet::mImage;

InventorySheet::InventorySheet(int x, int y) :mAlive(true), mDraw(false), mIKeyState(false), mLeftMouseState(false), mSelectedRectangle(-1)/*-1 means no selected rectangle*/
{
	mSprite.SetImage(*mImage);
	mSprite.SetPosition(x, y);
}

void InventorySheet::update()
{
	InventoryClass *IC = Inventory::getInstance();
	GameClass *GC = Game::getInstance();
	if (mApp->GetInput().IsKeyDown(sf::Key::I) && !mIKeyState) 
	{
		//toggle inventory diplay.
		mIKeyState = true;
		mDraw = !mDraw;
	}
	if (!mApp->GetInput().IsKeyDown(sf::Key::I) && mIKeyState) 
		mIKeyState = false;
	//If left click then check where the mouse is and pull that image from the array
	//of items in the Character Sheet Equipment or Orb Section.
	if(mApp->GetInput().IsMouseButtonDown(sf::Mouse::Left) && !mLeftMouseState && mDraw)
	{
		mLeftMouseState = true;
		//get the current mouse X and Y positions and the current Character Sheet sprites X and Y position.
		updateInputs();
		//check all the rectangles
		for(int i = 0, j = 0; i < numberOfInventory; i++)
		{
			if( i != 0 && (i % 6) == 0 )
				j++;
			mItemXLocation = ((i % 6) * 37) + 4;
			mItemYLocation = (j * 37) + 36;

			//check to see if the mouse cursor is inside the rectangle area of 
			//
			if( mMouseX >= mSpriteXpos + mItemXLocation + 1 && mMouseX < mSpriteXpos + mItemXLocation + ItemSpriteWidth 
				&& mMouseY >= mSpriteYpos + mItemYLocation && mMouseY <= mSpriteYpos + mItemYLocation + ItemSpriteHeight )
			{
				mSelectedRectangle = i;

				//break for loop and potentially save some interations time.
				break;
			}
		}

		//If there is no item in the item holder variable then get 
		//the current item in selected rectangle slot
		if( GC->itemHolder == NULL && mSelectedRectangle != -1 )
		{
			GC->itemHolder = IC->getItem(mSelectedRectangle);
			//reset mSelectedRectangle to -1 for next time we want to select
			mSelectedRectangle = -1;
		}
		//else we are checking to see if we can release the stored item into the 
		//selected inventory slot. Either swap or just place the item.
		if( GC->itemHolder != NULL && mSelectedRectangle != -1 )
		{
			Item *tmp = IC->addItem(mSelectedRectangle, GC->itemHolder);
			GC->itemHolder = tmp;
			mSelectedRectangle = -1;
		}

	}
	//toggle left mouse click.
	if( !mApp->GetInput().IsMouseButtonDown(sf::Mouse::Left) && mLeftMouseState && mDraw)
	{		
		mLeftMouseState = false;
		mSelectedRectangle = -1;
	}
}

void InventorySheet::draw()
{
	InventoryClass *IC = Inventory::getInstance();
	GameClass *GC = Game::getInstance();
	if(mDraw)
	{
		//If the draw toggle is set the draw the Character sheet to the screen.
		mApp->Draw(mSprite);
		IC->draw();
		updateInputs();
	}
}

void InventorySheet::updateInputs()
{
	mMouseX = mApp->GetInput().GetMouseX();
	mMouseY = mApp->GetInput().GetMouseY();
	mSpriteXpos = (int)mSprite.GetPosition().x;
	mSpriteYpos = (int)mSprite.GetPosition().y;
}