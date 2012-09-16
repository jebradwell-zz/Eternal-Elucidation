#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>

//#include "Abelia.h"
//#include "GResource.h"
//#include "GResourcePool.h"
//#include "GResourceManager.h"

std::vector<int> ResourceCounts;



//get this from some XML file listing all the resources instead in the real program.
enum resources
{
	Wood,
	Water,
	Fish,
	Paper,
	Salt,
	Pepper,
	Dirt,
	Orb,
	Stick,
	Rock,
	Stone,
	Pebble,
	Magent,
	Bread,
	Log,
	Pen,
	Necklace
};

std::string resourceStrs[17] = { "Wood",
	"Water",
	"Fish",
	"Paper",
	"Salt",
	"Pepper",
	"Dirt",
	"Orb",
	"Stick",
	"Rock",
	"Stone",
	"Pebble",
	"Magent",
	"Bread",
	"Log",
	"Pen",
	"Necklace"};

int randomNumber( int min, int max )
{
	int range = ( max - min ) + 1;
	return min + int( range * rand() / ( RAND_MAX + 1.0 ) );
}

//int randomExclude( int firstMin, int FirstMax, int SecondMin, int SecondMax, int index, int *num)
//{
//	if( index >= 0 )
//	{
//		if( randomNumber(0,1) == 0 )
//		{
//			num[index] = randomNumber( firstMin, FirstMax );
//			randomExclude( firstMin, num[index] - 1, num[index] + 1, FirstMax, index--, num );
//		}
//		else
//		{
//			num[index] = randomNumber( SecondMin, SecondMin );
//			randomExclude( SecondMin, num[index] - 1, num[index] + 1, SecondMax, index--, num );
//		}
//	}
//}


int main( int argc, char *argv[] )
{
	//GResourceManager ResManager;
	//ResManager.resourcesPools.push_back(
	//GResourcePool *plants;
	//plants->resources.push_back( new Abelia() );
	int resourceType_cap = 3;
	int resourceHarvestMin = 3;
	int resourceHarvestMax = 10;

	srand( (unsigned)time( NULL ) );
	//for( int i = 0; i < 10; i++ )
	//{
	//	std::cout << randomNumber(5, 100) << std::endl;
	//}


	//get number of resource types for this quest
	int NumOfQuestResTypes = randomNumber(1, resourceType_cap);
	std::cout << "Number Of resources for this quest: " << NumOfQuestResTypes << std::endl;

	//allocate the new unique resources for this quest to the questResource array
	std::vector<int> tmpResourceList;
	
	for(int i = 0; i < 17; i++)
	{
		tmpResourceList.push_back(i);
	}

	/*XXXXXXX
	We need a resource accumulator to find all the available resource around the area
	the town the NPC is in as well as the distance the resource lie to help give a level
	to the quest. That is in other words help give a difficulty ranking for the quest.
	*/

	/*XXXX
	We need to be able to pick which resource a NPC needs for his work... So if the NPC is a
	Black smith then he will need to obtain materials pertiate to black smithing... I.e. coal
	steal, iron, wood, stones, etc. These will be accumulated in the list of resources that 
	the player may potentially quest for.
	*/

	/*XXXXXX
	We will need to have rescieps available for what can be created with the given material lists
	as well as a current inventory of the NPC who is requesting the material.
	The reiceps will dictate the ratio of demands per material that the play will need to obtain.
	thus statements of 9 coal and 3 steal would be about the ratio a play would need to obtain
	to help the NPC stock his store to create swords. if swords took 3 coal and 1 steal to make.
	The store will have a list of items available which are created from resources and there will
	be a user define stock pile cap for items to make and backstock material resources per item
	that can be created.
	example list of rescipes:
	Qt: 10 - sword: 3 coal 1 steal 1 wood 
	Qt: 7 - dagger: 1 coal 1 steal 1 wood
	Qt: 3 - shield: 5 coal 3 steal 1 leather
	etc...

	backstock: 1 shield 3 daggers 4 swords worth of materials

	once the store is full the quests for resources are no longer available for people.
	*/

	/*XXXXXX
	for now we will just simply have quests which do not stock stores but just are relevant to
	the job the NCP currently fulfills in the game. So resouce quests will be unboundedly random
	that is they wont be tied to quote filling or ratio bounded by outside influences.
	We will generate a resouce quest with "resourceType_cap " and then for each item randomly
	select a quantiy to harvest between 3 - 10 or some other user define range.
	*/
	


	//XXXXXXXXXXXXXXXXXXXXXXXXXXX
	///////////////////////// ERROR!!!!!!!!!!!
	//need to use a hash tabel to recall the keys and randomly select the right resource without duplicates.
	int *questResource = new int[NumOfQuestResTypes];
	int *questResourceCount = new int[NumOfQuestResTypes];
	for( int i = 0; i < NumOfQuestResTypes; i++ )
	{
		questResource[i] =  tmpResourceList.at( randomNumber(0, tmpResourceList.size() - 1) );
		questResourceCount[i] = randomNumber( resourceHarvestMin, resourceHarvestMax );
		tmpResourceList.erase (tmpResourceList.begin() + questResource[i] );
	}

	std::cout << std::endl;
	for( int i = 0; i < NumOfQuestResTypes; i++ )
	{
		std::cout << resourceStrs[ questResource[i] ] << " " << questResourceCount[i]<< std::endl;
		std::cout << "Resource " << i + 1 << std::endl;
		std::cout << "Resource Number " << questResource[i] << std::endl;
		std::cout << "Resource Count " << questResourceCount[i] << std::endl;
		std::cout << std::endl;
	}

	


	return 0;
}