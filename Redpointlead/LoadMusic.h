#ifndef LOAD_MUSIC_H
#define LOAD_MUSIC_H

#include <iostream>
#include <SFML/Audio.hpp>
#include "tinyxml2/tinyxml2.h"

//Loading music is different in that it loads a mapping of pointers to music objects
//******might want to load everything this way in the asset bundle.****************
void LoadMusic( tinyxml2::XMLElement *element, std::map<std::string, sf::Music *> *music ) {
	//Grab first song element
	element = element->FirstChildElement();
	sf::Music tmp;
	while ( element ) {
		//Set name attribute
		tinyxml2::XMLAttribute *Atr = (tinyxml2::XMLAttribute *)element->FirstAttribute();
		std::string name = Atr->Value();

		//Load music from filepath attribute
		Atr = (tinyxml2::XMLAttribute *)Atr->Next();
		if (!tmp.OpenFromFile(Atr->Value())) {
			std::cout << "Could not load file : " << Atr->Value() << std::endl;
			continue;
		}

		//Add the song to the dictionary/map
		music->insert(std::pair<std::string, sf::Music *>( name, &tmp ));

		//Iterate to the next element
		element = element->NextSiblingElement();
	}
}

#endif //LOAD_MUSIC_H