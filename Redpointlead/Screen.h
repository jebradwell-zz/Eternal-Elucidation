#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <string>

//#include "ScreenFunctions.h"
#include "AssetUtilities.h"

typedef struct position {
	position(float x, float y) : x(x), y(y){}
	float x;
	float y;
} Position;

typedef struct screen_Title {
	screen_Title(){}
	std::string *value;
	Position    *pos;
} Screen_Title;

typedef struct option {
	option(){}
	Position	 *pos;
	std::string	 *type;
	std::string	 *label;
	std::string	 *label_font;
	std::string	 *title;
	std::string	 *title_font;
	std::string	 *value;
	std::string  *onImage;
	std::string  *offImage;
} Option;

class ScreenInterface
{
public:
	virtual int Run (sf::RenderWindow &App) = 0;
private:
};

class ScreenManager {
public:
	ScreenManager();
	int LoadScreens(std::string XmlFileName);
	int Run(sf::RenderWindow &App);
private:
	int							  _GenerateUniqueID();
	int							  _screenIdPool;
	int							  _screenIdIndex;
	std::map<std::string,int>	  _screenIdMappings;
	std::vector<ScreenInterface*> _screensPtrs;
};

class Screen : public ScreenInterface {
public:
	Screen();
	virtual int Run( sf::RenderWindow &App );
private:
	Assets				*_assets;
	std::string			*_name;
	std::string			*_backgroundImage;
	sf::Color			*_backgroundColor;
	Screen_Title		*_title;
	std::vector<Option*> *_options;
	friend class ScreenManager;
};

#endif //SCREEN_INTERFACE_H