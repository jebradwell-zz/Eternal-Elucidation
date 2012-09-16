


//TEST CASE FOR SELECTING RANDOM QUEST ITEMS IN A LIST.
//THIS TEST RANDOMLY SELECTS AN ITEM FROM A NOUN LIST AND
//THEN REMOVES THAT FROM THE SELECTED LIST. THUS YOU END
//UP WITH CHOOSING AN ITEM ONLY ONCE.

	//srand ( time(NULL) );
	//int capacity = 10;
	//int numItems = 0;
	//std::string tmpString;
	//std::vector<std::string> loadedQuestItems;
	//std::vector<std::string> questItems;

	//std::ofstream myfile;
	//myfile.open("outNouns.txt");

	//while( std::cin >> tmpString ) 
	//{
	//	loadedQuestItems.push_back(tmpString);
	//	numItems++;
	//}
	////chose 1-4 different types of types for this quest.
	//int numItemTypes = random( 1, 4 );
	//int tmpRandNum;
	//int t = loadedQuestItems.size();

	//for( int i = 0; i < t; i++ )
	//{
	//	tmpRandNum = random( 0, loadedQuestItems.size() - 1);
	//	questItems.push_back( loadedQuestItems[tmpRandNum] );
	//	loadedQuestItems.erase(loadedQuestItems.begin() + tmpRandNum);
	//}
	//myfile << t << std::endl;
	//myfile << questItems.size() << std::endl;
	//for( int i = 0; i < t; i++ )
	//{
	//	myfile << questItems[i] << std::endl;
	//}

	//myfile.close();