#include "Screen.h"
#include "tinyxml2/tinyxml2.h"
#include "LoadAssets.h"

///For all loading xml .h files we need to implement unit tests
///to check if each element and attribute has been loaded correctly 
///and spit out an error message explaining if it did not load correctly
///and why it didn't.

///Also for the load XML file part, if the load failed then we should figure
///out why by running a DTD validation over the file and having the validation
///1) spit back out where the file is corrupted, 
///2) or if the file is empty, or if the
///3) file name doesn't exist.

Screen::Screen() {
}

int Screen::Run( sf::RenderWindow &App ) {
	std::cout << "Screen Unit Tests, Enter any number other than 0-3" << std::endl;
	std::cout << "Current Screen info : " << std::endl;
	std::cout << "Title: " << *_title->value << std::endl;
	std::cout << "Name: " << *_name << std::endl;
	
	std::cout << " Please Selected a new screen: " << std::endl;
	std::cout << "0 Start Game" << std::endl;
	std::cout << "1 Load Game" << std::endl;
	std::cout << "2 Options" << std::endl;
	std::cout << "3 Quit" << std::endl;
	
	//std::map<std::string, sf::Sprite>::iterator it = _assets->sprites->begin();
	//for(; it != this->_assets->sprites->end(); ++it){
	//	App.Draw(it->second);
	//}

	bool done = false;
	sf::Sprite test;
	test = *_assets->sprites->find(*_backgroundImage)->second;
	while (!done) {
		sf::Event Event;
		while (App.GetEvent(Event))
		{
			// Close window : exit
			if (Event.Type == sf::Event::Closed)
				App.Close();
		}
		if (App.GetInput().IsKeyDown(sf::Key::Space))  done = true;;
		App.Clear();
		App.Draw(test);
		App.Display();
	}
	int number;
	std::cin >> number;
	system("cls");



	if( number < 4 && number > -1)
		return number;
	return -1;
}

ScreenManager::ScreenManager() : _screenIdPool(0), _screenIdIndex(0) {
}

//Create a screen function head/cpp file which this function requests calls from	
int ScreenManager::LoadScreens(std::string XmlFileName) {	
	tinyxml2::XMLDocument doc;
	if (doc.LoadFile(XmlFileName.c_str())) {
		std::cout << "could not load xml file : " << XmlFileName << std::endl;
		return 1; //error could not load xml file
	}
	tinyxml2::XMLElement *element;
	tinyxml2::XMLElement *assets;
	element = doc.FirstChildElement();
	assets = element = element->FirstChildElement();

	Assets *menu_assets = LoadAssets(assets);
	element = element->NextSiblingElement();

	while (element) {
		Screen *screen = new Screen();
		screen->_assets = menu_assets;
		//name="start_screen" backgroundColor="FFFFFF" backgroundImage="start_screen_bg">
		tinyxml2::XMLAttribute *Atr = (tinyxml2::XMLAttribute *)element->FirstAttribute();
		screen->_name				     = new std::string(Atr->Value());
		Atr								 = (tinyxml2::XMLAttribute *)Atr->Next();
		//screen->_backgroundColor       = new std::string(Atr->Value());
		Atr								 = (tinyxml2::XMLAttribute *)Atr->Next();
		screen->_backgroundImage	     = new std::string(Atr->Value());
		tinyxml2::XMLElement *title		 = element->FirstChildElement();
		tinyxml2::XMLAttribute *titleAtr = (tinyxml2::XMLAttribute *)title->FirstAttribute();
		screen->_title					 = new Screen_Title();
		screen->_title->value			 = new std::string(titleAtr->Value());
		titleAtr						 = (tinyxml2::XMLAttribute *)titleAtr->Next();
		double x, y;
		titleAtr->QueryDoubleValue(&x);
		titleAtr						 = (tinyxml2::XMLAttribute *)titleAtr->Next();
		titleAtr->QueryDoubleValue(&y);
		screen->_title->pos				 = new Position((float)x,(float)y);
		tinyxml2::XMLElement *options	 = title->NextSiblingElement();
		options						     = options->FirstChildElement();
		screen->_options				 = new std::vector<Option*>();
		while (options) {
			//Option type values:
			//Start_Btn				- <option type="Start_Btn" title="Start Game" font="arial" value="start_game_function" x="350" y="450" onImg="Btn_on" offImg="Btn_off" />
			//Transition_Btn		- same as Start_Btn
			//Quit_Btn				- same as Start_Btn
			//Load_Game_Btn			- same as Start_Btn
			//Control_Config_Btn	- <option type="Control_Config_Btn" title="Mouse1" title_font="arial" label="Attack" label_font="arial" x="350" y="300" onImg="Btn_on" offImg="Btn_off" />
			//Save_Btn				- same as Start_Btn
			Option *new_option = new Option();
			tinyxml2::XMLAttribute *optionAtr = (tinyxml2::XMLAttribute *)options->FirstAttribute();
			new_option->type					  = new std::string(optionAtr->Value());
			optionAtr						  = (tinyxml2::XMLAttribute *)optionAtr->Next();
			new_option->title				  = new std::string(optionAtr->Value());
			optionAtr						  = (tinyxml2::XMLAttribute *)optionAtr->Next();
			new_option->title_font			  = new std::string(optionAtr->Value());
			optionAtr						  = (tinyxml2::XMLAttribute *)optionAtr->Next();
			std::string cntrConfigStr("Control_Config_Btn");
			std::string quitBtnStr("Quit_Btn");
			if (new_option->type->compare(cntrConfigStr) == 0)  {
				new_option->label			  = new std::string(optionAtr->Value());
				optionAtr					  = (tinyxml2::XMLAttribute *)optionAtr->Next();
				new_option->label_font		  = new std::string(optionAtr->Value());
				optionAtr						  = (tinyxml2::XMLAttribute *)optionAtr->Next();
			}
			else if (new_option->type->compare(quitBtnStr) == 0) {
				new_option->label			  = NULL;
				new_option->label_font		  = NULL;
				new_option->value			  = NULL;
			}
			else {
				new_option->label			  = NULL;
				new_option->label_font		  = NULL;
				new_option->value			  = new std::string(optionAtr->Value());
				optionAtr						  = (tinyxml2::XMLAttribute *)optionAtr->Next();
			}
			double opt_x, opt_y;
			optionAtr->QueryDoubleValue(&opt_x);
			optionAtr						  = (tinyxml2::XMLAttribute *)optionAtr->Next();
			optionAtr->QueryDoubleValue(&opt_y);
			new_option->pos					  = new Position((float)opt_x, (float)opt_y);
			optionAtr						  = (tinyxml2::XMLAttribute *)optionAtr->Next();
			new_option->onImage				  = new std::string(optionAtr->Value());
			optionAtr						  = (tinyxml2::XMLAttribute *)optionAtr->Next();
			new_option->offImage				  = new std::string(optionAtr->Value());
			screen->_options->push_back(new_option);
			options = options->NextSiblingElement();
		}

		_screenIdMappings.insert ( std::pair<std::string,int>(*screen->_name,_GenerateUniqueID()) );

		_screensPtrs.push_back(screen);
		element = element->NextSiblingElement();
	}
	return 0; //no error ran correctly
}

int ScreenManager::Run(sf::RenderWindow &App) {
	while (_screenIdIndex >= 0) {
		_screenIdIndex = _screensPtrs[_screenIdIndex]->Run(App);
	}
	return 0;
}

int ScreenManager::_GenerateUniqueID() {
	return _screenIdPool++;
}