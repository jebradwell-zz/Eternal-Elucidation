#ifndef LOAD_ASSETS_H
#define LOAD_ASSETS_H

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "tinyxml2/tinyxml2.h"

#include "AssetUtilities.h"
#include "LoadImages.h"
#include "LoadSprites.h"
#include "LoadSounds.h"
#include "LoadMusic.h"
#include "LoadFonts.h"
#include "LoadXMLFiles.h"

Assets * LoadAssets( tinyxml2::XMLElement *element ) {
	//future development idea:
	//if we were to look at the count of images in the images element tag
	//then we can calculate how much memory we will need for all the images
	//which are to be loaded. then we could use this information to load the images
	//or any and all assets into a well organized block of memory which works
	//well with caching mechanizms. So that we don't get cache misses. 
	Assets *assets = new Assets();
	element = element->FirstChildElement();
	LoadImages(element, assets->images);
	
	element = element->NextSiblingElement();
	LoadSprites( element, assets->images, assets->sprites);
	
	element = element->NextSiblingElement();
	LoadSounds( element, assets->sounds );

	element = element->NextSiblingElement();
	LoadMusic( element, assets->music );

	element = element->NextSiblingElement();
	LoadFonts( element, assets->fonts );

	element = element->NextSiblingElement();
	LoadXMLFiles( element, assets->xmlFiles );

	return assets;
}

#endif //LOAD_SCREENS_H