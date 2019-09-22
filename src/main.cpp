#include "BFSClass.h"
#include "AStarClass.h"
#include "helpers.h"

#define ASTAR_SUPPORT 1

int main()
{
	string str;
	int n;
	cout << "Please Enter the no. of pancakes: (n)\n";
	cin  >> n;
	
	cout << "Please Enter the order of pancakes in following format,\n";
	cout << "Pancake ID which is consistent with its size: (1-n) followed by b/w depending on the front side of pancake is burnt (b) or white (w) \n";
	cout << "e.g. 1b2b3b4w \n"; 
	cin >> str;

	cout << "Please select algorithm: \n 1.A* 2.BFS\n";
	int opt;
	cin >> opt;
	
	switch(opt){
		case 1:
			{	
#if ASTAR_SUPPORT
				AStarTree t;
				t.TraverseTree(str,  CreateOutputString(n), n);
#else
				cout<< "Currently Work in progress\n";
#endif
			}
			break;
		case 2:
			{
				BFSTree t(n);
				t.CreateTree(str, CreateOutputString(n), n);
			}
			break;
		default:
			cout<< "Invalid Option\n";
			break;

	}
}
