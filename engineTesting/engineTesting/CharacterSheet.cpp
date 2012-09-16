#include "CharacterSheet.h"
#include <iostream>
#include "EquipmentClass.h"
#include "OrbClass.h"
#include "GameClass.h"

sf::Image *CharacterSheet::mImage;

CharacterSheet::CharacterSheet(int x, int y) :mAlive(true), mDraw(false), mCKeyState(false), mLeftMouseState(false), mRadius(10)/*Circle radius are set to 10.*/, mSelectedRectangle(-1)/*-1 means no selected rectangle*/,mSelectedCircle(-1)
{
	mSprite.SetImage(*mImage);
	mSprite.SetPosition(x, y);
	//xPosPairs and xPosPairs Example:
	// y=64 
	// x= 1*---------------
	//     |              |
	//     |              |
	//     |              |
	//     |              |
	//     |              |
	//     ---------------* y=95
	//                      x=31
	int xPosPairs[numberOfEquipment][2] = { {1, 31}, {1, 31}, {1, 31}, {1, 31}, {1, 31}, {1, 31}, {32, 63}, {64, 95}, {96, 127}, {128, 159}, {160, 191}, {192, 222}, {192, 222}, {192, 222}, {192, 222}, {192, 222}, {192, 222} };
	int yPosPairs[numberOfEquipment][2] = { {64, 95}, {96, 127}, {128, 159}, {160, 191}, {192, 223}, {224, 254}, {224, 254}, {224, 254}, {224, 254}, {224, 254}, {224, 254}, {224, 254}, {192, 223}, {160, 191}, {128, 159}, {96, 127}, {64, 95} };
	//locations of the center of all the circles in the character sheet.
	int circleXYPos[numberOfOrbs][2] = { {112, 84}, {142, 92}, {164, 114}, {172, 144}, {164, 174}, {142, 196}, {112, 204}, {82, 196}, {60, 174}, {52, 144}, {60, 114}, {82, 92} };
	for(int i = 0; i < numberOfEquipment; i++ )
	{
		this->mXPosPairs[i][0] = xPosPairs[i][0];
		this->mXPosPairs[i][1] = xPosPairs[i][1];
		this->mYPosPairs[i][0] = yPosPairs[i][0];
		this->mYPosPairs[i][1] = yPosPairs[i][1];
	}
	//there are 12 circles thus iterate 12 times to
	//copy them all over.
	for( int i = 0; i < numberOfOrbs; i++ )
	{
		mCircleXYPos[i][0] = circleXYPos[i][0];
		mCircleXYPos[i][1] = circleXYPos[i][1];
	}
}

