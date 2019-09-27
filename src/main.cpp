#include "BFSClass.h"
#include "AStarClass.h"
#include "helpers.h"
#include <regex>

int main()
{
	string str;
	int n=4;
	regex astar("(([1-4])([b|w])){4}(-a)$"), bfs("(([1-4])([b|w])){4}$");
	do {
	
		cout << "\nPlease Enter the order of pancakes in following format,\n";
		cout << "Pancake ID, consistent with its size: (1-4) followed by b or w\n" << 
			"depending on the front side of pancake is burnt (b) or white (w)\n" <<
			"End the string with -a for A* algorithm and nothing for BFS\n";
		cout << "e.g. 1b2b3b4w-a will use A* and  1b2b3b4w will use BFS  \n"; 
		cin >> str;

		if( regex_match(str, astar) ) {
			str = str.substr(0, str.size() - 2);	
			AStarTree t;
			t.TraverseTree(str, CreateOutputString(n), n);
			goto ask_option;
		} 
		
		if ( regex_match(str, bfs) ){
#if 0			
			BFSTree t(n);
			t.CreateTree(str, CreateOutputString(n), n);
#endif
			BFSTree t;
			t.TraverseTree(str, CreateOutputString(n), n);
			goto ask_option;
		}

		cout << "Invalid input, please provide the input in specified format.\n";
		
ask_option:		
		cout << "\nDo you want to continue: y | n?";
		char ch;
		cin >> ch;
		if(ch == 'n')
			exit(0);
	} while(1);

}
