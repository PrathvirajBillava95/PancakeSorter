#ifndef __BFS_CLASS_H__
#define __BFS_CLASS_H__

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

// BFSTree class:
// Functions and variables required to implement BFS search for pancake sorter problem
class BFSTree
{
	int GoalNode = -1;              //node which has the Goal State
	vector<string> NodeValue;       //array of strings to store the value of each nodes
	vector<int> cost;               //cost associated with the succesfor function, 1= '1 flip', 2= '2 flips' and so on
	vector<int> parent;
	
public:
	void PrintPath(int w, int cost);// Prints the shortest path to node w
	bool CheckIfVisited(string &str);// Check if the node is already been added to the tree
	void TraverseTree(string inputStr, string outputStr, int num); // Traverses the tree using BFS \
								       from the source state to goal state
};

#endif
