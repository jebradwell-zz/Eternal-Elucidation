#include "QuestGenerator.h"

int random( int smallest, int largest )
{
	rand();
	rand();
	return smallest + int((((largest - smallest) + 1) * rand()) / (RAND_MAX + 1.0));
}

std::map< std::string, int > quest_generator()
{
	std::string tmpString;
	std::vector<std::string> loadedQuestItems;
	std::vector<std::string> questItems;
	std::map<std::string, std::pair<int, int> > mappedQuestItems;
	
	std::map< std::string, int > quest;
	
	int tmpBegin, tmpEnd;
	while( std::cin >> tmpString ) 
	{
		std::cin >> tmpBegin;
		std::cin >> tmpEnd;
		mappedQuestItems.insert(std::pair< std::string, std::pair< int, int> >
			(tmpString, std::pair<int, int>(tmpBegin, tmpEnd)) );
		loadedQuestItems.push_back(tmpString);
	}

	srand ( (unsigned int)time(NULL) );
	//chose 1-10 different types of types for this quest.
	int numItemTypes = random( 1, 10 );
	int t = (int)loadedQuestItems.size();
	//t = numItemTypes;

	std::ofstream myfile;
	myfile.open("Assets/outNouns.txt");
	myfile << "Number of Items: " << t << std::endl;
	int tmpRandNum;
	for( std::map<std::string, std::pair<int, int> >::iterator mapIter; loadedQuestItems.size(); )
	{
		tmpRandNum = random( 0, (int)loadedQuestItems.size() - 1);
		mapIter = mappedQuestItems.find(loadedQuestItems[tmpRandNum]);
		quest.insert( std::pair<std::string, int>(loadedQuestItems[tmpRandNum] , 
			random(mapIter->second.first, mapIter->second.second) ) );
		loadedQuestItems.erase(loadedQuestItems.begin() + tmpRandNum);
	}
	for( std::map< std::string, int >::iterator questIter = quest.begin(); questIter != quest.end() ; questIter++ )
	{
		myfile << questIter->first << " " << questIter->second << std::endl;
	}
	myfile.close();
	return quest;
}