void CharacterSheet::update()
{
	GameClass *GC = Game::getInstance();
	EquipmentClass *EC = Equipment::getInstance();
	OrbClass *OC = Orbs::getInstance();
	if (mApp->GetInput().IsKeyDown(sf::Key::C) && !mCKeyState) 
	{
		//toggle inventory diplay.
		mCKeyState = true;
		mDraw = !mDraw;
	}
	if (!mApp->GetInput().IsKeyDown(sf::Key::C) && mCKeyState) 
		mCKeyState = false;
	//If left click then check where the mouse is and pull that image from the array
	//of items in the Character Sheet Equipment or Orb Section.
	if(mApp->GetInput().IsMouseButtonDown(sf::Mouse::Left) && !mLeftMouseState && mDraw)
	{
		mLeftMouseState = true;
		//get the current mouse X and Y positions and the current Character Sheet sprites X and Y position.
		updateInputs();
		//check all the rectangles
		for( int i = 0; i < numberOfEquipment; i++ )
		{
			//check to see if the mouse is over a rectangle AND which retangle it is over.
			if( mMouseX >= mSpriteXpos + mXPosPairs[i][0] + 1 && mMouseX < mSpriteXpos + mXPosPairs[i][1] && mMouseY >= mSpriteYpos + mYPosPairs[i][0] + 1 && mMouseY <= mSpriteYpos + mYPosPairs[i][1] )
			{
				mSelectedRectangle = i;

				//break for loop and potentially save some interations time.
				break;
			}
		}
		//check all the circles
		for( int i = 0; i < numberOfOrbs; i++ )
		{
			//get the X and Y componets of the mouse offset from each circle.
			int xCom = mMouseX - ( mSpriteXpos + mCircleXYPos[i][0] );
			int yCom = mMouseY - ( mSpriteYpos + mCircleXYPos[i][1] );
			//Blue outline
			//check to see if the mouse is inside the circle with pythagorian equation.
			if(xCom * xCom + yCom * yCom < mRadius * mRadius )
			{
				mSelectedCircle = i;
				//break for loop and potentially save some interations time.
				break;
			}
		}

		//If we have not selected something from the orbs or equipment sections yet then 
		//check and grab the selected item.
		if( GC->itemHolder == NULL && mSelectedRectangle != -1 )
		{
			GC->itemHolder = EC->getEquipment(mSelectedRectangle);
			//reset mSelectedRectangle to -1 for next time we want to select
			mSelectedRectangle = -1;
		}
		//else we are checking to see if we can release the stored item into the 
		//selected equipment section.
		if( GC->itemHolder != NULL && mSelectedRectangle != -1 && GC->itemHolder->mEquipmentType == mSelectedRectangle )
		{
			Item *tmp = EC->addEquipment(mSelectedRectangle, GC->itemHolder);
			GC->itemHolder = tmp;
			mSelectedRectangle = -1;
		}
		//for elucidation tiles 
		if( GC->itemHolder != NULL && mSelectedRectangle != -1 && GC->itemHolder->mEquipmentType >= EquipmentTypes::ElucidationTile && mSelectedRectangle >= EquipmentTypes::ElucidationTile)
		{
			Item *tmp = EC->addEquipment(mSelectedRectangle, GC->itemHolder);
			GC->itemHolder = tmp;
			mSelectedRectangle = -1;
		}

		/***************************************************************************/
		//Do the same thing for the orbs except check for -1 of the mSelectedCircle
		/***************************************************************************/

		//If we have not selected something from the orbs or equipment sections yet then 
		//check and grab the selected item.

		if( GC->itemHolder == NULL && mSelectedCircle != -1 )
		{
			GC->itemHolder = OC->grabOrb(mSelectedCircle);
			//reset mSelectedCircle to -1 for next time we want to select
			mSelectedCircle = -1;
		}
		//else we are checking to see if we can release the stored item into the 
		//selected orb or equipment section.
		if( GC->itemHolder != NULL && GC->itemHolder->mType == ItemTypes::Orb && mSelectedCircle != -1 )
		{
			Item *tmp = OC->addOrb(mSelectedCircle, GC->itemHolder);
			GC->itemHolder = tmp;
			mSelectedCircle = -1;
		}

	}
	//toggle left mouse click.
	if( !mApp->GetInput().IsMouseButtonDown(sf::Mouse::Left) && mLeftMouseState && mDraw)
	{		
		mLeftMouseState = false;
		mSelectedRectangle = -1;
		mSelectedCircle = -1;
	}
}

