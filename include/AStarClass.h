#ifndef __A_STAR_CLASS_H__
#define __A_STAR_CLASS_H__

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

// AStarTree class:
// Functions and variables required to implement A* search for pancake sorter problem
class AStarTree
{
	vector<string> NodeValue;	// stores the value of each state/ node
	vector<int> parent;		// stores parent of each state/ node
	vector<int> heuristics;		// stores the heuristics of each state/ node
	vector<int> cost;		// stores the cost of each state from its parent state
	vector<int> G;			// store the cost of each state from the source state
	vector<int> fn;			// store the (g+h) value of each state
	int GoalNode = -1;		// Node ID of goal state
public:
	int CalculateHeuristics(string str, int n);	// Calculates the Heuristics
	void SortMinFnValue(list<int> &q);		// Finds the minimum g+h value of all the elements in the queue
	void PrintShortestPath(int w, int c);		// Prints the shortest path to node w
	int HandleTieBreaker(int i, int j);		// Tie breaker mechanism
	bool CheckIfVisited(string &str);		// Check if the node with value str is already been added to the tree
	void TraverseTree(string inputStr, string outputStr, int num); // Traverses the tree using A* from the source state\
									to the goal state

};

#endif
