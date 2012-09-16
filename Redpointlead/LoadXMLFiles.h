#ifndef LOAD_XML_FILES_H
#define LOAD_XML_FILES_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "tinyxml2/tinyxml2.h"

void LoadXMLFiles( tinyxml2::XMLElement *element, std::map<std::string, tinyxml2::XMLDocument*> *xmlFiles ) {
	//Grab first xmlFile element
	element = element->FirstChildElement();
	tinyxml2::XMLDocument tmp;
	while ( element ) {
		//Set name attribute
		tinyxml2::XMLAttribute *Atr = (tinyxml2::XMLAttribute *)element->FirstAttribute();
		std::string name = Atr->Value();

		//Load xmlFile from filepath attribute
		Atr = (tinyxml2::XMLAttribute *)Atr->Next();
		std::string filePath = Atr->Value();
		if (tmp.LoadFile(filePath.c_str())) {
			std::cout << "Could not load file : " << filePath << std::endl;
			continue;
		}

		//Add the xmlFile to the dictionary/map
		xmlFiles->insert(std::pair<std::string, tinyxml2::XMLDocument*>( name, &tmp ));

		//Iterate to the next element
		element = element->NextSiblingElement();
	}
}

#endif //LOAD_XML_FILES_H