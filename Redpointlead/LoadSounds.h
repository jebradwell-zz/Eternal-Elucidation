#ifndef LOAD_SOUNDS_H
#define LOAD_SOUNDS_H

#include <iostream>
#include <SFML/Audio.hpp>
#include "tinyxml2/tinyxml2.h"

void LoadSounds( tinyxml2::XMLElement *element, std::map<std::string, sf::SoundBuffer> *sounds ) {
	//Grab first sound element
	element = element->FirstChildElement();
	sf::SoundBuffer tmp;
	while ( element ) {
		//Set name attribute
		tinyxml2::XMLAttribute *Atr = (tinyxml2::XMLAttribute *)element->FirstAttribute();
		std::string name = Atr->Value();

		//Load sound from filepath attribute
		Atr = (tinyxml2::XMLAttribute *)Atr->Next();
		if (!tmp.LoadFromFile(Atr->Value())) {
			std::cout << "Could not load file : " << Atr->Value() << std::endl;
			continue;
		}

		//Add the sound to the dictionary/map
		sounds->insert(std::pair<std::string, sf::SoundBuffer>( name, tmp ));

		//Iterate to the next element
		element = element->NextSiblingElement();
	}
}

#endif //LOAD_SOUNDS_H