void CharacterSheet::draw()
{
	EquipmentClass *EC = Equipment::getInstance();
	OrbClass *OC = Orbs::getInstance();
	GameClass *GC = Game::getInstance();
	if(mDraw)
	{
		//If the draw toggle is set the draw the Character sheet to the screen.
		mApp->Draw(mSprite);
		EC->draw();
		OC->draw();
		updateInputs();
		for( int i = 0; i < numberOfOrbs; i++ )
		{
			//get the X and Y componets of the mouse offset from each circle.
			int xCom = mMouseX - ( mSpriteXpos + mCircleXYPos[i][0] );
			int yCom = mMouseY - ( mSpriteYpos + mCircleXYPos[i][1] );
			//Blue outline
			//check to see if the mouse is inside the circle with pythagorian equation.
			if(xCom * xCom + yCom * yCom < mRadius * mRadius )
				if( GC->itemHolder != NULL && GC->itemHolder->mType != ItemTypes::Orb )
					//Red outline for items that can't be placed in the orb slots
					mCircle = sf::Shape::Circle(mCircleXYPos[i][0] + mSpriteXpos, mCircleXYPos[i][1] + mSpriteYpos, mRadius, sf::Color(0,0,0), 2.0, sf::Color(255,0,0));
				else
					//Blue outline for items that can be placed in the orb slots
					mCircle = sf::Shape::Circle(mCircleXYPos[i][0] + mSpriteXpos, mCircleXYPos[i][1] + mSpriteYpos, mRadius, sf::Color(0,0,0), 2.0, sf::Color(0,0,255));
			else
				mCircle = sf::Shape::Circle(mCircleXYPos[i][0] + mSpriteXpos, mCircleXYPos[i][1] + mSpriteYpos, mRadius, sf::Color(0,0,0), 2.0, sf::Color(224,224,224));
			mCircle.EnableFill(false);
			mApp->Draw(mCircle);
			//Draw outer black circle
			mCircle = sf::Shape::Circle(mCircleXYPos[i][0] + mSpriteXpos, mCircleXYPos[i][1] + mSpriteYpos, mRadius + 2, sf::Color(0,0,0), 1.0);
			mCircle.EnableFill(false);
			mApp->Draw(mCircle);
			//Draw inner black circle
			mCircle = sf::Shape::Circle(mCircleXYPos[i][0] + mSpriteXpos, mCircleXYPos[i][1] + mSpriteYpos, mRadius - 1, sf::Color(0,0,0), 1.0);
			mCircle.EnableFill(false);
			mApp->Draw(mCircle);
		}

		for( int i = 0; i < numberOfEquipment; i++ )
		{
			//check to see if the mouse is over a rectangle.
			if( mMouseX >= mSpriteXpos + mXPosPairs[i][0] + 1 && mMouseX < mSpriteXpos + mXPosPairs[i][1] && mMouseY >= mSpriteYpos + mYPosPairs[i][0] + 1 && mMouseY <= mSpriteYpos + mYPosPairs[i][1] )
			{
				//Blue outline in the case of item being held.
				if( GC->itemHolder != NULL && (GC->itemHolder->mEquipmentType == i || (GC->itemHolder->mEquipmentType >= EquipmentTypes::ElucidationTile && i >= EquipmentTypes::ElucidationTile)))
					mRectangle = sf::Shape::Rectangle(mSpriteXpos + mXPosPairs[i][0] + 2, mSpriteYpos +  mYPosPairs[i][0] + 2, mSpriteXpos + mXPosPairs[i][1] + 1, mSpriteYpos +  mYPosPairs[i][1] + 1, sf::Color(0, 0, 0), 2.0f, sf::Color(0, 0, 255));
				//Red outline. Equipment doesn't belong in this slot. For all items except elucidation tiles
				if( GC->itemHolder != NULL && GC->itemHolder->mEquipmentType != i )
					mRectangle = sf::Shape::Rectangle(mSpriteXpos + mXPosPairs[i][0] + 2, mSpriteYpos +  mYPosPairs[i][0] + 2, mSpriteXpos + mXPosPairs[i][1] + 1, mSpriteYpos +  mYPosPairs[i][1] + 1, sf::Color(0, 0, 0), 2.0f, sf::Color(255, 0, 0));

				if( GC->itemHolder != NULL && GC->itemHolder->mEquipmentType >= EquipmentTypes::ElucidationTile && i >= EquipmentTypes::ElucidationTile)
					mRectangle = sf::Shape::Rectangle(mSpriteXpos + mXPosPairs[i][0] + 2, mSpriteYpos +  mYPosPairs[i][0] + 2, mSpriteXpos + mXPosPairs[i][1] + 1, mSpriteYpos +  mYPosPairs[i][1] + 1, sf::Color(0, 0, 0), 2.0f, sf::Color(0, 0, 255));

				//Blue outline in the case with no item held by the item holder... aka no item on the mouse.
				if(GC->itemHolder == NULL )
					mRectangle = sf::Shape::Rectangle(mSpriteXpos + mXPosPairs[i][0] + 2, mSpriteYpos +  mYPosPairs[i][0] + 2, mSpriteXpos + mXPosPairs[i][1] + 1, mSpriteYpos +  mYPosPairs[i][1] + 1, sf::Color(0, 0, 0), 2.0f, sf::Color(0, 0, 255));
				mRectangle.EnableFill(false);
				mApp->Draw(mRectangle);
			}
		}
	}
}

void CharacterSheet::updateInputs()
{
	mMouseX = mApp->GetInput().GetMouseX();
	mMouseY = mApp->GetInput().GetMouseY();
	mSpriteXpos = (int)mSprite.GetPosition().x;
	mSpriteYpos = (int)mSprite.GetPosition().y;
}