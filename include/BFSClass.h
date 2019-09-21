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
	list<int> *adj;			//array of list to store the adjacent node
	int *parent;			//array of integers to store the parent node
	int GoalNode = -1;		//node which has the Goal State
	vector<string> NodeValue;	//array of strings to store the value of each nodes
	vector<int> cost;		//cost associated with the succesfor function, 1= '1 flip', 2= '2 flips' and so on
	size_t treeSize;		// size of the tree: no. of vertices in tree
	int gMaximumList = 1000;	// Maximum allocated size for *adj. 
					// The *adj is resized dynamically if the size exceeds gMaximumList
	
public:

	BFSTree(int n);			//constructor
	void AddEdge(int v, int w);	// Adds a node w to vertex v in the tree
	void BFS(int s);		// Traverses the tree using BFS
	void PrintPath(int w, int cost);// Prints the shortest path to node w
	void CreateTree(string inputStr, string outputStr, int num); // Creates the tree by expanding the source node to goal node
					// and finds the shortest path to goal node.
	bool CheckIfVisited(string &str);// Check if the node is already been added to the tree
};

#endif
