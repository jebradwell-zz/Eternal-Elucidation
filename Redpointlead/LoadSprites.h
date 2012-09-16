#ifndef LOAD_SPRITES_H
#define LOAD_SPRITES_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "tinyxml2/tinyxml2.h"


void setColorMap( std::map<std::string, sf::Color> *map, std::string color, sf::Color sfcolor) {
	map->insert(std::pair<std::string, sf::Color>(color,sfcolor));
}

std::map<std::string, sf::Color> getColorMap() {
	std::map<std::string, sf::Color> ColorMap;
	setColorMap(&ColorMap,"Black",sf::Color::Black);
	setColorMap(&ColorMap,"Blue",sf::Color::Blue);
	setColorMap(&ColorMap,"Cyan",sf::Color::Cyan);
	setColorMap(&ColorMap,"Green",sf::Color::Green);
	setColorMap(&ColorMap,"Magenta",sf::Color::Magenta);
	setColorMap(&ColorMap,"Red",sf::Color::Red);
	setColorMap(&ColorMap,"White",sf::Color::White);
	setColorMap(&ColorMap,"Yellow",sf::Color::Yellow);
	return ColorMap;
}

void LoadSprites( tinyxml2::XMLElement *element, std::map<std::string, sf::Image*> *images, std::map<std::string, sf::Sprite*> *sprites) {
	//Grab the first sprite element
	element = element->FirstChildElement();
	while ( element ) {
		sf::Sprite *tmp = new sf::Sprite;
		tinyxml2::XMLAttribute *Atr = (tinyxml2::XMLAttribute *)element->FirstAttribute();
		//Set the name attribute
		std::string name = Atr->Value();

		//Set the FlipX attribute
		Atr = (tinyxml2::XMLAttribute *)Atr->Next();
		std::string str("true");
		if ( str.compare( Atr->Value() ) == 0 )
			tmp->FlipX( true );
		else
			tmp->FlipX( false );

		//Set the FlipY attribute
		Atr = (tinyxml2::XMLAttribute *)Atr->Next();
		if ( str.compare( Atr->Value() ) == 0 )
			tmp->FlipY(true);
		else
			tmp->FlipY(false);

		//Set the Blend Mode attribute
		std::string alpha("Alpha"), add("Add"), multiply("Multiply");
		Atr = (tinyxml2::XMLAttribute *)Atr->Next();
		std::string setBlendModeValue = Atr->Value();
		if( alpha.compare( setBlendModeValue ) == 0 )
			tmp->SetBlendMode( sf::Blend::Alpha );
		else if( add.compare( setBlendModeValue ) == 0 )
			tmp->SetBlendMode( sf::Blend::Add );
		else if( multiply.compare( setBlendModeValue ) == 0 )
			tmp->SetBlendMode( sf::Blend::Multiply );
		else
			tmp->SetBlendMode(sf::Blend::None);

		//Set the CenterX attribute
		Atr = (tinyxml2::XMLAttribute *)Atr->Next();
		double CenterX, CenterY;
		Atr->QueryDoubleValue(&CenterX);

		//Set the CenterY attribute
		Atr = (tinyxml2::XMLAttribute *)Atr->Next();
		Atr->QueryDoubleValue( &CenterY );
		tmp->SetCenter( (float)CenterX, (float)CenterY );

		//Set the Set Color attribute
		Atr = (tinyxml2::XMLAttribute *)Atr->Next();
		std::string setColorValue = Atr->Value();
		std::string tag( "tag" ), value( "value" );
		//Set the Color attribute
		
		if ( tag.compare( setColorValue) == 0 ) {
			Atr = (tinyxml2::XMLAttribute *)Atr->Next();
			tmp->SetColor(getColorMap().find(Atr->Value())->second);
			Atr = (tinyxml2::XMLAttribute *)Atr->Next(); //skip pass R
			Atr = (tinyxml2::XMLAttribute *)Atr->Next(); //skip pass G
			Atr = (tinyxml2::XMLAttribute *)Atr->Next(); //skip pass B
			Atr = (tinyxml2::XMLAttribute *)Atr->Next(); //skip pass A
		}
		else if( value.compare(setColorValue) == 0 ) {
			//Set the RGBA attributes
			Atr = (tinyxml2::XMLAttribute *)Atr->Next();
			int r, g, b, a;
			Atr = (tinyxml2::XMLAttribute *)Atr->Next();
			Atr->QueryIntValue(&r);
			Atr = (tinyxml2::XMLAttribute *)Atr->Next();
			Atr->QueryIntValue(&g);
			Atr = (tinyxml2::XMLAttribute *)Atr->Next();
			Atr->QueryIntValue(&b);
			Atr = (tinyxml2::XMLAttribute *)Atr->Next();
			Atr->QueryIntValue(&a);
			tmp->SetColor(sf::Color::Color((sf::Uint8)r,(sf::Uint8)g,(sf::Uint8)b,(sf::Uint8)a));
		}
		else {
			Atr = (tinyxml2::XMLAttribute *)Atr->Next(); //get pass Color
			Atr = (tinyxml2::XMLAttribute *)Atr->Next(); //get pass R
			Atr = (tinyxml2::XMLAttribute *)Atr->Next(); //get pass G
			Atr = (tinyxml2::XMLAttribute *)Atr->Next(); //get pass B
			Atr = (tinyxml2::XMLAttribute *)Atr->Next(); //get pass A
		}
		//Set the Image attribute
		Atr = (tinyxml2::XMLAttribute *)Atr->Next();
		tmp->SetImage( *images->find(Atr->Value())->second );

		//Set the rotation, scale and the sub rect attributes
		double rot, scaleX, scaleY, L, T, R, B;
		Atr = (tinyxml2::XMLAttribute *)Atr->Next();
		Atr->QueryDoubleValue(&rot);
		Atr = (tinyxml2::XMLAttribute *)Atr->Next();
		Atr->QueryDoubleValue(&scaleX);
		Atr = (tinyxml2::XMLAttribute *)Atr->Next();
		Atr->QueryDoubleValue(&scaleY);
		Atr = (tinyxml2::XMLAttribute *)Atr->Next();
		Atr->QueryDoubleValue(&L);
		Atr = (tinyxml2::XMLAttribute *)Atr->Next();
		Atr->QueryDoubleValue(&T);
		Atr = (tinyxml2::XMLAttribute *)Atr->Next();
		Atr->QueryDoubleValue(&R);
		Atr = (tinyxml2::XMLAttribute *)Atr->Next();
		Atr->QueryDoubleValue(&B);

		tmp->SetRotation((float)rot);
		tmp->SetScaleX((float)scaleX);
		tmp->SetScaleY((float)scaleY);
		tmp->SetSubRect(sf::Rect<int>((int)L,(int)T,(int)R,(int)B));	

		//Set the X and Y destionation attributes
		double X, Y;
		Atr = (tinyxml2::XMLAttribute *)Atr->Next(); //get pass SetSubRectB
		Atr->QueryDoubleValue(&X);
		Atr = (tinyxml2::XMLAttribute *)Atr->Next(); //get pass SetX
		Atr->QueryDoubleValue(&Y);
		tmp->SetX((float)X);
		tmp->SetY((float)Y);

		//Add the sprite to the dictionary/map
		sprites->insert(std::pair<std::string, sf::Sprite*>( name, tmp ) );

		//Iterate to the next element
		element = element->NextSiblingElement();
	}
}


#endif