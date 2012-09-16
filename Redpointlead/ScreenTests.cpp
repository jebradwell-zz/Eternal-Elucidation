#include "UnitTests.h"
#include <iostream>

#include "Screen.h"

bool screenTests() {
	sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Screen Test");
	ScreenManager ScreenMgr;
	std::string xmlfile("assets/xml/sample.xml");
	if(ScreenMgr.LoadScreens(xmlfile.c_str())) {
		std::cout << "could not load file : " << xmlfile << std::endl;
		return false; //there was an error
	}
	ScreenMgr.Run(App);
	return true;
}