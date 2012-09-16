#include <iostream>
#include <time.h>

using namespace std;
// A-> AB
// B-> A
int main(int argc, char *argv[])
{
	int N = 14;
	int sampleTests = 20;
	while( cin >> N )
	{
		double sumTime = 0;
		for( int d = 0; d < sampleTests; d++ )
		{
			string tree;
			string tmp;
			clock_t start, end;
			start = clock();
			for( int i = 0; i < N; i++ )
			{
				//seed the tree with A
				if( tree.length() == 0) 
				{
					tree = "A";
				}
				unsigned int length = tree.length();
				for(int j = 0; j < length; j++ )
				{
					if( tree.at(j) == 'A' )
					{
						tmp += "AB";
					}
					if( tree.at(j) == 'B' )
					{
						tmp += "A";
					}
				}
				tree = tmp;
				tmp = "";
				//cout << tree.c_str() << endl;
			}
			double totaltime = ((double)clock()-(double)start) / (double) CLOCKS_PER_SEC;
			//cout << totaltime << endl;
			sumTime += totaltime;
		}
		//take the average time it takes to run N times
		cout << sumTime / sampleTests << endl;
	}
}