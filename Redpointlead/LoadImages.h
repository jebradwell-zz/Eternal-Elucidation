#ifndef LOAD_IMAGES_H
#define LOAD_IMAGES_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "tinyxml2/tinyxml2.h"

void LoadImages( tinyxml2::XMLElement *element, std::map<std::string, sf::Image*> *images ) {
	//Grab the first image element
	element = element->FirstChildElement();
	while( element ) {
		tinyxml2::XMLAttribute *Atr = (tinyxml2::XMLAttribute *)element->FirstAttribute();
		std::string fileName = Atr->Value();
		//get only the name of the file and store it into name
		//i.e. "player" from "\Images\player.png"
		std::string name( fileName.substr(fileName.find_last_of("/\\") + 1 ) );
		name = name.substr(0, name.find_last_of(".") );
		sf::Image *tmp = new sf::Image();
		//try to load the image from the file name.
		if (!tmp->LoadFromFile( fileName.c_str() ))
			std::cout << "Could Not open File: " << fileName.c_str() << std::endl;
		//test the type string to see if alpha values exist.
		std::string str("true");
		if( str.compare( element->Attribute("CreateMaskFromColor") ) == 0 ) {
			//if alpha values exist then set the image's mask to the values.
			tinyxml2::XMLAttribute *Atr = (tinyxml2::XMLAttribute *)element->FirstAttribute();
			Atr = (tinyxml2::XMLAttribute *)Atr->Next(); //get pass name attribute
			Atr = (tinyxml2::XMLAttribute *)Atr->Next(); //get pass type attribute
			int r, g, b, a;
			Atr = (tinyxml2::XMLAttribute *)Atr->QueryIntValue( &r );
			Atr = (tinyxml2::XMLAttribute *)Atr->Next(); //get pass R attribute
			Atr = (tinyxml2::XMLAttribute *)Atr->QueryIntValue( &g );
			Atr = (tinyxml2::XMLAttribute *)Atr->Next(); //get pass G attribute
			Atr = (tinyxml2::XMLAttribute *)Atr->QueryIntValue( &b );
			Atr = (tinyxml2::XMLAttribute *)Atr->Next(); //get pass B attribute
			Atr = (tinyxml2::XMLAttribute *)Atr->QueryIntValue( &a );
			tmp->CreateMaskFromColor( sf::Color::Color( (sf::Uint8)r, (sf::Uint8)g, (sf::Uint8)b, (sf::Uint8)a ) );
		}
		if( str.compare( element->Attribute("SetSmooth") ) == 0 )
			tmp->SetSmooth(true);
		else
			tmp->SetSmooth(false);
		images->insert(std::pair<std::string, sf::Image*>( name, tmp ) );
		element = element->NextSiblingElement();
	}
}

#endif //LOAD_IMAGES_H