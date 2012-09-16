#ifndef LOAD_FONTS_H
#define LOAD_FONTS_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "tinyxml2/tinyxml2.h"

void LoadFonts( tinyxml2::XMLElement *element, std::map<std::string, sf::Font> *fonts ) {
	//Grab first font element
	element = element->FirstChildElement();
	sf::Font tmp;
	while ( element ) {
		//Set name attribute
		tinyxml2::XMLAttribute *Atr = (tinyxml2::XMLAttribute *)element->FirstAttribute();
		std::string name = Atr->Value();

		//Load font from filepath attribute
		Atr = (tinyxml2::XMLAttribute *)Atr->Next();
		if (!tmp.LoadFromFile(Atr->Value())) {
			std::cout << "Could not load file : " << Atr->Value() << std::endl;
			continue;
		}

		//Add the font to the dictionary/map
		fonts->insert(std::pair<std::string, sf::Font>( name, tmp ));

		//Iterate to the next element
		element = element->NextSiblingElement();
	}
}

#endif //LOAD_FONTS_H