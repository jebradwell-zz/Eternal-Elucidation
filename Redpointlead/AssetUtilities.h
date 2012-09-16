#ifndef ASSETUTILTIES_H
#define ASSETUTILTIES_H

#include <string>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "tinyxml2/tinyxml2.h"

typedef struct assets {
	assets() : images(new (std::map<std::string, sf::Image*>)), sprites(new (std::map<std::string, sf::Sprite*>)),
			   sounds(new (std::map<std::string, sf::SoundBuffer>)), music(new (std::map<std::string, sf::Music*>)),
			   fonts(new (std::map<std::string, sf::Font>)), xmlFiles(new (std::map<std::string, tinyxml2::XMLDocument*>)){}
	std::map<std::string, sf::Image*> *images;
	std::map<std::string, sf::Sprite*> *sprites;
	std::map<std::string, sf::SoundBuffer> *sounds;
	std::map<std::string, sf::Music *> *music;
	std::map<std::string, sf::Font> *fonts;
	std::map<std::string, tinyxml2::XMLDocument*> *xmlFiles;
} Assets;

#endif //ASSETUTILTIES_H