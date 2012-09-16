///////////////////////////////////////////////////////////////////////////////
// COPYRIGHT © 2009 Jeb Bradwell, Adam Zech & Ron Moore
// This file is distributed under the terms of the GNU General Public License
///////////////////////////////////////////////////////////////////////////////
/// @file collision.cpp
///
/// @brief
/// Defines the collision class functions.
///
/// @remarks
/// ...
////////////////////////////////////////////////////////////////////////////////

//#include "Collision.h":  The .h file includes the .cpp file in this case
#include <vector>
#include "SFML/Graphics.hpp"
#include "GameObject.h"
#include "Collision.h"
#include <algorithm>

using std::vector;
namespace Collision
{
	bool ObjectsCollide(GameObject *o1, GameObject *o2)
	{
		sf::Rect<int> r1 = RectFromShapes(o1->CollisionBounds);
		r1.Offset(o1->Position.x,o1->Position.y);
		sf::Rect<int> r2 = RectFromShapes(o2->CollisionBounds);
		r2.Offset(o2->Position.x,o2->Position.y);
		// .Intersects does requires that they OVERlap, special check to see if they are 1 pixel objects at the same point. - Adam
		if (r2.Bottom==r1.Bottom && r1.Left==r2.Left && r1.Right==r2.Right && r1.Top == r2.Top)
			return true;
		return r1.Intersects(r2);
	}
	sf::Rect<int> RectFromShapes(vector<sf::Shape> inShapes)
	{
		size_t tSize=inShapes.size();
		//In thoery, this should never be called with an empty vector...
		//Returning an empty Rect if we do instead of the previous alternative (crash on vector iteration). -Adam
		if (tSize == 0)
			return sf::Rect<int>(0,0,0,0);
		vector<int> allX;
		vector<int> allY;

		for (size_t i=0;i<tSize;i++)
		{
			size_t tSize2=inShapes.at(i).GetNbPoints();
			for (size_t n=0;n<tSize2;n++)
			{
				allX.push_back(inShapes.at(i).GetPointPosition(n).x);
				allY.push_back(inShapes.at(i).GetPointPosition(n).y);
			}
		}
		int minX=*min_element(allX.begin(),allX.end());
		int maxX=*max_element(allX.begin(),allX.end());
		int minY=*min_element(allY.begin(),allY.end());
		int maxY=*max_element(allY.begin(),allY.end());

		return sf::Rect<int>(minX,minY,maxX,maxY);
	}
	vector< sf::Vector2<int> > PixelsCollide(GameObject *o1, GameObject *o2)
	{
		/*size_t shapes1 = o1->CollisionBounds.size();
		
		for (size_t i=0;i<shapes1;i++)
		{
			size_t points1 = o1->CollisionBounds.at(i).GetNbPoints;
			for (size_t n=0;n<points1;n++)
			{
				o1->CollisionBounds.at(i).g
			}
		}*/
		vector< sf::Vector2<int> > retVal;
		sf::Vector2<int> dummyValue = sf::Vector2<int>(10,10);
		retVal.push_back(dummyValue);
		return retVal;
	}
}
