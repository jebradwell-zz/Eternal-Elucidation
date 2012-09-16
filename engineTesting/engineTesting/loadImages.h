#ifndef LOAD_IMAGES_H
#define LOAD_IMAGES_H

#include <SFML/Graphics.hpp>
#include "tinyxml.h"

void LoadImages( const std::string file, std::map<std::string, sf::Image> *images )
{
	TiXmlDocument XMLdoc(file.c_str());
	if (XMLdoc.LoadFile())
	{
		TiXmlElement *e_image;
		e_image = XMLdoc.FirstChildElement( "Level" );
		e_image = e_image->FirstChildElement("Images");
		e_image = e_image->FirstChildElement("Image");
		while( e_image )
		{
			std::string fileName = e_image->Attribute("name");
			//get only the name of the file and store it into imageName
			//i.e. "player" from "\Images\player.png"
			std::string imageName( fileName.substr(fileName.find_last_of("/\\") + 1 ) );
			imageName = imageName.substr(0, imageName.find_last_of(".") );
			sf::Image tmp;
			//try to load the image from the file name.
			if (!tmp.LoadFromFile( fileName.c_str() ))
				std::cout << "Could Not open File: " << fileName.c_str() << std::endl;
			//test the type string to see if alpha values exist.
			std::string str("true");
			if( str.compare( e_image->Attribute("CreateMaskFromColor") ) == 0 )
			{
				//if alpha values exist then set the image's mask to the values.
				TiXmlAttribute *Atr = e_image->FirstAttribute();
				Atr = Atr->Next(); //get pass name attribute
				Atr = Atr->Next(); //get pass type attribute
				int r, g, b, a;
				Atr->QueryIntValue( &r );
				Atr = Atr->Next(); //get pass R attribute
				Atr->QueryIntValue( &g );
				Atr = Atr->Next(); //get pass G attribute
				Atr->QueryIntValue( &b );
				Atr = Atr->Next(); //get pass B attribute
				Atr->QueryIntValue( &a );
				tmp.CreateMaskFromColor( sf::Color::Color( (sf::Uint8)r, (sf::Uint8)g, (sf::Uint8)b, (sf::Uint8)a ) );
			}
			if( str.compare( e_image->Attribute("SetSmooth") ) == 0 )
				tmp.SetSmooth(true);
			else
				tmp.SetSmooth(false);
			images->insert(std::pair<std::string, sf::Image>( imageName, tmp ) );
			e_image = e_image->NextSiblingElement("Image");
		}
	}
}

#endif